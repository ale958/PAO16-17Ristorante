#include "database_tavoli.h"
QString DatabaseTavoli::filename="databasetavoli.xml";

DatabaseTavoli::DatabaseTavoli(){Load();}

DatabaseTavoli::~DatabaseTavoli(){
    SaveAndClose();
    auto it=dbTavoli.begin();
    for(;it!=dbTavoli.end();++it)
    {
        delete *it;
        it=dbTavoli.erase(it);
        it--;

    }
}

void DatabaseTavoli::addElementTavolo(Tavolo *tav)
{
       dbTavoli.push_back(tav);
}

void DatabaseTavoli::removeElementTavolo(Tavolo *tav){
    auto it=dbTavoli.begin();
    for(;it!=dbTavoli.end();++it)
    {
        if((*it)->getNumero()==tav->getNumero())
        {
            delete *it;
            it=dbTavoli.erase(it);
            it--;
        }
    }
}

void DatabaseTavoli::changeTipoTavolo(Tavolo *tv, QString tipo){
   Tavolo * tmp ;
   if(tipo=="Tavolo pub"){
       tmp= new TavoloPub(tv->getNumero(),"esterna",tv->getGrandezza(),tv->getOccupato());
   }
   else{
      tmp=new TavoloRistorante(tv->getNumero(),tv->getGrandezza(),tv->getOccupato());
   }

   removeElementTavolo(tv);
   addElementTavolo(tmp);
}

void DatabaseTavoli::addConsumazione(int num, Consumazione *c){
    auto it=dbTavoli.begin();

    for(;it!=dbTavoli.end();++it){
       if((*it)->getNumero()==num){
            (*it)->getOrdini().push_back(c);
       }
    }
}

Tavolo* DatabaseTavoli::getTavolo(int num)const{
    auto it=dbTavoli.begin();
    Tavolo *rt=nullptr;
    for(;it!=dbTavoli.end();++it){
       if((*it)->getNumero()==num){
          rt= *it;
       }
    }
    return rt;
}

Tavolo *DatabaseTavoli::getTavoloByConsumazione(int idC) const{
    auto it=dbTavoli.begin();
    Tavolo *t=nullptr;
    for(;it!=dbTavoli.end();++it){
        std::list<Consumazione*> lista_c=(*it)->getOrdini();
        auto itc=lista_c.begin();

        for(;itc!=lista_c.end();++itc){
           if(((*itc)->getId())==idC){
              t= *it;
           }
        }
    }
    return t;
}

Consumazione *DatabaseTavoli::getConsumazione(int idC){
    auto it=dbTavoli.begin();
    Consumazione *c=nullptr;
    for(;it!=dbTavoli.end();++it){
        std::list<Consumazione*> lista_c=(*it)->getOrdini();
        auto itc=lista_c.begin();
        for(;itc!=lista_c.end();++itc){
           if((*itc)->getId()==idC){
              c= *itc;
           }
        }
    }
    return c;
}


void DatabaseTavoli::removeConsumazione(int num, long int idC){
    auto it=dbTavoli.begin();
    for(;it!=dbTavoli.end();++it){
       if((*it)->getNumero()==num){
           (*it)->removeConsumazione(idC);
       }
    }
}

const std::list<Tavolo *> DatabaseTavoli::getAllTavoli() const{
    std::list<Tavolo*> tmp_tav;
    for(auto it=dbTavoli.begin();it!=dbTavoli.end();++it){
        tmp_tav.push_back(*it);
    }
    return tmp_tav;
}

void DatabaseTavoli::Load(){
    QFile file(filename);

    if(file.open(QIODevice::ReadOnly)){
        QXmlStreamReader xmlReader(&file);
        xmlReader.readNextStartElement();

        while(!xmlReader.atEnd()){
            Tavolo * t=nullptr;
            if(xmlReader.name()=="tavolopub"){t=new TavoloPub;}
            else if(xmlReader.name()=="tavoloristorante"){t=new TavoloRistorante;}
            if(t){
                t->loadTavolo(xmlReader);
                xmlReader.readNextStartElement();
                dbTavoli.push_back(t);
            }
            xmlReader.readNextStartElement();
        }
    }
}

bool DatabaseTavoli::isEmpty() const {return dbTavoli.size();}

void DatabaseTavoli::SaveAndClose(){

    QFile file(filename);
    file.open(QIODevice::WriteOnly);
    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement("tavoli");

    for(auto it=dbTavoli.begin();it!=dbTavoli.end();++it){
        (*it)->saveTavolo(xmlWriter);
    }

    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();
    file.close();
}
