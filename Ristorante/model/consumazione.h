#ifndef CONSUMAZIONE_H
#define CONSUMAZIONE_H
#include <QString>
#include <QTime>
#include"utente_generico.h"
class UtenteGenerico;

class Consumazione{
    private:
        static long int maxid;
        long int id;
        QString descrizione;
        QString tipo;//cucina o bar
        int quantita;
        double prezzo;
        bool consegnato;

    public:
        Consumazione(QString desc="", QString tipo="", int qt=0, double pr=0, bool con=0);

        QString getNome()const;
        int getQuantita()const;
        double getPrezzo()const;
        bool getConsegnato()const;
        int getId()const;
        QString getTipo() const;

        void setConsegnato(const bool& nuovoStato);
        void setTipo(const QString &nuovoTipo);
        void setQuantita(const int &nuovaQuant);
        void setDescrizione(const QString&nuovaDesc);
        void setPrezzo(const double &nuovoPrezzo);

};


#endif // CONSUMAZIONE_H
