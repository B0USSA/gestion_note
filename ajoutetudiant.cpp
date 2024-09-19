#include "ajoutetudiant.h"
#include "ui_ajoutetudiant.h"

AjoutEtudiant::AjoutEtudiant(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AjoutEtudiant),
    mainWindow(dynamic_cast<MainWindow*>(parent))  // Convertir le parent en MainWindow*
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
}

AjoutEtudiant::~AjoutEtudiant()
{
    delete ui;
}

void AjoutEtudiant::on_annuler_btn_clicked()
{
    this->close();
}


void AjoutEtudiant::on_pushButton_2_clicked(){}
void AjoutEtudiant::on_ajouoter_btn_clicked(){}

void AjoutEtudiant::on_ajouter_btn_clicked()
{
    db.open();

    QString newNum = ui->num_input->text();
    QSqlQuery check_query(db);
    check_query.prepare("SELECT COUNT(*) FROM etudiant WHERE num = :num");
    check_query.bindValue(":num", newNum);
    check_query.exec();

    check_query.next();
    int count = check_query.value(0).toInt();

    if (count > 0) {
        QMessageBox::warning(this, "Erreur", "Le numéro d'étudiant est déjà utilisé.");
        return;
    }

    QSqlDatabase::database().transaction();

    QSqlQuery insert_data(db);
    qDebug() << "Inserting " << ui->num_input->text();
    insert_data.prepare("INSERT INTO etudiant(nom, prenoms, num, niveau) VALUES (:nom, :prenoms, :num, :niveau)");
    insert_data.bindValue(":nom", ui->nom_input->text());
    insert_data.bindValue(":prenoms", ui->prenoms_input->text());
    insert_data.bindValue(":num", ui->num_input->text());
    insert_data.bindValue(":niveau", ui->niveau_input->currentText());

    if (insert_data.exec()) {
        QSqlDatabase::database().commit();
        qDebug() << "Student added.";
        this->accept();

        if (mainWindow) {
            mainWindow->list_students();
        }
    } else {
        QSqlDatabase::database().rollback();
        qDebug() << "Error adding student:" << insert_data.lastError().text();
        QMessageBox::warning(this, "Erreur", "Erreur lors de l'ajout de l'étudiant : " + insert_data.lastError().text());
    }

    db.close();
}


