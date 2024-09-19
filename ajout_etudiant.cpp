#include "ajout_etudiant.h"
#include "ui_ajout_etudiant.h"  // Assurez-vous de bien inclure ce fichier

AjoutEtudiant::AjoutEtudiant(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AjoutEtudiant)
{
    ui->setupUi(this);  // Lier l'interface utilisateur
}

AjoutEtudiant::~AjoutEtudiant()
{
    delete ui;
}
