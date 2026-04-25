#ifndef HOSPMANAGER_HPP
#define HOSPMANAGER_HPP
#include "doctor.hpp"
#include "patient.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

class hospman
{
private:
    vector<Doctor> doctor;
    vector<patient> patients;
    //        vector<appointment> appointments;
public:
    void loadinitialData();
    void saveallData();
    bool registerNewPatient(const patient &p);
    const vector<Doctor>& getDoctors();
    patient *findPatient(string id);
};

#endif
