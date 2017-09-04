#ifndef VW_LOGIN_H
#define  VW_LOGIN_H
#include<QDialog>
#include<QGridLayout>
#include<QLabel>
#include<QPushButton>
#include<QLineEdit>
#include<QVBoxLayout>
#include<QString>
#include<QRegExpValidator>
#include<QMessageBox>

class VLogin: public QDialog{
private:
    Q_OBJECT
    QGridLayout * gridLogin;
    QLineEdit * tUsername;
    QLineEdit * tPassword;
    QLabel * lUsername;
    QLabel *lPassword;
    QPushButton *pLogin;
    QVBoxLayout *layoutLogin;

public:
    VLogin();
    void svuota();

public slots:
    void login();

signals:
    void provaLogin(const QString&, const QString&);
};

#endif //  VW_LOGIN_H
