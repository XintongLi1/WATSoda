#include "nameServer.h"
#include "vendingMachine.h"
#include "printer.h"

NameServer::NameServer( Printer & prt, unsigned int numVendingMachines, unsigned int numStudents ) : prt(prt), numVendingMachines(numVendingMachines), numStudents(numStudents) {
    vms = new VendingMachine*[numVendingMachines];
    mapVM = new unsigned int[numStudents];
    for (unsigned int i = 0; i < numStudents; i += 1) {
        mapVM[i] = i % numVendingMachines;
    }
}

NameServer::~NameServer(){
    delete [] vms;
    delete [] mapVM;
}


void NameServer::main() {
    // start
    prt.print( Printer::NameServer, 'S');
    for (;;){
        if (registercnt < numVendingMachines) _Accept(VMregister);
        else {
            _Accept ( ~NameServer ) { break; }
            or _Accept( getMachine || getMachineList );
        }
    }

    // finish
    prt.print( Printer::NameServer, 'F');
}

	
void NameServer::VMregister( VendingMachine * vendingmachine ) {
    vms[registercnt] = vendingmachine;
    ++registercnt;
    // register vending machine
    prt.print( Printer::NameServer, 'R', vendingmachine->getId());
}

VendingMachine * NameServer::getMachine( unsigned int id ) {
    unsigned int vmId = mapVM[id];
    mapVM[id] = (mapVM[id] + 1) % numVendingMachines;
    // student s requesting vending machine v
    prt.print( Printer::NameServer, 'N', id, vms[vmId]->getId());
    return vms[vmId];
}

VendingMachine ** NameServer::getMachineList() {
    return vms;
}