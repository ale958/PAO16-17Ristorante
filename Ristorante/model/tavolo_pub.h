#ifndef TAVOLOPUB_H
#define TAVOLOPUB_H
#include"tavolo.h"
#include<QString>

class TavoloPub: public Tavolo{
private:
    static int coperto;
    QString locazione;
public:
    TavoloPub(int num =0, QString loc="interna", QString grand ="medio", bool occ =false);
    virtual int getPosti()const;
    virtual double getCoperto()const;
    virtual QString getTipo()const;
    QString getLocazione()const;

    void setLocazione(QString nuovaLoc);

    virtual void saveTavolo(QXmlStreamWriter & w);
    virtual void loadTavolo(QXmlStreamReader & r);


};

#endif // TAVOLOPUB_H
