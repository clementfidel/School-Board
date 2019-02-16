#include "ui_fenadmin.h"
#include "fenadmin.h"

//Permet de définir un champs avec un remplissage uniquement de chiffres.
void fenAdmin::fenModifSalleInit()
{


    QValidator *validatorInt = new QIntValidator(this);
    ui->nbPlace->setValidator(validatorInt);
}

//Permet d'ajouter une salle dans la base de donnée.
void fenAdmin::validerAjSalle()
{
    QSqlQuery query2;
    if(ui->nomSalle->text()!="" && ui->nbPlace->text()!="")
    {
        query2.prepare("SELECT nom_salle FROM salle WHERE nom_salle = :nom_salle");
        query2.bindValue(":nom_salle", ui->nomSalle->text());
        query2.exec();
        if(!query2.first())
        {

        query2.prepare("INSERT INTO salle (nom_salle, nb_place) VALUES (:nom_salle, :nb_place)");
        query2.bindValue(":nom_salle",ui->nomSalle->text());
        query2.bindValue(":nb_place",ui->nbPlace->text());
        query2.exec();
        QMessageBox::information(this,"Validation","Cette salle a bien été inséré.");

        }
        else
        {
            QMessageBox::warning(this,"Erreur","Cette salle existe déjà.");
        }

    }
    else
    {
        QMessageBox::warning(this,"Erreur","Veuillez remplir préalablement le nom ainsi que le nombre de place de la salle.");
    }


}

//Permet de supprimer une salle dans la base de donnée.
void fenAdmin::suppSalle()
{
    QSqlQuery query3;
    if(ui->nomSalle_2->text()!="")
    {
        query3.prepare("SELECT nom_salle FROM salle WHERE nom_salle = :nom_salle");
        query3.bindValue(":nom_salle", ui->nomSalle_2->text());
        query3.exec();
        if(query3.first())
        {

            query3.prepare("DELETE FROM salle WHERE nom_salle = :nom_salle");
            query3.bindValue(":nom_salle",ui->nomSalle_2->text());
            query3.exec();

            query3.prepare("SELECT nom_salle FROM salle WHERE nom_salle = :nom_salle");
            query3.bindValue(":nom_salle", ui->nomSalle_2->text());
            query3.exec();
            if(query3.first())
            {
                QMessageBox::warning(this,"Erreur","Vous ne pouvez pas supprimer une salle tant qu'il reste des cours dans cette salle.");
            }
            else
            {
                QMessageBox::information(this,"Validation","Cette salle a bien été supprimer.");
            }
        }
        else
        {
            QMessageBox::warning(this,"Erreur","Il n'existe pas de salle avec ce nom.");
        }
   }
   else
   {
        QMessageBox::warning(this,"Erreur","Veuillez remplir préalablement le nom de la salle a supprimer.");
   }
}
