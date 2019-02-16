#include "fenadmin.h"
#include "ui_fenadmin.h"
#include "smtp.h"


//Constructeur dans lequel tous les boutons du compte administrateur y sont déclarer.
fenAdmin::fenAdmin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::fenAdmin)
{
    ui->setupUi(this);

    connect(ui->Deco, SIGNAL(clicked()), this, SLOT(retour()));
    connect(ui->menuAddEleve, SIGNAL(clicked()), this, SLOT(menuAddEleve()));
    connect(ui->menuAddProf, SIGNAL(clicked()), this, SLOT(menuAddProf()));
    connect(ui->menuAddAdmin, SIGNAL(clicked()), this, SLOT(menuAddAdmin()));
    connect(ui->menuAddCours, SIGNAL(clicked()), this, SLOT(menuAddCours()));
    connect(ui->menuBulltin, SIGNAL(clicked()), this, SLOT(menuBulltin()));
    connect(ui->menuDelCours, SIGNAL(clicked()), this, SLOT(menuDelCours()));
    connect(ui->menuDelUser, SIGNAL(clicked()), this, SLOT(menuDelUser()));
    connect(ui->menuModifClasse, SIGNAL(clicked()), this, SLOT(menuModifClasse()));
    connect(ui->menuModifCours, SIGNAL(clicked()), this, SLOT(menuModifCours()));
    connect(ui->menuModifMatiere, SIGNAL(clicked()), this, SLOT(menuModifMatiere()));
    connect(ui->menuModifSalle, SIGNAL(clicked()), this, SLOT(menuModifSalle()));
    connect(ui->menuModifUser, SIGNAL(clicked()), this, SLOT(menuModifUser()));
    connect(ui->menuOccupation, SIGNAL(clicked()), this, SLOT(menuOccupation()));

    connect(ui->valider_2, SIGNAL(clicked()), this, SLOT(addEleveSlot()));

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(addCoursSlot()));
    connect(ui->professeur, SIGNAL(currentIndexChanged(int)), this, SLOT(modifMatiereSlot()));


    connect(ui->valider_3, SIGNAL(clicked()), this, SLOT(validerAjProfSlot()));
    connect(ui->spinBox, SIGNAL(valueChanged(int)), this, SLOT(nbMatiereProfSlot()));
    connect(ui->valider, SIGNAL(clicked()), this, SLOT(validerAjAdminSlot()));
    connect(ui->ajouter, SIGNAL(clicked()), this, SLOT(ajouterClasseProfSlot()));
    connect(ui->checkBox,SIGNAL(stateChanged(int)),this, SLOT(hidePasswordAdmin()));
    connect(ui->checkBox_2,SIGNAL(stateChanged(int)),this, SLOT(hidePasswordEleve()));
    connect(ui->checkBox_3,SIGNAL(stateChanged(int)),this, SLOT(hidePasswordProf()));


    connect(ui->addClasse, SIGNAL(clicked()), this, SLOT(validerAjClasseSlot()));
    connect(ui->delClasse, SIGNAL(clicked()), this, SLOT(suppClasseSlot()));

    connect(ui->val, SIGNAL(clicked()), this, SLOT(choiceDateSlot()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(selectionCoursSlot()));
    connect(ui->pushButton_18, SIGNAL(clicked()), this, SLOT(modifCoursSlot()));

    connect(ui->addMatiere, SIGNAL(clicked()), this, SLOT(ajouterMatiereSlot()));
    connect(ui->delMatiere, SIGNAL(clicked()), this, SLOT(supprimerMatiereSlot()));

    connect(ui->addSalle, SIGNAL(clicked()), this, SLOT(validerAjSalleSlot()));
    connect(ui->delSalle, SIGNAL(clicked()), this, SLOT(suppSalleSlot()));

    connect(ui->validerSearchModifUser, SIGNAL(clicked()), this, SLOT(findUserSlot()));
    connect(ui->validerModifUser, SIGNAL(clicked()), this, SLOT(modifUserSlot()));
    connect(ui->ajouter_2, SIGNAL(clicked()), this, SLOT(ajouterClasseProfModifSlot()));
    connect(ui->vider, SIGNAL(clicked()), this, SLOT(viderClasseProfModifSlot()));

    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(choiceDateSlot_2()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(suppCoursSlot()));

    connect(ui->validerSuppUser, SIGNAL(clicked()), this, SLOT(suppUserSlot()));

    connect(ui->valSalle, SIGNAL(clicked()), this, SLOT(dispoSalleSlot()));
    connect(ui->valClasse, SIGNAL(clicked()), this, SLOT(dispoClasseSlot()));
    connect(ui->valProf, SIGNAL(clicked()), this, SLOT(dispoProfSlot()));

    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(modifClasseSlot()));
    connect(ui->comboBox_2, SIGNAL(currentIndexChanged(int)), this, SLOT(modifEleveSlot()));
    connect(ui->savePDF, SIGNAL(clicked()), this, SLOT(saveSlot()));
    ui->stackedWidget->setCurrentIndex(13);
}


//Destructeur
fenAdmin::~fenAdmin()
{
    delete ui;
}

//Fonction qui s'éxécute quand on clique sur le bouton déconnexion, qui permet de retourner sur la ffenêtre déconnexion.
void fenAdmin::retour()
{
    FenConnexion *put = new FenConnexion(this);
    put->setFixedSize(800,600);
    put->show();
    this->hide();

}

//Permet d'afficher la page pour ajouter un élève.
void fenAdmin::menuAddEleve()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->classe_4->clear();
    fenAjUserInit();

}

//Permet d'afficher la page pour ajouter un administrateur.
void fenAdmin::menuAddAdmin()
{
    ui->stackedWidget->setCurrentIndex(0);
    fenAjUserInit();
}


//Permet d'afficher la page pour ajouter un professeur.
void fenAdmin::menuAddProf()
{
    ui->stackedWidget->setCurrentIndex(2);
    ui->classeProf->clear();
    ui->textBrowser_35->clear();
    fenAjUserInit();
}


//Permet d'afficher la page pour ajouter un cours.
void fenAdmin::menuAddCours()
{
    ui->stackedWidget->setCurrentIndex(4);
    ui->professeur->clear();
    ui->matiere->clear();
    ui->salle->clear();
    ui->classe->clear();
    fenAjCoursInit();
}

//Permet d'afficher la page pour crée un bulletin d'un élève.
void fenAdmin::menuBulltin()
{
    ui->stackedWidget->setCurrentIndex(11);
    ui->comboBox->clear();
    ui->comboBox_2->clear();
    bulletinInit();
}


//Permet d'afficher la page pour supprimer un cours.
void fenAdmin::menuDelCours()
{
    ui->stackedWidget->setCurrentIndex(5);
    ui->classe_2->clear();
    ui->matiere_2->clear();
    ui->salle_2->clear();
    ui->professeur_2->clear();
    ui->heure_debut_2->clear();
    ui->heure_fin_2->clear();

    fenSuppCoursInit();
}


//Permet d'afficher la page pour supprimer un utilisateur (élève,professeur et administrateur).
void fenAdmin::menuDelUser()
{
    ui->stackedWidget->setCurrentIndex(3);


}

//Permet d'afficher la page pour modifier un classe.
void fenAdmin::menuModifClasse()
{
    ui->stackedWidget->setCurrentIndex(7);
}

//Permet d'afficher la page pour modifier un cours.
void fenAdmin::menuModifCours()
{
    ui->stackedWidget->setCurrentIndex(6);
    ui->classe_3->clear();
    ui->matiere_3->clear();
    ui->salle_3->clear();
    ui->professeur_3->clear();
    ui->heure_debut_3->clear();
    ui->heure_fin_3->clear();

    fenModifCoursInit();
}

//Permet d'afficher la page pour modifier une matière.
void fenAdmin::menuModifMatiere()
{
    ui->stackedWidget->setCurrentIndex(8);
}

//Permet d'afficher la page pour modifier un salle.
void fenAdmin::menuModifSalle()
{
    ui->stackedWidget->setCurrentIndex(9);
    fenModifSalleInit();
}


//Permet d'afficher la page pour modifier un utilisateur.
void fenAdmin::menuModifUser()
{
    ui->stackedWidget->setCurrentIndex(10);
    fenModifUserInit();
}

//Permet d'afficher la page pour regarder les occupations des salles, classes et professeurs.
void fenAdmin::menuOccupation()
{
    ui->stackedWidget->setCurrentIndex(12);
    ui->classeSelec->clear();
    ui->profSelec->clear();
    occupationInit();
}

                    //Fonctions de fenAjCours.cpp

//Permet d'éxécuter la fonction quand l'administrateur clique sur le bouton pour inséré un cours dans la base de donnée.
void fenAdmin::addCoursSlot()
{
    validerAjCours();
}

//Permet d'éxécuter la fonction quand l'administrateur change le nom du professeur dans la liste déroulante lors de l'ajout d'un cours.
void fenAdmin::modifMatiereSlot()
{
   modifMatiere();
}

                    //Fonctions de fenAjUser.cpp

//Permet d'éxécuter la fonction quand l'administrateur clique sur le bouton pour inséré un élève dans la base de donnée.
void fenAdmin::addEleveSlot()
{
   validerAjEleve();
}

//Permet d'éxécuter la fonction quand l'administrateur clique sur le bouton pour inséré un administrateur dans la base de donnée.
void fenAdmin::validerAjAdminSlot()
{
   validerAjAdmin();
}
//Permet d'éxécuter la fonction quand l'administrateur clique sur le bouton pour inséré un professeur dans la base de donnée.
void fenAdmin::validerAjProfSlot()
{
    validerAjProf();
}

//Permet d'éxécuter la fonction quand l'administrateur clique sur le bouton pour ajouté des classes a un professeur lors de l'ajout d'un professeur dans la base de donnée.
void fenAdmin::ajouterClasseProfSlot()
{
   ajouterClasseProf();
}

//Permet d'éxécuter la fonction quand l'administrateur clique sur le bouton pour ajouter des matière a un professeur lors de l'ajout d'un professeur dans la base de donnée.
void fenAdmin::nbMatiereProfSlot()
{
   nbMatiereProf();
}
                    //Fonctions de fenModifClasse.cpp

//Permet d'éxécuter la fonction quand l'administrateur clique sur le bouton pour inséré une classe dans la base de donnée.
void fenAdmin::validerAjClasseSlot()
{
    validerAjClasse();
}

//Permet d'éxécuter la fonction quand l'administrateur clique sur le bouton pour supprimer une classe dans la base de donnée.
void fenAdmin::suppClasseSlot()
{
    suppClasse();
}

                    //Fonctions de fenModifCours.cpp

//Permet d'éxécuter la fonction quand l'administrateur clique sur le bouton pour choisir la date d'un cours a modifié.
void fenAdmin::choiceDateSlot()
{
    choiceDate();
}

//Permet d'éxécuter la fonction quand l'administrateur clique sur le bouton pour sélectionner le cours a modifié.
void fenAdmin::selectionCoursSlot()
{
    selectionCours();
}
//Permet d'éxécuter la fonction quand l'administrateur clique sur le bouton pour modifié un cours dans la base de donnée.
void fenAdmin::modifCoursSlot()
{
    modifCours();
}

                    //Fonctions de fenModifMatiere.cpp

//Permet d'éxécuter la fonction quand l'administrateur clique sur le bouton pour ajouter une matière dans la base de donnée.
void fenAdmin::ajouterMatiereSlot()
{
    ajouterMatiere();
}
//Permet d'éxécuter la fonction quand l'administrateur clique sur le bouton pour supprimer une matière dans la base de donnée.
void fenAdmin::supprimerMatiereSlot()
{
    supprimerMatiere();
}

                    //Fonctions de fenModifSalle.cpp

//Permet d'éxécuter la fonction quand l'administrateur clique sur le bouton pour ajouté une salle dans la base de donnée.
void fenAdmin::validerAjSalleSlot()
{
    validerAjSalle();
}
//Permet d'éxécuter la fonction quand l'administrateur clique sur le bouton pour supprimer un salle dans la base de donnée.
void fenAdmin::suppSalleSlot()
{
    suppSalle();
}
                    //Fonctions de fenModifUser.cpp

//Permet d'éxécuter la fonction quand l'administrateur clique sur le bouton pour trouvé un utilisateur afin de modifié/regarder ces informations.
void fenAdmin::findUserSlot()
{
    findUser();
}
//Permet d'éxécuter la fonction quand l'administrateur clique sur le bouton pour sélectionner modifiés les informations d'un utilisateur.
void fenAdmin::modifUserSlot()
{
    modifUser();
}

void fenAdmin::ajouterClasseProfModifSlot()
{
    ajouterClasseModifProf();
}

void fenAdmin::viderClasseProfModifSlot()
{
    viderClasseModifProf();
}

                    //Fonctions de fenSuppCours.cpp

//Permet d'éxécuter la fonction quand l'administrateur clique sur le bouton pour choisir la date d'un cours afin de le supprimer.
void fenAdmin::choiceDateSlot_2()
{
    choiceDateSupp();
}
//Permet d'éxécuter la fonction quand l'administrateur clique sur le bouton pour supprimer un cours.
void fenAdmin::suppCoursSlot()
{
    suppCours();
}


//Permet d'éxécuter la fonction quand l'administrateur clique sur le bouton pour supprimer un utilisateur.
void fenAdmin::suppUserSlot()
{
    suppUser();
}

                     //Fonctions de occupation.cpp

//Permet d'éxécuter la fonction quand l'administrateur clique sur le bouton pour voir l'occupation des salles.
void fenAdmin::dispoSalleSlot()
{
    dispoSalle();
}
//Permet d'éxécuter la fonction quand l'administrateur clique sur le bouton pour voir l'occupation des classes.
void fenAdmin::dispoClasseSlot()
{
    dispoClasse();
}
//Permet d'éxécuter la fonction quand l'administrateur clique sur le bouton pour voir l'occupation des professeurs.
void fenAdmin::dispoProfSlot()
{
    dispoProf();
}


                    //Fonctions de bulletin.cpp

//Permet d'éxécuter la fonction quand l'administrateur choisi une classe dans la liste déroulante.
void fenAdmin::modifClasseSlot()
{
    modifClasse();
}
//Permet d'éxécuter la fonction quand l'administrateur choisi une eleve dans la liste déroulante.
void fenAdmin::modifEleveSlot()
{
    modifEleve();
}
//Permet d'éxécuter la fonction quand l'administrateur clique sur le boutton pour sauvegarder le bulletin en PDF.
void fenAdmin::saveSlot()
{
    save();
}







