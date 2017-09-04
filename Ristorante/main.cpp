#include"model/database_tavoli.h"
#include"model/database_utenti.h"
#include"controller/c_main_windows.h"
#include<QApplication>


 int main(int argc, char *argv[])
{
    QApplication app(argc,argv);

    CMainWindows prima;

    prima.esecuzioneLogin();

    return app.exec();

 }

