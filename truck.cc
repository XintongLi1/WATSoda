#include "truck.h"
#include "nameServer.h"
#include "bottlingPlant.h"
#include "vendingMachine.h"

Truck::Truck( Printer & prt, NameServer & nameServer, BottlingPlant & plant,
		   unsigned int numVendingMachines, unsigned int maxStockPerFlavour ) : prt(prt), nameServer(nameServer), plant(plant), numVendingMachines(numVendingMachines), maxStockPerFlavour(maxStockPerFlavour) {}


void Truck::main() {
    // get all vending machines
    vms = nameServer.getMachineList();

    for (;;) {
        // Tims run
        yield(prng(1, 10));


        try {
            // throw away old bottles
            cargo = {0};

            // get new shipment
            plant.getShipment(cargo);
        } catch ( BottlingPlant::Shutdown &) { 
            return;
        }

        // cycle through vending machines and restock, remember which was last

        // call unsigned int * stock = machine.inventory() and no more than MaxStockPerFlavour
        // finish by calling machine.restocked()

        // 1 in 100 chnace of flat tire, yield 10
    }
}