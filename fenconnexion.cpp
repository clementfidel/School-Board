#include "fenconnexion.h"
#include "ui_fenconnexion.h"




//Constructeur permettant la déclaration du boutton pour se connecter.
FenConnexion::FenConnexion(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FenConnexion)
{
    ui->setupUi(this);
    connect(ui->btnConnexion, SIGNAL(clicked()), this, SLOT(connexion()));

}
//Destructeur
FenConnexion::~FenConnexion()
{
    delete ui;
}

//Permet de ce connecter avec n'importe quel type d'utilisateur (administrateur, professeur, élève).
void FenConnexion::connexion()
{
    int m_id=0;
    //QString queryStr;
    //queryStr = QString("%1").arg(QString(QCryptographicHash::hash(ui->password->text().toUtf8(),QCryptographicHash::Md5).toHex()));
    //qDebug()<< queryStr;
    QSqlQuery query2;
    query2.prepare("SELECT * FROM eleve WHERE email = :email AND password = :password");
    query2.bindValue(":email",ui->email->text());
    query2.bindValue(":password",ui->password->text());
    query2.exec();
    if(query2.first())
    {
        query2.prepare("SELECT id_eleve FROM eleve WHERE email = :email");
        query2.bindValue(":email",ui->email->text());
        query2.exec();
        query2.next();
        m_id = query2.value(0).toInt();
        qDebug() << m_id;
        fenEleve *put = new fenEleve(this, m_id);
        put->show();
        this->hide();

    }
    else
    {

        query2.prepare("SELECT * FROM professeur WHERE email = :email AND password = :password");
        query2.bindValue(":email",ui->email->text());
        query2.bindValue(":password",ui->password->text());
        query2.exec();
        if(query2.first())
        {

            query2.prepare("SELECT id_professeur FROM professeur WHERE email = :email");
            query2.bindValue(":email",ui->email->text());
            query2.exec();
            query2.next();
            m_id = query2.value(0).toInt();
            qDebug() << query2.value(0).toInt();
            fenProf *put = new fenProf(this, m_id);
            put->show();
            this->hide();

        }
        else
        {

            query2.prepare("SELECT * FROM administrateur WHERE email = :email AND password = :password");
            query2.bindValue(":email",ui->email->text());
            query2.bindValue(":password",ui->password->text());
            query2.exec();
            if(query2.first())
            {
                fenAdmin *put = new fenAdmin(this);
                put->show();
                this->hide();
            }
            else
            {
                  QMessageBox::warning(this,"Erreur", "Email ou mot de passe incorrect.");
            }
        }
    }   
}



