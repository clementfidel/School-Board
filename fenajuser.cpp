
#include "ui_fenadmin.h"
#include "fenadmin.h"
#include <smtp.h>




//Permet de remplir les listes déroulantes, et de définir ce que l'on peut inséré dans les champs.
void fenAdmin::fenAjUserInit()

{
    QValidator *validatorInt = new QIntValidator(this);

    QDate date = QDate::currentDate();

    ui->cne->setValidator(validatorInt);
    ui->cin->setValidator(validatorInt);
    ui->numTel->setValidator(validatorInt);
    ui->numRue->setValidator(validatorInt);
    ui->codePostal->setValidator(validatorInt);
    ui->numTel_2->setValidator(validatorInt);
    ui->date_naissance->setDate(date);
    ui->matiere_4->hide();
    ui->matiere_5->hide();
    ui->matiere_6->hide();
    ui->matiere_7->hide();
    ui->lineEdit_32->hide();
    ui->lineEdit_47->hide();
    ui->lineEdit_48->hide();
    ui->lineEdit_49->hide();
    ui->lineEdit_50->hide();
    ui->textBrowser_35->hide();

    QSqlQuery query3;
    query3.prepare("SELECT nom_classe FROM classe");
    query3.exec();
    while(query3.next())
    {
      ui->classe_4->addItem(query3.value(0).toString());
      ui->classeProf->addItem(query3.value(0).toString());
    }

   QRegularExpression rx("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b", QRegularExpression::CaseInsensitiveOption);
   ui->email->setValidator(new QRegularExpressionValidator(rx, this));
   ui->email_2->setValidator(new QRegularExpressionValidator(rx, this));
   ui->email_3->setValidator(new QRegularExpressionValidator(rx, this));


}
//Permet d'ajouter une classe a un professeur.
void fenAdmin::ajouterClasseProf()
{
    QSqlQuery query3;
    ui->lineEdit_50->show();
    ui->textBrowser_35->show();
    query3.prepare("SELECT id_classe FROM classe WHERE nom_classe = :nom_classe");
    query3.bindValue(":nom_classe",ui->classeProf->currentText());
    query3.exec();
    query3.next();
    int verif=0;
    for(int i = 0; i <classeProf.size(); i++)
    {
        if(classeProf.at(i)==query3.value(0).toInt())
        {
            verif=1;
        }
    }
    if(verif!=1)
    {
        ui->textBrowser_35->insertHtml("&nbsp;&nbsp;- "+ui->classeProf->currentText()+"<br>");

        classeProf = classeProf << query3.value(0).toInt();
        qDebug() << classeProf;
    }
    else
    {
        QMessageBox::warning(this,"Erreur", "Vous avez déja ajouter cette classe.");
    }

}
//Permet d'ajouter un élève dans la base de donnée.
void fenAdmin::validerAjEleve()
{
    int validation=0;
    QString chaineACrypter(ui->email->text());
    QString chaineCryptee;
    int decalage(3);

    QString alphabet = "y6zue2xfc4wrjo0tv1s.b3kg1n5ih8ml@-qp7d9a";
    int pos;
    chaineACrypter = chaineACrypter.toLower();

    QTextStream flux(&chaineCryptee);
    for(int i(0); i < chaineACrypter.size(); i++)
    {
            pos = alphabet.indexOf(chaineACrypter.at(i));
            flux<<alphabet.at((pos + decalage)%40);
    }

    qDebug() << chaineCryptee;


        if(ui->email->hasAcceptableInput())
        {


            QSqlQuery query2, query3, query4;



            query2.prepare("SELECT email FROM eleve WHERE email =:email");
            query2.bindValue(":email",ui->email->text());
            query2.exec();
            if (query2.first())
            {
                validation=1;
                QMessageBox::warning(this,"Erreur","Il existe déja un eleve avec cette email.");
            }
            query3.prepare("SELECT email FROM professeur WHERE email =:email");
            query3.bindValue(":email",ui->email->text());
            query3.exec();
            if (query3.first())
            {
                validation=1;
                QMessageBox::warning(this,"Erreur","Il existe déja un professeur avec cette email.");
            }
            query4.prepare("SELECT email FROM administrateur WHERE email =:email");
            query4.bindValue(":email",ui->email->text());
            query4.exec();
            if (query4.first())
            {
                validation=1;
                QMessageBox::warning(this,"Erreur","Il existe déja un administrateur avec cette email.");
            }

            query2.prepare("SELECT cin FROM eleve WHERE cin = :cin");
            query2.bindValue(":cin",ui->cin->text());
            query2.exec();
            if (query2.first())
            {

                QMessageBox::warning(this,"Erreur","Ce cin est déjà utilisé par un autre élève.");
                validation=1;
            }
            query2.prepare("SELECT cne FROM eleve WHERE cne = :cne");
            query2.bindValue(":cne",ui->cne->text());
            query2.exec();
            if (query2.first())
            {

                QMessageBox::warning(this,"Erreur","Ce cne est déjà utilisé par un autre élève.");
                validation=1;
            }
            if(validation==0)
            {

                query3.prepare("SELECT id_classe FROM classe WHERE nom_classe = :nom_classe");
                query3.bindValue(":nom_classe",ui->classe->currentText());
                query3.exec();
                query3.next();

                if(ui->checkBox_2->isChecked())
                {
                    if(ui->prenom->text()!="" && ui->nom->text()!="" &&  ui->cne->text()!="" && ui->cin->text()!="" && ui->numTel->text()!="" && ui->numRue->text()!="" && ui->nomRue->text()!="" && ui->codePostal->text()!="" && ui->nomVille->text()!="" && ui->email->text()!="")
                    {
                        query2.prepare("INSERT INTO eleve (cne, cin, nom, prenom, email, date_naissance, num_tel, num_rue, nom_rue, code_postal, ville, fk_id_classe) VALUES (:cne, :cin, :nom, :prenom, :email, :date_naissance, :num_tel, :num_rue, :nom_rue, :code_postal, :ville, :fk_id_classe)");

                        query2.bindValue(":cne",ui->cne->text());
                        query2.bindValue(":cin",ui->cin->text());
                        query2.bindValue(":nom",ui->nom->text());
                        query2.bindValue(":prenom",ui->prenom->text());
                        query2.bindValue(":email",ui->email->text());
                        query2.bindValue(":date_naissance",ui->date_naissance->date());
                        query2.bindValue(":num_tel",ui->numTel->text());
                        query2.bindValue(":num_rue",ui->numRue->text());
                        query2.bindValue(":nom_rue",ui->nomRue->text());
                        query2.bindValue(":code_postal",ui->codePostal->text());
                        query2.bindValue(":ville",ui->nomVille->text());
                        query2.bindValue(":fk_id_classe",query3.value(0).toInt());
                        query2.exec();
                        Smtp* smtp = new Smtp("setYourEmailGmail", "SetYourPasswordGmail", "smtp.gmail.com", 465);

                        smtp->sendMail("epsischool@gmail.com", ui->email->text() , "Identifiant EPSI","Bonjour,\n Veuillez trouver ci-dessous votre identifiant pour vous connecter sur l'application School Board : \n\n  -    Identifiant : " + ui->email_3->text() + "\n  -    Mot de passe : Veuillez cliquer sur ce lien afin d'avoir votre mot de passe : \nhttps://school-board.000webhostapp.com/passwordalea.php?id=" + chaineCryptee + "\n\nCordialement, \n EPSI School");
                        QObject::connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));
                        QMessageBox::information(this,"Validation", "L'élève a bien été inséré.");
                    }
                    else
                    {
                        QMessageBox::warning(this,"Erreur", "Veuillez remplir tous les champs.");
                    }
                }
                else
                {
                    if(ui->prenom->text()!="" && ui->nom->text()!="" && ui->mdp->text()!="" && ui->cne->text()!="" && ui->cin->text()!="" && ui->numTel->text()!="" && ui->numRue->text()!="" && ui->nomRue->text()!="" && ui->codePostal->text()!="" && ui->nomVille->text()!="" && ui->email->text()!="")
                    {
                        query2.prepare("INSERT INTO eleve (cne, cin, nom, prenom, email, password, date_naissance, num_tel, num_rue, nom_rue, code_postal, ville, fk_id_classe) VALUES (:cne, :cin, :nom, :prenom, :email, :password, :date_naissance, :num_tel, :num_rue, :nom_rue, :code_postal, :ville, :fk_id_classe)");

                        query2.bindValue(":cne",ui->cne->text());
                        query2.bindValue(":cin",ui->cin->text());
                        query2.bindValue(":nom",ui->nom->text());
                        query2.bindValue(":prenom",ui->prenom->text());
                        query2.bindValue(":email",ui->email->text());
                        query2.bindValue(":password",ui->mdp->text());
                        query2.bindValue(":date_naissance",ui->date_naissance->date());
                        query2.bindValue(":num_tel",ui->numTel->text());
                        query2.bindValue(":num_rue",ui->numRue->text());
                        query2.bindValue(":nom_rue",ui->nomRue->text());
                        query2.bindValue(":code_postal",ui->codePostal->text());
                        query2.bindValue(":ville",ui->nomVille->text());
                        query2.bindValue(":fk_id_classe",query3.value(0).toInt());


                        query2.exec();
                        QMessageBox::information(this,"Validation", "L'élève a bien été inséré.");
                    }
                    else
                    {
                        QMessageBox::warning(this,"Erreur", "Veuillez remplir tous les champs.");
                    }
                }

             }
        }
        else
        {
            QMessageBox::warning(this,"Erreur", "Le format de l'email est incorrect.");
        }
}





//Permet de cacher ou montrer les champs des matière en fonction du nombre indiqué dans la spinBox
void fenAdmin::nbMatiereProf()
{

    switch (ui->spinBox->value())
    {
    case 1:
        ui->matiere_1->show();
        ui->matiere_4->hide();
        ui->matiere_5->hide();
        ui->matiere_6->hide();
        ui->matiere_7->hide();
        ui->lineEdit_32->hide();
        ui->lineEdit_47->hide();
        ui->lineEdit_48->hide();
        ui->lineEdit_49->hide();
        break;

    case 2:
        ui->matiere_1->show();
        ui->matiere_4->show();
        ui->matiere_5->hide();
        ui->matiere_6->hide();
        ui->matiere_7->hide();
        ui->lineEdit_32->show();
        ui->lineEdit_47->hide();
        ui->lineEdit_48->hide();
        ui->lineEdit_49->hide();
        break;
    case 3:
        ui->matiere_1->show();
        ui->matiere_4->show();
        ui->matiere_5->show();

        ui->matiere_6->hide();
        ui->matiere_7->hide();

        ui->lineEdit_32->show();
        ui->lineEdit_47->show();
        ui->lineEdit_48->hide();
        ui->lineEdit_49->hide();
        break;
    case 4:
        ui->matiere_1->show();
        ui->matiere_4->show();
        ui->matiere_5->show();
        ui->matiere_6->show();

        ui->matiere_7->hide();

        ui->lineEdit_32->show();
        ui->lineEdit_47->show();
        ui->lineEdit_48->show();
        ui->lineEdit_49->hide();
        break;
    case 5:
        ui->matiere_1->show();
        ui->matiere_4->show();
        ui->matiere_5->show();
        ui->matiere_6->show();
        ui->matiere_7->show();

        ui->lineEdit_32->show();
        ui->lineEdit_47->show();
        ui->lineEdit_48->show();
        ui->lineEdit_49->show();
        break;
    default:
        break;
    }
}

//Permet de d'inséré un professeur dans la base de donnée.
void fenAdmin::validerAjProf()
{
    QString chaineACrypter(ui->email_2->text());
    QString chaineCryptee;
    int decalage(3);

    QString alphabet = "y6zue2xfc4wrjo0tv1s.b3kg1n5ih8ml@-qp7d9a";
    int pos;
    chaineACrypter = chaineACrypter.toLower();

    QTextStream flux(&chaineCryptee);
    for(int i(0); i < chaineACrypter.size(); i++)
    {
            pos = alphabet.indexOf(chaineACrypter.at(i));
            flux<<alphabet.at((pos + decalage)%40);
    }

    qDebug() << chaineCryptee;
    int validation=0;


        if(ui->email_2->hasAcceptableInput())
        {
            int idProf=0;
            QSqlQuery query2, query3, query4;
            query2.prepare("SELECT email FROM eleve WHERE email =:email");
            query2.bindValue(":email",ui->email_2->text());
            query2.exec();
            if (query2.first())
            {
                validation=1;
                QMessageBox::warning(this,"Erreur","Il existe déja un eleve avec cette email.");
            }
            query3.prepare("SELECT email FROM professeur WHERE email =:email");
            query3.bindValue(":email",ui->email_2->text());
            query3.exec();
            if (query3.first())
            {
                validation=1;
                QMessageBox::warning(this,"Erreur","Il existe déja un professeur avec cette email.");
            }
            query4.prepare("SELECT email FROM administrateur WHERE email =:email");
            query4.bindValue(":email",ui->email_2->text());
            query4.exec();
            if (query4.first())
            {
                validation=1;
                QMessageBox::warning(this,"Erreur","Il existe déja un administrateur avec cette email.");
            }

            if(validation==0)
            {
                if(ui->checkBox_3->isChecked())
                {
                    if(ui->prenom_2->text()!="" && ui->nom_2->text()!="" && ui->numTel_2->text()!=""  && ui->email_2->text()!="" && ui->matiere_1->text()!="")
                    {
                        query2.prepare("INSERT INTO professeur (nom, prenom, email, numero_tel)"
                                       "VALUES (:nom, :prenom, :email, :numero_tel)");
                        query2.bindValue(":nom",ui->nom_2->text());
                        query2.bindValue(":prenom",ui->prenom_2->text());
                        query2.bindValue(":email",ui->email_2->text());

                        query2.bindValue(":numero_tel",ui->numTel_2->text());
                        query2.exec();
                        Smtp* smtp = new Smtp("SetYourEmailGmail", "SetYourPasswordGmail", "smtp.gmail.com", 465);
                        smtp->sendMail("epsischool@gmail.com", ui->email_2->text() , "Identifiant EPSI","Bonjour,\n Veuillez trouver ci-dessous votre identifiant pour vous connecter sur l'application School Board : \n\n  -    Identifiant : " + ui->email_3->text() + "\n  -    Mot de passe : Veuillez cliquer sur ce lien afin d'avoir votre mot de passe : \nhttps://school-board.000webhostapp.com/passwordalea.php?id=" + chaineCryptee + "\n\nCordialement, \n EPSI School");
                        QObject::connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));
                        QMessageBox::information(this,"Validation", "Le professeur a bien été inséré.");
                    }
                    else
                    {
                        QMessageBox::warning(this,"Erreur", "Veuillez remplir tous les champs.");

                    }
                }

                else
                {
                    if(ui->prenom_2->text()!="" && ui->nom_2->text()!="" && ui->numTel_2->text()!="" && ui->mdp_2->text()!=""  && ui->email_2->text()!="" && ui->matiere_1->text()!="")
                    {
                    query2.prepare("INSERT INTO professeur (nom, prenom, email, password, numero_tel)"
                                   "VALUES (:nom, :prenom, :email, :password, :numero_tel)");
                    query2.bindValue(":nom",ui->nom_2->text());
                    query2.bindValue(":prenom",ui->prenom_2->text());
                    query2.bindValue(":email",ui->email_2->text());
                    query2.bindValue(":password",ui->mdp_2->text());
                    query2.bindValue(":numero_tel",ui->numTel_2->text());
                    query2.exec();
                    QMessageBox::information(this,"Validation", "Le professeur a bien été inséré.");
                    }
                    else
                    {
                        QMessageBox::warning(this,"Erreur", "Veuillez remplir tous les champs.");

                    }


                }


                query2.prepare("SELECT id_professeur FROM professeur WHERE email =:email");
                query2.bindValue(":email",ui->email_2->text());
                query2.exec();
                query2.next();
                idProf = query2.value(0).toInt();
                QList<QString> mater;
                 switch (ui->spinBox->value())
                 {
                     case 1:
                     {
                         mater << ui->matiere_1->text();
                        break;
                     }
                     case 2:
                     {
                         mater << ui->matiere_1->text() << ui->matiere_4->text();
                         break;
                     }
                     case 3:
                     {
                         mater << ui->matiere_1->text() << ui->matiere_4->text() << ui->matiere_5->text();
                         break;
                     }
                     case 4:
                     {
                         mater << ui->matiere_1->text() << ui->matiere_4->text() << ui->matiere_5->text() << ui->matiere_6->text();
                         break;
                     }
                     case 5:
                     {
                         mater << ui->matiere_1->text() << ui->matiere_4->text() << ui->matiere_5->text() << ui->matiere_6->text() << ui->matiere_7->text();
                         break;
                     }

                 }


                for(int i=0; i<ui->spinBox->value();i++)
                {
                    query2.prepare("SELECT id_matiere FROM matiere WHERE nom_matiere = :nom_matiere");
                    query2.bindValue(":nom_matiere",mater.at(i));
                    query2.exec();
                    query2.next();
                    if (!query2.first())
                    {
                        query2.prepare("INSERT INTO matiere (nom_matiere)  VALUES (:nom_matiere)");
                        query2.bindValue(":nom_matiere",mater.at(i));
                        query2.exec();

                        query2.prepare("SELECT id_matiere FROM matiere WHERE nom_matiere = :nom_matiere");
                        query2.bindValue(":nom_matiere",mater.at(i));
                        query2.exec();
                        query2.next();
                    }

                    int idMatiere = query2.value(0).toInt();
                    query2.prepare("INSERT INTO x_professeur_matiere (fk_id_professeur, fk_id_matiere)  VALUES (:fk_id_professeur, :fk_id_matiere)");
                    query2.bindValue(":fk_id_professeur",idProf);
                    query2.bindValue(":fk_id_matiere",idMatiere);
                    query2.exec();
                }

                query3.prepare("SELECT id_professeur FROM professeur WHERE email = :email");
                query3.bindValue(":email",ui->email_2->text());
                query3.exec();
                query3.next();
                for(int i = 0; i <classeProf.size(); i++)
                {
                    query2.prepare("INSERT INTO x_classe_professeur (fk_id_classe, fk_id_professeur) VALUES (:fk_id_classe, :fk_id_professeur)");
                    query2.bindValue(":fk_id_classe",classeProf.at(i));
                    query2.bindValue(":fk_id_professeur",query3.value(0).toInt());
                    query2.exec();
                }

            }

        }
        else
        {
            QMessageBox::warning(this,"Erreur", "Le format de l'email est incorrect.");
        }





}


//Permet d'inséré un administrateur dans la base de donnée.
void fenAdmin::validerAjAdmin()
{
    int validation=0;
    QString chaineACrypter(ui->email_3->text());
    QString chaineCryptee;
    int decalage(3);

    QString alphabet = "y6zue2xfc4wrjo0tv1s.b3kg1n5ih8ml@-qp7d9a";
    int pos;
    chaineACrypter = chaineACrypter.toLower();

    QTextStream flux(&chaineCryptee);
    for(int i(0); i < chaineACrypter.size(); i++)
    {
            pos = alphabet.indexOf(chaineACrypter.at(i));
            flux<<alphabet.at((pos + decalage)%40);
    }

    qDebug() << chaineCryptee;

        if(ui->email_3->hasAcceptableInput())
        {
            QString queryStr;
            QSqlQuery query2, query3, query4;

            query2.prepare("SELECT email FROM eleve WHERE email =:email");
            query2.bindValue(":email",ui->email_3->text());
            query2.exec();
            if (query2.first())
            {
                validation=1;
                QMessageBox::warning(this,"Erreur","Il existe déja un eleve avec cette email.");
            }
            query3.prepare("SELECT email FROM professeur WHERE email =:email");
            query3.bindValue(":email",ui->email_3->text());
            query3.exec();
            if (query3.first())
            {
                validation=1;
                QMessageBox::warning(this,"Erreur","Il existe déja un professeur avec cette email.");
            }
            query4.prepare("SELECT email FROM administrateur WHERE email =:email");
            query4.bindValue(":email",ui->email_3->text());
            query4.exec();
            if (query4.first())
            {
                validation=1;
                QMessageBox::warning(this,"Erreur","Il existe déja un administrateur avec cette email.");
            }

            if(validation==0)
            {
                if(ui->checkBox->isChecked())
                {
                    if(ui->email_3->text()!="")
                    {

                    query2.prepare("INSERT INTO administrateur (email) VALUES (:email)");

                    query2.bindValue(":email",ui->email_3->text());

                    query2.exec();

                    Smtp* smtp = new Smtp("SetYourEmailGmail", "SetYourPasswordGmail", "smtp.gmail.com", 465);
                    smtp->sendMail("SetYourEmailGmail", ui->email_3->text() , "Identifiant EPSI","Bonjour,\n Veuillez trouver ci-dessous votre identifiant pour vous connecter sur l'application School Board : \n\n  -    Identifiant : " + ui->email_3->text() + "\n  -    Mot de passe : Veuillez cliquer sur ce lien afin d'avoir votre mot de passe : \nhttps://school-board.000webhostapp.com/passwordalea.php?id=" + chaineCryptee + "\n\nCordialement, \n EPSI School");
                    QObject::connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));
                    QMessageBox::information(this,"Validation", "L'administrateur a bien été inséré.");
                    }
                    else
                    {
                        QMessageBox::warning(this,"Erreur", "Veuillez remplir tous les champs.");
                    }
                }
                else
                {
                    if(ui->email_3->text()!="" && ui->mdp_3->text()!="")
                    {
                    query2.prepare("INSERT INTO administrateur (email, password) VALUES (:email, :password)");

                    query2.bindValue(":email",ui->email_3->text());
                    query2.bindValue(":password",ui->mdp_3->text());

                    query2.exec();
                    QMessageBox::information(this,"Validation", "L'administrateur a bien été inséré.");
                    }
                    else
                    {
                        QMessageBox::warning(this,"Erreur", "Veuillez remplir tous les champs.");
                    }

                }

            }

        }
        else
        {
            QMessageBox::warning(this,"Erreur", "Le format de l'email incorrect.");
        }

}




void fenAdmin::hidePasswordAdmin()
{
    if (ui->checkBox->isChecked())
    {
        ui->lineEdit_108->hide();
        ui->mdp_3->hide();
    }
    else
    {
        ui->lineEdit_108->show();
        ui->mdp_3->show();
    }

}
void fenAdmin::hidePasswordEleve()
{
    if (ui->checkBox_2->isChecked())
    {
        ui->lineEdit_79->hide();
        ui->mdp->hide();
    }
    else
    {
        ui->lineEdit_79->show();
        ui->mdp->show();
    }
}
void fenAdmin::hidePasswordProf()
{
    if (ui->checkBox_3->isChecked())
    {
        ui->lineEdit_15->hide();
        ui->mdp_2->hide();
    }
    else
    {
        ui->lineEdit_15->show();
        ui->mdp_2->show();
    }
}
void fenAdmin::mailSent(QString status)
{
    if(status == "Message sent")
        QMessageBox::information(this, "Validation" ,"L'email a bien été envoyé" );
    else
        QMessageBox::information(this, "Validation" ,"L'email n'a pas pu être envoyé." );


}


