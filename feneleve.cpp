#include "feneleve.h"
#include "ui_feneleve.h"

#include "fenconnexion.h"

//Constructeur qui permet de déclarer les bouttons, mettre en couleurs les jours ou l'élève a cours, de remplir une liste déroulante et de définir des champs date, a la date de aujourd'hui.
fenEleve::fenEleve(QWidget *parent, int p_id) :
    QMainWindow(parent),
    ui(new Ui::fenEleve)
{
    ui->setupUi(this);
    this->m_id = p_id;

    connect(ui->EDTDay, SIGNAL(clicked()), this, SLOT(MoveToEDTDay()));
    connect(ui->EDTDate, SIGNAL(clicked()), this, SLOT(MoveToEDTPerso()));
    connect(ui->Note, SIGNAL(clicked()), this, SLOT(MoveToNote()));
    connect(ui->Deco, SIGNAL(clicked()), this, SLOT(retour()));
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(EDTperso()));
    connect(ui->calendar, SIGNAL(selectionChanged()), this, SLOT(selectDate()));
    connect(ui->valider, SIGNAL(clicked()), this, SLOT(selecNotesDecroissante()));
    connect(ui->valider_2, SIGNAL(clicked()), this, SLOT(selecNotesMatiere()));
    connect(ui->valider_3, SIGNAL(clicked()), this, SLOT(selecNotesDates()));

    selectDate();
    QDate date = QDate::currentDate();
    ui->dateEdit->setDate(date);
    ui->dateEdit_2->setDate(date);
    ui->dateEdit_3->setDate(date);
    ui->dateEdit_4->setDate(date);

    QSqlQuery fetchNotes;
    fetchNotes.prepare("SELECT nom_matiere FROM matiere");
    fetchNotes.exec();
    while(fetchNotes.next())
    {
        ui->matiere->addItem(fetchNotes.value(0).toString());
    }

    QSqlQuery query2;
        query2.prepare("SELECT fk_id_classe FROM eleve WHERE id_eleve = :id_eleve");
        query2.bindValue(":id_eleve",m_id);
        query2.exec();
        query2.next();
        int fkIdClasse = query2.value(0).toInt();
        query2.prepare("SELECT date_cours FROM cours WHERE fk_id_classe = :fk_id_classe");
        query2.bindValue(":fk_id_classe", fkIdClasse);
        query2.exec();
        while(query2.next())
        {
            QTextCharFormat currentDayHighlight;
            currentDayHighlight.setBackground(Qt::cyan);
            QDate today = query2.value(0).toDate();
            ui->calendar->setDateTextFormat(today, currentDayHighlight);
        }

        query2.prepare("SELECT nom ,prenom FROM eleve WHERE id_eleve = :id_eleve");
        query2.bindValue(":id_eleve", m_id);
        query2.exec();
        query2.next();
        ui->label_3->setText("Bienvenue : "+query2.value(0).toString()+ " "+query2.value(1).toString());
        ui->stackedWidget->setCurrentIndex(0);
}
//Destructeur.
fenEleve::~fenEleve()
{
    delete ui;
}
//Permet d'accéder a la page de l'EDT par plage de dates.
void fenEleve::MoveToEDTPerso()
{

    ui->stackedWidget->setCurrentIndex(2);
}
//Permet d'accéder a la page de 'EDT par jours.
void fenEleve::MoveToEDTDay()
{

    ui->stackedWidget->setCurrentIndex(0);
}
//Permet d'accéder a la page des notes.
void fenEleve::MoveToNote()
{

    ui->stackedWidget->setCurrentIndex(1);
}
//Permet de retourner sur la page de connexion.
void fenEleve::retour()
{
    FenConnexion *put = new FenConnexion(this);
    put->setFixedSize(800,600);
    put->show();
    this->hide();
}
//Permet d'afficher les notes de l'élève par ordre décroissante.
void fenEleve::selecNotesDecroissante()
{
    ui->textBrowser_5->clear();
    QSqlQuery fetchNotes, query3;
    fetchNotes.prepare("SELECT note, fk_id_matiere, date_note FROM notes WHERE fk_id_eleve = :fk_id_eleve ORDER BY date_note DESC");
    fetchNotes.bindValue(":fk_id_eleve", m_id);
    fetchNotes.exec();
    QString note = "<html><style type=\"text/css\"> \
            table { width:100%; background-color:#FFFFFF; border-collapse:collapse; border-width:1px; border-color:#000101; border-style:solid; color:#000101; } \
            table td, table th { border-width:1px;  border-color:#336600; border-style:solid; padding:3px; text-align:center;} \
            table thead { background-color:#CCFF99; } </style><div align=right><table align=center> <tr> <th>Note</th><th>Matiere</th><th>Date</th></tr>";
    while(fetchNotes.next())
    {
      query3.prepare("SELECT nom_matiere FROM matiere WHERE id_matiere = :id_matiere");
      query3.bindValue(":id_matiere", fetchNotes.value(1).toInt());
      query3.exec();
      query3.next();
      note = note + "<tr><td>"+fetchNotes.value(0).toString()+"</td><td>"+query3.value(0).toString()+"</td><td>"+fetchNotes.value(2).toString()+"</td></tr>";
      qDebug() << query3.value(0).toString();
    }
     note = note + "</table></html>",
     ui->textBrowser_5->setHtml(note);
}

//Permet d'afficher les notes de l'élève par matières.
void fenEleve::selecNotesMatiere()
{
     ui->textBrowser_8->clear();

    QSqlQuery fetchNotes, query3;
    query3.prepare("SELECT id_matiere FROM matiere WHERE nom_matiere = :nom_matiere");
    query3.bindValue(":nom_matiere", ui->matiere->currentText());
    query3.exec();
    query3.next();


    fetchNotes.prepare("SELECT note, date_note FROM notes WHERE fk_id_eleve = :fk_id_eleve AND fk_id_matiere = :fk_id_matiere");
    fetchNotes.bindValue(":fk_id_eleve", m_id);
    fetchNotes.bindValue(":fk_id_matiere",query3.value(0).toInt());
    fetchNotes.exec();
    QString note = "<html><style type=\"text/css\"> \
            table { width:100%; background-color:#FFFFFF; border-collapse:collapse; border-width:1px; border-color:#000101; border-style:solid; color:#000101; } \
            table td, table th { border-width:1px;  border-color:#336600; border-style:solid; padding:3px; text-align:center;} \
            table thead { background-color:#CCFF99; } </style><div align=right><table align=center> <tr> <th>Note</th><th>Matiere</th><th>Date</th></tr>";
    while(fetchNotes.next())
    {

      note = note + "<tr><td>"+fetchNotes.value(0).toString()+"</td><td>"+ui->matiere->currentText()+"</td><td>"+fetchNotes.value(1).toString()+"</td></tr>";
    }
     note = note + "</table></html>",
     ui->textBrowser_8->setHtml(note);
}

//Permet d'afficher les notes de l'élève entre 2 dates.
void fenEleve::selecNotesDates()
{
     ui->textBrowser_11->clear();
    qDebug() << "hel";
    QSqlQuery query6, query3;
    query6.prepare("SELECT note, fk_id_matiere, date_note FROM notes WHERE date_note >= :date_debut AND date_note <= :date_fin AND fk_id_eleve = :fk_id_eleve");
    query6.bindValue(":date_debut",ui->dateEdit_3->date().toString("yyyy-MM-dd"));
    query6.bindValue(":date_fin",ui->dateEdit_4->date().toString("yyyy-MM-dd"));
    query6.bindValue(":fk_id_eleve",m_id);
    query6.exec();
    QString note = "<html><style type=\"text/css\"> \
            table { width:100%; background-color:#FFFFFF; border-collapse:collapse; border-width:1px; border-color:#000101; border-style:solid; color:#000101; } \
            table td, table th { border-width:1px;  border-color:#336600; border-style:solid; padding:3px; text-align:center;} \
            table thead { background-color:#CCFF99; } </style><div align=right><table align=center> <tr> <th>Note</th><th>Matiere</th><th>Date</th></tr>";
    while(query6.next())
    {
       query3.prepare("SELECT nom_matiere FROM matiere WHERE id_matiere = :id_matiere");
       query3.bindValue(":id_matiere", query6.value(1).toInt());
       query3.exec();
       query3.next();
       note = note + "<tr><td>"+query6.value(0).toString()+"</td><td>"+query3.value(0).toString()+"</td><td>"+query6.value(2).toString()+"</td></tr>";
    }

    note = note + "</table></html>",
    ui->textBrowser_11->setHtml(note);
}

//Permet de supprimer tous les widget dans une zone de la page.
void fenEleve::clearWidgets(QLayout * layout)
{
   if (! layout)
      return;
   while (auto item = layout->takeAt(0)) {
      delete item->widget();
      clearWidgets(item->layout());
   }
}

//Permet d'afficher l'EDT entre 2 dates.
void fenEleve::selectDate()
{
    clearWidgets(ui->verticalLayout_2);
    QLayoutItem* item;
      while ( ( item = ui->verticalLayout_2->layout()->takeAt( 0 ) ) != NULL )
      {
          delete item->widget();
          delete item;
      }
    QSqlQuery query2, query6, query5, query4, query3;

    QString dateSelec = ui->calendar->selectedDate().toString("yyyy-MM-dd");


    query2.prepare("SELECT fk_id_classe FROM eleve WHERE id_eleve = :id_eleve");
    query2.bindValue(":id_eleve",m_id);
    query2.exec();
    query2.next();

    query6.prepare("SELECT heure_fin, heure_debut, fk_id_salle, fk_id_professeur,fk_id_matiere FROM cours WHERE date_cours = :date_cours AND fk_id_classe = :fk_id_classe");
    query6.bindValue(":date_cours",dateSelec);
    query6.bindValue(":fk_id_classe",query2.value(0).toInt());
    query6.exec();
    while(query6.next())
    {
        query5.prepare("SELECT nom_salle FROM salle WHERE id_salle = :id_salle");
        query5.bindValue(":id_salle",query6.value(2).toInt());
        query5.exec();
        query5.next();

        query4.prepare("SELECT nom FROM professeur WHERE id_professeur = :id_professeur");
        query4.bindValue(":id_professeur",query6.value(3).toInt());
        query4.exec();
        query4.next();

        query3.prepare("SELECT nom_matiere FROM matiere WHERE id_matiere = :id_matiere");
        query3.bindValue(":id_matiere",query6.value(4).toInt());
        query3.exec();
        query3.next();

        QHBoxLayout *hLayout = new QHBoxLayout;
        QTextBrowser *salleTB = new QTextBrowser;
        ui->verticalLayout_2->addLayout(hLayout);
        salleTB->setStyleSheet("QTextBrowser {background-color:rgb(20,30,38); color: white;}");
        salleTB->setHtml("<html><style type=\"text/css\"> \
                         table { width:100%; background-color:#000000; border-collapse:collapse; border-width:1px; border-color:#000000; border-style:solid; color:#FFFFFF; } \
                         table td, table th { border-width:1px;  border-color:#000000; border-style:solid; padding:3px; text-align:center;} \
                         table thead { background-color:#CCFF99; } \
                         </style><table align=center> <tr> <th>Matiere :"+query3.value(0).toString()+"</th><th>Salle :"+query5.value(0).toString()+"</th></tr><tr><th>Professeur :"+query4.value(0).toString()+"</th><th>Horaire :"+query6.value(1).toString()+"--->"+query6.value(0).toString()+"</th></tr></table></html>");
        hLayout->addWidget(salleTB);

    }
}
//Permet d'afficher l'EDT du jours quand on appuye sur une journé dans le calendrier
void fenEleve::EDTperso()
{
    int validation = 0;
    ui->textBrowser_4->clear();
    QSqlQuery query6, query5, query4, query3, query2;

    QString html = "<html><style type=\"text/css\"> \
            table { width:100%; background-color:#FFFFFF; border-collapse:collapse; border-width:1px; border-color:#000101; border-style:solid; color:#000101; } \
            table td, table th { border-width:1px;  border-color:#336600; border-style:solid; padding:3px; text-align:center;} \
            table thead { background-color:#CCFF99; } </style><table align=center> <tr> <th>Date</th><th>Heure de début</th><th>Heure de fin</th><th>Matiere</th><th>Enseignant</th><th>Salle</th></tr>";

    query2.prepare("SELECT fk_id_classe FROM eleve WHERE id_eleve = :id_eleve");
    query2.bindValue(":id_eleve",m_id);
    query2.exec();
    query2.next();

    query6.prepare("SELECT date_cours, heure_fin, heure_debut, fk_id_salle, fk_id_professeur,fk_id_matiere FROM cours WHERE date_cours >= :date_debut AND date_cours <= :date_fin AND fk_id_classe = :fk_id_classe");
    query6.bindValue(":date_debut",ui->dateEdit->date().toString("yyyy-MM-dd"));
    query6.bindValue(":date_fin",ui->dateEdit_2->date().toString("yyyy-MM-dd"));
    query6.bindValue(":fk_id_classe",query2.value(0).toInt());
    query6.exec();

    ui->textBrowser_4->clear();
    while(query6.next())
    {
        validation=1;
        query5.prepare("SELECT nom_salle FROM salle WHERE id_salle = :id_salle");
        query5.bindValue(":id_salle",query6.value(3).toInt());
        query5.exec();
        query5.next();

        query4.prepare("SELECT nom FROM professeur WHERE id_professeur = :id_professeur");
        query4.bindValue(":id_professeur",query6.value(4).toInt());
        query4.exec();
        query4.next();

        query3.prepare("SELECT nom_matiere FROM matiere WHERE id_matiere = :id_matiere");
        query3.bindValue(":id_matiere",query6.value(5).toInt());
        query3.exec();
        query3.next();

        html = html + "<tr><td>"+query6.value(0).toString()+"</td><td>"+query6.value(2).toString()+"</td><td>"+query6.value(1).toString()+"</td><td>"+query3.value(0).toString()+"</td><td>"+query4.value(0).toString()+"</td><td>"+query5.value(0).toString()+"</td></tr>";
    }
    if(validation==0)
    {
        QMessageBox::warning(this, "Erreur", "Il n'y a pas de cours entres ces dates.");
    }

   html = html +"</table></html>";
   ui->textBrowser_4->setHtml(html);



}


