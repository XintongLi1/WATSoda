#include "bottlingPlant.h"
#include "truck.h"
#include "printer.h"

BottlingPlant::BottlingPlant( Printer & prt, NameServer & nameServer, unsigned int numVendingMachines,
				 unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
				 unsigned int timeBetweenShipments ) : prt(prt), nameServer(nameServer), numVendingMachines(numVendingMachines), maxShippedPerFlavour(maxShippedPerFlavour), maxStockPerFlavour(maxStockPerFlavour), timeBetweenShipments(timeBetweenShipments) {}


void BottlingPlant::getShipment( unsigned int cargo[] ) {
	_Accept(~BottlingPlant) _Throw Shutdown{};
	_Else {
		for ( unsigned int i = 0; i < Flavours::NUM_OF_FLAVOURS; i += 1) cargo[i] = storage;
	}
	storage = 0;
}

void BottlingPlant::main() {
	prt.print(Printer::Kind::BottlingPlant, 'S');
	// create truck
	Truck t(prt, nameServer, *this, numVendingMachines, maxStockPerFlavour);

	for (;;) {
		// production run
		yield(timeBetweenShipments);

		storage = prng(maxShippedPerFlavour);
		prt.print(Printer::Kind::BottlingPlant, 'G', storage * Flavours::NUM_OF_FLAVOURS);

		// wait for truck
		_Accept(~BottlingPlant) {
			break;
		} or _Accept(getShipment) {
			prt.print(Printer::Kind::BottlingPlant, 'P');
		}
	}
    
	prt.print(Printer::Kind::BottlingPlant, 'F');
}