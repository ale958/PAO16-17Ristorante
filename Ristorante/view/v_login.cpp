#include "v_login.h"

VLogin::VLogin(){
    this->setAttribute(Qt::WA_DeleteOnClose);
    setWindowTitle("Finestra di accesso");
    setWindowFlags(windowFlags()  & ~Qt::WindowContextHelpButtonHint);

    lUsername=new QLabel("Username");
    lPassword=new QLabel("Password");
    tUsername=new QLineEdit();
    tPassword=new QLineEdit();

    tUsername->setPlaceholderText("Inserisci username");
    tPassword->setPlaceholderText("Inserisci password");

    tUsername->setValidator(new QRegExpValidator(QRegExp("[A-Za-z0-9]{1,15}")));

    tPassword->setEchoMode(QLineEdit::Password);

    pLogin=new QPushButton("Login");

    gridLogin=new QGridLayout;
    gridLogin->addWidget(lUsername, 0,0);
    gridLogin->addWidget(tUsername,0,1);
    gridLogin->addWidget(lPassword,1,0);
    gridLogin->addWidget(tPassword,1,1);
    gridLogin->addWidget(pLogin,2,1);

    layoutLogin=new QVBoxLayout();
    layoutLogin->addLayout(gridLogin);
    setLayout(layoutLogin);

    connect(pLogin,SIGNAL(clicked()),this,SLOT(login()));
}

void VLogin::login(){
    emit provaLogin(tUsername->text(),tPassword->text());
}

void VLogin::svuota(){
    tPassword->clear();
    tUsername->clear();
    tUsername->setFocus();
}
