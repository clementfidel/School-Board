
#include "ui_fenadmin.h"
#include "fenadmin.h"

//Permet de remplir les listes déroulantes et de défnir la date a la date d'aujourd'hui.
void fenAdmin::fenAjCoursInit()
{
    QDate date = QDate::currentDate();
    ui->dateCours->setDate(date);


    QSqlQuery query2;
    query2.prepare("SELECT nom FROM professeur");
    query2.exec();
    while(query2.next())
    {
        ui->professeur->addItem(query2.value(0).toString());
    }

    modifMatiere();

    query2.prepare("SELECT nom_salle FROM salle");
    query2.exec();
    while(query2.next())
    {


        ui->salle->addItem(query2.value(0).toString());

    }

    query2.prepare("SELECT nom_classe FROM classe");
    query2.exec();
    while(query2.next())
    {


        ui->classe->addItem(query2.value(0).toString());

    }




}


//Permet de remplir la liste déroulante des matières en fonction du nom du professeur.
void fenAdmin::modifMatiere()
{
    ui->matiere->clear();
    QSqlQuery query2;
    QSqlQuery query3;
    QSqlQuery query4;
    query3.prepare("SELECT id_professeur FROM professeur WHERE nom = :nom");
    query3.bindValue(":nom",ui->professeur->currentText());
    query3.exec();
    query3.next();

    query2.prepare("SELECT fk_id_matiere FROM x_professeur_matiere WHERE fk_id_professeur = :fk_id_professeur");
    query2.bindValue(":fk_id_professeur",query3.value(0).toInt());
    query2.exec();
    while(query2.next())
    {
        query4.prepare("SELECT nom_matiere FROM matiere WHERE id_matiere = :id_matiere");
        query4.bindValue(":id_matiere",query2.value(0).toInt());
        query4.exec();
        while(query4.next())
        {
            ui->matiere->addItem(query4.value(0).toString());
        }

    }
}

//Permet d'ajouter un cours dans la base de donnée.
void fenAdmin::validerAjCours()
{
    int fkProf=0;
    int fkMatiere=0;
    int fkSalle=0;
    int fkClasse=0;
    QSqlQuery query2, query3, query4, query5;





    query2.prepare("SELECT id_professeur FROM professeur WHERE nom = :nom");
    query2.bindValue(":nom",ui->professeur->currentText());
    query2.exec();
    query2.next();
    fkProf=query2.value(0).toInt();

    query2.prepare("SELECT id_matiere FROM matiere WHERE nom_matiere = :nom_matiere");
    query2.bindValue(":nom_matiere",ui->matiere->currentText());
    query2.exec();
    query2.next();
    fkMatiere=query2.value(0).toInt();

    query2.prepare("SELECT id_salle FROM salle WHERE nom_salle = :nom_salle");
    query2.bindValue(":nom_salle",ui->salle->currentText());
    query2.exec();
    query2.next();
    fkSalle=query2.value(0).toInt();

    query2.prepare("SELECT id_classe FROM classe WHERE nom_classe = :nom_classe");
    query2.bindValue(":nom_classe",ui->classe->currentText());
    query2.exec();
    query2.next();
    fkClasse=query2.value(0).toInt();

    query2.prepare("SELECT nb_place FROM salle WHERE nom_salle = :nom_salle");
    query2.bindValue(":nom_salle",ui->salle->currentText());
    query2.exec();
    query2.next();

    query3.prepare("SELECT COUNT(id_eleve) FROM eleve WHERE fk_id_classe = :fk_id_classe");
    query3.bindValue(":fk_id_classe",fkClasse);
    query3.exec();
    query3.next();

if(query2.value(0).toInt()>query3.value(0).toInt())
{

    if( ui->heure_debut->time()<( ui->heure_fin->time()))
    {
        if(ui->heure_debut->time()!=ui->heure_fin->time())
        {
            query2.prepare("SELECT fk_id_classe FROM cours WHERE ((:heure_debut BETWEEN heure_debut AND heure_fin) OR (:heure_fin BETWEEN heure_debut AND heure_fin) OR (:heure_debut < heure_debut AND :heure_fin > heure_fin) OR (:heure_debut > heure_debut AND :heure_fin < heure_fin)) AND date_cours = :date_cours AND fk_id_classe = :fk_id_classe");
            query2.bindValue(":heure_debut",ui->heure_debut->time());
            query2.bindValue(":heure_fin",ui->heure_fin->time());
            query2.bindValue(":date_cours",ui->dateCours->date());
            query2.bindValue(":fk_id_classe",fkClasse);
            query2.exec();
            if(!query2.first())
            {
                query3.prepare("SELECT fk_id_professeur FROM cours WHERE ((:heure_debut BETWEEN heure_debut AND heure_fin) OR (:heure_fin BETWEEN heure_debut AND heure_fin) OR (:heure_debut < heure_debut AND :heure_fin > heure_fin) OR (:heure_debut > heure_debut AND :heure_fin < heure_fin)) AND date_cours = :date_cours  AND fk_id_professeur = :fk_id_professeur");
                query3.bindValue(":heure_debut",ui->heure_debut->time());
                query3.bindValue(":heure_fin",ui->heure_fin->time());
                query3.bindValue(":date_cours",ui->dateCours->date());
                query3.bindValue(":fk_id_professeur",fkProf);
                query3.exec();
                if(!query3.first())
                {
                    query4.prepare("SELECT fk_id_salle FROM cours WHERE ((:heure_debut BETWEEN heure_debut AND heure_fin) OR (:heure_fin BETWEEN heure_debut AND heure_fin) OR (:heure_debut < heure_debut AND :heure_fin > heure_fin) OR (:heure_debut > heure_debut AND :heure_fin < heure_fin)) AND date_cours = :date_cours AND fk_id_salle = :fk_id_salle");
                    query4.bindValue(":heure_debut",ui->heure_debut->time());
                    query4.bindValue(":heure_fin",ui->heure_fin->time());
                    query4.bindValue(":date_cours",ui->dateCours->date());
                    query4.bindValue(":fk_id_salle",fkSalle);
                    query4.exec();
                    if(!query4.first())
                    {
                        if(ui->dateCours->date() >= QDate::currentDate())
                        {
                            query2.prepare("INSERT INTO cours (fk_id_professeur, fk_id_matiere, fk_id_salle, fk_id_classe, heure_debut, heure_fin, date_cours)VALUES (:fk_id_professeur, :fk_id_matiere, :fk_id_salle, :fk_id_classe, :heure_debut, :heure_fin, :date_cours)");

                                query2.bindValue(":fk_id_professeur",fkProf);
                                query2.bindValue(":fk_id_matiere",fkMatiere);
                                query2.bindValue(":fk_id_salle",fkSalle);
                                query2.bindValue(":fk_id_classe",fkClasse);
                                query2.bindValue(":heure_debut",ui->heure_debut->time());
                                query2.bindValue(":heure_fin",ui->heure_fin->time());
                                query2.bindValue(":date_cours",ui->dateCours->date());
                                query2.exec();
                                qDebug() <<"hhhhhhh";
                        }
                        else
                        {
                            QMessageBox::warning(this,"Erreur","Veuillez choisir un date postérieur a aujourd'hui.");
                        }



                    }
                    else
                    {
                        QMessageBox::warning(this,"Erreur","La salle est déja prise par un autre cours.");
                    }
                }
                else
                {
                    QMessageBox::warning(this,"Erreur","Le professeur a deja un cours a cette heure ci.");
                }
            }
            else
            {
                QMessageBox::warning(this,"Erreur","La classe a deja un cours a cette heure ci.");

            }
        }
        else
        {
            QMessageBox::warning(this,"Erreur","Veuillez ne pas rentrez la même heure de début et de fin de cours.");
        }
    }
    else
    {
        QMessageBox::warning(this,"Erreur","Veuillez rentrez une heure de début avant l'heure de fin du cours.");
    }

}
else
{
    QMessageBox::warning(this,"Erreur","Veuillez inséré le cours dans une salle avec suffisament de place pour la classe.");
}









}

