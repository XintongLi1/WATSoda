#ifndef __PRINTER_H__
#define __PRINTER_H__

#include <string>

struct Info {
	bool filled = false;
	std::string msg;
};


// _Cormonitor
_Monitor Printer {	// chose one of the two kinds of type constructor
	unsigned int numStudents, numVendingMachines, numCouriers, total;
	Info * buffer;		// store information
	void flush();		// flush the stored information

  public:
	enum Kind { Parent, Groupoff, WATCardOffice, NameServer, Truck, BottlingPlant, Student, Vending, Courier };
	Printer( unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers );
	~Printer();
	void print( Kind kind, char state );
	void print( Kind kind, char state, unsigned int value1 );
	void print( Kind kind, char state, unsigned int value1, unsigned int value2 );
	void print( Kind kind, unsigned int lid, char state );
	void print( Kind kind, unsigned int lid, char state, unsigned int value1 );
	void print( Kind kind, unsigned int lid, char state, unsigned int value1, unsigned int value2 );

  private:
	int getIndex(Kind kind, unsigned int lid = 0);		// get corresponding buffer index
};

#endif
