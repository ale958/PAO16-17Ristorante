#ifndef VW_GESTIONE_PROFILO_H
#define VW_GESTIONE_PROFILO_H
#include<QDialog>
#include<QGridLayout>
#include<QLabel>
#include<QPushButton>
#include<QLineEdit>
#include<QVBoxLayout>
#include<QString>
#include<QComboBox>

#include"model/database_utenti.h"

class VGestioneProfilo:public QDialog{
private:
    Q_OBJECT
    QLabel *lUsername;
    QLabel *lNome;
    QLabel *lCognome;
    QLabel *lPassword;
    QLabel *lTipo;
    QLabel *lRuolo;
    QComboBox *cSelezioneTipo;

    QLineEdit* tUsername;
    QLineEdit *tNome;
    QLineEdit* tCognome;
    QLineEdit* tPassword;

    QPushButton*pModifica;
    QPushButton*pElimina;

    QPushButton*pAggiungi;

    QVBoxLayout *layoutUtGestione;

    QGridLayout * gridUtGestione;

    UtenteGenerico *utente;
    UtenteGenerico *utenteModifica;

public:
    VGestioneProfilo(UtenteGenerico * ut, UtenteGenerico *utmod);
    void addLayoutMod();
    void setLayoutMod();
    void resetTextUsername();
    void svuota();
    void setLayoutAggiungi();

public slots:
    void save_change_profilo();
    void save_delete();
    void aggiungiUtente();

signals:
    void inviaModifica(UtenteGenerico*,QString,QString,QString,QString, QString);
    void inviaElimina(UtenteGenerico*);
    void logout();   
    void addGUtenti(UtenteGenerico *);
};

#endif // VW_GESTIONE_PROFILO_H
