#ifndef UTENTE_CONTROL_H
#define UTENTE_CONTROL_H
#include"model/database_utenti.h"
#include"view/v_gestione_profilo.h"
#include<QObject>
#include<QMessageBox>

class CUtente:public QObject
{
private:
    Q_OBJECT
    DatabaseUtenti * listaUtenti;
    VGestioneProfilo * vUtenti;

public:
    CUtente(DatabaseUtenti * dbUt, QObject* parent=0);
    void refreshVGestioneUtenti(VGestioneProfilo * vGUtenti);

public slots:
    void addCUtente(UtenteGenerico *u);
    void riceviModificheUtente(UtenteGenerico*u, QString nome, QString cognome, QString username, QString pass, QString tipo);
    void riceviEliminaUtente(UtenteGenerico *u);
};

#endif // UTENTE_CONTROL_H
