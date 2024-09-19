#include "modifieretudiant.h"
#include "ui_modifieretudiant.h"
#include <QDebug>

ModifierEtudiant::ModifierEtudiant(const QString &num, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModifierEtudiant),
    studentNum(num),
    mainWindow(dynamic_cast<MainWindow*>(parent))
{
    ui->setupUi(this);

    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setDatabaseName("gestion_note");
    db.setHostName("localhost");
    db.setPassword("");
    db.setUserName("root");

    if(db.open()) {
        qDebug() << "Connected";
    } else {
        qDebug() << "Not connected : " << db.lastError();
    }

    fillFields();
}

ModifierEtudiant::~ModifierEtudiant()
{
    delete ui;
}

void ModifierEtudiant::fillFields(){
    db.open();

    QSqlQuery get_data(db);
    get_data.prepare("SELECT * FROM etudiant WHERE num = :num");
    get_data.bindValue(":num", studentNum);
    if (get_data.exec()) {
        while (get_data.next()) {
            ui->nom_input->setText(QString(get_data.value("nom").toString()));
            ui->prenoms_input->setText(QString(get_data.value("prenoms").toString()));
            ui->num_input->setText(QString(get_data.value("num").toString()));
            ui->niveau_input->setCurrentText(QString(get_data.value("niveau").toString()));
        }
    }

    db.close();
}

void ModifierEtudiant::on_annuler_btn_clicked()
{
    this->close();
}

void ModifierEtudiant::on_ajouter_btn_clicked()
{
    db.open();

    QString newNum = ui->num_input->text();
    QSqlQuery check_query(db);
    check_query.prepare("SELECT COUNT(*) FROM etudiant WHERE num = :num");
    check_query.bindValue(":num", newNum);
    check_query.exec();

    check_query.next();
    int count = check_query.value(0).toInt();

    if (count > 0 && newNum != studentNum) {
        QMessageBox::warning(this, "Erreur", "Le numéro d'étudiant est déjà utilisé.");
        return;
    }


    QSqlDatabase::database().transaction();

    QSqlQuery update_data(db);
    qDebug() << "Updating " << ui->num_input->text();

    update_data.prepare("UPDATE etudiant SET nom = :nom, prenoms = :prenoms, niveau = :niveau, num = :num WHERE num = :numToModify");
    update_data.bindValue(":nom", ui->nom_input->text());
    update_data.bindValue(":prenoms", ui->prenoms_input->text());
    update_data.bindValue(":niveau", ui->niveau_input->currentText());
    update_data.bindValue(":num", ui->num_input->text());
    update_data.bindValue(":numToModify", studentNum);

    if (update_data.exec()) {
        QSqlDatabase::database().commit();
        qDebug() << "Student updated.";
        this->accept();

        if (mainWindow) {
            mainWindow->list_students();
        }
    } else {
        QSqlDatabase::database().rollback();  // Annuler la transaction en cas d'échec
        qDebug() << "Error updating student:" << update_data.lastError().text();
        QMessageBox::warning(this, "Erreur", "Erreur lors de la mise à jour de l'étudiant : " + update_data.lastError().text());
    }

    db.close();
}
