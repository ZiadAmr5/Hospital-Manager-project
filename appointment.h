#ifndef APPOINTMENT_H
#define APPOINTMENT_H
#include <string>
#include <QDate>
#include <QTime>
using namespace std;
class Appointment
{
    string doctorID;
    string PaitentID;
    QDate date;
    QTime time;
    bool Booked;

public:
    Appointment(string docID, QDate d, QTime t) 
        : doctorID(docID), date(d), time(t), Booked(false) {}

    string getD_ID() const { return doctorID; }
    string getP_ID() const { return PaitentID; }
    
    QDate getDate() const { return date; }
    QTime getTime() const { return time; }
    
    bool checkStatus() const { return Booked; }
    
    void setBooked(string pID) {
        Booked = true;
        PaitentID = pID;
    }
};
#endif // APPOINTMENT_H
