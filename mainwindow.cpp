#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(this,SIGNAL(usunFigurySignal()),ui->widget,SLOT(usunFigurySlot()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonDodaj_clicked()
{
    float rozmiar = ui->doubleSpinBoxRozmiar->value();
    if(rozmiar > 0)
    {
        if(ui->checkBoxTrojkat->isChecked())
        {
            ui->widget->dodajTrojkat(0,0,rozmiar);
        }
        if(ui->checkBoxKwadrat->isChecked())
        {
            ui->widget->dodajKwadrat(-10,-10,rozmiar);
        }
        if(ui->checkBoxKolo->isChecked())
        {
            ui->widget->dodajKolo(10,10,rozmiar/2); // rozmiar/2 , bo są wieksze :)
        }

        ui->widget->updateGL();
    }
}



void MainWindow::on_pushButtonReset_clicked()
{
    emit usunFigurySignal();
}
