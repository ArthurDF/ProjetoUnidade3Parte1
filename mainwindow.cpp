#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>
#include <cstdlib>
int ip;
bool state=false;

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent), ui(new Ui::MainWindow){
  ui->setupUi(this);
  socket = new QTcpSocket(this);
  tcpConnect();


  connect(ui->pushButtonPut,
          SIGNAL(clicked(bool)),
          this,
          SLOT(start()));

}


void MainWindow::tcpConnect(){
  QString IP = ui->IPText->toPlainText();

  socket->connectToHost(IP,1234);
  if(socket->waitForConnected(3000)){
    qDebug() << "Connected";
  }
  else{
    qDebug() << "Disconnected";
  }
}


void MainWindow::tcpDisconnect(){


  socket->disconnectFromHost();
  if(socket->waitForConnected(3000)){
    qDebug() << "Connected";
  }
  else{
    qDebug() << "Disconnected";
  }
}
void MainWindow::timerEvent(QTimerEvent *e){
    putData();

}
void MainWindow::start(){
   int time=ui->timmingSlider->value();

   if(state==false){
     ip=startTimer(time*1000);
     state=true;
    }
}
void MainWindow::stop(){
    killTimer(ip);
    state=false;
}
void MainWindow::sliderStart(){
    if(state==true){
        int time=ui->timmingSlider->value();
            killTimer(ip);
            ip=startTimer(time*1000);
    }
}


void MainWindow::putData(){
  QDateTime datetime;
  QString str;
  //qint64 msecdate;
  const QString data="yyyy-MM-ddThh:mm:ss";
  int minimo=ui->minSlider->value(), maximo=ui->maxSlider->value();

  if(socket->state()== QAbstractSocket::ConnectedState){

    //msecdate = QDateTime::currentDateTime().toMSecsSinceEpoch();
    //str = "set "+ QString::number(msecdate) + " " + QString::number(qrand()%35)+"\r\n";
    str = "set "+ QDateTime::currentDateTime().toString(data) + " " + QString::number((qrand()%(maximo-minimo+1)+minimo))+"\r\n";
    ui->saidaTexto->append(str);
      qDebug() << str;
      qDebug() << socket->write(str.toStdString().c_str()) << " bytes written";
      if(socket->waitForBytesWritten(3000)){
        qDebug() << "wrote";
      }
  }
}



MainWindow::~MainWindow(){
  delete socket;
  delete ui;
}
