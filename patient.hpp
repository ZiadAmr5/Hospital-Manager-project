#ifndef PATIENT_HPP
#define PATIENT_HPP

#include <iostream>
#include <string>
using namespace std;

class patient
{
private:
    string nationalid;
    string name;
    string birthdate;
    string gender;
    string mobilenumber;

public:
    patient(string Name, string ID, string MOBnumber);
    void editMobileNumber(string newNum);
    string getID() const;
    string getName();
    string getMobile();
};
#endif
