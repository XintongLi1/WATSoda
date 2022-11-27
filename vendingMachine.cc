#include "vendingMachine.h"

VendingMachine::VendingMachine( Printer & prt, NameServer & nameServer, unsigned int id, unsigned int sodaCost ) : prt(prt), nameServer(nameServer), id(id), sodaCost(sodaCost) {
    // register with NameServer
    nameServer.VMregister(this);
}

VendingMachine::~VendingMachine() {
    prt.print( Printer::Kind::Vending, id, 'F');
}

void VendingMachine::buy( BottlingPlant::Flavours flavour, WATCard & card ) {
    purchaseFlavour = flavour;
    purchaseCard = card;
    try {
        cond.wait();
    } _CatchResume(_Event & e) {
        _Throw e;
    }
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
    prt.print(Printer::Kind::Vending, id, 'S', sodaCost);
    for (;;) {
        _Accept(~VendingMachine) break;
        or _Accept( restocked ) prt.print(Printer::Kind::Vending, id, 'R');
        or _Accept( inventory ) prt.print(Printer::Kind::Vending, id, 'r');
        or _When ( !restocking ) _Accept( buy ) {
            // check for funds
            if (card.getBalance < sodaCost) _Resume Funds{} _At Resumer;

            // check in stock
            else if (stock[flavour] == 0) _Resume Stock{} _At Resumer;

            // 1 in 5 to give free
            else if (prng(5) == 4) _Resume Free{} _At Resumer;

            else {
                // charge card
                purchaseCard.withdraw(sodaCost);
                // decrease stock
                stock[purchaseFlavour] -= 1;
                prt.print( Printer::Kind::Vending, id, 'B', purchaseFlavour, stocks[purchaseFlavour]);
            }

            cond.signalBlock();
        }
    }
}