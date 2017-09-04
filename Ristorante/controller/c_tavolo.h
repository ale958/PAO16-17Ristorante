#ifndef TAVOLO_CONTROL_H
#define TAVOLO_CONTROL_H
#include"model/database_tavoli.h"
#include"view/v_gestione_tavoli.h"
#include<QObject>
#include<QMessageBox>

class CTavolo:public QObject
{
private:
    Q_OBJECT
    DatabaseTavoli * listaTavoli;
    VGestioneTavolo * vTavolo;

public:
  CTavolo(DatabaseTavoli * dbTav, QObject* parent=0);
  void refreshVGTavolo(VGestioneTavolo* vTav);

 public slots:
  void riceviModificheTav(Tavolo *t, UtenteGenerico *u, QString tipo, QString g, QString o, QString num, QString piano, QString loc);
  void riceviElimina(Tavolo*t);
  void riceviCrea(Tavolo*t);
};
#endif // TAVOLO_CONTROL_H
