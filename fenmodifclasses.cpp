
#include "ui_fenadmin.h"
#include "fenadmin.h"

//Permet d'ajouter une classe dans la base de donnée.
void fenAdmin::validerAjClasse()
{
    if(ui->nomClasse->text()!="")
    {
        QSqlQuery query2;
        query2.prepare("SELECT nom_classe FROM classe WHERE nom_classe = :nom_classe");
        query2.bindValue(":nom_classe", ui->nomClasse->text());
        query2.exec();
        if(query2.first())
        {
            QMessageBox::warning(this,"Erreur","Cette classe existe déja.");
        }
        else
        {
            query2.prepare("INSERT INTO classe (nom_classe) VALUES (:nom_classe)");
            query2.bindValue(":nom_classe",ui->nomClasse->text());
            query2.exec();
            QMessageBox::information(this,"Information","La classe a bien été ajouté.");
        }

    }
    else
    {
        QMessageBox::warning(this,"Erreur","Veuillez entrez un nom de classe préalablement.");
    }


}

//Permet de supprimer un classe dans la base de donnée.
void fenAdmin::suppClasse()
{

    QSqlQuery query3, query4;

    query3.prepare("SELECT id_classe FROM classe WHERE nom_classe = :nom_classe");
    query3.bindValue(":nom_classe", ui->nomClasse->text());
    query3.exec();
    if(query3.first())
    {
        int reponse = QMessageBox::question(this,"Question","Voulez vous vraiment supprimer cette classe ainsi que ces élèves ?", QMessageBox::Yes | QMessageBox::No);

        if(reponse == QMessageBox::Yes)
        {
            query4.prepare("DELETE FROM eleve WHERE fk_id_classe = :fk_id_classe");
            query4.bindValue(":fk_id_classe", query3.value(0).toInt());
            query4.exec();

            query3.prepare("DELETE FROM classe WHERE nom_classe = :nom_classe");
            query3.bindValue(":nom_classe",ui->nomClasse->text());
            query3.exec();
        }


    }
    else
    {
        QMessageBox::warning(this,"Erreur","Il n'existe pas de classe avec ce nom.");
    }


}
