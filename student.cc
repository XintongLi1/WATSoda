#include "student.h"

Student::Student( Printer & prt, NameServer & nameServer, WATCardOffice & cardOffice, Groupoff & groupoff,
			 unsigned int id, unsigned int maxPurchases ) : prt(prt), nameServer(nameServer), cardOffice(cardOffice), groupoff(groupoff), id(id), maxPurchases(maxPurchases) {}

void Student::main() {
    for (;;) {

        yield(prng(1, 10));

        // select number of bottles to purchase
        
        // select a flavour

        // create WATCard with $5 balance

        // create gift card with value of SodaCost

        // find vending machine location

        // wait until enough funds

        // purchase (Use gift card first)
        // gift cards can only be used once

        // Courier may lose WATCard, must create new one and buy again (no yield)

        // if free soda yield(4)

        // insufficient funds

        // out of stock


        // terminate when maxPurchases of favourite flavour
    }
}
