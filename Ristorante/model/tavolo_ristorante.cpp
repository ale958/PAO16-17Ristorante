#include "tavolo_ristorante.h"
int TavoloRistorante::coperto=2;
TavoloRistorante::TavoloRistorante(int num, QString grand, bool occ, int p):  Tavolo(num,grand,occ),piano(p){}
double TavoloRistorante::getCoperto()const{return coperto;}

QString TavoloRistorante::getTipo() const{
    return "Tavolo ristorante";
}

int TavoloRistorante::getPosti()const{
   if( Tavolo::getGrandezza() =="piccolo"){
        return 2;
   }
   else{
        if(Tavolo::getGrandezza() =="medio"){
             return 6;
        }
        else{
             return 12;
        }
   }
}
int TavoloRistorante::getPiano()const{return piano;}

void TavoloRistorante::setPiano(int nuovoPiano){
    piano=nuovoPiano;
}



void TavoloRistorante::loadTavolo(QXmlStreamReader &r){
   loadBaseTavolo(r);
   if(r.name()=="piano")this->piano=(r.readElementText()).toInt();
}

void TavoloRistorante::saveTavolo(QXmlStreamWriter &w){
    w.writeStartElement("tavoloristorante");
    saveBaseTavolo(w);
    w.writeTextElement("piano",QString::number(getPiano()));
    w.writeEndElement();
}

