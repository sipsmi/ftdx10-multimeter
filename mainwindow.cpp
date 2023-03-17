#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <XmlRpcCpp.h>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTimer *timer = new QTimer(this); // timer for regular polls
    connect(timer, &QTimer::timeout, this, &MainWindow::TimerSlot ); // connect it

    ui->statusbar->showMessage("G0FOZ: FTDX10 Control Panel v0.01alpha");
    ui->freqLabel->setText("  3.523.100");
    ui->power->setValue( 0);
    ui->swr->setValue( 0);

   timer->start(100); // 0.5 second clock ticks to poll XML-RPC values

}
// destructor
MainWindow::~MainWindow() {     delete ui; }
// Exit on menu
void MainWindow::on_actionQuit_triggered() {   qApp->exit(); }
// trap and pass to poll timer
void MainWindow::on_actionUpdate_Frequency_triggered() {     this->TimerSlot(); }

// handle the 0.5 second clock ticks
void MainWindow::TimerSlot()
{
    double po = getMeter(catCodeReadPO)*(100.0/255.0);
    double alc = getMeter(catCodeReadALC)*(5.0/255.0);
    double idd=  getMeter(catCodeReadIDD)*(25.0/255.0);
    double swr = getMeter(catCodeReadSWR)*(5.0/255.0);


    ui->freqLabel->setText( callRPC("rig.get_vfo") );
    ui->power->setValue(0);
    // update the test labels

    ui->sText->setText( QString::number(getMeter(catCodeReadS)) );
    ui->swrText->setText( QString::number(getMeter(catCodeReadSWR)) );
    ui->iddText->setText( QString::number(getMeter(catCodeReadIDD)) );
    ui->poText->setText( QString::number((getMeter(catCodeReadPO)*100)/255 ));
    ui->alcText->setText( QString::number((getMeter(catCodeReadALC)*5)/255  ) );

     ui->sMeter->setValue( getMeter(catCodeReadS));
     ui->alc->setValue( alc );
     ui->power->setValue(  po);
     ui->idd->setValue( idd );
     ui->swr->setValue( swr );
//    ui->iddText->setText( QString::number(getMeter(catCodeReadIDD)) );


}

QString MainWindow::callRPC(std::string call)
{
        xmlrpc_c::clientSimple myClient;
        xmlrpc_c::value result;

         myClient.call(serverUrl, call,  &result);
         std::string const retval((xmlrpc_c::value_string(result)));
         return QString::fromStdString(retval);

}// NEW to read the file and set to label

QString MainWindow::callRPCCatString(std::string catcall)
    {
            xmlrpc_c::clientSimple myClient;
            xmlrpc_c::value result;

             myClient.call(serverUrl, "rig.cat_string",  &result);
             std::string const retval((xmlrpc_c::value_string(result)));
             return QString::fromStdString(retval);

}// NEW to read the file and set to label

int MainWindow::getMeter(std::string meterType)
{
    std::string valueStr;
    xmlrpc_c::paramList parms;
    parms.add(xmlrpc_c::value_string(meterType));
    xmlrpc_c::clientSimple myClient;
    xmlrpc_c::value result;

     myClient.call(serverUrl, "rig.cat_string",parms, &result);
     std::string const retval((xmlrpc_c::value_string(result)));
     // RM response
     // "RMxyyyzzz;"  P2 = 0-255
     valueStr = retval.substr(3,3);
     return stoi(valueStr);
}

