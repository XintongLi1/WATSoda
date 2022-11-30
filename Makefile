CXX = u++ 				# compiler
CXXFLAGS = -g -multi -O2 -Wall -Wextra  \

OBJECTS = driver.o printer.o bank.o bottlingPlant.o  groupoff.o parent.o student.o truck.o vendingMachine.o watcardOffice.o watcard.o nameServer.o config.o # list of object files for question 3 prefixed with "q3"
EXEC = soda

DEPENDS = ${OBJECTS:.o=.d}			# substitute ".o" with ".d"

.PHONY : all clean
.ONESHELL :

#############################################################

.PHONY : ${EXEC}

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} -o $@ ${OBJECTS}

%.o: %.cc
	u++ -c ${CXXFLAGS} $< -o $@


#############################################################

-include ${DEPENDS}				# include *.d files containing program dependences

clean :						# remove files that can be regenerated
	rm -f *.d *.o ${EXEC}