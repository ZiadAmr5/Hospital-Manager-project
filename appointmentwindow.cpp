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

    ui->DocTable->setSelectionBehavior(QAbstractItemView::SelectRows); //these 3 lines prevent clicking on parts of the row or editing them
    ui->DocTable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->DocTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    UpdateTable("");
}

AppointmentWindow::~AppointmentWindow()
{
    delete ui;
}

void AppointmentWindow::UpdateTable(string Filter)
{
    const auto &doctors = M_hosp->getDoctors();
    const auto &slot = M_hosp->getSlots();

    ui->DocTable->setRowCount(0);

    for(int i = 0; i < (int)slot.size(); i++)
    {
        const string current_ID = slot[i].getD_ID();
        string c_Name = "unknown";
        string c_Dept = "no department";

        // Lookup Doctor Info
        for(const auto& d : doctors) {
            if(d.getID() == current_ID) {
                c_Name = d.getName();
                c_Dept = d.getDept();
                break;
            }
        }

        // Filtering Logic (Case Insensitive)
        string lowName = c_Name;
        string lowDep = c_Dept;
        for(auto& cs : lowName) cs = tolower(cs);
        for(auto& cs : lowDep) cs = tolower(cs);

        if(Filter.empty() || lowName.find(Filter) != string::npos || lowDep.find(Filter) != string::npos)
        {
            int row = ui->DocTable->rowCount();
            ui->DocTable->insertRow(row);

            // IMPORTANT: Store the hidden index 'i' for booking later
            QTableWidgetItem *nameItem = new QTableWidgetItem(QString::fromStdString(c_Name));
            nameItem->setData(Qt::UserRole, i);

            ui->DocTable->setItem(row, 0, nameItem);
            ui->DocTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(current_ID)));
            ui->DocTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(c_Dept)));
            ui->DocTable->setItem(row, 3, new QTableWidgetItem(slot[i].getDate().toString("yyyy-MM-dd")));
            ui->DocTable->setItem(row, 4, new QTableWidgetItem(slot[i].getTime().toString("HH:mm")));

            string status = slot[i].checkStatus() ? "Booked" : "Available";
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
    if (M_hosp->bookAppointment(row, m_patientID, errorMsg))
    {
        QMessageBox::information(this, "Success", "Appointment booked successfully!");
        UpdateTable(ui->SearchEdit->text().toStdString());
    } else {
        QMessageBox::warning(this, "Booking Failed", QString::fromStdString(errorMsg));
    }
}
