#include "vendingMachine.h"
#include "watcard.h"
#include "nameServer.h"
#include "printer.h"

VendingMachine::VendingMachine( Printer & prt, NameServer & nameServer, unsigned int id, unsigned int sodaCost ) : prt(prt), nameServer(nameServer), id(id), sodaCost(sodaCost) {
    // register with NameServer
    nameServer.VMregister(this);
}

VendingMachine::~VendingMachine() {
    prt.print( Printer::Kind::Vending, id, 'F');
}

void VendingMachine::buy( BottlingPlant::Flavours flavour, WATCard & card ) {
    purchaseFlavour = flavour;
    purchaseCard = &card;
    try {
        cond.wait();
    } _CatchResume(Funds & funds) {
        _Throw funds;
    } _CatchResume(Stock & stock) {
        _Throw stock;
    }_CatchResume(Free & free) {
        _Throw free;
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
        _Accept(~VendingMachine) break;
        or _Accept( restocked ) prt.print(Printer::Kind::Vending, id, 'R');
        or _Accept( inventory ) prt.print(Printer::Kind::Vending, id, 'r');
        or _When ( !restocking ) _Accept( buy ) {
            // check for funds
            if (purchaseCard->getBalance() < sodaCost) _Resume Funds{};

            // check in stock
            else if (stock[purchaseFlavour] == 0) _Resume Stock{};

            // 1 in 5 to give free
            else if (prng(5) == 4) _Resume Free{};

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