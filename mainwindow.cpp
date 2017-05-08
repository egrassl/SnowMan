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

void MainWindow::on_actionHomens_de_Grama_triggered()
{
    ui->widget->changeSnowMenTexture(3);
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

void MainWindow::on_actionGrama_triggered()
{
    ui->widget->changeFloorTexture(4);
}


void MainWindow::on_actionHomen_de_Neve_1_triggered()
{
    ui->widget->changeActiveSnowMan(0);
}

void MainWindow::on_actionHomem_de_Neve_2_triggered()
{
    ui->widget->changeActiveSnowMan(1);
}

void MainWindow::on_actionHomem_de_Neve_3_triggered()
{
    ui->widget->changeActiveSnowMan(2);
}

void MainWindow::on_actionHomem_de_Neve_4_triggered()
{
    ui->widget->changeActiveSnowMan(3);
}

void MainWindow::on_actionHomem_de_Neve_5_triggered()
{
    ui->widget->changeActiveSnowMan(4);
}
