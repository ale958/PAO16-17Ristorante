#include "cameriere.h"

Cameriere::Cameriere(QString nome, QString cognome, QString username, QString pass):UtenteGenerico(nome,cognome,username,pass){}

QString Cameriere::getTipo()const{return "cameriere";}

bool Cameriere::canDoTavolo() const{
    return false;
}

bool Cameriere::canDoConsumazioni() const{
    return true;
}

bool Cameriere::canDoGestione() const{
    return false;
}


void Cameriere::saveUtente(QXmlStreamWriter &xmlWriter){
    xmlWriter.writeStartElement(getTipo());
    saveBaseUtente(xmlWriter);
}

void Cameriere::loadUtente(QXmlStreamReader &xmlReader){
    loadBaseUtente(xmlReader);
}

