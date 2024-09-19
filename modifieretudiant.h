#ifndef MODIFIERETUDIANT_H
#define MODIFIERETUDIANT_H

#include "mainwindow.h"

#include <QDialog>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>

namespace Ui {
class ModifierEtudiant;
}

class ModifierEtudiant : public QDialog
{
    Q_OBJECT

public:
    explicit ModifierEtudiant(const QString &num, QWidget *parent = nullptr);
    ~ModifierEtudiant();

    void fillFields();

private slots:

    void on_annuler_btn_clicked();

    void on_ajouter_btn_clicked();

private:
    Ui::ModifierEtudiant *ui;
    QSqlDatabase db;
    MainWindow *mainWindow;
    QString studentNum;
};

#endif // ModifierEtudiant_H
