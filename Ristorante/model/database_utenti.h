#ifndef DATABASE_UTENTI_H
#define DATABASE_UTENTI_H


#include<QFile>
#include<QXmlStreamWriter>
#include<QXmlStreamReader>
#include<iostream>
#include<QString>
#include"admin.h"
#include"cameriere.h"
#include"cuoco.h"
#include<list>
using std::list;

class DatabaseUtenti{
private:
    static QString filename;
    list<UtenteGenerico *> dbUtenti;
    void makeAdmin();
public:
    void Load();
    void SaveAndClose();
    DatabaseUtenti();
    ~DatabaseUtenti();
    UtenteGenerico* getUtente(const QString &username);
    bool isEmpty() const;
    bool findUsername(const QString &username);
    UtenteGenerico *checkUtente(const QString& username, const QString&pass);
    void changeTipoUtente(UtenteGenerico *u, QString nuovoTipo);
    void addElementUtente(UtenteGenerico*u);
    void removeElementUtente(UtenteGenerico*u);
    const list<UtenteGenerico*> getAllUtenti()const;
};

#endif // DATABASE_UTENTI_H
