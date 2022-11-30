#include "nameServer.h"
#include "vendingMachine.h"

NameServer::NameServer( Printer & prt, unsigned int numVendingMachines, unsigned int numStudents ) : prt(prt), numVendingMachines(numVendingMachines), numStudents(numStudents) {
    vms = new VendingMachine*[numVendingMachines];
    // sodaCost?
    unsigned int sodaCost = 1;
    for (unsigned int i = 0; i < numVendingMachines; i += 1) vms[i] = new VendingMachine(prt, *this, i, sodaCost);
}

void NameServer::main() {

}
	
void NameServer::VMregister( VendingMachine * vendingmachine ) {}

VendingMachine * NameServer::getMachine( unsigned int id ) {
    return vms[id];
}

VendingMachine ** NameServer::getMachineList() {
    return vms;
}