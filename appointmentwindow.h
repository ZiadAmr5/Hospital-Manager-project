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
    explicit AppointmentWindow(hospman* hos,QWidget *parent = nullptr);
    ~AppointmentWindow();

private:
    Ui::AppointmentWindow *ui;
    hospman* M_hosp;
};

#endif // APPOINTMENTWINDOW_H
