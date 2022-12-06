#include <uPRNG.h>
#include "bottlingPlant.h"
#include "truck.h"
#include "printer.h"

BottlingPlant::BottlingPlant( Printer & prt, NameServer & nameServer, unsigned int numVendingMachines,
				 unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
				 unsigned int timeBetweenShipments ) : prt(prt), nameServer(nameServer), numVendingMachines(numVendingMachines), maxShippedPerFlavour(maxShippedPerFlavour), maxStockPerFlavour(maxStockPerFlavour), timeBetweenShipments(timeBetweenShipments) {
	storage = new unsigned int[Flavours::NUM_OF_FLAVOURS]{0};
}

BottlingPlant::~BottlingPlant(){
	delete [] storage;
}

void BottlingPlant::getShipment( unsigned int cargo[] ) {
	if (closeDown) {
		// Without this:
		// uC++ Runtime error (UNIX pid:38866) (uSerial &)0x55912230f000 : Rendezvous failure in accepted call from task Truck (0x5591224cd440) to mutex member of task BottlingPlant (0x55912230eda0).
		// Error occurred while executing task BottlingPlant (0x55912230eda0).
		uRendezvousAcceptor(); 	
		_Throw Shutdown{};
	}
	
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
			storage[i] = ::prng(maxShippedPerFlavour+1);
			num_production += storage[i];
		}
		
		prt.print(Printer::Kind::BottlingPlant, 'G', num_production);

		// wait for truck
		_Accept(~BottlingPlant) {
			closeDown = true;
			_Accept(getShipment);		// notify the truck
			break;
		} or _Accept(getShipment) {
			prt.print(Printer::Kind::BottlingPlant, 'P');
		}
	}
    
	prt.print(Printer::Kind::BottlingPlant, 'F');
}