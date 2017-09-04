#include "admin.h"

Admin::Admin(QString nome, QString cognome, QString username, QString pass):UtenteGenerico(nome,cognome,username,pass){}

QString Admin::getTipo()const{return "admin";}

bool Admin::canDoTavolo() const{
    return true;
}

bool Admin::canDoConsumazioni() const{
    return true;
}

bool Admin::canDoGestione() const{
    return true;
}

void Admin::saveUtente(QXmlStreamWriter &xmlWriter){
    xmlWriter.writeStartElement(getTipo());
    saveBaseUtente(xmlWriter);
}

void Admin::loadUtente(QXmlStreamReader &xmlReader){
    loadBaseUtente(xmlReader);
}
