#ifndef DOCTOR_HPP
#define DOCTOR_HPP
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Doctor
{
private:
    string id;
    string name;
    string department;

public:
    Doctor(string& Id, string& Name, string& Dep);
    string getName();
    string getDept();
};

#endif
