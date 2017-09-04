#include "c_main_windows.h"


CMainWindows::CMainWindows(QObject *parent):QObject(parent){
    vLogin=nullptr;
    cUtente=nullptr;
    cTavolo=nullptr;
    cConsumazione=nullptr;
    vMainWindows=nullptr;
    listaTavoli= new DatabaseTavoli();
    listaUtenti= new DatabaseUtenti();
}

CMainWindows::~CMainWindows(){
    delete listaTavoli;
    delete listaUtenti;
 }

void CMainWindows::esecuzioneLogin(){
    vLogin=new VLogin();
    connect(vLogin,SIGNAL(provaLogin(QString,QString)),this,SLOT(provaLoinMain(QString,QString)));
    vLogin->show();
    cUtente=new CUtente(listaUtenti,this);
    cTavolo=new CTavolo(listaTavoli,this);
    cConsumazione=new CConsumazione(listaUtenti,this);
}

void CMainWindows::provaLoinMain(const QString &username, const QString &password){
    utente=listaUtenti->checkUtente(username, password);
    if(!utente){
        QMessageBox::warning(0,"Autentizaione", "Autenticazione fallita");
        vLogin->svuota();
    }
    else{
        vMainWindows=new VMainWindows(listaTavoli,listaUtenti,utente);
        connect(vMainWindows,SIGNAL(provaLogout()),this,SLOT(refreshLogin()));
        connect(vMainWindows,SIGNAL(refreshVGestioneUtente(VGestioneProfilo*)),this,SLOT(refreshCProfilo(VGestioneProfilo*)));
        connect(vMainWindows,SIGNAL(refreshVTavolo(VGestioneTavolo*)),this,SLOT(refreshCTavoli(VGestioneTavolo*)));
        connect(vMainWindows,SIGNAL(refreshVConsumazione(VAddConsumazione*)),this,SLOT(refreshCConsumazione(VAddConsumazione*)));
        vLogin->close();
        vLogin=nullptr;
        vMainWindows->show();
    }
}

void CMainWindows::refreshLogin(){
    if(!vLogin)vLogin=new VLogin();
    connect(vLogin,SIGNAL(provaLogin(QString,QString)),this,SLOT(provaLoinMain(QString,QString)));
    vLogin->svuota();
    vLogin->show();
}

void CMainWindows::refreshCProfilo(VGestioneProfilo *vGProf){
    cUtente->refreshVGestioneUtenti(vGProf);
}

void CMainWindows::refreshCTavoli(VGestioneTavolo *vGTav){
    cTavolo->refreshVGTavolo(vGTav);
}

void CMainWindows::refreshCConsumazione(VAddConsumazione *VACons){
    cConsumazione->aggiorna_punt_view(VACons);
}
