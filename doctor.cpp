#include "doctor.hpp"




Doctor::Doctor(string &Id, string &Name, string &Dep): id(Id),name(Name),department(Dep){}

string Doctor::getName() const
{
    return name;
}

string Doctor::getDept() const
{
    return department;
}
