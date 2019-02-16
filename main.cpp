#include <QApplication>
#include <QtSql/QSqlDatabase>
#include <QtWidgets>
#include "fenconnexion.h"
#include "fenadmin.h"


//Permet d'executer l'application et de ce connecter a la base de donnée.
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
        db.setHostName("mysql2.paris1.alwaysdata.com");

        db.setUserName("projetc");
        db.setPassword("mashallah123");
        db.setDatabaseName("projetc_1");
        if(db.open())
        {
            qDebug() << "Vous etes connecte a " << db.hostName();
        }
        else
        {
           qDebug() << "Lance ton WAMP autiste.";
        }


    //MaFenetre fenetre;
    //fenetre.show();
    FenConnexion conn;
    conn.setWindowFlags( Qt::WindowTitleHint |  Qt::WindowMinimizeButtonHint | Qt::WindowSystemMenuHint | Qt::WindowCloseButtonHint);
    conn.show();
    conn.setFixedSize(785,600);
    return app.exec();
}
