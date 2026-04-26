#ifndef APPOINTMENT_H
#define APPOINTMENT_H
#include <string>
using namespace std;
class Appointment
{
    string doctorID;
    string PaitentID;
    string day;
    string Slot;
    bool Booked;


public:
    Appointment(string docID,string d,string Sol);
    string getD_ID()const;
    string getDay()const;
    string getTime()const;
    bool checkStatus();
};

#endif // APPOINTMENT_H
