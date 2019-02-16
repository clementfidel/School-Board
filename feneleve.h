#ifndef FENELEVE_H
#define FENELEVE_H

#include <QMainWindow>

#include "fenconnexion.h"

namespace Ui {
class fenEleve;
}

class fenEleve : public QMainWindow
{
    Q_OBJECT

public:
    explicit fenEleve(QWidget *parent = 0, int p_id = 0);
    ~fenEleve();
    void clearWidgets(QLayout * layout);



public slots:
    void selectDate();
    void EDTperso();
    void retour();
    void selecNotesDecroissante();
    void selecNotesMatiere();
    void selecNotesDates();
    void MoveToEDTPerso();
    void MoveToEDTDay();
    void MoveToNote();

private:
    Ui::fenEleve *ui;
    int m_id;
    QString moisS;
    QString jourS;
    QString matiere, salle, prof, matiere_2, matiere_3, matiere_4, salle_2, salle_3, salle_4, prof_2, prof_3, prof_4;
};

#endif // FENELEVE_H
