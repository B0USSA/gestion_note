#include "menu.h"
#include "ui_menu.h"
#include "mainwindow.h"
#include "matiere.h"

menu::menu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::menu)
{
    ui->setupUi(this);
}

menu::~menu()
{
    delete ui;
}

void menu::on_pushButton_clicked() {
    MainWindow *mainWin = new MainWindow();
    mainWin->setWindowModality(Qt::ApplicationModal);
    mainWin->show();
}

void menu::on_pushButton_4_clicked()
{
    Matiere *matiereWin = new Matiere();
    matiereWin->setWindowModality(Qt::ApplicationModal);
    matiereWin->show();
}
