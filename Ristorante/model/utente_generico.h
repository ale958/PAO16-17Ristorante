#ifndef UTENTEGENERICO_H
#define UTENTEGENERICO_H
#include<QString>



#include"consumazione.h"
#include "tavolo.h"
#include<list>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>

using std::list;
class Tavolo;
class Consumazione;

class UtenteGenerico{
private:
    QString nome;
    QString cognome;
    QString username;
    QString password;     
public:
    UtenteGenerico(QString nome="",QString cognome="",QString username="",QString pass="");
    virtual ~UtenteGenerico()=default;

    virtual QString getTipo() const =0;
    virtual bool canDoTavolo()const=0;
    virtual bool canDoConsumazioni()const=0;
    virtual bool canDoGestione()const=0;

    QString getNome()const;
    QString getCognome()const;
    QString getUsername()const;
    QString getPassword()const;

    void setUsername(const QString & nuovoUsername);
    void setNome(const QString& nuovoNome);
    void setCognome(const QString & nuovoCognome);
    void setPassword(const QString & nuovaPass);

    void saveBaseUtente(QXmlStreamWriter& xmlWriter);
    void loadBaseUtente(QXmlStreamReader& xmlReader);

    virtual void saveUtente(QXmlStreamWriter& xmlWriter)=0;
    virtual void loadUtente(QXmlStreamReader& xmlReader)=0;
};

#endif // UTENTEGENERICO_H
