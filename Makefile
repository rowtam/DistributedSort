###
# $Id: Makefile,v 1.2 2000/03/23 03:42:08 levine Exp $
###

#		Replace this with your name leaving the quotes
LASTNAME	= "Tam"
FIRSTNAME	= "Ronnie"

#               Submissions are normally sent to the grader account
GRADERS         = cs342gr@cec.wustl.edu
MAILTO          = $(GRADERS)

#		The name of a printer (typhoon, tornado, etc.)
PRINTER		= typhoon

#		The name of the executable file
EXECUTABLE	= main

#               Source files you want to compile
#               (NOTE: Don't need to compile header files, or source
#                files that only contain template class method definitions)
SRCS	        = main.cc Sort_Observer.cc Sorter.cc \
	          Sort_Info_Base.cc Sort_Info.cc\
	          Sort_Viewer_Client.cc Sort_Viewer_Adapter.cc String.cc \
		  Connector.cc Timer.cc
                  #### Don't need to explicitly compile .cc files than
                  #### contain only template class method definitions.

#               All your source files (needed for executable dependency)
ALL_SRCS        = $(SRCS) History.cc History.h Array.cc Array.h

#               All files to print and turn in (including output files, etc)
ALL_FILES       = $(ALL_SRCS)

#		C++ compiler.
CXX		= CC -xildoff +w -features=rtti

#                                                                             #
#################### DO NOT CHANGE ANYTHING BELOW THIS LINE ###################

#               The list of libraries that should be linked in
LIBS    =       -lsocket -lnsl

#               The name of the compiler
CCC      = $(CXX)

#               The name of the prettyprinter
ENSCRIPT = enscript

#               The name of the previewer (pageview or ghostview)
PREVIEWER = /usr/openwin/bin/pageview -right

OBJS     = $(SRCS:.cc=.o)

#               Any general flags that should be set for the compiler
#               NOTE: to optimize fully, change -g to -O4
CXXFLAGS  = -g
#               Any define flags that should be set for conditional compilation
DEFFLAGS  = -DUNIX
#               Any -I directories in which there are .h files that should be included
INCFLAGS  =
#               Flags that are specific to SUN object code
SUNFLAGS  =  #-misalign

#               The concatenation of all the flags that the compiler should get
CCFLAGS = $(DEFFLAGS) $(INCFLAGS) $(SUNFLAGS) $(CXXFLAGS)

###
# Targets
###

#               Construct the executable
$(EXECUTABLE): Templates.DB $(OBJS)
	$(CXX) -o $(EXECUTABLE) $(CCFLAGS) $(OBJS) $(LIBS)

VIEWER: Sort_Viewer.class

Sort_Viewer.class: Sort_Viewer.java
	@javac Sort_Viewer.java

#		Remove all junk that might be lying around
clean:
	-rm -f $(OBJS) core *.bak *~ ../toturnin ./toturnin
	-rm -fr Templates.DB SunWS_cache *.rpo TEST_TURNIN

realclean: clean
	-rm -f $(EXECUTABLE) *.class

toturnin:	clean $(ALL_FILES) readme
	zip -r - readme *.* Makefile \
	  | uuencode "homework" > ../toturnin

turnin: toturnin
	@if [ $(LASTNAME) = 'YOUR LAST NAME GOES HERE' -o \
	      $(FIRSTNAME) = 'YOUR FIRST NAME GOES HERE' ]; \
          then echo 'ERROR: you must edit your Makefile to set LASTNAME/FIRSTNAME!'; \
	else \
	  cat ../toturnin \
	    | /usr/ucb/Mail -s "Assignment-8 $(LASTNAME)_$(FIRSTNAME)" \
	$(MAILTO); \
	fi

test_turnin: toturnin
	@if [ $(LASTNAME) = 'YOUR LAST NAME GOES HERE' -o \
	      $(FIRSTNAME) = 'YOUR FIRST NAME GOES HERE' ]; \
          then echo 'ERROR: you must edit your Makefile to set LASTNAME/FIRSTNAME!'; \
	else \
	  (test -d TEST_TURNIN || mkdir TEST_TURNIN; cd TEST_TURNIN; \
           uudecode ../../toturnin; unzip homework; /bin/rm homework); \
	  echo ' '; \
	  echo 'You just _tested_ turnin, you did _not_ turn anything in!!!!'; \
	  echo 'Please make sure that the contents of the TEST_TURNIN'; \
	  echo 'directory are exactly what you want to turn in!'; \
	  echo 'Then, use "make turnin" to actually turn in your assignment.'; \
	fi

#		Preview the .h and .c files
preview:
	$(ENSCRIPT) -2Gr \
        -b$(LASTNAME)", "$(FIRSTNAME)" : $(LOGNAME)@cec.wustl.edu" \
        -p - $(ALL_FILES) | $(PREVIEWER) -

#		Print out the .h and .c files
print:
	enscript -2Gr -b "Tam, Ronnie : rot1@cec.wustl.edu" -P \
    tsunami *.cc *.h *.java Makefile readme \
	ir.out
#	$(ENSCRIPT) -2Gr \
#        -b$(LASTNAME)", "$(FIRSTNAME)" : $(LOGNAME)@cec.wustl.edu" \
#        -P $(PRINTER) $(ALL_FILES)

#		Change the Makefile to reflect the correct dependencies.
depend:
	-rm -f ccdep
	-rm -f eddep
	$(CXX) -xM $(CCFLAGS) $(SRCS) > ccdep
	sed -n '1,/^# DO NOT DELETE THIS LINE/p' Makefile > eddep
	echo \#\#\# >> eddep
	cat ccdep >> eddep
	cp Makefile Makefile.bak
	mv eddep Makefile
	rm ccdep

.SUFFIXES: .cpp
.cpp.o:
	$(COMPILE.cc) $(CCFLAGS) $(OUTPUT_OPTION) $<
.cpp:
	$(LINK.cc) $(LDFLAGS) -o $@ $< $(LDLIBS)

main.o: $(ALL_SRCS) Makefile

#### To avoid Sun CC warning about having to create Templates.DB.
Templates.DB:
	@test -d $@ || mkdir $@

###
# OBJECT FILE DEPENDENCIES FOLLOW.
#
# DO NOT DELETE THIS LINE -- make depend uses it
###
