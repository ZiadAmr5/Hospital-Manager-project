#ifndef DOCTOR_HPP
#define DOCTOR_HPP
#include <iostream>
#include <string>
#include <vector>
#include "appointment.h"
using namespace std;

class Doctor
{
private:
    string id;
    string name;
    string department;
public:

public:
    Doctor(string &Id, string &Name, string &Dep);
    string getName() const;
    string getDept() const;
    string getID()const;
     vector <Appointment>&getSlots();
};

#endif
