#ifndef DATABASE_TAVOLI_H
#define DATABASE_TAVOLI_H
#include<QMessageBox>
#include<QFile>
#include<QXmlStreamWriter>
#include<QXmlStreamReader>
#include<QString>
#include<iostream>
#include"tavolo.h"
#include"tavolo_pub.h"
#include"tavolo_ristorante.h"
#include<QFile>
#include<QXmlStreamReader>
#include<list>

class DatabaseTavoli{
private:
    static QString filename;
    std::list<Tavolo *> dbTavoli;

public:
    void Load();
    void SaveAndClose();
    DatabaseTavoli();
    ~DatabaseTavoli();
    bool isEmpty() const;
    void addElementTavolo(Tavolo*tav);
    void removeElementTavolo(Tavolo*tav);
    void changeTipoTavolo(Tavolo* tv, QString tipo);
    void addConsumazione(int num, Consumazione*c);
    void removeConsumazione(int num, long int idC);

    Tavolo* getTavolo(int num)const;
    Tavolo * getTavoloByConsumazione(int idC)const;
    Consumazione *getConsumazione(int idC);

    const std::list<Tavolo *> getAllTavoli()const;
};

#endif // DATABASE_TAVOLI_H
