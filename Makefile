CXX = u++					# compiler
CXXFLAGS = -g -multi -O2 -Wall -Wextra -MMD -D"${VIMPL}" -D"${OUTPUT}" \
			-D"${BCHECK}" # compiler flags
MAKEFILE_NAME = ${firstword ${MAKEFILE_LIST}}	# makefile name

OBJECTS = driver.o printer.o bank.o bottlingPlant.o  groupoff.o parent.o student.o truck.o vendingMachine.o waterCardOffice.o # list of object files for question 3 prefixed with "q3"
EXEC = vote

DEPENDS = ${OBJECTS:.o=.d}			# substitute ".o" with ".d"

#############################################################

.PHONY : all clean

all : ${EXEC}					# build all executables


ifeq (${shell if [ "${LOCKVIMPL}" = "${VIMPL}" -a "${OUTPUTTYPE}" = "${OUTPUT}" -a \
			"${BCHECKIMPL}" = "${BCHECK}" ] ; then echo true ; fi },true)
${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} $^ -o $@
else						# implementation type has changed => rebuilt
.PHONY : ${EXEC}
${EXEC} :
	${MAKE} ${EXEC} VIMPL="${VIMPL}" OUTPUT="${OUTPUT}" BCHECK="${BCHECK}" clean
endif

VoteImpl :
	echo "LOCKVIMPL=${VIMPL}\nOUTPUTTYPE=${OUTPUT}\nBCHECKIMPL=${BCHECK}" > VoteImpl
	sleep 1

#############################################################

${OBJECTS} : ${MAKEFILE_NAME}			# OPTIONAL : changes to this file => recompile

-include ${DEPENDS}				# include *.d files containing program dependences

clean :						# remove files that can be regenerated
	rm -f *.d *.o ${OBJECTS}