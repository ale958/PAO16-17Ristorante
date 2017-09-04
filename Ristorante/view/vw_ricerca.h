#ifndef WIDGET_RICERCA_H
#define WIDGET_RICERCA_H
#include<QDialog>
#include<QGridLayout>
#include<QLabel>
#include<QPushButton>
#include<QLineEdit>
#include<QVBoxLayout>
#include<QString>
#include<QComboBox>
#include<QHeaderView>

#include"model/database_tavoli.h"
#include"model/database_utenti.h"
#include"view/vw_liste.h"
#include"view/v_gestione_tavoli.h"

class VWRicerca:public QWidget{
private:
    Q_OBJECT
    DatabaseTavoli * listaTavoli;
    DatabaseUtenti * listaUtenti;
    UtenteGenerico * utente; //utente che si loggerà
    QPushButton * pRicerca;
    QPushButton * pRicercaAll;
    QPushButton * pRicercaConsTavolo;
    QLineEdit * tRicerca;
    QComboBox * tArgomentoRicerca;
    QGridLayout * gridRicerca;
    QVBoxLayout * layoutRicerca;
    VWListe * tabella;
    VGestioneProfilo * informazioni_utente;
    VGestioneTavolo * informazioni_tavolo;
    VAddConsumazione * informazioni_consumazione;

public:
    VWRicerca(DatabaseTavoli * dbTav=0, DatabaseUtenti *dbUtenti=0, UtenteGenerico * utLog=0, QWidget *parent =0);
    void creaLayout();


public slots:
    void cercaTutti();
    void nascondiCercaTutti(int x);
    void cercaItem();
    void doppioClick(int x);
    void cercaConsumazioniTavolo();
    void chiudiLista();

signals:
    void salvaModificheProfilo(VGestioneProfilo*);
    void salvaModificheTavolo(VGestioneTavolo*);
    void salvaConsumazione(VAddConsumazione*);
    void disattivaMainWindows();
};

#endif // WIDGET_RICERCA_H
