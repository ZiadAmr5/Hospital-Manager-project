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
               if (targetDate.toString("dddd").toLower().toStdString() == QString::fromStdString(dayStr).toLower().toStdString()) {
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
    ifstream inPat("patients_saved.csv");
    string pLine;
    while (getline(inPat, pLine)) {
        if (pLine.empty()) continue;
        stringstream ss(pLine); //string stream method, turning strings into an input/output stream, easier to divide the string this way ( as "tokens")
        string id, name, mob;
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, mob);
        patients.push_back(patient(id, name, mob));
    }
    inPat.close();

    // NEW: Load Saved Bookings and Apply them to the slots
    ifstream inApp("bookings_saved.csv");
    string aLine;
    while (getline(inApp, aLine)) {
        if (aLine.empty()) continue;
        stringstream ss(aLine);
        string dID, pID, dStr, tStr;
        getline(ss, dID, ',');
        getline(ss, pID, ',');
        getline(ss, dStr, ',');
        getline(ss, tStr);

        // Loop through generated slots to find the match
        for (auto &slot : appointments) {
            if (slot.getD_ID() == dID &&
                slot.getDate().toString("yyyy-MM-dd").toStdString() == dStr &&
                slot.getTime().toString("HH:mm").toStdString() == tStr) {

                slot.setBooked(pID); // "Re-book" the slot in memory
                break;
            }
        }
    }
    inApp.close();
}

bool hospman::registerNewPatient(const patient &p) {
    for (const auto &existing : patients) {
        if (existing.getID() == p.getID()) return false;
    }
    patients.push_back(p);
    return true;
}
void hospman::saveallData()
{

    ofstream outPat("patients_data.csv");
    if (outPat.is_open()) {
        for (const auto &p : patients) {
            outPat << p.getID() << ","
                   << p.getName() << ","
                   << p.getMobile() << "\n";
        }
        outPat.close();
        cout << "Patient records saved successfully." << endl;
    }

    ofstream outApp("bookings_saved.csv");
    if (outApp.is_open()) {
        for (const auto &a : appointments)
        {
            if (a.checkStatus())
            { // Only save if the slot is NOT available
                outApp << a.getD_ID() << ","
                       << a.getP_ID() << ","
                       << a.getDate().toString("yyyy-MM-dd").toStdString() << ","
                       << a.getTime().toString("HH:mm").toStdString() << "\n";
            }
        }
        outApp.close();
        cout << "Booking data saved successfully." << endl;
    }
}

bool hospman::bookAppointment(int slotIndex, string pID, string &errorMsg) {
    // Safety check: Index out of bounds
    if (slotIndex < 0 || slotIndex >= (int)appointments.size()) {
        errorMsg = "Invalid selection.";
        return false;
    }

    Appointment &selected = appointments[slotIndex];

    // Rule 1: Check if already booked (Status check)
    if (selected.checkStatus()) {
        errorMsg = "This slot is already taken by another patient.";
        return false;
    }

    // Rule 2: 1-hour advance notice (Rule h)
    QDateTime now = QDateTime::currentDateTime();
    QDateTime slotDT(selected.getDate(), selected.getTime());
    if (now.secsTo(slotDT) < 3600) {
        errorMsg = "Appointments must be booked at least 1 hour in advance.";
        return false;
    }

    // Rule 3: Max 2 appointments per calendar day (Rule i)
    int dailyCount = 0;
    for (const auto& a : appointments) {
        if (a.checkStatus() && a.getP_ID() == pID && a.getDate() == selected.getDate()) {
            dailyCount++;
        }
    }
    if (dailyCount >= 2) {
        errorMsg = "Limit reached: You cannot have more than 2 appointments on the same day.";
        return false;
    }

    // Rule 4: No double-booking the same exact time (Rule i)
    // (This is partially covered by the loop above, but good for clarity)
    for (const auto& a : appointments) {
        if (a.checkStatus() && a.getP_ID() == pID &&
            a.getDate() == selected.getDate() && a.getTime() == selected.getTime()) {
            errorMsg = "You already have another appointment at this exact time.";
            return false;
        }
    }

    // SUCCESS: Mark as booked and SAVE
    selected.setBooked(pID);
    saveallData(); // This ensures persistence!
    return true;
}

const vector<Doctor>& hospman::getDoctors() {
    return doctor;
}

const vector<Appointment>& hospman::getSlots() {
    return appointments;
}
