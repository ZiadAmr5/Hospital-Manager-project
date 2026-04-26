#ifndef APPOINTMENTWINDOW_H
#define APPOINTMENTWINDOW_H

#include <QDialog>
#include "hospmanager.hpp"

namespace Ui {
class AppointmentWindow;
}

class AppointmentWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AppointmentWindow(hospman *hos, QWidget *parent = nullptr);
    void UpdateTable(string Filter);
    ~AppointmentWindow();

private slots:
    void on_SearchEdit_textChanged(const QString &arg1);

private:
    Ui::AppointmentWindow *ui;
    hospman *M_hosp;
};

#endif // APPOINTMENTWINDOW_H
