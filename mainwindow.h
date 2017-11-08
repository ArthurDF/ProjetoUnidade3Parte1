#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QDebug>

namespace Ui {

class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
    /**
   * @brief timerEvent temporizador que faz a chamada da função putData() a cada time(definido pelo usuario) segundos
   * @param e evento QTimer
   */
  void timerEvent(QTimerEvent *e);
  

public slots:
  /**
   * @brief putData realiza o envio de dados para o servidor e mostra no browser a data, hora e numero de dados enviados
   * a data e hora estao no formato yyyy-MM-ddThh:mm:ss
   * o numero minimo e maximo de dados é definido pelo usuario nos sliders MIN e MAX, respectivamente
   */
  void putData();
  /**
    * @brief tcpConnect faz a conexão com o servidor TCP com o click do botao Connect usando o IP digitado pelo usuario no editor de texto
    */
   void tcpConnect();
   /**
    * @brief tcpDisconnect desconecta o IP ao servidor TCP com o click do botao Disconnect
    */
   void tcpDisconnect();
   /**
    * @brief start dá inicio ao envio de dados com o click do botao Start dando inicio ao timer
    * a frequencia do timer(quantas vezes os dados são enviados por segundo) é definida pelo usuario no slider Timing
    */
   void start();
   /**
    * @brief stop termina o envio de dados com o click do botao Stop finalizando o timer
    */
   void stop();
   /**
    * @brief sliderStart atualiza frequencia de envio de dados de acordo com a atualização do slider do Timming
    */
   void sliderStart();

private:
  Ui::MainWindow *ui;
  QTcpSocket *socket;
};

#endif // MAINWINDOW_H
