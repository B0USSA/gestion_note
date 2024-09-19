#include "notematiere.h"
#include "ui_notematiere.h"
#include "modifiernote.h"

NoteMatiere::NoteMatiere(const QString &niv, const QString &mat, QWidget *parent) :
    QMainWindow(parent),
    studentNiv(niv),
    matiere(mat),
    ui(new Ui::NoteMatiere)
{
    ui->setupUi(this);

    list_students();

    setupTable();

    ui->matiereLabel->setText(matiere);
}

NoteMatiere::~NoteMatiere()
{
    delete ui;
}

void NoteMatiere::connectToDb(){
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

void NoteMatiere::setupTable()
{
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void NoteMatiere::list_students() {
    connectToDb();

    QSqlQuery get_data(db);
    get_data.prepare("SELECT * FROM etudiant WHERE niveau = :niv ORDER BY num ASC");
    get_data.bindValue(":niv", studentNiv);

    int rowNb = 0;

    if(get_data.exec()) {
        ui->tableWidget->setRowCount(get_data.size());
        while(get_data.next()) {
            QString _num = get_data.value("num").toString();
            QString _nom = get_data.value("nom").toString();
            QString _prenoms = get_data.value("prenoms").toString();

            QSqlQuery get_data_note(db);
            get_data_note.prepare("SELECT * FROM note WHERE num_etudiant = :num AND matiere = :mat");
            get_data_note.bindValue(":num", _num);
            get_data_note.bindValue(":mat", matiere);

            if(get_data_note.exec() && get_data_note.next()) {
                QString _note = get_data_note.value("note").toString();

                ui->tableWidget->setItem(rowNb, 0 , new QTableWidgetItem(_num));
                ui->tableWidget->setItem(rowNb, 1 , new QTableWidgetItem(_nom));
                ui->tableWidget->setItem(rowNb, 2 , new QTableWidgetItem(_prenoms));
                ui->tableWidget->setItem(rowNb, 3 , new QTableWidgetItem(_note == "-1" ? "~" : _note));
            } else {
                QSqlQuery insert_note(db);
                insert_note.prepare("INSERT INTO note (num_etudiant, matiere, note) VALUES (:num, :mat, :note)");
                insert_note.bindValue(":num", _num);
                insert_note.bindValue(":mat", matiere);
                insert_note.bindValue(":note", -1);
                if(insert_note.exec()) {
                    ui->tableWidget->setItem(rowNb, 0 , new QTableWidgetItem(_num));
                    ui->tableWidget->setItem(rowNb, 1 , new QTableWidgetItem(_nom));
                    ui->tableWidget->setItem(rowNb, 2 , new QTableWidgetItem(_prenoms));
                    ui->tableWidget->setItem(rowNb, 3 , new QTableWidgetItem("~"));
                } else {
                    qDebug() << "Erreur lors de l'insertion de la note: " << insert_note.lastError();
                }
            }

            rowNb++;
        }
    } else {
        qDebug() << "Erreur lors de la récupération des étudiants: " << get_data.lastError();
    }

    db.close();
}

void NoteMatiere::on_update_btn_clicked()
{
    connectToDb();

    QSqlQuery check_data(db);
    check_data.prepare("SELECT COUNT(*) FROM note WHERE num_etudiant = :num AND matiere = :mat");
    check_data.bindValue(":num", ui->num_input->text());
    check_data.bindValue(":mat", matiere);
    check_data.exec();

    if(check_data.next() && check_data.value(0).toInt() > 0) {
        QString studentNum = ui->num_input->text();

        QSqlQuery getNomPrenoms(db);
        getNomPrenoms.prepare("SELECT nom,prenoms FROM etudiant WHERE num = :num");
        getNomPrenoms.bindValue(":num", studentNum);
        getNomPrenoms.exec();
        getNomPrenoms.next();

        QString nomPrenoms = getNomPrenoms.value("nom").toString() + getNomPrenoms.value("prenoms").toString();

        ModifierNote *modifierNoteForm = new ModifierNote(studentNum, matiere, nomPrenoms, this);

        modifierNoteForm->exec();
    } else {
        QMessageBox::warning(this, "Erreur", "Ce numéro n'est pas listé dans le tableau.");
    }

    db.close();
}
