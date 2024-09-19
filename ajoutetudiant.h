#ifndef AJOUTETUDIANT_H
#define AJOUTETUDIANT_H

#include "mainwindow.h"

#include <QDialog>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>

namespace Ui {
class AjoutEtudiant;
}

class AjoutEtudiant : public QDialog
{
    Q_OBJECT

public:
    explicit AjoutEtudiant(QWidget *parent = nullptr);
    ~AjoutEtudiant();

private slots:
    void on_pushButton_2_clicked();

    void on_annuler_btn_clicked();

    void on_ajouoter_btn_clicked();

    void on_ajouter_btn_clicked();

private:
    Ui::AjoutEtudiant *ui;
    QSqlDatabase db;
    MainWindow *mainWindow;
};

#endif // AJOUTETUDIANT_H
