
#include "ui_fenadmin.h"
#include "fenadmin.h"

//Permet de remplir la liste déroulante avec les noms des différentes classes.
void fenAdmin::bulletinInit()
{
    QSqlQuery ids;
    ids.prepare("SELECT nom_classe FROM classe");
    ids.exec();
    while(ids.next())
    {
        ui->comboBox->addItem(ids.value(0).toString());
    }
}



//Permet de retourner la date d'aujourd'hui au format dd.MM.yyyy.
QString fenAdmin::currDate()
{
    QDate date = QDate::currentDate();
    return date.toString("dd.MM.yyyy");
}


//Permet de récuperé l'ID de l'élève et d'éxécuter la fonction pdf, en fonction du nom qui est affiché dans la liste déroulante.
void fenAdmin::modifEleve()
{
    QSqlQuery ids2;
    ids2.prepare("SELECT id_eleve FROM eleve WHERE nom = :nom");
    ids2.bindValue(":nom",ui->comboBox_2->currentText());
    ids2.exec();
    ids2.next();
    m_id=ids2.value(0).toInt();
    fenAdmin::pdf(m_id);
}


//Permet de remplir la liste déroulante des élèves avec leurs noms en fonction de la classe choisi.
void fenAdmin::modifClasse()
{

    ui->comboBox_2->clear();

    QSqlQuery ids;
    QSqlQuery ids2;
    ids.prepare("SELECT id_classe FROM classe WHERE nom_classe = :nom_classe");
    ids.bindValue(":nom_classe",ui->comboBox->currentText());
    ids.exec();
    ids.next();

    ids2.prepare("SELECT nom FROM eleve WHERE fk_id_classe = :fk_id_classe");
    ids2.bindValue(":fk_id_classe",ids.value(0).toInt());
    ids2.exec();
    while(ids2.next())
    {
        ui->comboBox_2->addItem(ids2.value(0).toString());
    }
}


//Permet d'afficher le bulletin de l'eleve choisi. Le bulletin est organisé par matières. Pour chaques matières, le professeur, les notes et les commentaires du professeur sont affichés.
void fenAdmin::pdf(int m_id)
{
    int id_eleve = m_id;
    QSqlQuery nomEleve;
    nomEleve.prepare("SELECT nom, prenom FROM eleve WHERE id_eleve = :id_eleve");
    nomEleve.bindValue(":id_eleve", id_eleve);
    nomEleve.exec(); nomEleve.next();
    QString eleveS = nomEleve.value(0).toString() + " "+nomEleve.value(1).toString();
    html="";
    html =     "<html><style type=\"text/css\"> \
            table { width:100%; background-color:#FFFFFF; border-collapse:collapse; border-width:1px; border-color:#000101; border-style:solid; color:#000101; } \
            table td, table th { border-width:1px;  border-color:#336600; border-style:solid; padding:3px; } \
            table thead { background-color:#CCFF99; } </style><div align=right> Fait le "
                        + currDate() +
                    "</div>"
                    "<div align=left>"
                       "School Board<br>"
                    "</div>"    "<h1 align=center>Bulletin de "+eleveS+"</h1>"
                    "<p align=justify>";
    QString e = "è";
    html = html + "<table align=center> <tr><th>Mati"+e+"re</th><th>Professeur</th><th>Moyenne</th><th>Notes</th><th>Commentaire</th></tr>";

    QSqlQuery notes;
    notes.prepare("SELECT DISTINCT fk_id_matiere  FROM notes WHERE fk_id_eleve = :fk_id_eleve");
    notes.bindValue(":fk_id_eleve", id_eleve);
    notes.exec();
    while(notes.next())
    {
         id_matiere = notes.value(0).toInt();
         qDebug() << id_matiere;
         fenAdmin::ids();
         html = html + "<div align=center><tr><td align=center>" + fenAdmin::matiere() + "</td>&nbsp;&nbsp;<td align=center>"+ fenAdmin::prof() +"</td><td align= center>" + fenAdmin::moyenne() + "</td><td align= center>" + fenAdmin::note() + "</td><td align= center>" + fenAdmin::comm() + "</td></tr></div>";

    }
    html = html +"</table>";

    html =  html + "</p>"
               "<div align=right>Cordialement</div></html>";

    document.setHtml(html);
    ui->textBrowser->setHtml(html);
}


//Permet d'enregistré le bulletin au format PDF sur son ordinateur.
void fenAdmin::save()
{

    QString fileName = QFileDialog::getSaveFileName(this,
                                                    QObject::tr("Sauvegarder fichier notes"),
                                                    "Notes", "pdf(*.pdf)");
   // QFileInfo fi(filePath);
   //QString fileName= fi.fileName();
   /* QString desktopPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    QString destinationPath= desktopPath+QDir::separator()+fileName;
    if(QFile::copy(filePath, destinationPath))
        qDebug() << "success";
    else
        qDebug() << "failed";
    */

     qDebug() << fileName;

    QPdfWriter writer(fileName);

    document.print(&writer);
}


//Fonction qui permet de récuperé l'id du professeur en fonction de l'ID de la matière
void fenAdmin::ids()
{
    QSqlQuery ids;
    ids.prepare("SELECT fk_id_prof FROM notes WHERE fk_id_matiere = :fk_id_matiere");
    ids.bindValue(":fk_id_matiere", id_matiere);
    ids.exec();
    ids.next();
    id_prof_bull = ids.value(0).toInt();
   //qDebug() << id_prof_bull;

}



//Permet de retourné le nom du professeur grâce a l'ID du professeur.
QString fenAdmin::prof()
{
    QSqlQuery prof;
    prof.prepare("SELECT nom FROM professeur WHERE id_professeur = :fk_id_prof");
    prof.bindValue(":fk_id_prof", id_prof_bull);
    prof.exec();
    prof.next();
    return prof.value(0).toString();

}


//Permet de récuperé tous les commentaires d'un professeur sur la matière conçerné.
QString fenAdmin::comm()
{

    QSqlQuery comm;
    comm.prepare("SELECT comm FROM notes WHERE fk_id_matiere = :fk_id_matiere AND fk_id_eleve = :fk_id_eleve");
    comm.bindValue(":fk_id_matiere", id_matiere);
    comm.bindValue(":fk_id_eleve", m_id);
    comm.exec();
    commListString.clear();
    while(comm.next())
    {
        commListString = commListString + comm.value(0).toString()+"   ";

    }

    return commListString;
}

//Permet de récuperé toutes les notes d'une matière d'un élève.
QString fenAdmin::note()
{

    QSqlQuery note;
    note.prepare("SELECT note FROM notes WHERE fk_id_matiere = :fk_id_matiere AND fk_id_eleve = :fk_id_eleve");
    note.bindValue(":fk_id_matiere", id_matiere);
    note.bindValue(":fk_id_eleve", m_id);
    note.exec();
    noteListString.clear();
    while(note.next())
    {
        noteListString = noteListString + note.value(0).toString();

    }

    return noteListString;

}


//Permet de récuperé les nom des matières en fonction de leurs ID.
QString fenAdmin::matiere()
{
    QSqlQuery matiere;
    matiere.prepare("SELECT nom_matiere FROM matiere WHERE id_matiere = :id_matiere");
    matiere.bindValue(":id_matiere", id_matiere);
    matiere.exec();
    matiere.next();
    return matiere.value(0).toString();
}


//Permet de calculer la moyenne de l'élève dans une matière. (attendre la v2.0)
float fenAdmin::moyenne()
{
    QSqlQuery note;
    note.prepare("SELECT note FROM notes WHERE id_notes = :id_notes");
    note.bindValue(":id_notes", id_note);
    note.exec();
    int total=0;
    while(note.next())
    {
        QRegExp rx("[/ ]");
        QStringList list = note.value(0).toString().split(rx, QString::SkipEmptyParts);

        QString name = list.at(0);

        for(int i = 1; i < list.size(); i++)
        {
            nums.append(list.at(i).toInt());
        }


        for(int i = 0; i < nums.size(); i++)
        {
           total = total + nums.at(i);
        }
        moy=total/nums.size();
    }
    return  moy;
}
