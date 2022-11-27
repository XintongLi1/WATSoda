#ifndef __STUDENT_H__
#define __STUDENT_H__

class Printer, NameServer, WATCardOffice, Groupoff;

_Task Student {
	unsigned int id, maxPurchases, amount, flavour;
	Printer & prt;
	NameServer & nameServer;
	WATCardOffice & cardOffice;
	WATCard::FWATCard & card, & giftCard;
	Groupoff & groupoff;

	VendingMachine * vm;

	void main();
  public:
	Student( Printer & prt, NameServer & nameServer, WATCardOffice & cardOffice, Groupoff & groupoff,
			 unsigned int id, unsigned int maxPurchases );
};

#endif