#ifndef APPOINTMENTWINDOW_H
#define APPOINTMENTWINDOW_H

#include <QDialog>
#include <string>
#include "hospmanager.hpp"
namespace Ui {
class AppointmentWindow;
}

class AppointmentWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AppointmentWindow(hospman *hos, std::string patientID, QWidget *parent = nullptr);
    void UpdateTable(std::string Filter);
    ~AppointmentWindow();

private slots:
    void on_SearchEdit_textChanged(const QString &arg1);
    void on_DocTable_cellDoubleClicked(int row, int column); // Added this line

private:
    Ui::AppointmentWindow *ui;
    hospman *M_hosp;
    std::string m_patientID;
};
#endif // APPOINTMENTWINDOW_H
