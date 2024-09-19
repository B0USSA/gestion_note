#ifndef AJOUTETUDIANT_H
#define AJOUTETUDIANT_H

#include <QDialog>

namespace Ui {
class AjoutEtudiant;
}

class AjoutEtudiant : public QDialog
{
    Q_OBJECT

public:
    explicit AjoutEtudiant(QWidget *parent = nullptr);
    ~AjoutEtudiant();

private:
    Ui::AjoutEtudiant *ui;
};

#endif // AJOUTETUDIANT_H
