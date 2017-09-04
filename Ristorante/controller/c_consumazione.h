#ifndef CONSUMAZIONI_CONTROL_H
#define CONSUMAZIONI_CONTROL_H
#include"model/database_utenti.h"
#include"view/v_add_consumazione.h"
#include<QObject>

class CConsumazione:public QObject
{
private:
    Q_OBJECT
    DatabaseUtenti * listaUtenti;
    VAddConsumazione * vConsumazione;

public:
    CConsumazione(DatabaseUtenti * dbUt, QObject* parent=0);
    void aggiorna_punt_view(VAddConsumazione *vCons);

public slots:
    void addConsumazione(Consumazione *c, Tavolo *t);
    void delConsumazione(Consumazione*c, Tavolo*t);
    void changeConsumazione(Consumazione*c, QString desc, int q, double p, QString tipo, bool consegnato);
};

#endif // CONSUMAZIONI_CONTROL_H
