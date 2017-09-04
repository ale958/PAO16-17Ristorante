#include "c_tavolo.h"

CTavolo::CTavolo(DatabaseTavoli *dbTav, QObject *parent):  QObject(parent),listaTavoli(dbTav){}

void CTavolo::refreshVGTavolo(VGestioneTavolo *vTav){
    vTavolo=vTav;
    connect(vTavolo,SIGNAL(inviaModificheTav(Tavolo*,UtenteGenerico*,QString,QString,QString,QString,QString,QString)),
            this,SLOT(riceviModificheTav(Tavolo*, UtenteGenerico*,QString,QString,QString,QString,QString,QString)));
    connect(vTavolo,SIGNAL(inviaEliminaTav(Tavolo*)),this,SLOT(riceviElimina(Tavolo*)));
    connect(vTavolo,SIGNAL(inviaCreaTav(Tavolo*)),this,SLOT(riceviCrea(Tavolo*)));
}

void CTavolo::riceviModificheTav(Tavolo * t, UtenteGenerico * u, QString tipo, QString g, QString o,
                                 QString num, QString piano, QString loc){
  bool modifiche=0;
  bool tavolocorretto=1;
  bool occ =false;
  if(o=="Si")occ=true;

  if(occ!= t->getOccupato()){
        t->setOccupato(occ);
        modifiche=1;
  }
  if(u->canDoTavolo()){
      if(num!=""&&t->getNumero()!=num.toInt()){
          Tavolo* app=listaTavoli->getTavolo(num.toInt());
          if(app){
              QMessageBox::warning(0,"Errore modifica del numero","Numero del tavolo già esistente");
              vTavolo->resetNumeroTav();
              modifiche=0;
              tavolocorretto=0;
          }
          else{
              t->setNumero(num.toInt());
               modifiche=1;
          }
      }
      if(tavolocorretto){
          if(tipo!=t->getTipo()){
              QMessageBox::warning(0,"Attenzione","Avendo cambiato il tipo del tavolo le consumazioni andranno perse");
              listaTavoli->changeTipoTavolo(t,tipo);
              Tavolo* app=listaTavoli->getTavolo(num.toInt());
              t=app;
          }
          if(g!=""&&t->getGrandezza()!=g){
              t->setGrandezza(g);
               modifiche=1;
          }

          if(tipo=="Tavolo pub"){
             (dynamic_cast<TavoloPub*>(t))->setLocazione(loc);
             modifiche=1;
          }
          if(tipo=="Tavolo ristorante"){
             (dynamic_cast<TavoloRistorante*>(t))->setPiano(piano.toInt());
             modifiche=1;
          }
      }
  }
  if (modifiche){//è avvenuto almeno un cambiamento
    QMessageBox::information(0,"Modifiche tavolo","Modifiche avvenute correttamente");
    vTavolo->close();
  }
  listaTavoli->SaveAndClose();
}


void CTavolo::riceviElimina(Tavolo *t){
    vTavolo->close();
    listaTavoli->removeElementTavolo(t);
    listaTavoli->SaveAndClose();
    QMessageBox::warning(0,"Eliminazione tavolo","Tavolo eliminato correttamente");
}

void CTavolo::riceviCrea(Tavolo *t){


    if(listaTavoli->getTavolo(t->getNumero())){
        QMessageBox::warning(0,"Errore","Impossibile aggiungere il tavolo, esiste già un tavolo con questo numero");
        delete t;
        t=nullptr;
        vTavolo->resetNumeroTav();
    }
    else{
        listaTavoli->addElementTavolo(t);
        vTavolo->close();
        listaTavoli->SaveAndClose();
        QMessageBox::information(0,"Inserimento tavolo", "Inserimento avvenuto con successo!");
    }
}
