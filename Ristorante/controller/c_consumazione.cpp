#include "c_consumazione.h"

CConsumazione::CConsumazione(DatabaseUtenti *dbUt, QObject *parent):QObject(parent), listaUtenti(dbUt){
    vConsumazione=nullptr;
}

void CConsumazione::aggiorna_punt_view(VAddConsumazione *vCons){
    vConsumazione=vCons;
    connect(vConsumazione,SIGNAL(creaConsumazione(Consumazione*,Tavolo*)),this,SLOT(addConsumazione(Consumazione*,Tavolo*)));
    connect(vConsumazione,SIGNAL(eliminaConsumazione(Consumazione*,Tavolo*)),this,SLOT(delConsumazione(Consumazione*,Tavolo*)));
    connect(vConsumazione,SIGNAL(modificaConsumazione(Consumazione*,QString,int,double,QString,bool)),
            this,SLOT(changeConsumazione(Consumazione*,QString,int,double,QString,bool)));
}

void CConsumazione::addConsumazione(Consumazione * c, Tavolo *t){
    t->addConsumazione(c);
}

void CConsumazione::delConsumazione(Consumazione * c, Tavolo *t){
    t->removeConsumazione(c->getId());
    QMessageBox::information(0,"Rimozione consumazione","Rimozione consumazione avvenuta correttamente");
}

void CConsumazione::changeConsumazione(Consumazione *c, QString desc, int q, double p, QString tipo, bool consegnato){
     c->setDescrizione(desc);
     c->setPrezzo(p);
     c->setQuantita(q);
     c->setTipo(tipo);
     c->setConsegnato(consegnato);
     QMessageBox::information(0,"Consumazione","Modifiche avvenute con successo");
}
