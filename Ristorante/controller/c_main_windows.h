#ifndef MAINWINDOWS_C_H
#define MAINWINDOWS_C_H
#include"model/database_tavoli.h"
#include"model/database_utenti.h"
#include<QObject>
#include"view/v_login.h"
#include"view/v_mainwindows.h"
#include"c_utente.h"
#include"c_consumazione.h"
#include"c_tavolo.h"

#include<QMessageBox>

class CMainWindows:public QObject
{
private:
    Q_OBJECT
    DatabaseTavoli * listaTavoli;
    DatabaseUtenti *listaUtenti;
    UtenteGenerico* utente; //utente che si loggerà

    VLogin * vLogin;
    VMainWindows * vMainWindows;

    CUtente *cUtente;
    CTavolo *cTavolo;
    CConsumazione * cConsumazione;

public:
    CMainWindows(QObject *parent =0);
    ~CMainWindows();
    void esecuzioneLogin();

public slots:
     void provaLoinMain(const QString&username, const QString&password);
     void refreshLogin();

     void refreshCProfilo(VGestioneProfilo * vGProf);
     void refreshCTavoli(VGestioneTavolo * vGTav);
     void refreshCConsumazione(VAddConsumazione * VACons);
};

#endif // MAINWINDOWS_C_H
