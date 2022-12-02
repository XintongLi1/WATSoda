#include "truck.h"
#include "nameServer.h"
#include "bottlingPlant.h"
#include "vendingMachine.h"
#include "printer.h"


Truck::Truck( Printer & prt, NameServer & nameServer, BottlingPlant & plant,
		   unsigned int numVendingMachines, unsigned int maxStockPerFlavour ) : prt(prt), nameServer(nameServer), plant(plant), numVendingMachines(numVendingMachines), maxStockPerFlavour(maxStockPerFlavour), numFlavours(BottlingPlant::Flavours::NUM_OF_FLAVOURS) {
    cargo = new unsigned int[numFlavours];
}


void Truck::main() {
    prt.print( Printer::Kind::Truck, 'S' ); 
    // get all vending machines
    machines = nameServer.getMachineList();

    for (;;) {
        _Accept( ~Truck ) break;
        _Else {
            // Tims run
            yield(prng(1, 10));

            try {
                // get new shipment
                plant.getShipment(cargo);
            } catch ( BottlingPlant::Shutdown &) { 
                break;
            }

            unsigned int total = 0;
            for (unsigned int i = 0; i < numFlavours; i+= 1) total += cargo[i];

            prt.print( Printer::Kind::Truck, 'P', total );  

            for (unsigned int i = 0; i < numVendingMachines; i += 1) {
                // break if out of stock
                if (total == 0) break;

                prt.print( Printer::Kind::Truck, 'd', total );  

                // cycle through vending machines and restock, remember which was last
                nextMachine = ( nextMachine + 1 ) % numVendingMachines;

                VendingMachine* next = machines[nextMachine];
                unsigned int * nextStock = next->inventory();

                unsigned int notReplenished = 0;
                for (unsigned int f = 0; f < numFlavours; f += 1) {
                    // fill no more than maxStockPerFlavour
                    unsigned int toStock = std::min( maxStockPerFlavour - nextStock[f], cargo[f] );

                    nextStock[f] += toStock, cargo[f] -= toStock, total -= toStock;
                    notReplenished += maxStockPerFlavour - nextStock[f];
                }

                // finish by calling machine.restocked()
                next->restocked();

                // print amount ot replenished
                if (notReplenished > 0) prt.print( Printer::Kind::Truck, 'U', next->getId(), notReplenished );
                // print remiaing amount
                prt.print( Printer::Kind::Truck, 'D', next->getId(), total );

                // 1 in 100 chnace of flat tire, yield 10
                if (prng(100) == 0) yield(10);
            }
        }
    }
    prt.print( Printer::Kind::Truck, 'F' ); 
}