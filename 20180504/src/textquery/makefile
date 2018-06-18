# executable files for this directory
OBJECTS = andQueryTest.exe and_orQueryTest.exe \
          wordQueryTest.exe \


# tells make to use the file "..\MS_makefile_template", which
# defines general rules for making .obj and .exe files
include .\MS_makefile_template

LOCFLAGS = /I..\12 -I..\6


get_print.obj andQueryTest.obj and_orQueryTest.obj \
wordQueryTest.obj Query.obj: Query.h ..\12\TextQuery.h

wordQueryTest.exe: Query.obj wordQueryTest.obj ..\12\TextQuery.obj get_print.obj
	$(CPP) $(CPPFLAGS) $(LOCFLAGS) wordQueryTest.obj Query.obj \
		..\12\TextQuery.obj get_print.obj 

andQueryTest.exe: Query.obj andQueryTest.obj ..\12\TextQuery.obj get_print.obj
	$(CPP) $(CPPFLAGS) $(LOCFLAGS) andQueryTest.obj Query.obj \
		..\12\TextQuery.obj get_print.obj 

and_orQueryTest.exe: and_orQueryTest.obj Query.obj ..\12\TextQuery.obj \
		get_print.obj
	$(CPP) $(CPPFLAGS) $(LOCFLAGS) and_orQueryTest.obj Query.obj \
		..\12\TextQuery.obj get_print.obj 