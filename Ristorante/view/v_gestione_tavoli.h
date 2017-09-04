#ifndef VW_GESTIONE_TAVOLI_H
#define VW_GESTIONE_TAVOLI_H
#include<QDialog>
#include<QGridLayout>
#include<QLabel>
#include<QPushButton>
#include<QLineEdit>
#include<QVBoxLayout>
#include<QString>
#include<QComboBox>
#include<QRadioButton>
#include"model/database_tavoli.h"
#include"v_add_consumazione.h"

class VGestioneTavolo:public QDialog{
private:
    Q_OBJECT
    UtenteGenerico * utente;
    Tavolo * tavModifica;

    QLabel * lNumero;
    QLabel * lTipo;
    QLabel * lGrandezza;
    QLabel * lOccupato;
    QLabel * lLocazione;
    QLabel * lPiano;

    QLineEdit * tNumero;
    QLineEdit * tPiano;
    QComboBox * cTipo;
    QComboBox * cGrandezza;
    QComboBox * cOccupato;
    QComboBox * cLocazione;

    QPushButton * pSalvaModifiche;
    QPushButton * pElimina;

    QPushButton * pCrea;

    QPushButton * pAggiungi;

    QVBoxLayout * layoutTavolo;

    QGridLayout * gridTavolo;

public:
    VGestioneTavolo(UtenteGenerico*, Tavolo* tav=nullptr);
    void addLayout();
    void setLayoutCrea();
    void setLayoutModifica();
    void resetNumeroTav();

 public slots:
    void refreshConsumazione();
    void salvaTavolo();
    void salvaEliminazione();
    void salvaCreaTavolo();
    void cambiaTipo(QString tipo);
    void disattivaFinestraIntermedia();

 signals:
    void inviaModificheTav(Tavolo*, UtenteGenerico *, QString, QString, QString, QString, QString, QString);
    void inviaEliminaTav(Tavolo *);
    void inviaCreaTav(Tavolo* );
    void refreshVTavolo(VAddConsumazione *);

};

#endif // VW_GESTIONE_TAVOLI_H
