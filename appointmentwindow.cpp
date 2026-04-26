#include "appointmentwindow.h"
#include <QTableWidget>
#include "ui_appointmentwindow.h"
#include <QDebug>
#include <QLineEdit>
#include <string>
#include <QMessageBox>
using namespace std;
AppointmentWindow::AppointmentWindow(hospman *hos, std::string patientID, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AppointmentWindow)
    , M_hosp(hos)
    , m_patientID(patientID)
{
    ui->setupUi(this);
    ui->DocTable->setColumnCount(6);
    QStringList headers;
    headers << "Doctor Name" << "ID" << "Department" << "Date" << "Time" << "Status";
    ui->DocTable->setHorizontalHeaderLabels(headers);
    UpdateTable("");
}

AppointmentWindow::~AppointmentWindow()
{
    delete ui;
}

void AppointmentWindow::UpdateTable(std::string Filter)
{
    ui->DocTable->setRowCount(0);
    const auto &doctors = M_hosp->getDoctors();
    const auto &allSlots = M_hosp->getSlots(); // Renamed from 'slots'

    for (int i = 0; i < (int)allSlots.size(); i++) {
        std::string c_Name = "Unknown";
        std::string c_Dept = "No Dept";

        for (const auto &d : doctors) {
            if (d.getID() == allSlots[i].getD_ID()) {
                c_Name = d.getName();
                c_Dept = d.getDept();
                break;
            }
        }

        std::string searchTarget = c_Name + " " + c_Dept;
        for(auto &c : searchTarget) c = tolower(c);
        std::string lowFilter = Filter;
        for(auto &c : lowFilter) c = tolower(c);

        if (Filter.empty() || searchTarget.find(lowFilter) != std::string::npos) {
            int row = ui->DocTable->rowCount();
            ui->DocTable->insertRow(row);
            ui->DocTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(c_Name)));
            ui->DocTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(allSlots[i].getD_ID())));
            ui->DocTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(c_Dept)));
            ui->DocTable->setItem(row, 3, new QTableWidgetItem(allSlots[i].getDate().toString("yyyy-MM-dd")));
            ui->DocTable->setItem(row, 4, new QTableWidgetItem(allSlots[i].getTime().toString("HH:mm")));

            std::string status = allSlots[i].checkStatus() ? "Booked (" + allSlots[i].getP_ID() + ")" : "Available";
            ui->DocTable->setItem(row, 5, new QTableWidgetItem(QString::fromStdString(status)));
        }
    }
}

void AppointmentWindow::on_SearchEdit_textChanged(const QString &arg1)
{
    UpdateTable(arg1.toStdString());
}

void AppointmentWindow::on_DocTable_cellDoubleClicked(int row, int column)
{
    std::string errorMsg;
    if (M_hosp->bookAppointment(row, m_patientID, errorMsg)) {
        QMessageBox::information(this, "Success", "Appointment booked successfully!");
        UpdateTable(ui->SearchEdit->text().toStdString());
    } else {
        QMessageBox::warning(this, "Booking Failed", QString::fromStdString(errorMsg));
    }
}
