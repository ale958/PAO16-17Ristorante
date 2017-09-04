#ifndef TAVOLORISTORANTE_H
#define TAVOLORISTORANTE_H
#include"tavolo.h"
#include<QString>

class TavoloRistorante: public Tavolo{
private:
    static int coperto;
    int piano;

public:
    TavoloRistorante(int num=0, QString grand="medio", bool occ=0, int p=0);
    virtual int getPosti()const;
    virtual double getCoperto()const;
    virtual QString getTipo()const;
    virtual void saveTavolo(QXmlStreamWriter & w);
    virtual void loadTavolo(QXmlStreamReader & r);
    int getPiano()const;
    void setPiano(int nuovoPiano);

};

#endif // TAVOLORISTORANTE_H
