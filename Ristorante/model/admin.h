#ifndef UT_ADMIN_H
#define UT_ADMIN_H

#include"utente_generico.h"
#include"database_utenti.h"
#include"database_tavoli.h"
class DatabaseUtenti;

class Admin: public UtenteGenerico{
public:
    Admin(QString nome="",QString cognome="",QString username="",QString pass="");

    QString getTipo()const;

    virtual bool canDoTavolo()const;
    virtual bool canDoConsumazioni()const;
    virtual bool canDoGestione()const;

    virtual void saveUtente(QXmlStreamWriter& xmlWriter);
    virtual void loadUtente(QXmlStreamReader& xmlReader);
};

#endif // UT_ADMIN_H
