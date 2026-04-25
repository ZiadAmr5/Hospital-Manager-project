#include "doctor.hpp"




Doctor::Doctor(string &Id, string &Name, string &Dep): id(Id),name(Name),department(Dep){}

string Doctor::getName()
{
    return name;
}

string Doctor::getDept()
{
    return department;
}
