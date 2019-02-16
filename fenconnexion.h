#ifndef FENCONNEXION_H
#define FENCONNEXION_H

#include "fenadmin.h"
#include "feneleve.h"
#include "fenprof.h"

#include <QMainWindow>
#include <QFileDialog>
#include <QTextDocument>
#include <QDate>
#include <QPdfWriter>
#include <QDebug>
#include <QSqlQuery>
#include <QMessageBox>
#include <QCryptographicHash>
#include <QLayout>
#include <QList>

namespace Ui {
class FenConnexion;
}

class FenConnexion : public QMainWindow
{
    Q_OBJECT

public:
    explicit FenConnexion(QWidget *parent = 0);
    ~FenConnexion();



public slots:
    void connexion();



private:
    Ui::FenConnexion *ui;


};

#endif // FENCONNEXION_H
