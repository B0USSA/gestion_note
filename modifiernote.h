#ifndef MODIFIERNOTE_H
#define MODIFIERNOTE_H

#include "notematiere.h"

#include <QDialog>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>

namespace Ui {
class ModifierNote;
}

class ModifierNote : public QDialog
{
    Q_OBJECT

public:
    explicit ModifierNote(const QString &num, const QString &mat, const QString &nom, QWidget *parent = 0);
    ~ModifierNote();

private slots:
    void on_annuler_btn_clicked();

    void on_ajouter_btn_clicked();

private:
    Ui::ModifierNote *ui;
    QString numEtudiant;
    QString matiere;
    QString nomPrenoms;
    void fillFields();
    QSqlDatabase db;
    NoteMatiere *noteMat;
};

#endif // MODIFIERNOTE_H
