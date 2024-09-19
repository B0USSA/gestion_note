#include "matiere.h"
#include "ui_matiere.h"
#include "notematiere.h"

Matiere::Matiere(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Matiere)
{
    ui->setupUi(this);

    QStringList matieresL1 = {"Base d'algèbre 1", "Base d'analyse 1", "Probabilité et Statistique", "Mathématiques discrètes",
                              "Algorithme et structure de données", "Langage C", "Initiation à la Programmation Orienté Objet",
                              "Développement de site web en HTML/CSS", "Technologie XML et DHTML", "Système d'exploitation Unix",
                              "Système d'exploitation Windows", "Théorie des réseaux", "Architecture des ordinateurs",
                              "Technologies des réseaux", "Electronique analogique", "Electronique numérique",
                              "Introduction aux systèmes embarqués", "Base de l'Informatique", "Introduction aux méthodes",
                              "Comptabilité générale", "Anglais 1", "Français 1", "Projet système et Base de données", "Soutenance"};
    ui->matiere_input->addItems(matieresL1);
}

Matiere::~Matiere()
{
    delete ui;
}


void Matiere::on_niveau_input_currentIndexChanged(const QString &arg1)
{
    ui->matiere_input->clear();

    if(arg1 == "L1") {
        QStringList matieresL1 = {"Base d'algèbre 1", "Base d'analyse 1", "Probabilité et Statistique", "Mathématiques discrètes",
                                  "Algorithme et structure de données", "Langage C", "Initiation à la Programmation Orienté Objet",
                                  "Développement de site web en HTML/CSS", "Technologie XML et DHTML", "Système d'exploitation Unix",
                                  "Système d'exploitation Windows", "Théorie des réseaux", "Architecture des ordinateurs",
                                  "Technologies des réseaux", "Electronique analogique", "Electronique numérique",
                                  "Introduction aux systèmes embarqués", "Base de l'Informatique", "Introduction aux méthodes",
                                  "Comptabilité générale", "Anglais 1", "Français 1", "Projet système et Base de données", "Soutenance"};
        ui->matiere_input->addItems(matieresL1);
    }
    else if(arg1 == "L2") {
        QStringList matieresL2 = {"Algèbre 2", "Analyse 2", "Probabilité et Statistique 2", "Programmation linéaire",
                                  "Langage Python", "Programmation objet en C++", "Algorithme et structure de données avancés",
                                  "Langage Java", "SGBD relationnelle", "MERISE 1", "MERISE 2", "Développement web en Javascript",
                                  "Développement d'applications en C#", "Développement web en PHP", "Administration réseaux Unix",
                                  "Base de l'administration des réseaux", "Commutation et Routage IP",
                                  "Base de la sécurité de Système d'Information", "Administration système Unix",
                                  "Administration système Microsoft", "Langage Assembleur", "Electronique analogique 2",
                                  "Programmation des microcontrôleurs", "Anglais", "Technique de communication",
                                  "Méthode de Travail Universitaire", "Stage en entreprise", "Soutenance"};
        ui->matiere_input->addItems(matieresL2);
    }
    else if(arg1 == "L3") {
        QStringList matieresL3 = {"Langage JAVA", "Technologie JAVA", "Technologie Python", "Technologies JSP et Servlet 1",
                                  "Développement Web API", "Technologie web mobile", "Développement d'application Mobile",
                                  "Génie Logiciel", "Administration SGBD ORACLE", "UML", "Patrons de conception",
                                  "Interaction Homme-Machine", "Téléphonie sur IP", "Architecture des réseaux mobiles",
                                  "Administration réseaux Unix avancée", "Administration réseaux Microsoft", "Base de la cybersécurité",
                                  "Architecture réseaux sécurisées", "Sécurité web, Mail et réseaux sociaux", "Assembleur appliqué",
                                  "Anglais", "Technique de communication", "Marketing", "Organisation et Management",
                                  "Entrepreneuriat", "Gestion de Projet", "Droit des affaires et du travail", "Stage",
                                  "Soutenance de rapports de stage"};
        ui->matiere_input->addItems(matieresL3);
    }
    else if(arg1 == "M1") {
        QStringList matieresM1 = {"Recherche opérationnelle", "Analyse des données", "Analyse numérique",
                                  "Réseau de Pétri et programmation multi-tâche", "Algorithmique avancé",
                                  "Technologie avancée en Java", "Technologie web avancée", "Développement d'application Mobile",
                                  "Intégration Web-SIG", "Ingénierie des besoins", "Génie logiciel", "Interaction Homme-Machine",
                                  "Intelligence artificielle", "Python pour Machine Learning",
                                  "Programmation parallèle et distribuée", "Programmation des réseaux",
                                  "Systèmes embarqués et temps réels", "Sécurité sous Unix",
                                  "Administration système et réseau avancée", "Technique de communication", "Anglais techniques",
                                  "Projets", "Soutenances", "Voyage d’études"};
        ui->matiere_input->addItems(matieresM1);
    }
    else if(arg1 == "M2") {
        QStringList matieresM2 = {"Réutilisation logiciel & frameworks", "Architecture Orienté Service",
                                  "BPM et Workflow", "Administration avancée de base de données",
                                  "Machine Learning et Deep Learning", "Développement mobile hybride",
                                  "Technologie de virtualisation et SDN", "Internet des Objets", "GRID et CLUSTER",
                                  "Sécurité avancée", "MPLS et QoS", "Téléphonie sur IP avancée",
                                  "Réseau mobile avancée", "Méthodes Agile", "Système d’Information Décisionnelle",
                                  "Aide à la décision et optimisation multi-critère", "Modélisation mathématique",
                                  "Système multi-agents", "Méthodologie d'élaboration de mémoires",
                                  "Méthodologie de recherche", "Encadrement des mémoires", "Soutenance de mémoires"};
        ui->matiere_input->addItems(matieresM2);
    }
}

void Matiere::on_pushButton_clicked()
{
    QString studentNiv = ui->niveau_input->currentText();
    QString matiere = ui->matiere_input->currentText();

    NoteMatiere *noteMatiereForm = new NoteMatiere(studentNiv, matiere);
    noteMatiereForm->setWindowModality(Qt::ApplicationModal);
    noteMatiereForm->show();
}
