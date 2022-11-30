#ifndef __STUDENT_H__
#define __STUDENT_H__

#include "watcard.h"
#include "bottlingPlant.h"

class Printer;
_Task NameServer;
_Task WATCardOffice;
_Task Groupoff;
_Task VendingMachine;

_Task Student {
	Printer & prt;
	NameServer & nameServer;
	WATCardOffice & cardOffice;
	Groupoff & groupoff;
	unsigned int id, maxPurchases, amount;
	BottlingPlant::Flavours flavour;
	WATCard::FWATCard card, giftCard;
	WATCard * thisCard = nullptr;

	VendingMachine * vm;

	void main();
  public:
	Student( Printer & prt, NameServer & nameServer, WATCardOffice & cardOffice, Groupoff & groupoff,
			 unsigned int id, unsigned int maxPurchases );
};

#endif