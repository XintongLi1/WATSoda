#include <uPRNG.h>
#include "parent.h"
#include "bank.h"
#include "printer.h"

Parent::Parent( Printer & prt, Bank & bank, unsigned int numStudents, unsigned int parentalDelay ) : prt(prt), bank(bank), numStudents(numStudents), parentalDelay(parentalDelay) {}

void Parent::main() {
    PRNG prng;
    // print start message
    prt.print(Printer::Parent, 'S');

    for (;;) {
        // yielding busy wait to destructor
        _Accept(~Parent) {
            // print finish message
            prt.print(Printer::Parent, 'F');
            return;
        }
        _Else {
            // each gift has to delay first
            yield(parentalDelay);

            // give between 1 - 3 inclusive
            unsigned int student_id = prng(numStudents), gift = prng(1, 3);

            // gift student
            bank.deposit(student_id, gift);

            // print deposit gift message
            prt.print(Printer::Parent, 'D', student_id, gift);
        }
    }
    prt.print(Printer::Kind::Parent, 'F'); 
}