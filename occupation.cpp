#include "ui_fenadmin.h"
#include "fenadmin.h"

//Permet de remplir les listes déroulantes et de définir les champs de date ala date d'aujourd'hui.
void fenAdmin::occupationInit()
{


    QSqlQuery query2;
    query2.prepare("SELECT nom_classe FROM classe");
    query2.exec();
    while(query2.next())
    {
        ui->classeSelec->addItem(query2.value(0).toString());
    }

    query2.prepare("SELECT nom FROM professeur");
    query2.exec();
    while(query2.next())
    {
        ui->profSelec->addItem(query2.value(0).toString());
    }
    QDate date = QDate::currentDate();
    ui->classeDateDebut->setDate(date);
    ui->classeDateFin->setDate(date);
    ui->salleDateDebut->setDate(date);
    ui->salleDateFin->setDate(date);
    ui->profDateDebut->setDate(date);
    ui->profDateFin->setDate(date);
}

//Permet d'afficher les salles qui sont occuper entres les 2 dates choisi.
void fenAdmin::dispoSalle()
{
    if(ui->salleDateDebut->date()<ui->salleDateFin->date())
    {
        ui->salleAffichage->clear();
        QSqlQuery query3, query4;

        query4.prepare("SELECT date_cours, heure_debut, heure_fin, fk_id_salle  FROM cours WHERE date_cours >= :date_debut AND date_cours <= :date_fin");
        query4.bindValue(":date_debut",ui->salleDateDebut->date().toString("yyyy-MM-dd"));
        query4.bindValue(":date_fin",ui->salleDateFin->date().toString("yyyy-MM-dd"));
        query4.exec();

        QString occup = "<html><style type=\"text/css\"> \
                table { width:100%; background-color:#FFFFFF; border-collapse:collapse; border-width:1px; border-color:#000101; border-style:solid; color:#000101; } \
                table td, table th { border-width:1px;  border-color:#336600; border-style:solid; padding:3px; text-align:center;} \
                table thead { background-color:#CCFF99; } </style><div align=right><table align=center><tr><th>Date</th><th>Heure de début</th><th>Heure de fin</th><th>Salle</th></tr>";
        while(query4.next())
        {

                query3.prepare("SELECT nom_salle FROM salle WHERE id_salle = :id_salle");
                query3.bindValue(":id_salle",query4.value(3).toInt());
                query3.exec();
                query3.next();
                occup = occup + "<tr><td>"+query4.value(0).toString()+"</td><td>"+query4.value(1).toString()+"</td><td>"+query4.value(2).toString()+"</td><td>"+query3.value(0).toString()+"</td></tr>";

        }

        occup = occup +"</table></html>";
        ui->salleAffichage->setHtml(occup);

        if(!query4.first())
        {
            ui->salleAffichage->clear();
            QMessageBox::warning(this,"Erreur","Il n'y a pas de cours entre ces dates.");
        }
    }
    else
    {
        QMessageBox::warning(this,"Erreur","Veuillez inséré une date de début avant la date de fin.");
    }

}
//Permet d'afficher les cours d'un classe sélectionner, entres 2 dates.
void fenAdmin::dispoClasse()
{
    if(ui->classeDateDebut->date()<ui->classeDateFin->date())
    {
        ui->classeAffichage->clear();

        QSqlQuery query3, query4, query7;

        query7.prepare("SELECT id_classe FROM classe WHERE nom_classe = :nom_classe");
        query7.bindValue(":nom_classe",ui->classeSelec->currentText());
        query7.exec();
        query7.next();

        query4.prepare("SELECT date_cours ,heure_debut, heure_fin, fk_id_salle FROM cours WHERE date_cours >= :date_debut AND date_cours <= :date_fin AND fk_id_classe = :fk_id_classe");
        query4.bindValue(":date_debut",ui->classeDateDebut->date().toString("yyyy-MM-dd"));
        query4.bindValue(":date_fin",ui->classeDateFin->date().toString("yyyy-MM-dd"));
        query4.bindValue(":fk_id_classe",query7.value(0).toInt());
        query4.exec();


        QString occup = "<html><style type=\"text/css\"> \
                table { width:100%; background-color:#FFFFFF; border-collapse:collapse; border-width:1px; border-color:#000101; border-style:solid; color:#000101; } \
                table td, table th { border-width:1px;  border-color:#336600; border-style:solid; padding:3px; text-align:center;} \
                table thead { background-color:#CCFF99; } </style><div align=right><table align=center><tr><th>Date</th><th>Heure de début</th><th>Heure de fin</th><th>Salle</th></tr>";
        while(query4.next())
        {
           query3.prepare("SELECT nom_salle FROM salle WHERE id_salle = :id_salle");
           query3.bindValue(":id_salle",query4.value(3).toInt());
           query3.exec();
           query3.next();

           occup = occup + "<tr><td>"+query4.value(0).toString()+"</td><td>"+query4.value(1).toString()+"</td><td>"+query4.value(2).toString()+"</td><td>"+query3.value(0).toString()+"</td></tr>";

        }
         occup = occup +"</table></html>";
          ui->classeAffichage->setHtml(occup);
        if(!query4.first())
        {
            ui->classeAffichage->clear();
            QMessageBox::warning(this,"Erreur","Cette classe n'a pas cours entre ces dates.");
        }
     }
     else
     {
        QMessageBox::warning(this,"Erreur","Veuillez inséré une date de début avant la date de fin.");
     }
}

//Permet d'afficher les cours avec le professeur sélectionner, entre 2 dates.
void fenAdmin::dispoProf()
{
    if(ui->profDateDebut->date()<ui->profDateFin->date())
    {

    ui->profAffichage->clear();
    QSqlQuery query3, query4, query7;


    query7.prepare("SELECT id_professeur FROM professeur WHERE nom = :nom");
    query7.bindValue(":nom",ui->profSelec->currentText());
    query7.exec();
    query7.next();




        query4.prepare("SELECT date_cours ,heure_debut, heure_fin, fk_id_salle FROM cours WHERE date_cours >= :date_debut AND date_cours <= :date_fin AND fk_id_professeur = :fk_id_professeur");
        query4.bindValue(":date_debut",ui->profDateDebut->date().toString("yyyy-MM-dd"));
        query4.bindValue(":date_fin",ui->profDateFin->date().toString("yyyy-MM-dd"));
        query4.bindValue(":fk_id_professeur",query7.value(0).toInt());
        query4.exec();


        QString occup = "<html><style type=\"text/css\"> \
                table { width:100%; background-color:#FFFFFF; border-collapse:collapse; border-width:1px; border-color:#000101; border-style:solid; color:#000101; } \
                table td, table th { border-width:1px;  border-color:#336600; border-style:solid; padding:3px; text-align:center;} \
                table thead { background-color:#CCFF99; } </style><div align=right><table align=center><tr><th>Date</th><th>Heure de début</th><th>Heure de fin</th><th>Salle</th></tr>";
        while(query4.next())
        {
           query3.prepare("SELECT nom_salle FROM salle WHERE id_salle = :id_salle");
           query3.bindValue(":id_salle",query4.value(3).toInt());
           query3.exec();
           query3.next();

           occup = occup + "<tr><td>"+query4.value(0).toString()+"</td><td>"+query4.value(1).toString()+"</td><td>"+query4.value(2).toString()+"</td><td>"+query3.value(0).toString()+"</td></tr>";

        }
         occup = occup +"</table></html>";
         ui->profAffichage->setHtml(occup);

        if(!query4.first())
        {
            ui->profAffichage->clear();
            QMessageBox::warning(this,"Erreur","Ce professeur n'a pas cours entre ces dates.");
        }
    }
    else
    {
        QMessageBox::warning(this,"Erreur","Veuillez inséré une date de début avant la date de fin.");
    }

}
