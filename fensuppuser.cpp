#include "ui_fenadmin.h"
#include "fenadmin.h"




//Permet de supprimer un utilisateur grâce a sont email.
void fenAdmin::suppUser()
{

    QSqlQuery query3;
    query3.prepare("SELECT * FROM eleve WHERE email = :email");
    query3.bindValue(":email",ui->email_6->text());
    query3.exec();


    if(query3.first())
    {

        QMessageBox::information(this,"Information", "Eleve supprimer");
        query3.prepare("DELETE FROM eleve WHERE email = :email");
        query3.bindValue(":email",ui->email_6->text());
        query3.exec();


    }
    else
    {

        query3.prepare("SELECT * FROM professeur WHERE email = :email");
        query3.bindValue(":email",ui->email_6->text());
        query3.exec();


        if(query3.first())
        {


           query3.prepare("DELETE FROM professeur WHERE email = :email");
           query3.bindValue(":email",ui->email_6->text());
           query3.exec();

           query3.prepare("SELECT * FROM professeur WHERE email = :email");
           query3.bindValue(":email",ui->email_6->text());
           query3.exec();
           if(query3.first())
           {
               QMessageBox::warning(this,"Erreur", "Veuillez préalablement supprimer les cours prévu avec ce professeur.");
           }
           else
           {
               QMessageBox::information(this,"Information", "Professeur supprimer");
           }


        }
        else
        {

            query3.prepare("SELECT * FROM administrateur WHERE email = :email");
            query3.bindValue(":email",ui->email_6->text());
            query3.exec();


            if(query3.first())
            {

                QMessageBox::information(this,"Information", "Administrateur supprimer");
                query3.prepare("DELETE FROM administrateur WHERE email = :email");
                query3.bindValue(":email",ui->email_6->text());
                query3.exec();


            }
            else
            {
                  QMessageBox::warning(this,"Erreur", "Email inconu");
                  //qDebug() << query3.lastError().text();

            }
        }
    }
}
