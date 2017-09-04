#ifndef UT_CUCINA_H
#define UT_CUCINA_H
#include"utente_generico.h"

class Cuoco:public UtenteGenerico{
public:  
    Cuoco(QString nome="",QString cognome="",QString username="",QString pass="");

    QString getTipo()const;

    virtual bool canDoTavolo()const;
    virtual bool canDoConsumazioni()const;
    virtual bool canDoGestione()const;

    virtual void saveUtente(QXmlStreamWriter& xmlWriter);
    virtual void loadUtente(QXmlStreamReader& xmlReader);
};

#endif // UT_CUCINA_H
