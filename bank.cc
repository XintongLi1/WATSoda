#include "bank.h"

Bank::Bank( unsigned int numStudents ) : numStudents(numStudents) {
    studentArray = new Student[numStudents](0);
}

Bank::~Bank() {
    delete [] studentArray;
}

void Bank::deposit( unsigned int id, unsigned int amount ) {
    studentArray[id] += amount;
}

void Bank::withdraw( unsigned int id, unsigned int amount ) {
    if (studentArray[id] < amount) throw InsufficientFunds{};
    studentArray[id] -= amount;
}