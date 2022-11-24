#include "truck.h"

Truck::Truck( Printer & prt, NameServer & nameServer, BottlingPlant & plant,
		   unsigned int numVendingMachines, unsigned int maxStockPerFlavour ) : prt(prt), nameServer(nameServer), plan(plant), numVendingMachines(numVendingMachines), maxStockPerFlavour(maxStockPerFlavour) {}


void Truck::main() {
    for (;;) {
        // Tims run
        yield(prng(1, 10));


        try {
            shipment = plant.getShipment();
        } catch ( ShuttingDown &) { 
            return;
        }

        // cycle through vending machines and restock, remember which was last

        // 1 in 100 chnace of flat tire, yield 10
    }
}