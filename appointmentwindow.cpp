#include "appointmentwindow.h"
#include <QTableWidget>
#include "ui_appointmentwindow.h"
#include <QDebug>
#include <QLineEdit>
#include <string>
using namespace std;
AppointmentWindow::AppointmentWindow(hospman *hos, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AppointmentWindow)
    , M_hosp(hos)
{
    ui->setupUi(this);

    // Get doctors from the manager
    const auto &doctors = M_hosp->getDoctors();
    const auto &slot = M_hosp->getSlots();

   // ui->DocTable->setRowCount(doctors.size());
    ui->DocTable->setRowCount(slot.size());
    qDebug()<<"slot size is: "<<slot.size();
    ui->DocTable->setColumnCount(6); // this controls the number of colm.
    for(int i=0;i<slot.size();i++)
    {
        const string current_ID= slot[i].getD_ID();
        string c_Name = "unknown";
        string c_Dept= "no department";
        for(const auto& d:doctors)
        {
            if(d.getID()==current_ID)
            {
                c_Name =d.getName();
                c_Dept = d.getDept();
                break;
            }
        }
        ui->DocTable->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(c_Name)));
        ui->DocTable->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(current_ID)));
        ui->DocTable->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(c_Dept)));
        ui->DocTable->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(slot[i].getDay())));
        ui->DocTable->setItem(i,4,new QTableWidgetItem(QString::fromStdString(slot[i].getTime())));
    }

    ui->DocTable->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->DocTable->setSelectionMode(QAbstractItemView::SingleSelection);


}

AppointmentWindow::~AppointmentWindow()
{
    delete ui;
}

void AppointmentWindow::on_SearchEdit_textChanged(const QString &arg1)
{
    string TexttoSearch = arg1.toLower().toStdString(); //converts the search test to lower case and then to standard string
    UpdateTable(TexttoSearch);
}
void AppointmentWindow::UpdateTable(string Filter) //rows go to zero then to the number containing the search
{
    const auto &doctors = M_hosp->getDoctors();
    const auto &slot = M_hosp->getSlots();

    ui->DocTable->setRowCount(0); //this makes the rows "dissappear"
    for(int i=0;i<slot.size();i++)
    {
        const string current_ID= slot[i].getD_ID();
        string c_Name = "unknown";
        string c_Dept= "no department";
        for(const auto& d:doctors)
        {
            if(d.getID()==current_ID)
            {
                c_Name =d.getName();
                c_Dept = d.getDept();
                break;
            }
        }
        string lowName = c_Name;  //variables for lower case
        string lowDep =c_Dept;
        for(auto& cs: lowName) //cs is short for case. we convert the strings from the csv file itself to lower case, so that the search text and the file text have a match
        {
            cs = tolower(cs);
        }
        for(auto& cs:lowDep)
        {
            cs= tolower(cs);
        }
        if(Filter.empty()||lowName.find(Filter)!=string::npos||lowDep.find(Filter)!=string::npos)
        {
            int row= ui->DocTable->rowCount(); // takes current row
            ui->DocTable->insertRow(row);

            ui->DocTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(c_Name)));
            ui->DocTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(current_ID)));
            ui->DocTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(c_Dept)));
            ui->DocTable->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(slot[i].getDay())));
            ui->DocTable->setItem(row,4,new QTableWidgetItem(QString::fromStdString(slot[i].getTime())));
        }


    }

}

