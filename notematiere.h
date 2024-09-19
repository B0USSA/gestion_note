#ifndef NOTEMATIERE_H
#define NOTEMATIERE_H

#include <QMainWindow>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>

namespace Ui {
class NoteMatiere;
}

class NoteMatiere : public QMainWindow
{
    Q_OBJECT

public:
    explicit NoteMatiere(const QString &niv, const QString &mat, QWidget *parent = 0);
    ~NoteMatiere();
    void list_students();

private slots:
    void on_update_btn_clicked();

private:
    Ui::NoteMatiere *ui;
    QSqlDatabase db;
    void connectToDb();
    QString studentNiv;
    QString matiere;
    void setupTable();
};

#endif // NOTEMATIERE_H
