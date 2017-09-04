#ifndef VW_LISTA_H
#define VW_LISTA_H

#include <QWidget>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QVBoxLayout>
#include"model/database_tavoli.h"
#include"model/database_utenti.h"
#include"v_gestione_profilo.h"

class VWListe:public QTableWidget{
 private:
    Q_OBJECT
    DatabaseTavoli * listaTavoli;
    DatabaseUtenti * listaUtenti;

public:
    VWListe(DatabaseTavoli *dbTav, DatabaseUtenti*dbUt, QWidget *parent=0);
    void viewPersonale();
    void addListUsers(UtenteGenerico *utente);
    void addListAllUsers();
    void addItemUser(int row, UtenteGenerico *ut);

    void viewTavoli();
    void addListTavoli(Tavolo *tav);
    void addListAllTavoli();
    void addItemTavoli(int r, Tavolo *tav);

    void viewConsumazioni();
    void addListConsumazioni(QString nome);
    void addItemConsumazione(int row, Consumazione *c);
    void addListaConsumazioniTv(int numTav);
};

#endif // VW_LISTA_H
