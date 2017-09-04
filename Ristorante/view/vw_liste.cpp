#include "vw_liste.h"


VWListe::VWListe(DatabaseTavoli *dbTav, DatabaseUtenti *dbUt, QWidget *parent):
      QTableWidget(parent), listaTavoli(dbTav), listaUtenti(dbUt){

    setSelectionMode(QAbstractItemView::SingleSelection);
    setSelectionBehavior(QAbstractItemView::SelectRows);

}

void VWListe::viewPersonale(){
    this->setRowCount(0);
    QStringList tableHeader;
    setColumnCount(4);
    setColumnWidth(0,100);
    setColumnWidth(1,100);
    setColumnWidth(2,100);
    setColumnWidth(3,100);
    setMaximumWidth(403);
    tableHeader<<"Username"<<"Tipo"<<"Nome"<<"Cognome";
    setHorizontalHeaderLabels(tableHeader);
    setEditTriggers(QAbstractItemView::NoEditTriggers);

}

void VWListe::addListUsers(UtenteGenerico * utente){
    int row=0;
    if(utente){
        setRowCount(row+1);
        addItemUser(row,utente);
    }
    else{
        QMessageBox::warning(0,"Utente", "Utente non trovato");
    }
}

void VWListe::addListAllUsers(){
    int row=0;
    std::list<UtenteGenerico*> listUtenti=listaUtenti->getAllUtenti();
    std::list<UtenteGenerico*>::const_iterator it=listUtenti.begin();

    for(;it!=listUtenti.end();it++){
        if(*it){
            setRowCount(row+1);
            addItemUser(row,*it);
            row++;
        }
    }
}

void VWListe::addItemUser(int row, UtenteGenerico*ut){
    setItem(row,0,new QTableWidgetItem(ut->getUsername()));
    setItem(row,1,new QTableWidgetItem(ut->getTipo()));
    setItem(row,2,new QTableWidgetItem(ut->getNome()));
    setItem(row,3,new QTableWidgetItem(ut->getCognome()));
}

void VWListe::viewTavoli(){
   this->setRowCount(0);
    QStringList tableHeader;
    setColumnCount(4);
    setColumnWidth(0,100);
    setColumnWidth(1,150);
    setColumnWidth(2,100);
    setColumnWidth(3,100);
    setMaximumWidth(452);

    tableHeader<<"Numero"<<"Tipo"<<"Posti"<<"Occupato";
    setHorizontalHeaderLabels(tableHeader);

    setEditTriggers(QAbstractItemView::NoEditTriggers);

}

void VWListe::addListTavoli(Tavolo *tav){
    int row=0;
    if(tav){
        setRowCount(row+1);
        addItemTavoli(row,tav);
    }
    else{
        QMessageBox::warning(0,"Tavolo", "Tavolo non trovato");
    }

}

void VWListe::addListAllTavoli(){
    int row=0;
    std::list<Tavolo*> prova=listaTavoli->getAllTavoli();
    std::list<Tavolo*>::const_iterator it=prova.begin();

    for(;it!=prova.end();it++){

        if(*it){
            setRowCount(row+1);
            addItemTavoli(row,*it);
            row++;
        }
    }
}

void VWListe::addItemTavoli(int r, Tavolo *tav){
    setItem(r,0,new QTableWidgetItem(QString::number(tav->getNumero())));
    setItem(r,1,new QTableWidgetItem(tav->getTipo()));
    setItem(r,2,new QTableWidgetItem(QString::number(tav->getPosti())));
    QTableWidgetItem *Occupato = new QTableWidgetItem;
    if(tav->getOccupato()==0)Occupato->setText("No");
    else Occupato->setText("Si");
    setItem(r,3,Occupato);

}

void VWListe::viewConsumazioni(){
    this->setRowCount(0);
    QStringList tableHeader;
    setColumnCount(6);
    setColumnWidth(0,50);
    setColumnWidth(1,90);
    setColumnWidth(2,75);
    setColumnWidth(3,117);
    setColumnWidth(4,100);
    setColumnWidth(5,60);
    setMaximumWidth(494);

    tableHeader<<"Id"<<"Descrizione"<<"Quantità"<<"Prezzo unitario"<<"Consegnata"<<"Tipo";
    setHorizontalHeaderLabels(tableHeader);

    setEditTriggers(QAbstractItemView::NoEditTriggers);

}

void VWListe::addListConsumazioni(QString nome){
    int row=0;
    std::list<Tavolo*> listTavoli=listaTavoli->getAllTavoli();
    auto it=listTavoli.begin();

    for(;it!=listTavoli.end();++it){

        if(*it){
            std::list<Consumazione*> listConsum=(*it)->getOrdini();
            auto itc=listConsum.begin();

            for(;itc!=listConsum.end();++itc){
                if((*itc)->getNome().contains(nome)){
                    setRowCount(row+1);
                    addItemConsumazione(row,*itc);
                    row++;
                }
            }
        }
    }

    if(row==0){
        QMessageBox::warning(0,"Consumazione", "Nessuna consumazione con questa descrizione trovata");
    }
}

void VWListe::addItemConsumazione(int row, Consumazione *c){
    setItem(row,0,new QTableWidgetItem(QString::number(c->getId())));
    setItem(row,1,new QTableWidgetItem(c->getNome()));
    setItem(row,2,new QTableWidgetItem(QString::number(c->getQuantita())));
    setItem(row,3,new QTableWidgetItem(QString::number(c->getPrezzo())));
    QTableWidgetItem *Consegnato = new QTableWidgetItem;
    if(c->getConsegnato()==0)Consegnato->setText("No");
    else Consegnato->setText("Si");
    setItem(row,4,Consegnato);
    setItem(row,5,new QTableWidgetItem(c->getTipo()));
}

void VWListe::addListaConsumazioniTv(int numTav){
    int row=0;
    Tavolo *tv=listaTavoli->getTavolo(numTav);
    if(tv){
        std::list<Consumazione*> listOrdini=tv->getOrdini();
        auto itc=listOrdini.begin();

       for(;itc!=listOrdini.end();++itc){
            setRowCount(row+1);
            addItemConsumazione(row,*itc);
            row++;
       }
    }
    else{
        QMessageBox::warning(0,"Errore inserimento", "Il numero del tavolo inserito è inesistente");
    }
}

