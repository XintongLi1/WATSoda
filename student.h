#ifndef __STUDENT_H__
#define __STUDENT_H__

class Printer, NameServer, WATCardOffice, Groupoff;

_Task Student {
	unsigned int id, maxPurchases;
	Printer & prt;
	NameServer & nameServer;
	WATCardOffice & cardOffice;
	Groupoff & groupoff;
	void main();
  public:
	Student( Printer & prt, NameServer & nameServer, WATCardOffice & cardOffice, Groupoff & groupoff,
			 unsigned int id, unsigned int maxPurchases );
};

#endif