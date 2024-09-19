#include "modifiernote.h"
#include "ui_modifiernote.h"

ModifierNote::ModifierNote(const QString &num, const QString &mat, const QString &nom, QWidget *parent) :
    QDialog(parent),
    matiere(mat),
    numEtudiant(num),
    nomPrenoms(nom),
    noteMat(dynamic_cast<NoteMatiere*>(parent)),
    ui(new Ui::ModifierNote)
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

ModifierNote::~ModifierNote()
{
    delete ui;
}

void ModifierNote::fillFields()
{
    db.open();

    QSqlQuery get_data(db);
    get_data.prepare("SELECT * FROM note WHERE num_etudiant = :num AND matiere = :mat");
    get_data.bindValue(":num", numEtudiant);
    get_data.bindValue(":mat", matiere);
    if (get_data.exec()) {
        while (get_data.next()) {
            ui->label_num->setText(QString(get_data.value("num_etudiant").toString()));
            ui->label_matiere->setText(QString(get_data.value("matiere").toString()));
            ui->label_nom->setText(nomPrenoms);
            ui->note_input->setValue(double(get_data.value("note").toDouble()));
        }
    }

    db.close();
}

void ModifierNote::on_annuler_btn_clicked()
{
    this->close();
}

void ModifierNote::on_ajouter_btn_clicked()
{
    db.open();

    QSqlDatabase::database().transaction();

    QSqlQuery update_data(db);
    qDebug() << "Updating " << numEtudiant;

    update_data.prepare("UPDATE note SET note = :note WHERE num_etudiant = :num AND matiere = :mat");
    update_data.bindValue(":note", ui->note_input->value());
    update_data.bindValue(":mat", matiere);
    update_data.bindValue(":num", numEtudiant);

    if (update_data.exec()) {
        QSqlDatabase::database().commit();
        qDebug() << "Mark updated.";
        this->accept();

        if (noteMat) {
            noteMat->list_students();
        }
    } else {
        QSqlDatabase::database().rollback();  // Annuler la transaction en cas d'échec
        qDebug() << "Error updating student:" << update_data.lastError().text();
        QMessageBox::warning(this, "Erreur", "Erreur lors de la mise à jour de la note : " + update_data.lastError().text());
    }

    db.close();
}
