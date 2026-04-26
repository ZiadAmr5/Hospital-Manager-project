#include "hospmanager.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

void hospman::loadinitialData()
{
    ifstream docFile("doctors.csv");
    ifstream avfile("availability.csv");
    string line,header;

    if (!docFile.is_open()||!avfile.is_open())
    {
        cout << "One of the Files did not open!";
        return;
    }

        getline(docFile, header);

    while (getline(docFile,line))
        {
            stringstream Docss(line);   //string stream treats strings as if they were on the input output stream,  useful to divide strings
          string name ,id, dept;
            getline(Docss,name,',');
          getline(Docss,id,',');
                getline(Docss,dept);

            doctor.push_back(Doctor(id, name, dept));
        }
        docFile.close();

        getline(avfile,header);

        while(getline(avfile,line))
        {
            stringstream AVss(line);
            string id,day,start,end;
            getline(AVss,id,',');
            getline(AVss,day,',');
            getline(AVss,start,',');
            getline(AVss,end,',');
            string timeRange = start+"-"+end;
            appointments.push_back(Appointment(id,day,timeRange));
        }
        avfile.close();



}
bool hospman::registerNewPatient(const patient &p)
{
    for (const auto &existing : patients) {
        if (existing.getID() == p.getID()) {
            cout << "Error: Patient already registered." << endl;
            return false;
        }
    }
    patients.push_back(p);
    cout << "Sucess!@!@";
    return true;
}

void hospman::saveallData()
{
    ofstream outPat("patients_saved.csv");
    for (auto &p : patients) {
        outPat << p.getID() << "," << p.getName() << "," << p.getMobile() << endl;
    }
    outPat.close();
    cout << "All data saved to disk." << endl;
}

const vector<Doctor> &hospman::getDoctors()
{
    return doctor;
}
const vector<Appointment> &hospman::getSlots()
{
    return appointments;
}
