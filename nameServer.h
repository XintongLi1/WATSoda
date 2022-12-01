#ifndef __NAMESERVER_H__
#define __NAMESERVER_H__

_Task VendingMachine;
class Printer;

_Task NameServer {
	Printer & prt;
	unsigned int numVendingMachines, numStudents, registercnt = 0;
	VendingMachine ** vms;
	unsigned int * mapVM;		// index of vms assigned to students

	void main();
  public:
	NameServer( Printer & prt, unsigned int numVendingMachines, unsigned int numStudents );
	void VMregister( VendingMachine * vendingmachine );
	VendingMachine * getMachine( unsigned int id ) __attribute__(( warn_unused_result ));
	VendingMachine ** getMachineList() __attribute__(( warn_unused_result ));
	~NameServer();
};

#endif