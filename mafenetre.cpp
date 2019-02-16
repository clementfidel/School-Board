#include <QApplication>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLineEdit>
#include <QFormLayout>
#include <QString>
#include <QInputDialog>

#include "MaFenetre.h"


MaFenetre::MaFenetre() : QWidget()
{

    bouton1 = new QPushButton("Professeurs", this);
    bouton2 = new QPushButton("Elèves", this);
    bouton3 = new QPushButton("Administrateurs", this);
    boutonInscri = new QPushButton("Inscription", this);

    layout = new QVBoxLayout;
    layout->addWidget(bouton1);
    layout->addWidget(bouton2);
    layout->addWidget(bouton3);
    layout->addWidget(boutonInscri);
    setLayout(layout);
    QObject::connect(bouton1, SIGNAL(clicked()), this, SLOT(connexion()));
    QObject::connect(bouton2, SIGNAL(clicked()), this, SLOT(connexion()));
    QObject::connect(bouton3, SIGNAL(clicked()), this, SLOT(connexion()));
    QObject::connect(boutonInscri, SIGNAL(clicked()), this, SLOT(afficherInscri()));





}

void MaFenetre::afficherInscri()
{
    fenInscri = new inscription();

    fenInscri->show();
    hide();
}

void MaFenetre::connexion()
{
    bool okE = false;
    bool okP = false;
    email = new QLineEdit("",this);
    password = new QLineEdit("",this);
   QString email = QInputDialog::getText(this, "Connexion", "Email :", QLineEdit::Normal, QString(), &okE);
   QString password = QInputDialog::getText(this, "Connexion", "Password : ", QLineEdit::Password, QString(), &okP);

}
