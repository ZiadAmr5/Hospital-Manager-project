#ifndef HOSPMANAGER_HPP
#define HOSPMANAGER_HPP
#include "doctor.hpp"
#include "patient.hpp"
#include "appointment.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class hospman
{
public:
    void loadinitialData();
    void saveallData();
    bool registerNewPatient(const patient &p);
    const vector<Doctor> &getDoctors();
    vector<Appointment> appointments;
    const vector<Appointment>& getSlots();
    patient *findPatient(string id);
private:
    vector<Doctor> doctor;
    vector<patient> patients;


};

#endif
