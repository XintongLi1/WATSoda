#ifndef __TRUCK_H__
#define __TRUCK_H__

_Monitor Printer;
_Task NameServer;
_Task BottlingPlant;
_Task VendingMachine;

_Task Truck {
	Printer & prt;
	NameServer & nameServer;
	BottlingPlant & plant;
	unsigned int numVendingMachines, maxStockPerFlavour, * cargo, curr = 0;

	VendingMachine** vms;
	
	void main();
  public:
	Truck( Printer & prt, NameServer & nameServer, BottlingPlant & plant,
		   unsigned int numVendingMachines, unsigned int maxStockPerFlavour );
};

#endif