#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

// Linux headers
#include <fcntl.h> // Contains file controls like O_RDWR
#include <errno.h> // Error integer and strerror() function
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h> // write(), read(), close()

// simple XML client
#include <xmlrpc-c/base.hpp>
#include <xmlrpc-c/client_simple.hpp>

// general includes
#include <string>



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QTimer *timer; // NEW

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
 //   int serial_port =0;
    void updatePoll(); //
    QString callRPC(std::string call); // CAT string
    QString callRPCCatString(std::string catcall); // CAT string
    int getMeter(std::string meterType);  // Call the CAT but specific to meter 255 extractio
    void debugMsg(std::string msg);

private slots:
    void on_actionQuit_triggered();
    void on_actionUpdate_Frequency_triggered();
    void TimerSlot(); // NEW slot

private:
    Ui::MainWindow *ui;
     const std::string serverUrl = "http://localhost:12345/";

    // FTDX10 CAT codes for meters
    const  std::string catCodeReadALC = "RM4;";
    const std::string catCodeReadSWR = "RM6;";
    const std::string catCodeReadPO = "RM5;";
    const std::string catCodeReadIDD = "RM7;";
    const std::string catCodeReadCOMP = "RM3;";
    const std::string catCodeReadS = "RM1;";
    const bool tdebug = true;


};
#endif // MAINWINDOW_H
