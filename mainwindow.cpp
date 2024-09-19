#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ajoutetudiant.h"
#include "modifieretudiant.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connectToDb();

    list_students();

    setupTable();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connectToDb(){
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

void MainWindow::setupTable()
{
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void MainWindow::list_students(){

    connectToDb();

    QSqlQuery get_data(db);
    get_data.prepare("SELECT * FROM etudiant ORDER BY num ASC");
    if(get_data.exec()){
        int rowNb = 0;
        ui->tableWidget->setRowCount(get_data.size());
        while(get_data.next()){
            ui->tableWidget->setItem(rowNb, 0 , new QTableWidgetItem(QString(get_data.value("num").toString())));
            ui->tableWidget->setItem(rowNb, 1 , new QTableWidgetItem(QString(get_data.value("nom").toString())));
            ui->tableWidget->setItem(rowNb, 2 , new QTableWidgetItem(QString(get_data.value("prenoms").toString())));
            ui->tableWidget->setItem(rowNb, 3 , new QTableWidgetItem(QString(get_data.value("niveau").toString())));

            rowNb++;
        }
    }

    db.close();
}

void MainWindow::on_delete_btn_clicked()
{
    connectToDb();

    QSqlQuery check_data(db);
    check_data.prepare("SELECT COUNT(*) FROM etudiant WHERE num = :num");
    check_data.bindValue(":num", ui->num_input->text());
    check_data.exec();

    if(check_data.next() && check_data.value(0).toInt() > 0) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Confirmation", "Êtes-vous sûr de vouloir supprimer l'étudiant ?",
                                      QMessageBox::Yes|QMessageBox::No);

        if (reply == QMessageBox::Yes) {
            QSqlDatabase::database().transaction();
            QSqlQuery delete_data(db);
            qDebug() << "Deleting " << ui->num_input->text();
            delete_data.prepare("DELETE FROM etudiant WHERE num = :num");
            delete_data.bindValue(":num", ui->num_input->text());
            delete_data.exec();
            QSqlDatabase::database().commit();

            qDebug() << "Student deleted.";
        } else {
            qDebug() << "Deletion cancelled.";
        }
    } else {
        QMessageBox::warning(this, "Erreur", "Le numéro n'existe pas dans la base de données.");
    }

    db.close();
    list_students();
}


void MainWindow::on_add_btn_clicked()
{
    AjoutEtudiant ajoutEtudiantForm(this);
    ajoutEtudiantForm.exec();
}

void MainWindow::on_update_btn_clicked()
{
    connectToDb();

    QSqlQuery check_data(db);
    check_data.prepare("SELECT COUNT(*) FROM etudiant WHERE num = :num");
    check_data.bindValue(":num", ui->num_input->text());
    check_data.exec();

    if(check_data.next() && check_data.value(0).toInt() > 0) {
        QString studentNum = ui->num_input->text();

        ModifierEtudiant *modifierEtudiantForm = new ModifierEtudiant(studentNum, this);

        modifierEtudiantForm->exec();
    } else {
        QMessageBox::warning(this, "Erreur", "Le numéro n'existe pas dans la base de données.");
    }

    db.close();
}
