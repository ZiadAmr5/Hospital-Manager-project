#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include "patient.hpp"
#include <QString>
#include <QObject>
#include <QDebug>
#include <QTableWidget>
#include "appointmentwindow.h"
MainWindow::MainWindow(hospman* h,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    ,m_hosp(h)
{
    ui->setupUi(this);

    connect(ui->RegisterButton,&QPushButton::clicked,this,&MainWindow::onRegisterClick);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::onRegisterClick()
{
    QString name = ui->nameLabel->text();
    QString Id= ui->NIDLabel->text();
    QString number = ui->NumberLabel->text();
    patient p(name.toStdString(),Id.toStdString(),number.toStdString());
    qDebug()<<"Sucess!!!";
    m_hosp->registerNewPatient(p);
    AppointmentWindow* app = new AppointmentWindow(m_hosp,this);
    app->show();

}
