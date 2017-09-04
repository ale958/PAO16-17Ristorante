#include "vw_ricerca.h"

VWRicerca::VWRicerca(DatabaseTavoli *dbTav, DatabaseUtenti *dbUtenti, UtenteGenerico *utLog, QWidget *parent):
     QWidget(parent),listaTavoli(dbTav), listaUtenti(dbUtenti), utente(utLog){
    this->setAttribute(Qt::WA_DeleteOnClose);
    tabella=nullptr;

    informazioni_utente=nullptr;
    informazioni_tavolo=nullptr;
    informazioni_consumazione=nullptr;
    creaLayout();
}

void VWRicerca::creaLayout(){
    pRicerca=new QPushButton("Cerca");

    pRicerca->setFixedWidth(70);
    pRicerca->setFixedHeight(20);
    pRicercaAll=new QPushButton("Cerca tutti");
    pRicercaAll->setFixedWidth(120);
    pRicercaAll->setFixedHeight(20);
    pRicercaConsTavolo=new QPushButton("Cerca per tavolo");
    pRicercaConsTavolo->setFixedWidth(120);
    pRicercaConsTavolo->setFixedHeight(20);
    tRicerca=new QLineEdit();

    tRicerca->setFixedWidth(200);
    tRicerca->setFixedHeight(20);
    tRicerca->setPlaceholderText("Inserisci testo ricerca");

    tArgomentoRicerca=new QComboBox();
    tArgomentoRicerca->addItem("Tavolo");
    tArgomentoRicerca->addItem("Consumazione");
    tArgomentoRicerca->addItem("Personale");
    tArgomentoRicerca->setFixedWidth(130);
    tArgomentoRicerca->setFixedHeight(20);

    tabella= new VWListe(listaTavoli, listaUtenti,this);
    connect(tabella,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(doppioClick(int)));

    gridRicerca=new QGridLayout();

    gridRicerca->addWidget(pRicerca,0,0);
    gridRicerca->addWidget(pRicercaAll,0,1);
    gridRicerca->addWidget(pRicercaConsTavolo,0,1);

    gridRicerca->addWidget(tRicerca,0,2);
    gridRicerca->addWidget(tArgomentoRicerca,0,3);
    gridRicerca->addWidget(tabella,2,0,2,8);

    layoutRicerca=new QVBoxLayout();
    layoutRicerca->addLayout(gridRicerca);
    pRicercaConsTavolo->hide();

    connect(pRicerca,SIGNAL(clicked(bool)),this,SLOT(cercaItem()));

    connect(tArgomentoRicerca,SIGNAL(activated(int)),this,SLOT(nascondiCercaTutti(int)));

    connect(pRicercaAll,SIGNAL(clicked(bool)),this,SLOT(cercaTutti()));

    connect(pRicercaConsTavolo,SIGNAL(clicked(bool)),this,SLOT(cercaConsumazioniTavolo()));

    setLayout(layoutRicerca);
    tabella->close();

}

void VWRicerca::chiudiLista(){
    tabella->close();
}

void VWRicerca::cercaTutti(){
    tRicerca->clear();
    if(tArgomentoRicerca->currentText()=="Personale"){
        tabella->viewPersonale();
        tabella->addListAllUsers();

    }
    else if(tArgomentoRicerca->currentText()=="Tavolo"){

        tabella->viewTavoli();
        tabella->addListAllTavoli();
    }
    tabella->verticalHeader()->hide();
    tabella->show();
}

void VWRicerca::cercaItem(){
    QString testo=tRicerca->text();
    tabella->clear();
    if(tArgomentoRicerca->currentText()=="Personale"){
        tabella->viewPersonale();
        tabella->addListUsers(listaUtenti->getUtente(testo));
    }
    else{
        if(tArgomentoRicerca->currentText()=="Tavolo"){

        tabella->viewTavoli();
        tabella->addListTavoli(listaTavoli->getTavolo(testo.toInt()));

         }
        else if(tArgomentoRicerca->currentText()=="Consumazione"){

        tabella->viewConsumazioni();
        tabella->addListConsumazioni(testo);

        }
    }
    tabella->verticalHeader()->hide();
    tabella->show();
    tRicerca->clear();
}

void VWRicerca::doppioClick(int x){
   if(tabella->horizontalHeaderItem(0)->text()=="Username"&&utente->getTipo()=="admin"){

       UtenteGenerico *ut_modificare=listaUtenti->getUtente((tabella->item(x,0))->text());
       informazioni_utente=new VGestioneProfilo(utente,ut_modificare);
       connect(informazioni_utente,SIGNAL(inviaElimina(UtenteGenerico*)),this,SLOT(chiudiLista()));
       connect(informazioni_utente,SIGNAL(inviaModifica(UtenteGenerico*,QString,QString,QString,QString,QString)),this,SLOT(chiudiLista()));
       emit disattivaMainWindows();
       connect(informazioni_utente,SIGNAL(finished(int)),this,SIGNAL(disattivaMainWindows()));
       informazioni_utente->setLayoutMod();
       informazioni_utente->show();
       emit salvaModificheProfilo(informazioni_utente);

    }
   if(tabella->horizontalHeaderItem(0)->text()=="Numero"&&utente->canDoTavolo()){

      Tavolo *tavolo_modificare=listaTavoli->getTavolo((tabella->item(x,0))->text().toInt());
      informazioni_tavolo=new VGestioneTavolo(utente,tavolo_modificare);
      emit disattivaMainWindows();
      connect(informazioni_tavolo,SIGNAL(inviaEliminaTav(Tavolo*)),this,SLOT(chiudiLista()));
      connect(informazioni_tavolo,SIGNAL(inviaCreaTav(Tavolo*)),this,SLOT(chiudiLista()));
      connect(informazioni_tavolo,SIGNAL(inviaModificheTav(Tavolo*,UtenteGenerico*,QString,QString,QString,QString,QString,QString)),this,SLOT(chiudiLista()));
      connect(informazioni_tavolo,SIGNAL(finished(int)),this,SIGNAL(disattivaMainWindows()));
      connect(informazioni_tavolo,SIGNAL(refreshVTavolo(VAddConsumazione*)),this,SIGNAL(salvaConsumazione(VAddConsumazione*)));
      informazioni_tavolo->setLayoutModifica();
      informazioni_tavolo->show();
      emit salvaModificheTavolo(informazioni_tavolo);
    }
   //consumazione da tavolo
   if(tabella->horizontalHeaderItem(0)->text()=="Numero"&& !utente->canDoTavolo() && utente->canDoConsumazioni()){

       informazioni_consumazione = new VAddConsumazione(utente,listaTavoli->getTavolo((tabella->item(x,0))->text().toInt()));
       emit disattivaMainWindows();
       connect(informazioni_consumazione,SIGNAL(finished(int)),this,SIGNAL(disattivaMainWindows()));
       informazioni_consumazione->setLayoutAggiungiCons();
       informazioni_consumazione->show();
      emit salvaConsumazione(informazioni_consumazione);
    }
   //consumazione da tabella
   if(tabella->horizontalHeaderItem(0)->text()=="Id"&&utente->canDoConsumazioni()){
        Consumazione* cons_modificare=listaTavoli->getConsumazione(tabella->item(x,0)->text().toInt());
        informazioni_consumazione = new VAddConsumazione(utente,listaTavoli->getTavoloByConsumazione(cons_modificare->getId()));
        connect(informazioni_consumazione,SIGNAL(eliminaConsumazione(Consumazione*,Tavolo*)),this,SLOT(chiudiLista()));
        connect(informazioni_consumazione,SIGNAL(modificaConsumazione(Consumazione*,QString,int,double,QString,bool)),this,SLOT(chiudiLista()));

        emit disattivaMainWindows();
        connect(informazioni_consumazione,SIGNAL(finished(int)),this,SIGNAL(disattivaMainWindows()));
        informazioni_consumazione->setLayoutModificaCons(cons_modificare);
        informazioni_consumazione->show();
       emit salvaConsumazione(informazioni_consumazione);
   }
}

void VWRicerca::cercaConsumazioniTavolo(){
    int ntv=tRicerca->text().toInt();
    tabella->viewConsumazioni();
    tabella->addListaConsumazioniTv(ntv);
    tabella->show();
}

void VWRicerca::nascondiCercaTutti(int x){
    tRicerca->clear();
    tabella->close();
    if(x==1){
        pRicercaAll->hide();
        pRicercaConsTavolo->show();
        tRicerca->setValidator(new QRegExpValidator(QRegExp("([A-Za-z0-9]{1,30}[ ]){1,5}")));
    }
    else{
        pRicercaConsTavolo->hide();
        pRicercaAll->show();
        if(x==2){
           tRicerca->setValidator(new QRegExpValidator(QRegExp("[A-Za-z]{1,15}")));
        }
        if(x==0){
           tRicerca->setValidator(new QRegExpValidator(QRegExp("[0-9]{1,3}")));
        }
    }
}
