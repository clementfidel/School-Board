#include "ui_fenadmin.h"
#include "fenadmin.h"

//Permet de cacher toutes les informations inutile lorsqu'on arrive sur la page.
void fenAdmin::fenModifUserInit()
{
    QValidator *validatorInt = new QIntValidator(this);
    ui->email_5->hide();
    ui->password->hide();
    ui->nom_3->hide();
    ui->prenom_3->hide();
    ui->numeroTel->hide();
    ui->cne_2->hide();
    ui->cin_2->hide();
    ui->dateNaissance->hide();
    ui->numRue_2->hide();
    ui->nomRue_2->hide();
    ui->codePostal_2->hide();
    ui->ville->hide();
    ui->pushButton_2->hide();
    ui->lineEdit_149->hide();
    ui->lineEdit_151->hide();
    ui->lineEdit_153->hide();
    ui->lineEdit_155->hide();
    ui->lineEdit_156->hide();
    ui->lineEdit_157->hide();
    ui->lineEdit_160->hide();
    ui->lineEdit_162->hide();
    ui->lineEdit_164->hide();
    ui->lineEdit_165->hide();
    ui->lineEdit_166->hide();
    ui->lineEdit_167->hide();
    ui->lineEdit_77->hide();
    ui->classe_5->hide();
    ui->lineEdit_85->hide();

    ui->ajouter_2->hide();
    ui->vider->hide();
    ui->textBrowser_2->hide();
    ui->comboBox_3->hide();

    ui->validerModifUser->hide();

    ui->cne_2->setValidator(validatorInt);
    ui->cin_2->setValidator(validatorInt);
    ui->numRue_2->setValidator(validatorInt);
    ui->codePostal_2->setValidator(validatorInt);
    ui->numeroTel->setValidator(validatorInt);


    QRegularExpression rx("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b", QRegularExpression::CaseInsensitiveOption);
    ui->email_5->setValidator(new QRegularExpressionValidator(rx, this));







}





//Permet d'afficher les informations de la personne selon le type d(utilisateur (administrateur, professeur ou élève).
void fenAdmin::findUser()
{
    ui->email_5->hide();
    ui->password->hide();
    ui->nom_3->hide();
    ui->prenom_3->hide();
    ui->numeroTel->hide();
    ui->cne_2->hide();
    ui->cin_2->hide();
    ui->dateNaissance->hide();
    ui->numRue_2->hide();
    ui->nomRue_2->hide();
    ui->codePostal_2->hide();
    ui->ville->hide();
    ui->validerModifUser->hide();
    ui->classe_5->hide();
    ui->lineEdit_149->hide();
    ui->lineEdit_151->hide();
    ui->lineEdit_153->hide();
    ui->lineEdit_155->hide();
    ui->lineEdit_156->hide();
    ui->lineEdit_157->hide();
    ui->lineEdit_160->hide();
    ui->lineEdit_162->hide();
    ui->lineEdit_164->hide();
    ui->lineEdit_165->hide();
    ui->lineEdit_166->hide();
    ui->lineEdit_167->hide();
    ui->lineEdit_77->hide();
    ui->lineEdit_85->hide();


    ui->ajouter_2->hide();
    ui->vider->hide();
    ui->textBrowser_2->hide();
    ui->comboBox_3->hide();


    ui->nom_3->clear();
    ui->prenom_3->clear();
    ui->numeroTel->clear();
    ui->email_5->clear();
    ui->password->clear();
    ui->cne_2->clear();
    ui->cin_2->clear();
    ui->dateNaissance->clear();
    ui->nomRue_2->clear();
    ui->numRue_2->clear();
    ui->codePostal_2->clear();
    ui->ville->clear();
    ui->classe_5->clear();


    QSqlQuery query3, query4;
    query3.prepare("SELECT * FROM eleve WHERE email = :email");
    query3.bindValue(":email",ui->email_4->text());
    query3.exec();


    if(query3.first())
    {
        a=1;

        query3.prepare("SELECT id_eleve FROM eleve WHERE email = :email");
        query3.bindValue(":email",ui->email_4->text());
        query3.exec();
        query3.next();
        id_eleve = query3.value(0).toInt();

          QSqlQuery queryDate;
          queryDate.prepare("SELECT date_naissance FROM eleve WHERE id_eleve = :id_eleve");
          queryDate.bindValue(":id_eleve",id_eleve);
          queryDate.exec();
          queryDate.next();
          QString dateS = queryDate.value(0).toString();


          int year, month, day;

          QString yearS = dateS.mid(0,4);
          QString monthS = dateS.mid(5,2);
          QString dayS = dateS.mid(8,2);

          year = yearS.toInt();
          month = monthS.toInt();
          day = dayS.toInt();

          QDate dateFinal(year, month, day);


        query3.prepare("SELECT cne, cin, nom, prenom, password, date_naissance, num_tel, num_rue, code_postal, ville, nom_rue, fk_id_classe FROM eleve WHERE email = :email");
        query3.bindValue(":email",ui->email_4->text());
        query3.exec();
        query3.next();

        query4.prepare("SELECT nom_classe FROM classe");
        query4.exec();
        while(query4.next())
        {
            ui->classe_5->addItem(query4.value(0).toString());
            ui->comboBox_3->addItem(query4.value(0).toString());
        }

        query4.prepare("SELECT nom_classe FROM classe WHERE id_classe = :id_classe");
        query4.bindValue(":id_classe", query3.value(11).toInt());
        query4.exec();
        query4.next();
        ui->classe_5->setCurrentText(query4.value(0).toString());






        ui->nom_3->show();
        ui->prenom_3->show();
        ui->numeroTel->show();
        ui->email_5->show();
        ui->password->show();
        ui->cne_2->show();
        ui->cin_2->show();
        ui->dateNaissance->show();
        ui->numRue_2->show();
        ui->nomRue_2->show();
        ui->codePostal_2->show();
        ui->ville->show();
        ui->validerModifUser->show();
        ui->classe_5->show();


        ui->lineEdit_149->show();
        ui->lineEdit_151->show();
        ui->lineEdit_153->show();
        ui->lineEdit_155->show();
        ui->lineEdit_156->show();
        ui->lineEdit_157->show();
        ui->lineEdit_160->show();
        ui->lineEdit_162->show();
        ui->lineEdit_164->show();
        ui->lineEdit_165->show();
        ui->lineEdit_166->show();
        ui->lineEdit_167->show();
        ui->lineEdit_77->show();




        ui->email_5->insert(ui->email_4->text());
        ui->cne_2->insert(query3.value(0).toString());
        ui->cin_2->insert(query3.value(1).toString());
        ui->nom_3->insert(query3.value(2).toString());
        ui->prenom_3->insert(query3.value(3).toString());
        ui->password->insert(query3.value(4).toString());
        ui->dateNaissance->setDate(dateFinal);
        ui->numeroTel->insert(query3.value(6).toString());
        ui->numRue_2->insert(query3.value(7).toString());
        ui->codePostal_2->insert(query3.value(8).toString());
        ui->ville->insert(query3.value(9).toString());
        ui->nomRue_2->insert(query3.value(10).toString());


    }
    else
    {

        query3.prepare("SELECT id_professeur FROM professeur WHERE email = :email");
        query3.bindValue(":email",ui->email_4->text());
        query3.exec();


        if(query3.first())
        {
            a=2;
            query4.prepare("SELECT nom_classe FROM classe");
            query4.exec();
            while(query4.next())
            {
                ui->comboBox_3->addItem(query4.value(0).toString());
            }
            query3.prepare("SELECT id_professeur FROM professeur WHERE email = :email");
            query3.bindValue(":email",ui->email_4->text());
            query3.exec();
            query3.next();
            id_prof = query3.value(0).toInt();

            QString classe;
            query3.prepare("SELECT fk_id_classe FROM x_classe_professeur WHERE fk_id_professeur = :fk_id_professeur");
            query3.bindValue(":fk_id_professeur",query3.value(0).toInt());
            query3.exec();
            query3.prepare("SELECT nom_classe FROM classe WHERE id_classe = :id_classe");
            query3.bindValue(":id_classe",query3.value(0).toInt());
            query3.exec();
            while(query3.next())
            {
                classe = classe +"- "+ query3.value(0).toString()+"<br>";
            }
            ui->textBrowser_2->setHtml(classe);




           query3.prepare("SELECT nom, prenom, numero_tel, password FROM professeur WHERE email = :email");
           query3.bindValue(":email",ui->email_4->text());
           query3.exec();
           query3.next();




           ui->nom_3->show();
           ui->prenom_3->show();
           ui->numeroTel->show();
           ui->email_5->show();
           ui->password->show();
           ui->validerModifUser->show();
           ui->ajouter_2->show();
           ui->vider->show();
           ui->textBrowser_2->show();
           ui->comboBox_3->show();

           ui->lineEdit_149->show();
           ui->lineEdit_151->show();
           ui->lineEdit_153->show();
           ui->lineEdit_155->show();
           ui->lineEdit_156->show();
           ui->lineEdit_85->show();



           ui->email_5->insert(ui->email_4->text());
           ui->password->insert(query3.value(3).toString());
           ui->nom_3->insert(query3.value(0).toString());
           ui->prenom_3->insert(query3.value(1).toString());
           ui->numeroTel->insert(query3.value(2).toString());


        }
        else
        {

            query3.prepare("SELECT * FROM administrateur WHERE email = :email");
            query3.bindValue(":email",ui->email_4->text());
            query3.exec();


            if(query3.first())
            {
                a=3;

                query3.prepare("SELECT id_administrateur FROM administrateur WHERE email = :email");
                query3.bindValue(":email",ui->email_4->text());
                query3.exec();
                query3.next();
                id_admin = query3.value(0).toInt();

                query3.prepare("SELECT password FROM administrateur WHERE email = :email");
                query3.bindValue(":email",ui->email_4->text());
                query3.exec();
                query3.next();
                ui->validerModifUser->show();
                ui->email_5->show();
                ui->password->show();
                ui->email_5->insert(ui->email_4->text());
                ui->password->insert(query3.value(0).toString());

                ui->lineEdit_149->show();
                ui->lineEdit_151->show();


            }
            else
            {
                  QMessageBox::warning(this,"Erreur", "Email inconu");


            }
        }
    }
}

//Permet de modifié l'uilisateur préalablement séléctionner en fonction du type d'utilisateur.
void fenAdmin::modifUser()
{
    int validation=0;
    QSqlQuery query2, query3, query4;
    if(ui->email_4->text()!=ui->email_5->text())
    {
        query2.prepare("SELECT email FROM eleve WHERE email =:email");
        query2.bindValue(":email",ui->email_5->text());
        query2.exec();
        if (query2.first())
        {
            validation=1;
            QMessageBox::warning(this,"Erreur","Il existe déja un eleve avec cette email.");
        }
        query3.prepare("SELECT email FROM professeur WHERE email =:email");
        query3.bindValue(":email",ui->email_5->text());
        query3.exec();
        if (query3.first())
        {
            validation=1;
            QMessageBox::warning(this,"Erreur","Il existe déja un professeur avec cette email.");
        }
        query4.prepare("SELECT email FROM administrateur WHERE email =:email");
        query4.bindValue(":email",ui->email_5->text());
        query4.exec();
        if (query4.first())
        {
            validation=1;
            QMessageBox::warning(this,"Erreur","Il existe déja un administrateur avec cette email.");
        }
    }

    if(a==1)
    {

        if(ui->prenom_3->text()!="" && ui->nom_3->text()!="" && ui->password->text()!="" && ui->cne_2->text()!="" && ui->cin_2->text()!="" && ui->numeroTel->text()!="" && ui->numRue_2->text()!="" && ui->nomRue_2->text()!="" && ui->codePostal_2->text()!="" && ui->ville->text()!="" && ui->email_5->text()!="")
        {
            if(validation==0)
            {
                query4.prepare("SELECT id_classe FROM classe WHERE nom_classe =:nom_classe");
                query4.bindValue(":nom_classe",ui->classe_5->currentText());
                query4.exec();
                query4.next();

                query3.prepare("UPDATE eleve SET nom = :nom, prenom = :prenom, num_tel = :num_tel, password = :password, email = :email, cne = :cne, cin = :cin, date_naissance = :date_naissance, num_rue = :num_rue, nom_rue = :nom_rue, code_postal = :code_postal, ville = :ville,  fk_id_classe = :fk_id_classe WHERE id_eleve = :id_eleve");
                query3.bindValue(":id_eleve",id_eleve);
                query3.bindValue(":email",ui->email_5->text());
                query3.bindValue(":password",ui->password->text());
                query3.bindValue(":nom",ui->nom_3->text());
                query3.bindValue(":prenom",ui->prenom_3->text());
                query3.bindValue(":num_tel",ui->numeroTel->text());
                query3.bindValue(":cne",ui->cne_2->text());
                query3.bindValue(":cin",ui->cin_2->text());
                query3.bindValue(":date_naissance",ui->dateNaissance->text());
                query3.bindValue(":num_rue",ui->numRue_2->text());
                query3.bindValue(":nom_rue",ui->nomRue_2->text());
                query3.bindValue(":code_postal",ui->codePostal_2->text());
                query3.bindValue(":ville",ui->ville->text());
                query3.bindValue(":fk_id_classe",query4.value(0).toInt());
                query3.exec();
            }
        }
        else
        {
            QMessageBox::warning(this,"Erreur", "Veuillez remplirs tous les champs.");
        }


    }
    else if(a==2)
    {

        if(ui->prenom_3->text()!="" && ui->nom_3->text()!="" && ui->password->text()!="" && ui->numeroTel->text()!="" && ui->email_5->text()!="")
        {
            if(validation==0)
            {
                query3.prepare("UPDATE professeur SET nom = :nom, prenom = :prenom, numero_tel = :numero_tel, password = :password, email = :email WHERE id_professeur = :id_professeur");
                query3.bindValue(":id_professeur",id_prof);
                query3.bindValue(":email",ui->email_5->text());
                query3.bindValue(":password",ui->password->text());
                query3.bindValue(":nom",ui->nom_3->text());
                query3.bindValue(":prenom",ui->prenom_3->text());
                query3.bindValue(":numero_tel",ui->numeroTel->text());
                query3.exec();
            }

        }
        else
        {
            QMessageBox::warning(this,"Erreur", "Veuillez remplirs tous les champs.");
        }

    }
    else if(a==3)
    {
        if( ui->password->text()!="" && ui->email_5->text()!="")
        {
            if(validation==0)
            {
                query3.prepare("UPDATE administrateur SET email = :email, password = :password WHERE id_administrateur = :id_administrateur");
                query3.bindValue(":id_administrateur",id_admin);
                query3.bindValue(":email",ui->email_5->text());
                query3.bindValue(":password",ui->password->text());
                query3.exec();
            }
        }
        else
        {
            QMessageBox::warning(this,"Erreur", "Veuillez remplirs tous les champs.");
        }

    }
}

void fenAdmin::ajouterClasseModifProf()
{

}

void fenAdmin::viderClasseModifProf()
{
    ui->textBrowser_2->clear();
}
