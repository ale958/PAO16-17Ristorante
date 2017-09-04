#include "cuoco.h"

Cuoco::Cuoco(QString nome, QString cognome, QString username, QString pass):UtenteGenerico(nome,cognome,username,pass){}

QString Cuoco::getTipo()const{return "cuoco";}

bool Cuoco::canDoTavolo() const{
    return false;
}

bool Cuoco::canDoConsumazioni() const{
    return false;
}

bool Cuoco::canDoGestione() const{
    return false;
}


void Cuoco::saveUtente(QXmlStreamWriter &xmlWriter){
    xmlWriter.writeStartElement(getTipo());
    saveBaseUtente(xmlWriter);
}

void Cuoco::loadUtente(QXmlStreamReader &xmlReader){
    loadBaseUtente(xmlReader);
}

