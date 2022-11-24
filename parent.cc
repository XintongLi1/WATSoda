#include "parent.h"

Parent::Parent( Printer & prt, Bank & bank, unsigned int numStudents, unsigned int parentalDelay ) : prt(prt), bank(bank), numStudents(numStudents), parentalDelay(parentalDelay) {}

void Parent::main() {
    for (;;) {
        // yielding busy wait to destructor
        _Accept(~Parent) return;
        _Else {
            // each gift has to delay first
            yield(parentalDelay);

            // give between 1 - 3 inclusive
            unsigned int student_id = prng(0, numStudents), gift = prng(1, 4);

            // gift student
            bank.deposit(student_id, gift);
        }
    }
}