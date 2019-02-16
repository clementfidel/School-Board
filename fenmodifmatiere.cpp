#include "ui_fenadmin.h"
#include "fenadmin.h"



//Permet d'ajouter un matière dans la base de donnée.
void fenAdmin::ajouterMatiere()
{
    if(ui->nomMatiere->text()!="")
    {
        QSqlQuery query2;
        query2.prepare("SELECT nom_matiere FROM matiere WHERE nom_matiere = :nom_matiere");
        query2.bindValue(":nom_matiere", ui->nomMatiere->text());
        query2.exec();
        if(query2.first())
        {
            QMessageBox::warning(this,"Erreur","Cette matière existe déja.");
        }
        else
        {
            query2.prepare("INSERT INTO matiere (nom_matiere) VALUES (:nom_matiere)");
            query2.bindValue(":nom_matiere",ui->nomMatiere->text());
            query2.exec();
            QMessageBox::information(this,"Validation","La matière a bien été inséré.");
        }
    }
    else
    {
        QMessageBox::warning(this,"Erreur","Veuillez préalablement rentrer le nom de la matiere.");
    }

}

//Permet de supprimer une matière dans la base de donnée.
void fenAdmin::supprimerMatiere()
{
    if(ui->nomMatiere->text()!="")
    {
        QSqlQuery query3;
        query3.prepare("SELECT nom_matiere FROM matiere WHERE nom_matiere = :nom_matiere");
        query3.bindValue(":nom_matiere", ui->nomMatiere->text());
        query3.exec();
        if(query3.first())
        {

            query3.prepare("DELETE FROM matiere WHERE nom_matiere = :nom_matiere");
            query3.bindValue(":nom_matiere",ui->nomMatiere->text());
            query3.exec();

            query3.prepare("SELECT nom_matiere FROM matiere WHERE nom_matiere = :nom_matiere");
            query3.bindValue(":nom_matiere", ui->nomMatiere->text());
            query3.exec();
            if(query3.first())
            {
                QMessageBox::warning(this,"Erreur","Vous ne pouvez pas supprimer une matière tant qu'il reste des cours dans cette matière.");
            }
            else
            {
                QMessageBox::information(this,"Information","La matière a bien été supprimer.");
            }
        }
        else
        {
            QMessageBox::warning(this,"Erreur","Il n'existe pas de matière avec ce nom.");
        }
    }
    else
    {
        QMessageBox::warning(this,"Erreur","Veuillez préalablement rentrer le nom de la matière.");
    }
}
