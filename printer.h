#ifndef __PRINTER_H__
#define __PRINTER_H__

#include <string>


// _Cormonitor
_Monitor Printer {	// chose one of the two kinds of type constructor
	unsigned int numStudents, numVendingMachines, numCouriers, total;
	std::string* buffer;
	void flush(unsigned int id, std::string turn);
  public:
	enum Kind { Parent, Groupoff, WATCardOffice, NameServer, Truck, BottlingPlant, Student, Vending, Courier };
	Printer( unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers );
	void print( Kind kind, char state );
	void print( Kind kind, char state, unsigned int value1 );
	void print( Kind kind, char state, unsigned int value1, unsigned int value2 );
	void print( Kind kind, unsigned int lid, char state );
	void print( Kind kind, unsigned int lid, char state, unsigned int value1 );
	void print( Kind kind, unsigned int lid, char state, unsigned int value1, unsigned int value2 );
};

#endif
