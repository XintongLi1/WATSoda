#include "vendingMachine.h"
#include "watcard.h"
#include "nameServer.h"
#include "printer.h"
#include "bottlingPlant.h"

#include <iostream>

using namespace std;

VendingMachine::VendingMachine( Printer & prt, NameServer & nameServer, unsigned int id, unsigned int sodaCost ) : prt(prt), nameServer(nameServer), id(id), sodaCost(sodaCost) {
    // register with NameServer
    nameServer.VMregister(this);

    // stock starts empty
    stock = new unsigned int[BottlingPlant::Flavours::NUM_OF_FLAVOURS];
    for (unsigned int i = 0; i < BottlingPlant::Flavours::NUM_OF_FLAVOURS; i+=1){
        stock[i] = 0;
    }
}

VendingMachine::~VendingMachine() {
    delete [] stock;
    prt.print( Printer::Kind::Vending, id, 'F');
}

void VendingMachine::buy( BottlingPlant::Flavours flavour, WATCard & card ) {

    // check in stock
    if (stock[flavour] == 0) {
        uRendezvousAcceptor();      // uC++ textbook page 122
        _Throw Stock{};
    }

    // check for funds
    else if (card.getBalance() < sodaCost) {
        uRendezvousAcceptor(); 
        _Throw Funds{};
    }

    // 1 in 5 to give free
    else if (prng(5) == 4) {
        stock[flavour] -= 1;
        prt.print(Printer::Kind::Vending, id, 'A');
        uRendezvousAcceptor(); 
        _Throw Free{};
    }          

    else {
        // charge card
        card.withdraw(sodaCost);
        // decrease stock
        stock[flavour] -= 1;
        prt.print( Printer::Kind::Vending, id, 'B', flavour, stock[flavour]);
    }

}

unsigned int * VendingMachine::inventory() {
    restocking = true;
    return stock;
}

void VendingMachine::restocked() {
    restocking = false;
}

unsigned int VendingMachine::cost() const {
    return sodaCost;
}

unsigned int VendingMachine::getId() const {
    return id;
}

void VendingMachine::main() {
    prt.print(Printer::Kind::Vending, id, 'S', sodaCost);
    for (;;) {
        _When (!restocking) _Accept(~VendingMachine) break;
        or _Accept( restocked ) prt.print(Printer::Kind::Vending, id, 'R');
        or _Accept( inventory ) prt.print(Printer::Kind::Vending, id, 'r');
        or _When ( !restocking ) _Accept( buy );
    }
}