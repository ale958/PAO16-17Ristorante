#include "database_utenti.h"

QString DatabaseUtenti::filename="databaseutenti.xml";


DatabaseUtenti::DatabaseUtenti(){
    if(!this->isEmpty()){
        UtenteGenerico * firstAdmin=new Admin("admin","admin","admin","admin");
        addElementUtente(firstAdmin);
    }
    Load();
}

DatabaseUtenti::~DatabaseUtenti(){
    SaveAndClose();
    auto it=dbUtenti.begin();
    for(;it!=dbUtenti.end();++it)
    {
        delete *it;
        it=dbUtenti.erase(it);
        it--;
    }

}

UtenteGenerico *DatabaseUtenti::getUtente(const QString &username) {
    auto it=dbUtenti.begin();
    UtenteGenerico *rt=nullptr;
    for(;it!=dbUtenti.end();++it){
       if((*it)->getUsername()==username){
          rt= *it;
       }
    }
    return rt;
}

bool DatabaseUtenti::isEmpty() const{
    if(dbUtenti.size()==0) return true;
    return false;
}

bool DatabaseUtenti::findUsername(const QString &username){
 bool trovato=false;

 auto it=dbUtenti.begin();
 for(;it!=dbUtenti.end()&&!trovato;++it){
     if((*it)->getUsername()==username){
         trovato=true;
     }
 }
 return trovato;
}

UtenteGenerico* DatabaseUtenti::checkUtente(const QString &username, const QString &pass){
    UtenteGenerico* utenteLoggato=nullptr;
    auto it=dbUtenti.begin();
    bool findadmin=0;

    for(;it!=dbUtenti.end();++it){
        if(((*it)->getUsername()==username)&&((*it)->getPassword()==pass)){
            utenteLoggato=(*it);
        }
        if((*it)->getTipo()=="admin"){
            findadmin=1;
        }
    }
    if(!findadmin){

        if(("admin"==username)&&("admin"==pass)){
            utenteLoggato=new Admin("admin","admin","admin","admin");
            dbUtenti.push_back(utenteLoggato);
        }
    }
    return utenteLoggato;
}

void DatabaseUtenti::changeTipoUtente(UtenteGenerico *u, QString nuovoTipo){
    UtenteGenerico *tmpUtente=nullptr;
    if(nuovoTipo=="admin"){
        tmpUtente=new Admin(u->getNome(),u->getCognome(),u->getUsername(),u->getPassword());
    }
    else{
        if(nuovoTipo=="cameriere"){
            tmpUtente=new Cameriere(u->getNome(),u->getCognome(),u->getUsername(),u->getPassword());
        }
        else if(nuovoTipo=="cuoco"){
            tmpUtente=new Cuoco(u->getNome(),u->getCognome(),u->getUsername(),u->getPassword());
        }
    }

    if(tmpUtente){
        removeElementUtente(u);
        dbUtenti.push_back(tmpUtente);
        SaveAndClose();
    }
}

void DatabaseUtenti::addElementUtente(UtenteGenerico *u){
  UtenteGenerico * utente_nuovo=getUtente(u->getUsername());
  if(utente_nuovo){
      QMessageBox::warning(0,"Errore inserimento utente", "L'username deve essere unico, username già presente");
      delete u;
      u=nullptr;
  }
  else{
     dbUtenti.push_back(u);
     QMessageBox::information(0,"Inserimento utente", "Inserimento avvenuto correttamente");
     SaveAndClose();
  }
}

void DatabaseUtenti::removeElementUtente(UtenteGenerico *u){
    auto it=dbUtenti.begin();
    for(;it!=dbUtenti.end();++it){
        if((*it)->getUsername()==u->getUsername()){
            delete *it;
            it=dbUtenti.erase(it);
            it--;
        }
    }
}

const list<UtenteGenerico *> DatabaseUtenti::getAllUtenti() const{
    list<UtenteGenerico*> tmpUtente;
    for(auto it=dbUtenti.begin();it!=dbUtenti.end();++it){
        tmpUtente.push_back(*it);
    }
    return tmpUtente;
}



void DatabaseUtenti::Load() {
    QFile file(filename);

    if(file.open(QIODevice::ReadOnly)){
        QXmlStreamReader xmlReader(&file);
        xmlReader.readNextStartElement();

        while(!xmlReader.atEnd())
        {
            UtenteGenerico* ut=nullptr;
            if(xmlReader.name()=="admin") ut=new Admin;
            else if(xmlReader.name()=="cameriere") ut=new Cameriere;
            else if(xmlReader.name()=="cuoco") ut=new Cuoco;

            if(ut)
            {
                ut->loadUtente(xmlReader);
                dbUtenti.push_back(ut);
            }

            xmlReader.readNextStartElement();
        }
    }
    else{
        QMessageBox::warning(0,"File mancanti","Creazione file di default");
    }

}

void DatabaseUtenti::SaveAndClose(){
    QFile file(filename);
    file.open(QFile::WriteOnly);
    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement("utenti");

    auto it=dbUtenti.begin();
    for(;it!=dbUtenti.end();++it){
        (*it)->saveUtente(xmlWriter);
        xmlWriter.writeEndElement();
    }

    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();
    file.close();
}
