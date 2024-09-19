#ifndef MATIERE_H
#define MATIERE_H

#include <QMainWindow>

namespace Ui {
class Matiere;
}

class Matiere : public QMainWindow
{
    Q_OBJECT

public:
    explicit Matiere(QWidget *parent = 0);
    ~Matiere();

private slots:
    void on_niveau_input_3_currentIndexChanged(const QString &arg1);

    void on_niveau_input_2_currentIndexChanged(const QString &arg1);

    void on_niveau_input_currentIndexChanged(const QString &arg1);

    void on_pushButton_clicked();

private:
    Ui::Matiere *ui;
};

#endif // MATIERE_H
