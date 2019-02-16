#ifndef FENPROF_H
#define FENPROF_H

#include <QMainWindow>
#include "fenconnexion.h"

namespace Ui {
class fenProf;
}

class fenProf : public QMainWindow
{
    Q_OBJECT

public:
    explicit fenProf(QWidget *parent = 0, int p_id=0);
    ~fenProf();
    void clearWidgets(QLayout * layout);

public slots:
    void selectDate();
    void ajoutEleve();
    void ajoutAbs();
    void ajoutNote();
    void EDTperso();
    void retour();
    void MoveToNote();
    void MoveToAbs();
    void MoveToEDTPerso();
    void MoveToEDTDay();

private:
    Ui::fenProf *ui;
    int m_id;
    QString moisS;
    QString jourS;
    QString matiere, salle,classe, matiere_2, matiere_3, matiere_4, salle_2, salle_3, salle_4, classe_2, classe_3, classe_4;
    QList<QString> idEleve;
    int nbLigne=0;
    int idClasse=0;
    int idMatiere=0;

};

#endif // FENPROF_H
