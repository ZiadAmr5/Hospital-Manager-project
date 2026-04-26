#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "hospmanager.hpp"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(hospman *h, QWidget *parent = nullptr);
    void onRegisterClick();
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    hospman *m_hosp;
};
#endif // MAINWINDOW_H
