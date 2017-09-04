#include "consumazione.h"

long int Consumazione::maxid=0;

Consumazione::Consumazione(QString desc, QString tipo, int qt, double pr, bool con):  descrizione(desc), tipo(tipo), quantita(qt), prezzo(pr),consegnato(con){
    maxid++;
    id=maxid;
}

QString Consumazione::getNome()const{
    return descrizione;
}

int Consumazione::getQuantita()const{
    return quantita;
}
double Consumazione::getPrezzo()const{
    return prezzo;
}

bool Consumazione::getConsegnato() const{
    return consegnato;
}

int Consumazione::getId()const{
    return id;
}

void Consumazione::setConsegnato(const bool &nuovoStato){
    consegnato=nuovoStato;
}

void Consumazione::setQuantita(const int &nuovaQuant){
    quantita=nuovaQuant;
}

void Consumazione::setDescrizione(const QString &nuovaDesc){
    descrizione=nuovaDesc;
}

void Consumazione::setPrezzo(const double &nuovoPrezzo){
    prezzo=nuovoPrezzo;
}

void Consumazione::setTipo(const QString &nuovoTipo){
    tipo=nuovoTipo;
}

QString Consumazione::getTipo() const{
    return tipo;
}
