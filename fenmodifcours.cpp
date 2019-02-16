#include "ui_fenadmin.h"
#include "fenadmin.h"

//Permet de cacher les textes inutile lorsqu'on arrive sur la page et définis le champs de la date a la date d'aujourd'hui.
void fenAdmin::fenModifCoursInit()
{

    QDate date = QDate::currentDate();
    ui->dateCours_3->setDate(date);
    ui->classeEdit->hide();
    ui->professeurEdit->hide();
    ui->heureDebutEdit->hide();
    ui->heureFinEdit->hide();
    ui->salleEdit->hide();
    ui->matiereEdit->hide();

    ui->classe_3->hide();
    ui->matiere_3->hide();
    ui->salle_3->hide();
    ui->professeur_3->hide();
    ui->heure_debut_3->hide();
    ui->heure_fin_3->hide();
    ui->dateCoursEdit->hide();

    ui->lineEdit_40->hide();
    ui->lineEdit_41->hide();
    ui->lineEdit_42->hide();
    ui->lineEdit_43->hide();
    ui->lineEdit_44->hide();
    ui->lineEdit_45->hide();
    ui->lineEdit_46->hide();

   ui->pushButton_4->hide();
   ui->pushButton_18->hide();




}

//Permet de remplir toute les listes déroulantes en fonction des cours qu'il y a dans la journée précédament séléctionner
void fenAdmin::choiceDate()
{

    QSqlQuery query2;
    QSqlQuery query3;
    query2.prepare("SELECT fk_id_classe FROM cours WHERE date_cours = :date_cours");
    query2.bindValue(":date_cours", ui->dateCours_3->date());
    ui->classe->clear();
    query2.exec();

        while(query2.next())
        {

            query3.prepare("SELECT nom_classe FROM classe WHERE id_classe = :id_classe");
            query3.bindValue(":id_classe",query2.value(0).toInt());
            query3.exec();
            while(query3.next())
            {
                ui->classe_3->addItem(query3.value(0).toString());
            }
        }
        if(query2.first())
        {
            ui->classeEdit->hide();
            ui->matiereEdit->hide();
            ui->professeurEdit->hide();
            ui->salleEdit->hide();
            ui->heureDebutEdit->hide();
            ui->heureFinEdit->hide();
            ui->pushButton_18->hide();
             ui->dateCoursEdit->hide();

            ui->classe_3->show();
            ui->pushButton_4->show();
            ui->professeur_3->show();
            ui->heure_debut_3->show();
            ui->heure_fin_3->show();
            ui->salle_3->show();
            ui->matiere_3->show();
            ui->lineEdit_40->show();
            ui->lineEdit_41->show();
            ui->lineEdit_42->show();
            ui->lineEdit_43->show();
            ui->lineEdit_44->show();
            ui->lineEdit_45->show();


        query2.prepare("SELECT heure_debut FROM cours WHERE date_cours = :date_cours");
        query2.bindValue(":date_cours", ui->dateCours_3->date());
        query2.exec();
        ui->heure_debut_3->clear();
        while(query2.next())
        {
            ui->heure_debut_3->addItem(query2.value(0).toString());
        }

        query2.prepare("SELECT heure_fin FROM cours WHERE date_cours = :date_cours");
        query2.bindValue(":date_cours", ui->dateCours_3->date());
        query2.exec();
        ui->heure_fin_3->clear();
        while(query2.next())
        {
            ui->heure_fin_3->addItem(query2.value(0).toString());
        }


        query2.prepare("SELECT fk_id_professeur FROM cours WHERE date_cours = :date_cours");
        query2.bindValue(":date_cours", ui->dateCours_3->date());
        query2.exec();
        ui->professeur_3->clear();
        while(query2.next())
        {
            query3.prepare("SELECT nom FROM professeur WHERE id_professeur =:id_professeur");
            query3.bindValue(":id_professeur",query2.value(0).toInt());
            query3.exec();
            while(query3.next())
            {
                ui->professeur_3->addItem(query3.value(0).toString());
            }
        }





        query2.prepare("SELECT fk_id_matiere FROM cours WHERE date_cours = :date_cours");
        query2.bindValue(":date_cours", ui->dateCours_3->date());
        query2.exec();
        ui->matiere_3->clear();
        while(query2.next())
        {
            query3.prepare("SELECT nom_matiere FROM matiere WHERE id_matiere = :id_matiere");
            query3.bindValue(":id_matiere",query2.value(0).toInt());
            query3.exec();

            while(query3.next())
            {
                ui->matiere_3->addItem(query3.value(0).toString());

            }
        }



        query2.prepare("SELECT fk_id_salle FROM cours WHERE date_cours = :date_cours");
        query2.bindValue(":date_cours", ui->dateCours_3->date());
        query2.exec();
        ui->salle_3->clear();
        while(query2.next())
        {
            query3.prepare("SELECT nom_salle FROM salle WHERE id_salle = :id_salle");
            query3.bindValue(":id_salle",query2.value(0).toInt());
            query3.exec();
            while(query3.next())
            {
                ui->salle_3->addItem(query3.value(0).toString());
            }
        }







    }
    else
    {
        QMessageBox::warning(this,"Erreur","Il n'y a pas de cours ce jour ci.");


    }



}

//Permet de séléctionner précisement le cours a modifié.
void fenAdmin::selectionCours()
{
    int fkProf=0;
    int fkMatiere=0;
    int fkSalle=0;
    int fkClasse=0;
    ui->lineEdit_46->show();

    QSqlQuery query2;

    query2.prepare("SELECT id_professeur FROM professeur WHERE nom = :nom");
    query2.bindValue(":nom",ui->professeur_3->currentText());
    query2.exec();
    query2.next();
    if(query2.first())
    {

        fkProf=query2.value(0).toInt();
    }




    query2.prepare("SELECT id_matiere FROM matiere WHERE nom_matiere = :nom_matiere");
    query2.bindValue(":nom_matiere",ui->matiere_3->currentText());
    query2.exec();
    query2.next();
    if(query2.first())
    {

        fkMatiere=query2.value(0).toInt();
    }



    query2.prepare("SELECT id_salle FROM salle WHERE nom_salle = :nom_salle");
    query2.bindValue(":nom_salle",ui->salle_3->currentText());
    query2.exec();
    query2.next();
    if(query2.first())
    {

        fkSalle=query2.value(0).toInt();
    }



    query2.prepare("SELECT id_classe FROM classe WHERE nom_classe = :nom_classe");
    query2.bindValue(":nom_classe",ui->classe_3->currentText());
    query2.exec();
    query2.next();
    if(query2.first())
    {

        fkClasse=query2.value(0).toInt();
    }
    query2.prepare("SELECT id_cours FROM cours WHERE fk_id_professeur = :fk_id_professeur AND fk_id_matiere = :fk_id_matiere AND fk_id_salle = :fk_id_salle AND fk_id_classe = :fk_id_classe AND heure_debut = :heure_debut AND heure_fin = :heure_fin AND date_cours = :date_cours");
    query2.bindValue(":fk_id_professeur",fkProf);
    query2.bindValue(":fk_id_matiere",fkMatiere);
    query2.bindValue(":fk_id_salle",fkSalle);
    query2.bindValue(":fk_id_classe",fkClasse);
    query2.bindValue(":heure_debut",ui->heure_debut_3->currentText());
    query2.bindValue(":heure_fin",ui->heure_fin_3->currentText());
    query2.bindValue(":date_cours",ui->dateCours_3->date());
    query2.exec();
    query2.next();
    if(query2.first())
    {
        idCours=query2.value(0).toInt();
        ui->classe_3->hide();
        ui->pushButton_4->hide();
        ui->professeur_3->hide();
        ui->heure_debut_3->hide();
        ui->heure_fin_3->hide();
        ui->salle_3->hide();
        ui->matiere_3->hide();

        ui->classeEdit->clear();
        ui->matiereEdit->clear();
        ui->professeurEdit->clear();
        ui->salleEdit->clear();
        ui->heureDebutEdit->clear();
        ui->heureFinEdit->clear();

        ui->classeEdit->show();
        ui->matiereEdit->show();
        ui->professeurEdit->show();
        ui->salleEdit->show();
        ui->heureDebutEdit->show();
        ui->heureFinEdit->show();
        ui->pushButton_18->show();
         ui->dateCoursEdit->show();



        ui->matiereEdit->insert(ui->matiere_3->currentText());
        ui->professeurEdit->insert(ui->professeur_3->currentText());
        ui->salleEdit->insert(ui->salle_3->currentText());
        ui->classeEdit->insert(ui->classe_3->currentText());

        ui->heureDebutEdit->setTime(QTime::fromString(ui->heure_debut_3->currentText()));
        ui->heureFinEdit->setTime(QTime::fromString(ui->heure_fin_3->currentText()));
    }
    else
    {
        QMessageBox::warning(this,"Erreur","Il n'y a pas de cours existant avec ces informations.");


    }
}

//Permet de modifié le cours dans la base de donnée.
void fenAdmin::modifCours()
{
    int fkProf=0;
    int fkMatiere=0;
    int fkSalle=0;
    int fkClasse=0;
    int validation=0;


    QSqlQuery query2;

    query2.prepare("SELECT id_professeur FROM professeur WHERE nom = :nom");
    query2.bindValue(":nom",ui->professeurEdit->text());
    query2.exec();
    query2.next();
    if(query2.first())
    {

        fkProf=query2.value(0).toInt();
    }
    else
    {
        validation=1;
        QMessageBox::warning(this,"Erreur","Il n'existe pas de professeur avec ce nom.");
    }




    query2.prepare("SELECT id_matiere FROM matiere WHERE nom_matiere = :nom_matiere");
    query2.bindValue(":nom_matiere",ui->matiereEdit->text());
    query2.exec();
    query2.next();
    if(query2.first())
    {

        fkMatiere=query2.value(0).toInt();
    }
    else
    {
        validation=1;
        QMessageBox::warning(this,"Erreur","Il n'existe pas de matiere avec ce nom.");
    }



    query2.prepare("SELECT id_salle FROM salle WHERE nom_salle = :nom_salle");
    query2.bindValue(":nom_salle",ui->salleEdit->text());
    query2.exec();
    query2.next();
    if(query2.first())
    {

        fkSalle=query2.value(0).toInt();
    }
    else
    {
        validation=1;
        QMessageBox::warning(this,"Erreur","Il n'existe pas de salle avec ce nom.");
    }



    query2.prepare("SELECT id_classe FROM classe WHERE nom_classe = :nom_classe");
    query2.bindValue(":nom_classe",ui->classeEdit->text());
    query2.exec();
    query2.next();
    if(query2.first())
    {

        fkClasse=query2.value(0).toInt();
    }
    else
    {
        validation=1;
        QMessageBox::warning(this,"Erreur","Il n'existe pas de classe avec ce nom.");
    }

        if(validation==0)
        {
            query2.prepare("UPDATE cours SET fk_id_professeur = :fk_id_professeur, fk_id_matiere = :fk_id_matiere, fk_id_salle = :fk_id_salle, fk_id_classe = :fk_id_classe,  heure_debut = :heure_debut, heure_fin = :heure_fin, date_cours = :date_cours WHERE id_cours = :id_cours");
            query2.bindValue(":id_cours",idCours);
            query2.bindValue(":fk_id_professeur",fkProf);
            query2.bindValue(":fk_id_matiere",fkMatiere);
            query2.bindValue(":fk_id_salle",fkSalle);
            query2.bindValue(":fk_id_classe",fkClasse);
            query2.bindValue(":heure_debut",ui->heureDebutEdit->text());
            query2.bindValue(":heure_fin",ui->heureFinEdit->text());
            query2.bindValue(":date_cours",ui->dateCoursEdit->date());
            query2.exec();
            QMessageBox::information(this,"Validation","Le cours a bien été modifié.");

        }
}




