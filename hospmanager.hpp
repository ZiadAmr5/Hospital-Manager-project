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
    hospman() {}
    void loadinitialData();
    void saveallData();
    bool registerNewPatient(const patient &p);
    const vector<Doctor> &getDoctors();
    const vector<Appointment>& getSlots();
    patient *findPatient(string id);
    bool bookAppointment(int slotIndex, string pID, string &errorMsg);
private:
    vector<Doctor> doctor;
    vector<patient> patients;
    vector<Appointment> appointments;

};

#endif
