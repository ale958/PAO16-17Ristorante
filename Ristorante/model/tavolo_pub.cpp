#include "tavolo_pub.h"
int TavoloPub::coperto=1;

double TavoloPub::getCoperto()const{return coperto;}

TavoloPub::TavoloPub(int num, QString loc, QString grand, bool occ):Tavolo(num,grand,occ),locazione(loc){}

QString TavoloPub::getTipo() const{
    return "Tavolo pub";
}

QString TavoloPub::getLocazione()const{return locazione;}

int TavoloPub::getPosti()const{
   if( Tavolo::getGrandezza() =="piccolo"){
        return 2;
   }
   else{
        if(Tavolo::getGrandezza() =="medio"){
             return 4;
        }
        else{
             return 12;
        }
   }
}

void TavoloPub::saveTavolo(QXmlStreamWriter & w){
    w.writeStartElement("tavolopub");
    saveBaseTavolo(w);
    w.writeTextElement("locazione",getLocazione());
    w.writeEndElement();
}

void TavoloPub::loadTavolo(QXmlStreamReader &r){
    loadBaseTavolo(r);
    if(r.name()=="locazione")this->locazione=r.readElementText();
}

void TavoloPub::setLocazione(QString nuovaLoc){
   locazione=nuovaLoc;
}
