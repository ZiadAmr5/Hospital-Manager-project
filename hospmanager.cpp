#include "hospmanager.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <QDateTime>
using namespace std;
void hospman::loadinitialData()
{
    ifstream docFile("doctors.csv");
    string line, header;
    
    if (docFile.is_open()) {
        getline(docFile, header);
        while (getline(docFile, line)) {
            stringstream Docss(line);
            string name, id, dept;
            getline(Docss, name, ',');
            getline(Docss, id, ',');
            getline(Docss, dept);
            doctor.push_back(Doctor(id, name, dept));
        }
        docFile.close();
    }

    ifstream avfile("availability.csv");
    if (avfile.is_open()) {
        getline(avfile, header);
        QDate today = QDate::currentDate();

        while (getline(avfile, line)) {
            stringstream AVss(line);
            string id, dayStr, startStr, endStr;
            getline(AVss, id, ',');
            getline(AVss, dayStr, ',');
            getline(AVss, startStr, ',');
            getline(AVss, endStr, ',');

            QTime startTime = QTime::fromString(QString::fromStdString(startStr), "HH:mm");
            QTime endTime = QTime::fromString(QString::fromStdString(endStr), "HH:mm");

            for (int i = 0; i < 60; ++i) {
                QDate targetDate = today.addDays(i);
                if (targetDate.toString("dddd").toStdString() == dayStr) {
                    QTime slotTime = startTime;
                    while (slotTime.addSecs(20 * 60) <= endTime) {
                        appointments.push_back(Appointment(id, targetDate, slotTime));
                        slotTime = slotTime.addSecs(20 * 60);
                    }
                }
            }
        }
        avfile.close();
    }
}

bool hospman::bookAppointment(int slotIndex, string pID, string &errorMsg)
{
    if (slotIndex < 0 || slotIndex >= (int)appointments.size()) return false;
    
    Appointment &app = appointments[slotIndex];
    QDateTime now = QDateTime::currentDateTime();
    QDateTime slotDateTime(app.getDate(), app.getTime());

    if (app.checkStatus()) {
        errorMsg = "Slot already booked.";
        return false;
    }

    if (now.secsTo(slotDateTime) < 3600) {
        errorMsg = "Must book at least 1 hour in advance.";
        return false;
    }

    if (now.date().daysTo(app.getDate()) > 60) {
        errorMsg = "Cannot book more than 2 months in advance.";
        return false;
    }

    for (const auto& a : appointments) {
        if (a.checkStatus() && a.getP_ID() == pID) {
            if (a.getDate() == app.getDate() && a.getTime() == app.getTime()) {
                errorMsg = "Double booking detected for this patient.";
                return false;
            }
        }
    }

    app.setBooked(pID);
    return true;
}

bool hospman::registerNewPatient(const patient &p)
{
    for (const auto &existing : patients) {
        if (existing.getID() == p.getID()) {
            return false;
        }
    }
    patients.push_back(p);
    return true;
}

void hospman::saveallData()
{
    ofstream outPat("patients_saved.csv");
    for (auto &p : patients) {
        outPat << p.getID() << "," << p.getName() << "," << p.getMobile() << endl;
    }
    outPat.close();
}
