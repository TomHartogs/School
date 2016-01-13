#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private slots:
  void on_SchutSluice1_clicked();

  void on_SchutSluice3_clicked();

  void on_SchutSluice2_clicked();

  void on_SchutSluice4_clicked();

private:
  Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
