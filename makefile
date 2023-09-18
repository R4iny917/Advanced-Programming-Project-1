objs = Admin.o Calculator.o Data.o Project.o SQLinterpreter.o User.o
platform: $(objs)
		g++ $(objs) -o platform

Admin.o:Admin.h Data.h User.h
Calculator.o:Calculator.h
Data.o:Data.h
Project.o:Project.cpp User.h Admin.h Data.h
SQLinterpreter.o:SQLinterpreter.h Data.h User.h
User.o:User.h Data.h Calculator.h

clean:
		rm *.o
		rm platform