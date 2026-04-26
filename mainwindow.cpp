#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include "patient.hpp"
#include <QString>
#include <QObject>
#include <QDebug>
#include <QTableWidget>
#include "appointmentwindow.h"
MainWindow::MainWindow(hospman *h, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_hosp(h)
{
    ui->setupUi(this);
    connect(ui->RegisterButton, &QPushButton::clicked, this, &MainWindow::onRegisterClick);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onRegisterClick()
{
    QString name = ui->nameEdit->text();
    QString Id = ui->IdEdit->text();
    QString number = ui->NumberEdit->text();

    if(name.isEmpty() || Id.isEmpty()) return;

    patient p(name.toStdString(), Id.toStdString(), number.toStdString());

    if(m_hosp->registerNewPatient(p)) {
        AppointmentWindow *app = new AppointmentWindow(m_hosp, Id.toStdString(), this);
        app->show();
    }
}
