#ifndef __TRUCK_H__
#define __TRUCK_H__

_Monitor Printer;
_Task NameServer;
_Task VendingMachine;
_Task BottlingPlant;

_Task Truck {
	Printer & prt;
	NameServer & nameServer;
	BottlingPlant & plant;
	unsigned int numVendingMachines, maxStockPerFlavour, numFlavours, * cargo, curr = 0, nextMachine = 0;

	VendingMachine** machines;
	
	void main();
  public:
	Truck( Printer & prt, NameServer & nameServer, BottlingPlant & plant,
		   unsigned int numVendingMachines, unsigned int maxStockPerFlavour );
	~Truck();
};

#endif