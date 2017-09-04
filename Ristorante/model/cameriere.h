#ifndef UT_CAMERIERE_H
#define UT_CAMERIERE_H

#include"utente_generico.h"
#include"database_tavoli.h"

class Cameriere: public UtenteGenerico{
public:
    Cameriere(QString nome="",QString cognome="",QString username="",QString pass="");
    QString getTipo()const;

    virtual bool canDoTavolo()const;
    virtual bool canDoConsumazioni()const;
    virtual bool canDoGestione()const;

    virtual void saveUtente(QXmlStreamWriter& xmlWriter);
    virtual void loadUtente(QXmlStreamReader& xmlReader);

};

#endif // UT_CAMERIERE_H
