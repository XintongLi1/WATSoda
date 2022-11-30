#ifndef __PARENT_H__
#define __PARENT_H__

class Printer;
class Bank;

_Task Parent {
	Printer & prt;
	Bank & bank;
	unsigned int numStudents, parentalDelay;
	void main();
  public:
	Parent( Printer & prt, Bank & bank, unsigned int numStudents, unsigned int parentalDelay );
};

#endif