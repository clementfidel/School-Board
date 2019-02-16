#include "fenprof.h"
#include "ui_fenprof.h"
#include <QPalette>
#include <QScrollArea>
#include <QLabel>

//Constructeur dans lequel on déclare les différents bouttons et nous remplissont les listes déroulantes.
fenProf::fenProf(QWidget *parent, int p_id) :
    QMainWindow(parent),
    ui(new Ui::fenProf)
{

    ui->setupUi(this);
    this->m_id = p_id;
    ui->selectionNote->setFixedWidth(30);
    QDate date = QDate::currentDate();
    ui->dateEdit->setDate(date);
    ui->dateEdit_2->setDate(date);
    ui->dateAbs->setDate(date);
    connect(ui->EDTDay, SIGNAL(clicked()), this, SLOT(MoveToEDTDay()));
    connect(ui->EDTDate, SIGNAL(clicked()), this, SLOT(MoveToEDTPerso()));
    connect(ui->Note, SIGNAL(clicked()), this, SLOT(MoveToNote()));
    connect(ui->Abs, SIGNAL(clicked()), this, SLOT(MoveToAbs()));

    connect(ui->calendarWidget, SIGNAL(selectionChanged()), this, SLOT(selectDate()));
    connect(ui->selectionner, SIGNAL(clicked()), this, SLOT(ajoutEleve()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(ajoutAbs()));
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(ajoutNote()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(EDTperso()));
    connect(ui->Deco, SIGNAL(clicked()), this, SLOT(retour()));
    QSqlQuery cours3;
    QSqlQuery cours4;
    cours3.prepare("SELECT fk_id_classe FROM x_classe_professeur WHERE fk_id_professeur = :fk_id_professeur");
    cours3.bindValue(":fk_id_professeur", m_id);
    cours3.exec();
    while(cours3.next())
    {
        cours4.prepare("SELECT nom_classe FROM classe WHERE id_classe = :id_classe");
        cours4.bindValue(":id_classe",cours3.value(0).toInt());
        cours4.exec();
        while(cours4.next())
        {
            ui->selectionClasse->addItem(cours4.value(0).toString());
        }
    }





    cours4.prepare("SELECT fk_id_matiere FROM x_professeur_matiere WHERE fk_id_professeur = :fk_id_professeur");
    cours4.bindValue(":fk_id_professeur", m_id);
    cours4.exec();
    while(cours4.next())
    {
        cours3.prepare("SELECT nom_matiere FROM matiere WHERE id_matiere = :id_matiere");
        cours3.bindValue(":id_matiere",cours4.value(0).toInt());
        cours3.exec();
        while(cours3.next())
        {

            ui->matiereNote->addItem(cours3.value(0).toString());
            ui->matiere->addItem(cours3.value(0).toString());
        }
    }








    QSqlQuery query2;

        query2.prepare("SELECT date_cours FROM cours WHERE fk_id_professeur = :fk_id_professeur");
        query2.bindValue(":fk_id_professeur", m_id);
        query2.exec();
        while(query2.next())
        {

            QTextCharFormat currentDayHighlight;
            currentDayHighlight.setBackground(Qt::cyan);
            QDate today = query2.value(0).toDate();
            ui->calendarWidget->setDateTextFormat(today, currentDayHighlight);
        }

        query2.prepare("SELECT nom, prenom FROM professeur WHERE id_professeur = :id_professeur");
        query2.bindValue(":id_professeur", m_id);
        query2.exec();
        query2.next();
        ui->label_23->setText("Bienvenue : "+query2.value(0).toString()+ " "+query2.value(1).toString());
        ui->stackedWidget->setCurrentIndex(0);
        ui->pushButton->hide();
}
//Destructeur
fenProf::~fenProf()
{
    delete ui;
}
//Permet d'accéder a la page de l'EDT avec une plage de dates.
void fenProf::MoveToEDTPerso()
{
    ui->stackedWidget->setCurrentIndex(2);
}
//Permet d'accéder a la page de l'EDT par jours.
void fenProf::MoveToEDTDay()
{
    ui->stackedWidget->setCurrentIndex(0);
}
//Permet d'accéder a la page pour inséré des notes.
void fenProf::MoveToNote()
{
    ui->stackedWidget->setCurrentIndex(1);
}
//Permet d'accéder a la page pour inséré des absences.
void fenProf::MoveToAbs()
{

    ui->stackedWidget->setCurrentIndex(3);
}
//Permet d'accéder a la page de connexion.
void fenProf::retour()
{
    FenConnexion *put = new FenConnexion(this);
    put->setFixedSize(800,600);
    put->show();
    this->hide();
}
//Permet d'ajouter d'inséré les notes dans la base de donnée.
void fenProf::ajoutNote()
{
    QWidget *WNom3 = new QWidget;
    int val=0;
    for(int i = 1; i < nbLigne+1; i++)
    {
        QLayoutItem *item3 = ui->gridLayout_2->itemAtPosition(i,1);


        WNom3= item3->widget();

        QString note2 = ((QLineEdit*)WNom3)->text();

        if(note2.toInt()>ui->selectionNote->text().toInt() || note2.toInt()<0)
       {
            val=1;
            QMessageBox::warning(this,"Erreur","Veuillez entrer des notes inférieurs au maximum spécifié.");
       }


    }
      if(val!=1)
      {

        for(int i = 1; i < nbLigne+1; i++)
        {

            QLayoutItem *item = ui->gridLayout_2->itemAtPosition(i,2);
            QWidget *WNom = item->widget();
            QString comm = ((QLineEdit*)WNom)->text();

            QLayoutItem *item2 = ui->gridLayout_2->itemAtPosition(i,1);
            QWidget *WNom2 = item2->widget();
            QString note = ((QLineEdit*)WNom2)->text();
            qDebug() << comm;
            qDebug() << note;

            if (!note.isEmpty())
            {
                qDebug() << ui->selectionNote->text();
                note = note + "/"+ ui->selectionNote->text();
                QSqlQuery query2;
                qDebug()<<idEleve.at(i-1);

                query2.prepare("INSERT INTO notes (note, comm,fk_id_eleve, fk_id_prof,fk_id_classe, date_note, fk_id_matiere) VALUES (:note, :comm, :fk_id_eleve, :fk_id_prof, :fk_id_classe, :date_note, :fk_id_matiere)");

                query2.bindValue(":note",note);
                query2.bindValue(":comm",comm);
                query2.bindValue(":fk_id_eleve",idEleve.at(i-1));
                query2.bindValue(":fk_id_prof",m_id);
                query2.bindValue(":fk_id_classe",idClasse);
                query2.bindValue(":fk_id_matiere",idMatiere);
                query2.bindValue(":date_note",ui->dateEdit_3->date());
                query2.exec();

            }
        }

      }

}
//Permet d'ajouter les absence dans la base de donnée.
void fenProf::ajoutAbs()
{
    if (ui->nom->text()!="" || ui->prenom->text()!="")
    {
        if(ui->heure_debut->time()<(ui->heure_fin->time()))
        {
            QSqlQuery cours4, cours5, query2, query6;
            cours4.prepare("SELECT nom, prenom, cne FROM eleve WHERE nom = :nom AND prenom = :prenom");
            cours4.bindValue(":nom", ui->nom->text());
            cours4.bindValue(":prenom", ui->prenom->text());
            cours4.exec();
            cours4.next();
            if(cours4.first())
            {
                cours5.prepare("SELECT id_matiere FROM matiere WHERE nom_matiere = :nom_matiere");
                cours5.bindValue(":nom_matiere", ui->matiere->currentText());
                cours5.exec();
                cours5.next();

                query6.prepare("SELECT id_absence FROM absence WHERE heure_debut = :heure_debut AND heure_fin = :heure_fin AND date = :date AND CNE = :CNE");
                query6.bindValue(":heure_debut",ui->heure_debut->time());
                query6.bindValue(":heure_fin",ui->heure_fin->time());
                query6.bindValue(":date",ui->dateAbs->date());
                query6.bindValue(":CNE",cours4.value(2).toInt());
                query6.exec();
                if(!query6.first())
                {

                    query2.prepare("INSERT INTO absence (fk_id_matiere, heure_debut, heure_fin, date, CNE)VALUES (:fk_id_matiere, :heure_debut, :heure_fin, :date, :CNE)");


                        query2.bindValue(":fk_id_matiere",cours5.value(0).toInt());

                        query2.bindValue(":heure_debut",ui->heure_debut->time());
                        query2.bindValue(":heure_fin",ui->heure_fin->time());
                        query2.bindValue(":date",ui->dateAbs->date());
                        query2.bindValue(":CNE",cours4.value(2).toInt());
                        query2.exec();
                        QMessageBox::information(this,"Validation","L'absence a bien été inséré.");
                }
                else
                {
                    QMessageBox::warning(this,"Erreur","Il existe déjà une absence avec ces informations.");
                }

            }
            else
            {
                QMessageBox::warning(this,"Erreur","Il n'existe pas d'élève avec ce nom et prénom.");
            }
        }
        else
        {
            QMessageBox::warning(this,"Erreur","Veuillez inséré une date de début antérieur a la date de fin.");
        }
    }
    else
    {
        QMessageBox::warning(this,"Erreur","Veuillez préalablement inséré le nom et/ou le prénom.");
    }


}
//Permet de crée dynamiquement les champs pour inséré les notes de toutes une classe.
void fenProf::ajoutEleve()
{
    int val=0;
    ui->scrollAreaWidgetContents->hide();
    ui->pushButton->hide();
    if(ui->selectionNote->text()!="")
    {
        QSqlQuery cours3,cours4;
        cours3.prepare("SELECT id_matiere FROM matiere WHERE nom_matiere = :nom_matiere");
        cours3.bindValue(":nom_matiere",ui->matiereNote->currentText());
        cours3.exec();
        cours3.next();
        idMatiere=cours3.value(0).toInt();
        cours3.prepare("SELECT id_classe FROM classe WHERE nom_classe = :nom_classe");
        cours3.bindValue(":nom_classe",ui->selectionClasse->currentText());
        cours3.exec();
        cours3.next();
        idClasse=cours3.value(0).toInt();
        cours4.prepare("SELECT nom, prenom, id_eleve FROM eleve WHERE fk_id_classe = :fk_id_classe");
        cours4.bindValue(":fk_id_classe",cours3.value(0).toInt());
        cours4.exec();
        int x = 1 ;
        clearWidgets(ui->gridLayout_2);
        QLabel *eleve = new QLabel;
        QLabel *notee = new QLabel;
        QLabel *commentaire = new QLabel;

        eleve->setText("<b>Eleve</b>");
        notee->setText("<b>Note</b>");
        commentaire->setText("<b>Commentaire</b>");



        ui->gridLayout_2->addWidget(eleve,0,0);
        ui->gridLayout_2->addWidget(notee,0,1);
        ui->gridLayout_2->addWidget(commentaire,0,2);

        nbLigne=0;
        while(cours4.next())
        {
            ui->scrollAreaWidgetContents->show();
            ui->pushButton->show();
            QLineEdit *note = new QLineEdit;
            QLineEdit *comm = new QLineEdit;
            QValidator *validatorInt = new QIntValidator(this);
             note->setValidator(validatorInt);
             note->setFixedWidth(50);
            nbLigne++;
            idEleve.append(cours4.value(2).toString());
            comm->setFixedWidth(300);
            comm->setMaxLength(300);

            QLabel *nomEleve = new QLabel;
            nomEleve->setText( cours4.value(0).toString() +"  "+ cours4.value(1).toString());




            note->setStyleSheet("QLineEdit {color:black; border: 1px solid black; }");
            note->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
            comm->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
            comm->setStyleSheet("QLineEdit {color:black; border: 1px solid black;}");
            ui->scrollArea->setWidgetResizable(true);
            ui->gridLayout_2->addWidget(nomEleve, x , 0);
           ui->gridLayout_2->addWidget(note, x ,1);
           ui->gridLayout_2->addWidget(comm, x ,2);
             x++;


        }


    }
    else
    {
        val=1;
        QMessageBox::warning(this,"Erreur", "Veuillez remplir préalablement le champs  \"Note sur :\".");
    }
    if(val==0 && ui->pushButton->isHidden())
    {
        QMessageBox::warning(this,"Erreur", "Il n'y a pas d'élève dans cette classe.");
    }

}
//Permet de supprimer tous les widget dans une zone sur la page.
void fenProf::clearWidgets(QLayout * layout) {
   if (! layout)

      return;
   while (auto item = layout->takeAt(0)) {
      delete item->widget();
      clearWidgets(item->layout());
   }
}

//Permet d'afficher tous les cours du professeur entres 2 dates.
void fenProf::selectDate()
{
    QString dateSelec = ui->calendarWidget->selectedDate().toString("yyyy-MM-dd");

    clearWidgets(ui->verticalLayout);
    QLayoutItem* item;
      while ( ( item = ui->verticalLayout->layout()->takeAt( 0 ) ) != NULL )
      {
          delete item->widget();
          delete item;
      }
    QSqlQuery query2, query6, query5, query4, query3;


    query6.prepare("SELECT heure_fin, heure_debut, fk_id_salle, fk_id_classe, fk_id_matiere FROM cours WHERE date_cours = :date_cours AND fk_id_professeur = :fk_id_professeur");
    query6.bindValue(":date_cours",dateSelec);
    query6.bindValue(":fk_id_professeur",m_id);
    query6.exec();
    while(query6.next())
    {
        query5.prepare("SELECT nom_salle FROM salle WHERE id_salle = :id_salle");
        query5.bindValue(":id_salle",query6.value(2).toInt());
        query5.exec();
        query5.next();

        query4.prepare("SELECT nom_classe FROM classe WHERE id_classe = :id_classe");
        query4.bindValue(":id_classe",query6.value(3).toInt());
        query4.exec();
        query4.next();

        query3.prepare("SELECT nom_matiere FROM matiere WHERE id_matiere = :id_matiere");
        query3.bindValue(":id_matiere",query6.value(4).toInt());
        query3.exec();
        query3.next();

        QHBoxLayout *hLayout = new QHBoxLayout;
        QTextBrowser *salleTB = new QTextBrowser;
        ui->verticalLayout->addLayout(hLayout);
        salleTB->setHtml("<html><style type=\"text/css\"> \
                         table { width:100%; background-color:#000000; border-collapse:collapse; border-width:1px; border-color:#000000; border-style:solid; color:#FFFFFF; } \
                         table td, table th { border-width:1px;  border-color:#000000; border-style:solid; padding:3px; text-align:center;} \
                         table thead { background-color:#CCFF99; } \
                         </style><table align=center> <tr> <th>Matiere :"+query3.value(0).toString()+"</th><th>Salle :"+query5.value(0).toString()+"</th></tr><tr><th>Classe :"+query4.value(0).toString()+"</th><th>Horaire :"+query6.value(1).toString()+"--->"+query6.value(0).toString()+"</th></tr></table></html>");
        hLayout->addWidget(salleTB);

    }




}

//Permet d'afficher l'EDT du professeur sur un jours sélectionner sur le calendrier.
void fenProf::EDTperso()
{
    ui->textBrowser_4->clear();
    QSqlQuery query6, query5, query4, query3;

    QString html = "<html><style type=\"text/css\"> \
            table { width:100%; background-color:#FFFFFF; border-collapse:collapse; border-width:1px; border-color:#000101; border-style:solid; color:#000101; } \
            table td, table th { border-width:1px;  border-color:#336600; border-style:solid; padding:3px;  text-align:center;} \
            table thead { background-color:#CCFF99; } </style><table align=center> <tr> <th>Date</th><th>Heure de début</th><th>Heure de fin</th><th>Matiere</th><th>Classe</th><th>Salle</th></tr>";


    query6.prepare("SELECT date_cours, heure_fin, heure_debut, fk_id_salle, fk_id_classe,fk_id_matiere FROM cours WHERE date_cours >= :date_debut AND date_cours <= :date_fin AND fk_id_professeur = :fk_id_professeur");
    query6.bindValue(":date_debut",ui->dateEdit->date().toString("yyyy-MM-dd"));
    query6.bindValue(":date_fin",ui->dateEdit_2->date().toString("yyyy-MM-dd"));
    query6.bindValue(":fk_id_professeur",m_id);
    query6.exec();
    while(query6.next())
    {
        query5.prepare("SELECT nom_salle FROM salle WHERE id_salle = :id_salle");
        query5.bindValue(":id_salle",query6.value(3).toInt());
        query5.exec();
        query5.next();

        query4.prepare("SELECT nom_classe FROM classe WHERE id_classe = :id_classe");
        query4.bindValue(":id_classe",query6.value(4).toInt());
        query4.exec();
        query4.next();

        query3.prepare("SELECT nom_matiere FROM matiere WHERE id_matiere = :id_matiere");
        query3.bindValue(":id_matiere",query6.value(5).toInt());
        query3.exec();
        query3.next();

        html = html + "<tr><td>"+query6.value(0).toString()+"</td><td>"+query6.value(2).toString()+"</td><td>"+query6.value(1).toString()+"</td><td>"+query3.value(0).toString()+"</td><td>"+query4.value(0).toString()+"</td><td>"+query5.value(0).toString()+"</td></tr>";
    }

   html = html +"</table></html>";

   if(query6.first())
      ui->textBrowser_4->setHtml(html);
      else
          ui->textBrowser->setHtml("");

}

