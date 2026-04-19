#ifndef DOCTOR_HPP
#define DOCTOR_HPP
#include <string>
#include <iostream>
#include <vector>
using namespace std;

class Doctor{
    private:
        string id;
        string name;
        string department;
        
    public:
        
        string getName();
        string getDept();


};







#endif
