#ifndef __TRUCK_H__
#define __TRUCK_H__

class Printer, NameServer, BottlingPlant;

_Task Truck {
	unsigned int numVendingMachines, maxStockPerFlavour;
	
	Printer & prt;
	NameServer & nameServer;
	BottlingPlant & plant;
	void main();
  public:
	Truck( Printer & prt, NameServer & nameServer, BottlingPlant & plant,
		   unsigned int numVendingMachines, unsigned int maxStockPerFlavour );
};

#endif