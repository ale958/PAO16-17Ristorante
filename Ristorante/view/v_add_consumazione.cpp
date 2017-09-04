#include "v_add_consumazione.h"

VAddConsumazione::VAddConsumazione(UtenteGenerico * utente, Tavolo *tv, QWidget *parent, Consumazione *c):
    QDialog(parent),utLog(utente),tav(tv), consum(c){
    this->setAttribute(Qt::WA_DeleteOnClose);
    setWindowFlags(windowFlags()  & ~Qt::WindowContextHelpButtonHint);
    setWindowTitle("Aggiunta consumazione");

    creaLayout();
    setModal(1);
}

void VAddConsumazione::creaLayout(){
    lDescrizione=new QLabel("Descrizione:");
    lQuantit=new QLabel("Quantità:");
    lPrezzo=new QLabel("Prezzo unitario:");
    lTipo=new QLabel("Tipo:");
    lConsegnato =new QLabel("Consegnato:");

    tDescrizione= new QLineEdit();
    tDescrizione->setPlaceholderText("Inserisci testo");
    tDescrizione->setValidator(new QRegExpValidator(QRegExp("([A-Za-z]{1,30}[ ]){1,5}")));

    tQuantit= new QLineEdit();
    tQuantit->setPlaceholderText("Inserisci quantità");
    tQuantit->setValidator(new QRegExpValidator(QRegExp("[0-9]{1,10}")));

    tPrezzo= new QLineEdit();
    tPrezzo->setPlaceholderText("Inserisci prezzo");
    tPrezzo->setValidator(new QRegExpValidator(QRegExp("[0-9]{1,3}[.][0-9]{1,2}")));

   pAggiungi=new QPushButton("Aggiungi");
   pElimina=new QPushButton("Elimina");
   pModifica=new QPushButton("Salva modifiche");

   connect(pAggiungi,SIGNAL(clicked(bool)),this,SLOT(clickPAggiungi()));
   connect(pElimina,SIGNAL(clicked(bool)),this,SLOT(clickPElimina()));
   connect(pModifica,SIGNAL(clicked(bool)),this,SLOT(clickPModifica()));

   cTipo=new QComboBox;
   cTipo->addItem("bar");
   cTipo->addItem("cucina");
   cConsegnato=new QComboBox;
   cConsegnato->addItem("Si");
   cConsegnato->addItem("No");

   grid=new QGridLayout();
   grid->addWidget(lDescrizione,0,0);
   grid->addWidget(lQuantit,1,0);
   grid->addWidget(lPrezzo,2,0);
   grid->addWidget(lTipo,3,0);
   grid->addWidget(lConsegnato,4,0);

   grid->addWidget(tDescrizione,0,1);
   grid->addWidget(tQuantit,1,1);
   grid->addWidget(tPrezzo,2,1);
   grid->addWidget(cTipo,3,1);
   grid->addWidget(cConsegnato,4,1);

   grid->addWidget(pAggiungi,5,0);
   grid->addWidget(pElimina,5,1);
   grid->addWidget(pModifica,5,0);

   vbox=new QVBoxLayout();
   vbox->addLayout(grid);

   setLayout(vbox);
}

void VAddConsumazione::setLayoutModificaCons(Consumazione * cons){
    consum=cons;
    pAggiungi->hide();
    tDescrizione->setText(cons->getNome());
    tQuantit->setText(QString::number(cons->getQuantita()));
    tPrezzo->setText(QString::number(cons->getPrezzo()));
    cTipo->setCurrentText(cons->getTipo());

    if(cons->getConsegnato()){
        cConsegnato->setCurrentText("Si");
    }
    else{
        cConsegnato->setCurrentText("No");
    }

}

void VAddConsumazione::setLayoutAggiungiCons(){
    pElimina->hide();
    pModifica->hide();
}

void VAddConsumazione::clickPAggiungi(){
    if(tDescrizione->text()!=""&&tPrezzo->text()!=""&&tQuantit->text()!=""){
        Consumazione * cons = new Consumazione();
        bool consegnato=false;
        if(cConsegnato->currentText()=="Si")consegnato=true;
        cons->setConsegnato(consegnato);

        cons->setDescrizione(tDescrizione->text());
        cons->setPrezzo(tPrezzo->text().toDouble());
        cons->setQuantita(tQuantit->text().toInt());
        cons->setTipo(cTipo->currentText());
        emit creaConsumazione(cons,tav);
        this->close();
    }
    else{
         QMessageBox::information(0,"Errore","Completare tutti i campi");
    }
}

void VAddConsumazione::clickPElimina(){
    emit eliminaConsumazione(consum,tav);
    close();
}

void VAddConsumazione::clickPModifica(){
    bool consegnato=false;
    if(cConsegnato->currentText()=="Si")consegnato=true;
    QString desc=(tDescrizione->text());
    int qt=tQuantit->text().toInt();
    double pr=tPrezzo->text().toDouble();
    QString tipo=cTipo->currentText();

    if(desc!=""&&tQuantit->text()!=""&&tPrezzo->text()!=""){
        emit modificaConsumazione(consum, desc, qt, pr, tipo, consegnato);
        close();
    }
    else
        QMessageBox::warning(0,"Modifiche consumazione","Completare tutti i campi");


}
