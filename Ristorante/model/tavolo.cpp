#include "tavolo.h"


Tavolo::Tavolo(int num, QString grand, bool occ):  numero(num), grandezza(grand),occupato(occ){}

Tavolo::~Tavolo(){
    auto it=first.begin();
    for(;it!=first.end();++it){
            delete *it;
            it=first.erase(it);
            it--;
    }

}

QString Tavolo::getGrandezza()const{
    return grandezza;
}

void Tavolo::setGrandezza(QString nuovaGrand){
    grandezza=nuovaGrand;
}
void Tavolo::setOccupato(bool nuovoOcc){
    occupato=nuovoOcc;
}

void Tavolo::saveBaseTavolo(QXmlStreamWriter &xmlWriter){
    xmlWriter.writeTextElement("grandezza",getGrandezza());
    xmlWriter.writeTextElement("occupato",QString::number(getOccupato()));
    xmlWriter.writeTextElement("numero",QString::number(getNumero()));
}

void Tavolo::loadBaseTavolo(QXmlStreamReader &r){
    r.readNextStartElement();
    if(r.name()=="grandezza")this->setGrandezza(r.readElementText());
    r.readNextStartElement();
    if(r.name()=="occupato")this->setOccupato((r.readElementText()).toInt());
    r.readNextStartElement();
    if(r.name()=="numero")this->setNumero((r.readElementText()).toInt());
    r.readNextStartElement();
}

void Tavolo::removeConsumazione(long int idC){
    auto it=first.begin();
    for(;it!=first.end();++it){
        if(idC==(*it)->getId()){
           delete *it;
            it=first.erase(it);
            it--;
        }
    }
}

void Tavolo::setNumero(int idTav){
    numero=idTav;
}
bool Tavolo::getOccupato()const{
    return occupato;
}

int Tavolo::getNumero() const{
    return numero;
}

std::list<Consumazione *> Tavolo::getOrdini(){
    list<Consumazione*> tmpCons;
    for(auto it=first.begin();it!=first.end();++it){
        tmpCons.push_back(*it);
    }
    return tmpCons;
}

void Tavolo::addConsumazione(Consumazione *consum){
   if(consum){
    first.push_back(consum);
    QMessageBox::information(0,"Aggiunta consumazione","Aggiunta consumazione avvenuta con successo");
   }
}
