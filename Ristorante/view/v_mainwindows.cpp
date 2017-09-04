#include "v_mainwindows.h"

VMainWindows::VMainWindows(DatabaseTavoli *dbTav, DatabaseUtenti *dbUtenti, UtenteGenerico *ut, QWidget *parent):
    QMainWindow(parent), listaTavoli(dbTav),listaUtenti(dbUtenti), utente(ut){
   this->setAttribute(Qt::WA_DeleteOnClose);
   setWindowTitle("Ristorante");
   setFixedHeight(523);
   setFixedWidth(600);
   QRect wmainPosition = geometry();
   wmainPosition.moveCenter(QApplication::desktop()->availableGeometry().center());
   setGeometry(wmainPosition);
   addMenuBarOpt();
   wRicerca=nullptr;

   vGestioneUtente=nullptr;
   vGestioneProfilo=nullptr;
   vGestioneTavolo=nullptr;
   addRicerca();

}

void VMainWindows::addMenuBarOpt(){
    menuProfilo=new QMenu("Opzioni",this);
    mLogout=new QAction("Logout",this);
    mGestioneProfilo=new QAction("Modifica impostazioni account",this);

    menuProfilo->addAction(mLogout);
    menuProfilo->addAction(mGestioneProfilo);

    connect(mLogout,SIGNAL(triggered(bool)),this,SLOT(disconnessione()));
    connect(mGestioneProfilo,SIGNAL(triggered(bool)),this,SLOT(openGestioneProfilo()));
    menuBar()->addMenu(menuProfilo);

    if(utente->canDoGestione()){
        menuGestione=new QMenu("Gestione",this);
        mGestioneUtenti=new QAction("Aggiungi Utente",this);
        mGestioneTavoli=new QAction("Aggiungi Tavolo",this);

        menuGestione->addAction(mGestioneUtenti);
        menuGestione->addAction(mGestioneTavoli);

        connect(mGestioneUtenti,SIGNAL(triggered(bool)),this,SLOT(openGestioneUtente()));
        connect(mGestioneTavoli,SIGNAL(triggered(bool)),this,SLOT(openGestioneTavolo()));
        menuBar()->addMenu(menuGestione);
    }


}

void VMainWindows::addRicerca(){

    wRicerca=new VWRicerca(listaTavoli,listaUtenti,utente);
    connect(wRicerca,SIGNAL(disattivaMainWindows()),this,SLOT(disattivaFinestra()));

    connect(wRicerca, SIGNAL(salvaModificheProfilo(VGestioneProfilo*)),this,SLOT(refreshVProfilo(VGestioneProfilo *)));
    connect(wRicerca,SIGNAL(salvaModificheTavolo(VGestioneTavolo*)),this,SIGNAL(refreshVTavolo(VGestioneTavolo*)));
    connect(wRicerca,SIGNAL(salvaConsumazione(VAddConsumazione*)),this,SIGNAL(refreshVConsumazione(VAddConsumazione*)));
    setCentralWidget(wRicerca);
}

void VMainWindows::disconnessione(){
    emit provaLogout();
    this->close();
}

void VMainWindows::openGestioneUtente(){

    openGestionePersonale();
    vGestioneProfilo->setLayoutAggiungi();
    vGestioneProfilo->show();
}

void VMainWindows::openGestionePersonale(){
    vGestioneProfilo=new VGestioneProfilo(utente,utente);
    disattivaFinestra();
    connect(vGestioneProfilo,SIGNAL(finished(int)),this,SLOT(disattivaFinestra()));
    emit(refreshVGestioneUtente(vGestioneProfilo));
    connect(vGestioneProfilo,SIGNAL(logout()),this,SLOT(disconnessione()));

    wRicerca->chiudiLista();
}

void VMainWindows::openGestioneProfilo(){
    openGestionePersonale();
    vGestioneProfilo->setLayoutMod();
    vGestioneProfilo->show();
}

void VMainWindows::openGestioneTavolo(){
    vGestioneTavolo=new VGestioneTavolo(utente);
    disattivaFinestra();
    connect(vGestioneTavolo,SIGNAL(finished(int)),this,SLOT(disattivaFinestra()));

    emit(refreshVTavolo(vGestioneTavolo));
    vGestioneTavolo->setLayoutCrea();
    vGestioneTavolo->show();
    wRicerca->chiudiLista();
}

void VMainWindows::refreshVProfilo(VGestioneProfilo *vGestProfilo){
    connect(vGestProfilo, SIGNAL(logout()),this,SLOT(disconnessione()));
    emit refreshVGestioneUtente(vGestProfilo);
}

void VMainWindows::disattivaFinestra(){
    if(isEnabled()){
        this->setEnabled(0);
    }
    else{
        this->setEnabled(1);
    }
}



