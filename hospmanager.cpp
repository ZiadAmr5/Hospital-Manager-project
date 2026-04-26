#include "hospmanager.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <QDateTime>
#include <algorithm> 
using namespace std;
void hospman::loadinitialData()
{
    ifstream docFile("doctors.csv");
    string line, header;

    if (!docFile.is_open()) {
        cout << "FAILED to open doctors.csv! Check if it is in the build folder." << endl;
    } else {
        getline(docFile, header);
        int count = 0;
        while (getline(docFile, line)) {
            if (line.empty() || line[0] == '\r') continue;
            stringstream Docss(line);
            string name, id, dept;
            getline(Docss, name, ',');
            getline(Docss, id, ',');
            getline(Docss, dept);
            if (!dept.empty() && dept.back() == '\r') dept.pop_back();

            doctor.push_back(Doctor(id, name, dept));
            count++;
        }
        cout << "Successfully loaded " << count << " doctors." << endl;
        docFile.close();
    }

    ifstream avfile("availability.csv");
    if (!avfile.is_open()) {
        cout << "FAILED to open availability.csv!" << endl;
    } else {
        getline(avfile, header);
        QDate today = QDate::currentDate();
        int slotCount = 0;

        while (getline(avfile, line)) {
            if (line.empty() || line[0] == '\r') continue;
            stringstream AVss(line);
            string id, dayStr, startStr, endStr;
            getline(AVss, id, ',');
            getline(AVss, dayStr, ',');
            getline(AVss, startStr, ',');
            getline(AVss, endStr);
            if (!endStr.empty() && endStr.back() == '\r') endStr.pop_back();

            QTime startTime = QTime::fromString(QString::fromStdString(startStr), "HH:mm");
            QTime endTime = QTime::fromString(QString::fromStdString(endStr), "HH:mm");

            for (int i = 0; i < 60; ++i) {
                QDate targetDate = today.addDays(i);
                if (targetDate.toString("dddd").toStdString() == dayStr) {
                    QTime slotTime = startTime;
                    while (slotTime.addSecs(20 * 60) <= endTime) {
                        appointments.push_back(Appointment(id, targetDate, slotTime));
                        slotTime = slotTime.addSecs(20 * 60);
                        slotCount++;
                    }
                }
            }
        }
        cout << "Generated " << slotCount << " appointment slots for the next 60 days." << endl;
        avfile.close();
    }
}
bool hospman::registerNewPatient(const patient &p) {
    for (const auto &existing : patients) {
        if (existing.getID() == p.getID()) return false;
    }
    patients.push_back(p);
    return true;
}

bool hospman::bookAppointment(int slotIndex, string pID, string &errorMsg) {
    
    return true;
}

const vector<Doctor>& hospman::getDoctors() {
    return doctor;
}

const vector<Appointment>& hospman::getSlots() {
    return appointments;
}
