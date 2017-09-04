#include "v_gestione_profilo.h"

VGestioneProfilo::VGestioneProfilo(UtenteGenerico *ut, UtenteGenerico *utmod):utente(ut),utenteModifica(utmod)
{
    this->setAttribute(Qt::WA_DeleteOnClose);

    setWindowFlags(windowFlags()& ~Qt::WindowContextHelpButtonHint);
    setWindowTitle("Gestione Utente");
    addLayoutMod();
    setModal(1);
}

void VGestioneProfilo::addLayoutMod()
{

    lNome=new QLabel("Nome");
    lCognome=new QLabel("Cognome");
    lUsername=new QLabel("Username");
    lPassword=new QLabel("Password");
    lTipo=new QLabel("Tipo");

    lRuolo=new QLabel(utenteModifica->getTipo());
    tNome=new QLineEdit();
    tNome->setValidator(new QRegExpValidator(QRegExp("[A-Za-z]{1,15}")));
    tCognome=new QLineEdit();
    tCognome->setValidator(new QRegExpValidator(QRegExp("[A-Za-z]{1,15}")));
    tUsername=new QLineEdit();
    tUsername->setValidator(new QRegExpValidator(QRegExp("[A-Za-z0-9]{1,15}")));
    tPassword=new QLineEdit();

    cSelezioneTipo=new QComboBox();

    cSelezioneTipo->addItem("cameriere");
    cSelezioneTipo->addItem("cuoco");

    cSelezioneTipo->setCurrentText(utenteModifica->getTipo());

    tNome->setPlaceholderText("Inserisci nome");
    tCognome->setPlaceholderText("Inserisci cognome");
    tUsername->setPlaceholderText("Inserisci username");
    tPassword->setPlaceholderText("Inserisci password");

    tNome->setText(utenteModifica->getNome());
    tCognome->setText(utenteModifica->getCognome());
    tUsername->setText(utenteModifica->getUsername());
    tPassword->setText(utenteModifica->getPassword());

    pModifica=new QPushButton("Salva le modifiche");
    pElimina=new QPushButton("Elimina l'utente");
    pAggiungi=new QPushButton("Aggiungi Utente");

    gridUtGestione=new QGridLayout;
    gridUtGestione->addWidget(lNome, 0,0);
    gridUtGestione->addWidget(lCognome,1,0);
    gridUtGestione->addWidget(lUsername,2,0);
    gridUtGestione->addWidget(lPassword,3,0);

    gridUtGestione->addWidget(tNome, 0,1);
    gridUtGestione->addWidget(tCognome,1,1);
    gridUtGestione->addWidget(tUsername,2,1);
    gridUtGestione->addWidget(tPassword,3,1);

    gridUtGestione->addWidget(lTipo,4,0);
    gridUtGestione->addWidget(cSelezioneTipo,4,1);
    gridUtGestione->addWidget(lRuolo,4,1);
    gridUtGestione->addWidget(pModifica,6,0);
    gridUtGestione->addWidget(pElimina,6,1);
    gridUtGestione->addWidget(pAggiungi,7,0);

    layoutUtGestione=new QVBoxLayout();
    layoutUtGestione->addLayout(gridUtGestione);

    connect(pModifica,SIGNAL(clicked()),this,SLOT(save_change_profilo()));
    connect(pAggiungi,SIGNAL(clicked()),this,SLOT(aggiungiUtente()));
    connect(pElimina,SIGNAL(clicked()),this,SLOT(save_delete()));

    setLayout(layoutUtGestione);
}

void VGestioneProfilo::setLayoutMod()
{
    pAggiungi->hide();
    if(utente->canDoGestione() && utente->getUsername()!=utenteModifica->getUsername()){
        lRuolo->hide();
    }
    else{

        cSelezioneTipo->hide();
        pElimina->hide();
    }
}

void VGestioneProfilo::resetTextUsername()
{
    tUsername->clear();
    tUsername->setText(utenteModifica->getUsername());
    tUsername->setFocus();
}
void VGestioneProfilo::svuota()
{
    tPassword->clear();
    tUsername->clear();
    tNome->clear();
    tCognome->clear();
    tUsername->setFocus();
}

void VGestioneProfilo::setLayoutAggiungi()
{
    pAggiungi->show();
    pElimina->hide();
    pModifica->hide();
    lRuolo->hide();
    cSelezioneTipo->show();
    this->svuota();
}

void VGestioneProfilo::save_change_profilo()
{

    if(tNome->text()!=""&&tCognome->text()!=""&&tUsername->text()!=""&&tPassword->text()!=""){
        if(utenteModifica->getTipo()=="admin"){
            emit inviaModifica(utenteModifica,tNome->text(),tCognome->text(),
                               tUsername->text(), tPassword->text(), lRuolo->text());
        }
        else{
            emit inviaModifica(utenteModifica,tNome->text(),tCognome->text(),
                               tUsername->text(), tPassword->text(), cSelezioneTipo->currentText());
        }
    }
    else{
        tNome->setText(utenteModifica->getNome());

        tCognome->setText(utenteModifica->getCognome());

        tUsername->setText(utenteModifica->getUsername());

        tPassword->setText(utenteModifica->getPassword());
        QMessageBox::warning(0,"Modifiche fallite","Compilare tutti i campi");
    }

}

void VGestioneProfilo::aggiungiUtente()
{
  if(tNome->text()!=""&&tCognome->text()!=""&&tUsername->text()!=""&&tPassword->text()!=""){
     UtenteGenerico *tmpUtente=nullptr;
     if(cSelezioneTipo->currentText()=="cameriere"){
        tmpUtente= new Cameriere(tNome->text(),tCognome->text(), tUsername->text(),tPassword->text());
     }
     else if(cSelezioneTipo->currentText()=="cuoco"){
         tmpUtente= new Cuoco(tNome->text(),tCognome->text(), tUsername->text(),tPassword->text());
     }
     emit addGUtenti(tmpUtente);
 }
 else{
     QMessageBox::warning(0,"Attenzione","È necessario riempire tutti i campi dati");
 }
}
void VGestioneProfilo::save_delete()
{
    emit inviaElimina(utenteModifica);
    if(utente==utenteModifica){
        emit logout();
    }
    this->close();
}
