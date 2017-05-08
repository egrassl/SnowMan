#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <glwidget.h>

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
    void on_actionEnsolarado_triggered();

    void on_actionNublado_triggered();

    void on_actionHomens_de_Lava_triggered();

    void on_actionHomens_de_Neve_triggered();

    void on_actionNeve1_triggered();

    void on_actionNeve2_triggered();

    void on_actionLava_triggered();

    void on_actionFim_de_Tarde_triggered();

    void on_actionGrama_triggered();

    void on_actionHomens_de_Grama_triggered();

    void on_actionHomen_de_Neve_1_triggered();

    void on_actionHomem_de_Neve_2_triggered();

    void on_actionHomem_de_Neve_3_triggered();

    void on_actionHomem_de_Neve_4_triggered();

    void on_actionHomem_de_Neve_5_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
