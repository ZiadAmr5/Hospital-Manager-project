#ifndef PATIENT_HPP
#define PATIENT_HPP

#include <iostream>
#include <string>
using namespace std;

class patient{
    private:
        string nationalid;
        string name;
        string birthdate;
        string gender;
        string mobilenumber;

    public:
        void editMobileNumber( string newNum);

};
#endif
