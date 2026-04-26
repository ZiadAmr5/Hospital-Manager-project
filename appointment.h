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
    Appointment(string docID,QDate d,QTime t);
    string getD_ID()const {return doctorID; }
    string getDay()const {return paitentID;}
    QDate getTime()const {return date;}
    QTime getTime() const {return time; }
    bool checkStatus() const {return booked;}
    void setBooked(string pID){
        booked = true;
        patientID = pID;
    }
};

#endif // APPOINTMENT_H
