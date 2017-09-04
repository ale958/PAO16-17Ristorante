#include "v_gestione_tavoli.h"

VGestioneTavolo::VGestioneTavolo(UtenteGenerico *u, Tavolo *tav):utente(u),tavModifica(tav){
    this->setAttribute(Qt::WA_DeleteOnClose);

    setWindowFlags(windowFlags()  & ~Qt::WindowContextHelpButtonHint);
    setWindowTitle("Gestione Tavolo");
    addLayout();
    setModal(1);
}

void VGestioneTavolo::addLayout(){
    QLabel *lNumero;
    QLabel *lTipo;
    QLabel *lGrandezza;
    QLabel *lOccupato;

    lNumero=new QLabel("Numero");
    lGrandezza=new QLabel("Grandezza");
    lOccupato=new QLabel("Occupato");
    lTipo=new QLabel("Tipo");
    lLocazione= new QLabel("Locazione");
    lPiano= new QLabel("Piano");

    tNumero=new QLineEdit();
    tNumero->setValidator(new QRegExpValidator(QRegExp("[0-9]{1,3}")));
    tNumero->setPlaceholderText("Inserisci numero");

    tPiano=new QLineEdit();
    tPiano->setValidator(new QRegExpValidator(QRegExp("[0-9]{1,3}")));
    tPiano->setPlaceholderText("Inserisci piano");

    cTipo=new QComboBox();
    cTipo->addItem("Tavolo pub");
    cTipo->addItem("Tavolo ristorante");

    cGrandezza=new QComboBox();
    cGrandezza->addItem("piccolo");
    cGrandezza->addItem("medio");
    cGrandezza->addItem("grande");

    cOccupato=new QComboBox();
    cOccupato->addItem("Si");
    cOccupato->addItem("No");

    cLocazione = new QComboBox();
    cLocazione->addItem("esterna");
    cLocazione->addItem("interna");

    pSalvaModifiche=new QPushButton("Salva le modifiche");
    pElimina=new QPushButton("Elimina il tavolo");
    pCrea=new QPushButton("Crea tavolo");
    pAggiungi=new QPushButton("Aggiungi consumazione");

    gridTavolo=new QGridLayout;
    gridTavolo->addWidget(lLocazione,4,0 );
    gridTavolo->addWidget(cLocazione,4,1);
    gridTavolo->addWidget(lPiano,5,0);
    gridTavolo->addWidget(tPiano,5,1);

    gridTavolo->addWidget(lNumero, 0,0);
    gridTavolo->addWidget(lGrandezza,1, 0);
    gridTavolo->addWidget(lOccupato,2, 0);
    gridTavolo->addWidget(lTipo,3,0);
    gridTavolo->addWidget(pSalvaModifiche,6,0);
    gridTavolo->addWidget(pElimina,6,1);
    gridTavolo->addWidget(pCrea,7,0);
    gridTavolo->addWidget(pAggiungi,8,0);
    gridTavolo->addWidget(tNumero,0,1);
    gridTavolo->addWidget(cTipo,3,1);

    gridTavolo->addWidget(cGrandezza,1,1);
    gridTavolo->addWidget(cOccupato,2,1);

    layoutTavolo=new QVBoxLayout();
    layoutTavolo->addLayout(gridTavolo);

    connect(cTipo,SIGNAL(currentIndexChanged(QString)),this,SLOT(cambiaTipo(QString)));
    connect(pSalvaModifiche,SIGNAL(clicked()),this,SLOT(salvaTavolo()));
    connect(pElimina,SIGNAL(clicked()),this,SLOT(salvaEliminazione()));
    connect(pCrea,SIGNAL(clicked(bool)),this,SLOT(salvaCreaTavolo()));
    connect(pAggiungi,SIGNAL(clicked(bool)),this,SLOT(refreshConsumazione()));

    setLayout(layoutTavolo);
    cambiaTipo(cTipo->currentText());
}

void VGestioneTavolo::setLayoutCrea(){
    pSalvaModifiche->hide();
    pElimina->hide();
    pAggiungi->hide();
}

void VGestioneTavolo::setLayoutModifica(){
    if(tavModifica){
          tNumero->setText(QString::number(tavModifica->getNumero()));
          cGrandezza->setCurrentText(tavModifica->getGrandezza());
          if(tavModifica->getOccupato()){
              cOccupato->setCurrentText("Si");
          }
          else{
              cOccupato->setCurrentText("No");
          }
          if(tavModifica->getTipo()=="Tavolo pub"){
              cLocazione->setCurrentText(dynamic_cast<TavoloPub*>(tavModifica)->getLocazione());
              lPiano->hide();
              tPiano->hide();

          }
          if(tavModifica->getTipo()=="Tavolo ristorante"){
              tPiano->setText(QString::number(dynamic_cast<TavoloRistorante *> (tavModifica)->getPiano()));
              lLocazione->hide();
              cLocazione->hide();
          }
           cTipo->setCurrentText(tavModifica->getTipo());
    }
    pCrea->hide();
}

void VGestioneTavolo::resetNumeroTav(){
    tNumero->clear();
    if(tavModifica)
    tNumero->setText(QString::number(tavModifica->getNumero()));
}


void VGestioneTavolo::refreshConsumazione(){
    VAddConsumazione * wAggiuntaConsumazione= new VAddConsumazione(utente,tavModifica);
    disattivaFinestraIntermedia();
    connect(wAggiuntaConsumazione,SIGNAL(finished(int)),this,SLOT(disattivaFinestraIntermedia()));
    wAggiuntaConsumazione->setLayoutAggiungiCons();
    emit refreshVTavolo(wAggiuntaConsumazione);
    wAggiuntaConsumazione->show();

}

void VGestioneTavolo::salvaTavolo(){
   if(tNumero->text()==""){
        QMessageBox::warning(0,"Attenzione","È necessario inserire il numero del tavolo");
   }
   else{
       if(cTipo->currentText()=="Tavolo ristorante" && tPiano->text()==""){
               QMessageBox::warning(0,"Attenzione","È necessario inserire il piano");
       }
       else{
            emit inviaModificheTav(tavModifica,utente,cTipo->currentText(),cGrandezza->currentText(),cOccupato->currentText(),
                                   tNumero->text(), tPiano->text(),cLocazione->currentText());
        }
   }

}

void VGestioneTavolo::salvaEliminazione(){
    emit(inviaEliminaTav(tavModifica));
}

void VGestioneTavolo::salvaCreaTavolo(){
    Tavolo * tmp=nullptr;
    if(tNumero->text()!=""){
        if(tPiano->text()==""&&cTipo->currentText()=="Tavolo ristorante"){
            QMessageBox::warning(0,"Attenzione","E' necessario inserire il piano");
            }
        else{
            if(cTipo->currentText()=="Tavolo pub"){
                tmp=new TavoloPub(tNumero->text().toInt(),cLocazione->currentText(),cGrandezza->currentText(),cOccupato->currentText().toInt());
            }
            else{
                tmp=new TavoloRistorante(tNumero->text().toInt(),cGrandezza->currentText(),cOccupato->currentText().toInt(),tPiano->text().toInt());
             }
                emit inviaCreaTav(tmp);
       }
    }
    else{
        QMessageBox::warning(0,"Attenzione","E' necessario inserire il numero dei tavoli");
   }
}

void VGestioneTavolo::cambiaTipo(QString tipo){
    if(tipo=="Tavolo pub"){
        lPiano->hide();
        tPiano->hide();
        lLocazione->show();
        cLocazione->show();
    }
    if(tipo=="Tavolo ristorante"){
        lLocazione->hide();
        cLocazione->hide();
        lPiano->show();
        tPiano->show();
    }
}

void VGestioneTavolo::disattivaFinestraIntermedia(){
    if(isEnabled()){
        this->setEnabled(0);
    }
    else{
        this->setEnabled(1);
    }
}
