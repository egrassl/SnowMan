#include "mainwindow.h"
#include "ui_mainwindow.h"

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

void MainWindow::on_actionNublado_triggered()
{
    ui->widget->setSkyColor(1);
}

void MainWindow::on_actionEnsolarado_triggered()
{
    ui->widget->setSkyColor(2);
}

void MainWindow::on_actionFim_de_Tarde_triggered()
{
    ui->widget->setSkyColor(3);
}

void MainWindow::on_actionHomens_de_Lava_triggered()
{
    ui->widget->changeSnowMenTexture(2);
}

void MainWindow::on_actionHomens_de_Neve_triggered()
{
    ui->widget->changeSnowMenTexture(1);
}

void MainWindow::on_actionNeve1_triggered()
{
    ui->widget->changeFloorTexture(1);
}

void MainWindow::on_actionNeve2_triggered()
{
    ui->widget->changeFloorTexture(2);
}

void MainWindow::on_actionLava_triggered()
{
    ui->widget->changeFloorTexture(3);
}


