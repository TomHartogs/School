#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"

#include <stdio.h>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::on_SchutSluice1_clicked()
{
  qDebug() << "test";
}

void MainWindow::on_SchutSluice2_clicked()
{

}

void MainWindow::on_SchutSluice3_clicked()
{

}

void MainWindow::on_SchutSluice4_clicked()
{

}
