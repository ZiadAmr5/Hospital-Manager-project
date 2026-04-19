#include "patient.hpp"
#include <iostream>
using namespace std;
#include <string>
#include <vector>


void patient::editMobileNumber(string newNum){

   string inputnumber; 
    do {
    cout << "please enter your current number" << endl;
   cin >> inputnumber; 
    if ( inputnumber == mobilenumber ){
    cout << "please enter your new mobile number" << endl;
    cin >> newNum;
    mobilenumber = newNum;
    cout << "The number has been entered succesfully" << endl;
    }
    else{
        cout << "please enter the correct phone number" << endl;
    }
    }  while ( inputnumber != mobilenumber );

}

int main() {
    




    return 0;
}
