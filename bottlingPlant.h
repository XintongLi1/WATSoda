#ifndef __BOTTLINGPLANT_H__
#define __BOTTLINGPLANT_H__

class Printer;
_Task NameServer;

_Task BottlingPlant {
	Printer & prt;
	NameServer & nameServer;
	unsigned int numVendingMachines, maxShippedPerFlavour, maxStockPerFlavour, timeBetweenShipments, storage = 0;
	
	void main();
  public:
	enum Flavours { BluesBlackCherry, ClassicCreamSoda, RockRootBeer, JazzLime, NUM_OF_FLAVOURS = 4 };
	_Event Shutdown {};					// shutdown plant
	BottlingPlant( Printer & prt, NameServer & nameServer, unsigned int numVendingMachines,
				 unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
				 unsigned int timeBetweenShipments );
	void getShipment( unsigned int cargo[] );
};

#endif