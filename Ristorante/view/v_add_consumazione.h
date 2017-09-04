#ifndef VW_AGGIUNTA_CONSUMAZIONE_H
#define VW_AGGIUNTA_CONSUMAZIONE_H

#include<QDialog>
#include<QGridLayout>
#include<QLabel>
#include<QPushButton>
#include<QLineEdit>
#include<QVBoxLayout>
#include<QString>
#include<QComboBox>

#include"model/database_tavoli.h"
#include"model/database_utenti.h"

class VAddConsumazione:public QDialog{

private:
    Q_OBJECT

    UtenteGenerico * utLog;
    Tavolo * tav;
    Consumazione * consum;

    QLabel * lDescrizione;
    QLabel * lQuantit;
    QLabel * lPrezzo;
    QLabel * lTipo;
    QLabel * lConsegnato;

    QLineEdit * tDescrizione;
    QLineEdit * tQuantit;
    QLineEdit * tPrezzo;

    QPushButton * pAggiungi;
    QPushButton * pElimina;
    QPushButton * pModifica;
    QComboBox * cTipo;
    QComboBox * cConsegnato;

    QGridLayout * grid;
    QVBoxLayout * vbox;

public:

    VAddConsumazione(UtenteGenerico * utente, Tavolo *tv,QWidget *parent=0, Consumazione * c=0);
    void creaLayout();
    void setLayoutModificaCons(Consumazione * cons);
    void setLayoutAggiungiCons();

 public slots:
    void clickPAggiungi();
    void clickPElimina();
    void clickPModifica();

  signals:
    void creaConsumazione(Consumazione *,Tavolo *);
    void eliminaConsumazione(Consumazione *, Tavolo *);
    void modificaConsumazione(Consumazione *, QString, int, double, QString, bool);
};

#endif // VW_AGGIUNTA_CONSUMAZIONE_H
