#include "ui_fenadmin.h"
#include "fenadmin.h"


//Permet de cache les informations inutile lorsqu'on on arrive sur la page.
void fenAdmin::fenSuppCoursInit()
{


    QDate date = QDate::currentDate();
    ui->dateCours_2->setDate(date);
    ui->classe_2->hide();
    ui->professeur_2->hide();
    ui->heure_debut_2->hide();
    ui->heure_fin_2->hide();
    ui->salle_2->hide();
    ui->matiere_2->hide();
    ui->lineEdit_23->hide();
    ui->lineEdit_24->hide();
    ui->lineEdit_25->hide();
    ui->lineEdit_26->hide();
    ui->lineEdit_27->hide();
    ui->lineEdit_28->hide();
    ui->pushButton_2->hide();

}


//Permet de remplir les listes déroulantes décrivant les information des cours en fonction de la date sélectionner.
void fenAdmin::choiceDateSupp()
{



    qDebug() <<"hello";
    QSqlQuery query2;
     QSqlQuery query3;

    query2.prepare("SELECT DISTINCT fk_id_classe FROM cours WHERE date_cours = :date_cours");
    query2.bindValue(":date_cours", ui->dateCours_2->date());
    ui->classe_2->clear();
    query2.exec();

        while(query2.next())
        {

            query3.prepare("SELECT nom_classe FROM classe WHERE id_classe = :id_classe");
            query3.bindValue(":id_classe",query2.value(0).toInt());
            query3.exec();
            while(query3.next())
            {
                ui->classe_2->addItem(query3.value(0).toString());
            }
        }
        if(query2.first())
        {
            ui->classe_2->show();
            ui->pushButton_2->show();
            ui->professeur_2->show();
            ui->heure_debut_2->show();
            ui->heure_fin_2->show();
            ui->salle_2->show();
            ui->matiere_2->show();

            ui->lineEdit_23->show();
            ui->lineEdit_24->show();
            ui->lineEdit_25->show();
            ui->lineEdit_26->show();
            ui->lineEdit_27->show();
            ui->lineEdit_28->show();


        query2.prepare("SELECT DISTINCT heure_debut FROM cours WHERE date_cours = :date_cours");
        query2.bindValue(":date_cours", ui->dateCours_2->date());
        query2.exec();
        ui->heure_debut_2->clear();
        while(query2.next())
        {

            ui->heure_debut_2->addItem(query2.value(0).toString());
        }



        query2.prepare("SELECT DISTINCT heure_fin FROM cours WHERE date_cours = :date_cours");
        query2.bindValue(":date_cours", ui->dateCours_2->date());
        query2.exec();
        ui->heure_fin_2->clear();
        while(query2.next())
        {
            ui->heure_fin_2->addItem(query2.value(0).toString());
        }



        query2.prepare("SELECT DISTINCT fk_id_professeur FROM cours WHERE date_cours = :date_cours");
        query2.bindValue(":date_cours", ui->dateCours_2->date());
        query2.exec();
        ui->professeur_2->clear();
        while(query2.next())
        {
            query3.prepare("SELECT nom FROM professeur WHERE id_professeur =:id_professeur");
            query3.bindValue(":id_professeur",query2.value(0).toInt());
            query3.exec();
            while(query3.next())
            {
                ui->professeur_2->addItem(query3.value(0).toString());
            }
        }





        query2.prepare("SELECT DISTINCT fk_id_matiere FROM cours WHERE date_cours = :date_cours");
        query2.bindValue(":date_cours", ui->dateCours_2->date());
        query2.exec();
        ui->matiere->clear();
        while(query2.next())
        {
            query3.prepare("SELECT nom_matiere FROM matiere WHERE id_matiere = :id_matiere");
            query3.bindValue(":id_matiere",query2.value(0).toInt());
            query3.exec();

            while(query3.next())
            {
                ui->matiere_2->addItem(query3.value(0).toString());

            }
        }



        query2.prepare("SELECT DISTINCT fk_id_salle FROM cours WHERE date_cours = :date_cours");
        query2.bindValue(":date_cours", ui->dateCours_2->date());
        query2.exec();
        ui->salle->clear();
        while(query2.next())
        {
            query3.prepare("SELECT nom_salle FROM salle WHERE id_salle = :id_salle");
            query3.bindValue(":id_salle",query2.value(0).toInt());
            query3.exec();
            while(query3.next())
            {
                ui->salle_2->addItem(query3.value(0).toString());
            }
        }






    }
    else
    {
        QMessageBox::warning(this,"Erreur","Il n'y a pas de cours ce jour ci");

    }



}
//Permet de supprimer le cours dans la base de donnée en fonction des informations affichés dans les listes déroulantes.
void fenAdmin::suppCours()
{


    int fkProf=0;
    int fkMatiere=0;
    int fkSalle=0;
    int fkClasse=0;
    QSqlQuery query2;

    query2.prepare("SELECT id_professeur FROM professeur WHERE nom = :nom");
    query2.bindValue(":nom",ui->professeur_2->currentText());
    query2.exec();
    query2.next();
    fkProf=query2.value(0).toInt();

    query2.prepare("SELECT id_matiere FROM matiere WHERE nom_matiere = :nom_matiere");
    query2.bindValue(":nom_matiere",ui->matiere_2->currentText());
    query2.exec();
    query2.next();
    fkMatiere=query2.value(0).toInt();

    query2.prepare("SELECT id_salle FROM salle WHERE nom_salle = :nom_salle");
    query2.bindValue(":nom_salle",ui->salle_2->currentText());
    query2.exec();
    query2.next();
    fkSalle=query2.value(0).toInt();

    query2.prepare("SELECT id_classe FROM classe WHERE nom_classe = :nom_classe");
    query2.bindValue(":nom_classe",ui->classe_2->currentText());
    query2.exec();
    query2.next();
    fkClasse=query2.value(0).toInt();


    query2.prepare("SELECT id_cours FROM cours WHERE date_cours = :date_cours AND fk_id_professeur = :fk_id_professeur AND fk_id_matiere = :fk_id_matiere AND fk_id_salle = :fk_id_salle AND fk_id_classe = :fk_id_classe AND heure_debut = :heure_debut AND heure_fin = :heure_fin");
    query2.bindValue(":date_cours",ui->dateCours_2->date());
    query2.bindValue(":fk_id_professeur",fkProf);
    query2.bindValue(":fk_id_matiere",fkMatiere);
    query2.bindValue(":fk_id_salle",fkSalle);
    query2.bindValue(":fk_id_classe",fkClasse);
    query2.bindValue(":heure_debut",ui->heure_debut_2->currentText());
    query2.bindValue(":heure_fin",ui->heure_fin_2->currentText());
    query2.exec();
    if(query2.first())
    {
        query2.prepare("DELETE FROM cours WHERE fk_id_professeur = :fk_id_professeur AND fk_id_matiere = :fk_id_matiere AND fk_id_salle = :fk_id_salle AND fk_id_classe = :fk_id_classe AND heure_debut = :heure_debut AND heure_fin = :heure_fin AND date_cours = :date_cours");
        query2.bindValue(":fk_id_professeur",fkProf);
        query2.bindValue(":fk_id_matiere",fkMatiere);
        query2.bindValue(":fk_id_salle",fkSalle);
        query2.bindValue(":fk_id_classe",fkClasse);
        query2.bindValue(":heure_debut",ui->heure_debut_2->currentText());
        query2.bindValue(":heure_fin",ui->heure_fin_2->currentText());
        query2.bindValue(":date_cours",ui->dateCours_2->date());
        query2.exec();
        QMessageBox::information(this,"Validation","Ce cours a bien été supprimer.");
    }
    else
    {
        QMessageBox::warning(this,"Erreur","Il n'y a pas de cours avec ces informations.");
    }



}


