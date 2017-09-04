#ifndef VW_MAINWINDOWS_H
#define VW_MAINWINDOWS_H

#include<QMainWindow>
#include<QMenuBar>
#include<QAction>
#include<QApplication>
#include<QDesktopWidget>


#include"model/database_tavoli.h"
#include"model/database_utenti.h"
#include"view/vw_ricerca.h"
#include"view/v_gestione_profilo.h"

#include <QTableWidget>
#include <QTableWidgetItem>

class VMainWindows:public QMainWindow{
private:
    Q_OBJECT
    DatabaseTavoli * listaTavoli;
    DatabaseUtenti * listaUtenti;

    UtenteGenerico * utente; //utente che si loggerà

    QMenu * menuProfilo ;
    QAction * mLogout;
    QAction * mGestioneProfilo;

    QMenu * menuGestione ;
    QAction * mGestioneUtenti;
    QAction * mGestioneTavoli;

    VWRicerca * wRicerca;

    VGestioneProfilo * vGestioneUtente;
    VGestioneProfilo * vGestioneProfilo;
    VGestioneTavolo * vGestioneTavolo;

public:
    VMainWindows(DatabaseTavoli * dbTav=0, DatabaseUtenti *dbUtenti=0,UtenteGenerico *ut=0, QWidget *parent =0);
    void addMenuBarOpt();
    void addRicerca();
    void openGestionePersonale();

public slots:
    void disconnessione();
    void openGestioneUtente();
    void openGestioneProfilo();
    void openGestioneTavolo();
    void refreshVProfilo(VGestioneProfilo * vGestProfilo);
    void disattivaFinestra();

signals:
    void provaLogout();
    void refreshVGestioneUtente(VGestioneProfilo*);
    void refreshVTavolo(VGestioneTavolo*);
    void refreshVConsumazione(VAddConsumazione*);
};

#endif // VW_MAINWINDOWS_H
