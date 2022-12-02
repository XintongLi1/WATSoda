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
    stock = new unsigned int[BottlingPlant::Flavours::NUM_OF_FLAVOURS]{0};
}

VendingMachine::~VendingMachine() {
    delete [] stock;
    prt.print( Printer::Kind::Vending, id, 'F');
}

void VendingMachine::buy( BottlingPlant::Flavours flavour, WATCard & card ) {
    purchaseFlavour = flavour;
    purchaseCard = &card;
    
    cond.wait();

    std::string currRaise = raise;
    raise = "";

    if (currRaise == "funds") _Throw Funds{};
    if (currRaise == "stock") _Throw Stock{};
    if (currRaise == "free")  _Throw Free{};

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
        _Accept(~VendingMachine) break;
        or _Accept( restocked ) prt.print(Printer::Kind::Vending, id, 'R');
        or _Accept( inventory ) prt.print(Printer::Kind::Vending, id, 'r');
        or _When ( !restocking ) _Accept( buy ) {

            // check in stock
            if (stock[purchaseFlavour] == 0) {
                raise = "stock";
            }

            // 1 in 5 to give free
            else if (prng(5) == 4) {
                stock[purchaseFlavour] -= 1;
                raise = "free";
            }

            // check for funds
            else if (purchaseCard->getBalance() < sodaCost) {
                raise == "funds";
            }

            else {
                // charge card
                purchaseCard->withdraw(sodaCost);
                // decrease stock
                stock[purchaseFlavour] -= 1;
                prt.print( Printer::Kind::Vending, id, 'B', purchaseFlavour, stock[purchaseFlavour]);
            }

            cond.signalBlock();
        }
    }
}