#ifndef TAVOLO_H
#define TAVOLO_H
#include<QString>
#include<QMessageBox>
#include"consumazione.h"
#include<QXmlStreamWriter>
#include<QXmlStreamReader>
#include<list>
#include"utente_generico.h"
class UtenteGenerico;


class Consumazione;

class Tavolo{
private:
    int numero;
    QString grandezza;
    bool occupato;
    std::list<Consumazione *> first;

public:
    Tavolo(int num=0, QString grand ="medio", bool occ =false);
    virtual ~Tavolo();
    virtual int getPosti() const=0;
    virtual double getCoperto() const =0;
    virtual QString getTipo()const=0;
    QString getGrandezza()const;
    bool getOccupato()const;
    int getNumero()const;
    std::list<Consumazione *> getOrdini();

    void setNumero(int idTav);
    void setGrandezza(QString nuovaGrand);
    void setOccupato(bool nuovoOcc);

    void saveBaseTavolo(QXmlStreamWriter& xmlWriter);
    void loadBaseTavolo(QXmlStreamReader& r);
    virtual void saveTavolo(QXmlStreamWriter & w)=0;
    virtual void loadTavolo(QXmlStreamReader & r)=0;

    void addConsumazione(Consumazione* consum);
    void removeConsumazione(long int idC);

};

#endif // TAVOLO_H
