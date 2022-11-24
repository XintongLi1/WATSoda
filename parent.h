#ifndef __PARENT_H__
#define __PARENT_H__

_Task Parent {
	void main();
  public:
	Parent( Printer & prt, Bank & bank, unsigned int numStudents, unsigned int parentalDelay );
};

#endif