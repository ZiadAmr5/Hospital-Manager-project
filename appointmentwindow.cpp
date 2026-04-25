#include "appointmentwindow.h"
#include "ui_appointmentwindow.h"
#include <QTableWidget>

AppointmentWindow::AppointmentWindow(hospman* hos,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AppointmentWindow)
    ,M_hosp(hos)
{
    ui->setupUi(this);




        // Get doctors from the manager
        const auto& doctors = M_hosp->getDoctors();

    ui->DocTable->setRowCount(doctors.size());
        ui->DocTable->setColumnCount(2);

        for(int i = 0; i < doctors.size(); ++i) {
            ui->DocTable->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(doctors[i].getName())));
            ui->DocTable->setItem(i, 1, new QTableWidgetItem("Available"));
        }

}

AppointmentWindow::~AppointmentWindow()
{
    delete ui;
}
