#include "c_utente.h"

CUtente::CUtente(DatabaseUtenti *dbUt, QObject *parent):QObject(parent),listaUtenti(dbUt) {
    vUtenti=nullptr;
}

void CUtente::refreshVGestioneUtenti(VGestioneProfilo *vGUtenti){
    vUtenti=vGUtenti;
    connect(vUtenti,SIGNAL(addGUtenti(UtenteGenerico*)),this,SLOT(addCUtente(UtenteGenerico*)));
    connect(vUtenti,SIGNAL(inviaModifica(UtenteGenerico*,QString,QString,QString,QString,QString)),
            this,SLOT(riceviModificheUtente(UtenteGenerico*,QString,QString,QString,QString,QString)));
    connect(vUtenti,SIGNAL(inviaElimina(UtenteGenerico*)),this,SLOT(riceviEliminaUtente(UtenteGenerico*)));
}

void CUtente::addCUtente(UtenteGenerico *u){
    vUtenti->svuota();
    listaUtenti->addElementUtente(u);
}

void CUtente::riceviModificheUtente(UtenteGenerico * u, QString nome, QString cognome, QString username, QString pass, QString tipo){
    if(u->getUsername()!=username && listaUtenti->findUsername(username)){
        vUtenti->resetTextUsername();
        QMessageBox::information(0,"Modifiche utente", "Username già in uso, inserirne un altro");

    }
    else{
        u->setNome(nome);
        u->setCognome(cognome);
        u->setUsername(username);
        u->setPassword(pass);

        if(tipo!=u->getTipo()){// è stato modificato anche il tipo dell'utente
            listaUtenti->changeTipoUtente(u,tipo);
        }
        QMessageBox::information(0,"Modifiche utente", "Avvenute correttamente");
        listaUtenti->SaveAndClose();
        vUtenti->close();
    }
}

void CUtente::riceviEliminaUtente(UtenteGenerico *u){
    listaUtenti->removeElementUtente(u);
    listaUtenti->SaveAndClose();
}

