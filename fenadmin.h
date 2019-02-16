#ifndef FENADMIN_H
#define FENADMIN_H

#include <QTextDocument>
#include "QMainWindow"
#include "fenconnexion.h"




namespace Ui {
class fenAdmin;

}

class fenAdmin : public QMainWindow
{
    Q_OBJECT


public:
    explicit fenAdmin(QWidget *parent = 0);
    ~fenAdmin();
    void fenAjUserInit();
    void bulletinInit();
    void fenAjCoursInit();
    void fenModifCoursInit();
    void fenModifSalleInit();
    void fenModifUserInit();
    void fenSuppCoursInit();
    void occupationInit();

    void validerAjEleve();
    void validerAjProf();
    void nbMatiereProf();
    void validerAjAdmin();

    void ajouterClasseProf();

    void validerAjCours();
    void modifMatiere();

    void validerAjClasse();
    void suppClasse();

    void choiceDate();
    void modifCours();
    void selectionCours();

    void ajouterMatiere();
    void supprimerMatiere();

    void validerAjSalle();
    void suppSalle();

    void modifUser();
    void findUser();
    void ajouterClasseModifProf();
    void viderClasseModifProf();

    void choiceDateSupp();
    void suppCours();

    void suppUser();

    void dispoSalle();
    void dispoClasse();
    void dispoProf();

    void save();
    void modifEleve();
    void modifClasse();
    void pdf(int m_id);
    QString prof();
    QString comm();
    QString currDate();
    QString matiere();

    QString note();
    float moyenne();
    void ids();



public slots:
    void mailSent(QString);
    void menuAddEleve();
    void menuAddProf();
    void menuAddAdmin();
    void menuAddCours();
    void menuBulltin();
    void menuDelCours();
    void menuDelUser();
    void menuModifClasse();
    void menuModifCours();
    void menuModifMatiere();
    void menuModifSalle();
    void menuModifUser();
    void menuOccupation();

    void addCoursSlot();
    void addEleveSlot();
    void modifMatiereSlot();
    void validerAjProfSlot();
    void nbMatiereProfSlot();
    void validerAjAdminSlot();
    void ajouterClasseProfSlot();
    void hidePasswordAdmin();
    void hidePasswordEleve();
    void hidePasswordProf();

    void validerAjClasseSlot();
    void suppClasseSlot();

    void choiceDateSlot();
    void selectionCoursSlot();
    void modifCoursSlot();

    void ajouterMatiereSlot();
    void supprimerMatiereSlot();

    void validerAjSalleSlot();
    void suppSalleSlot();

    void findUserSlot();
    void modifUserSlot();
    void ajouterClasseProfModifSlot();
    void viderClasseProfModifSlot();

    void choiceDateSlot_2();
    void suppCoursSlot();

    void suppUserSlot();

    void dispoSalleSlot();
    void dispoClasseSlot();
    void dispoProfSlot();

    void modifClasseSlot();
    void modifEleveSlot();
    void saveSlot();

    void retour();









private:
    Ui::fenAdmin *ui;

    int idCours=0;
    int validateur=0;

    int a=0;
    int id_prof=0;
    int id_eleve=0;
    int id_admin=0;
    QList<int> classeProf;
    QString noteListString;
    QString nom_matiere;
    int m_id;
    int id_note;
    int id_matiere;
    QString html;
    QTextDocument document;
    int id_prof_bull;
    QList <int> nums;
    QString  commListString;
    float moy;





};


#endif // FENADMIN_H
