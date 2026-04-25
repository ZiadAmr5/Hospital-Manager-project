#include "hospmanager.hpp"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

void hospman::loadinitialData()
{
    ifstream docFile("doctors.csv");
    string name, id, dept, header;

    if(!docFile.is_open())
    {
        cout<<"File did not open!";
        return;
    }
    if (docFile.is_open()) {
        getline(docFile, header);

        while (getline(docFile, name, ',') && getline(docFile, id, ',') && getline(docFile, dept))
        {
            cout<<id<<endl;
            doctor.push_back(Doctor(id, name, dept));

        }
        docFile.close();
    }
}
bool hospman::registerNewPatient(patient p)
{
    for (const auto &existing : patients) {
        if (existing.getID() == p.getID()) {
            cout << "Error: Patient already registered." << endl;
            return false;
        }
    }
    patients.push_back(p);
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
