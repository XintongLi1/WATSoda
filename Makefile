CXX = u++					# compiler
CXXFLAGS = -g -multi -O2 -Wall -Wextra  \
MAKEFILE_NAME = ${firstword ${MAKEFILE_LIST}}	# makefile name

OBJECTS = driver.o printer.o bank.o bottlingPlant.o  groupoff.o parent.o student.o truck.o vendingMachine.o waterCardOffice.o # list of object files for question 3 prefixed with "q3"
EXEC = soda

DEPENDS = ${OBJECTS:.o=.d}			# substitute ".o" with ".d"

#############################################################

.PHONY : all clean

all : ${EXEC}					# build all executables

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} $^ -o $@

#############################################################

${OBJECTS} : ${MAKEFILE_NAME}			# OPTIONAL : changes to this file => recompile

-include ${DEPENDS}				# include *.d files containing program dependences

clean :						# remove files that can be regenerated
	rm -f *.d *.o ${OBJECTS}