#include "vendingMachine.h"

VendingMachine::VendingMachine( Printer & prt, NameServer & nameServer, unsigned int id, unsigned int sodaCost ) : prt(prt), nameServer(nameServer), id(id), sodaCost(sodaCost), restocking(false) {
    // starts empty
    stock = new unsigned int[NumFlavours](0);
}

VendingMachine::~VendingMachine() {
    delete [] stock;
}

void VendingMachine::buy( BottlingPlant::Flavours flavour, WATCard & card ) {
    // check for funds

    // check in stock

    // 1 in 5 to give free 

    // charge card
}

unsigned int * VendingMachine::inventory() __attribute__(( warn_unused_result )) {
    restocking = true;
    return stock;
}

void VendingMachine::restocked() {
    restocking = false;
}

unsigned int cost() const {
    return sodaCost;
}

unsigned int getId() const {
    return id;
}

void VendingMachine::main() {
    for (;;) {
    
    }
}