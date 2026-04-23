#ifndef HOSPMANAGER_HPP
#define HOSPMANAGER_HPP 
#include <iostream>
#include <vector>
#include <string>
#include "doctor.hpp"
#include "patient.hpp"
using namespace std;

class hospman{
    private:
        vector <Doctor> doctor;
        vector <patient> patients;
//        vector<appointment> appointments;
    public:
        void loadinitialData();
        void saveallData();
        bool registerNewPatient( patient p );
        patient* findPatient(string id);





};











#endif
