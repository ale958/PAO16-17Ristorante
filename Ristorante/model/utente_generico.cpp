#include "utente_generico.h"

UtenteGenerico::UtenteGenerico(QString nome, QString cognome, QString username, QString pass):
    nome(nome), cognome(cognome), username(username), password(pass){}

QString UtenteGenerico::getNome()const{
    return nome;
}
QString UtenteGenerico::getCognome()const{
    return cognome;
}
QString UtenteGenerico::getUsername()const{
    return username;
}
QString UtenteGenerico::getPassword()const{
    return password;
}

void UtenteGenerico::setUsername(const QString &nuovoUsername){
    username=nuovoUsername;
}

void UtenteGenerico::setNome(const QString &nuovoNome){
    nome=nuovoNome;
}

void UtenteGenerico::setCognome(const QString &nuovoCognome){
    cognome=nuovoCognome;
}

void UtenteGenerico::setPassword(const QString &nuovaPass){
    password=nuovaPass;
}

void UtenteGenerico::saveBaseUtente(QXmlStreamWriter &xmlWriter){
    xmlWriter.writeTextElement("nome",getNome());
    xmlWriter.writeTextElement("cognome",getCognome());
    xmlWriter.writeTextElement("username",getUsername());
    xmlWriter.writeTextElement("password",getPassword());
}

void UtenteGenerico::loadBaseUtente(QXmlStreamReader &xmlReader){
    xmlReader.readNextStartElement();
    if(xmlReader.name()=="nome") {
        setNome(xmlReader.readElementText());
        xmlReader.readNextStartElement();
    }
    if(xmlReader.name()=="cognome") {
        setCognome(xmlReader.readElementText());
        xmlReader.readNextStartElement();
    }
    if(xmlReader.name()=="username") {
        setUsername(xmlReader.readElementText());
        xmlReader.readNextStartElement();
    }
    if(xmlReader.name()=="password") {
        setPassword(xmlReader.readElementText());
        xmlReader.readNextStartElement();
    }
}

