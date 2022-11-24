#ifndef __PARENT_H__
#define __PARENT_H__

class Printer, Bank;

_Task Parent {
	unsigned int numStudents, parentalDelay;

	Printer & prt;
	Bank & bank;
	void main();
  public:
	Parent( Printer & prt, Bank & bank, unsigned int numStudents, unsigned int parentalDelay );
};

#endif