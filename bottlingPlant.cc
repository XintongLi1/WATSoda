#include "bottlingPlant.h"
#include "truck.h"
#include "printer.h"

BottlingPlant::BottlingPlant( Printer & prt, NameServer & nameServer, unsigned int numVendingMachines,
				 unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
				 unsigned int timeBetweenShipments ) : prt(prt), nameServer(nameServer), numVendingMachines(numVendingMachines), maxShippedPerFlavour(maxShippedPerFlavour), maxStockPerFlavour(maxStockPerFlavour), timeBetweenShipments(timeBetweenShipments) {
					storage = new unsigned int[Flavours::NUM_OF_FLAVOURS];
					for (unsigned int i = 0; i < Flavours::NUM_OF_FLAVOURS; ++i){
						storage[i] = 0;			// num of production for each flavor
					}
				 }


void BottlingPlant::getShipment( unsigned int cargo[] ) {
	if (closeDown) _Throw Shutdown{};
	
	for ( unsigned int i = 0; i < Flavours::NUM_OF_FLAVOURS; i += 1) {
		cargo[i] = storage[i];
	}
	
}

void BottlingPlant::main() {
	prt.print(Printer::Kind::BottlingPlant, 'S');
	// create truck
	Truck t(prt, nameServer, *this, numVendingMachines, maxStockPerFlavour);

	for (;;) {
		// production run
		yield(timeBetweenShipments);

		unsigned int num_production = 0;
		for (unsigned int i = 0; i < Flavours::NUM_OF_FLAVOURS; ++i){
			storage[i] = prng(maxShippedPerFlavour+1);
			num_production += storage[i];
		}
		
		prt.print(Printer::Kind::BottlingPlant, 'G', num_production);

		// wait for truck
		_Accept(~BottlingPlant) {
			closeDown = true;
			delete [] storage;
			_Accept(getShipment);		// notify the truck
			break;
		} or _Accept(getShipment) {
			prt.print(Printer::Kind::BottlingPlant, 'P');
		}
	}
    
	prt.print(Printer::Kind::BottlingPlant, 'F');
}