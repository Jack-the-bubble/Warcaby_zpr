#all:
#	g++ -o test.elf python_test.cpp  -I/usr/include/python3.6 -L/usr/include/boost/ -lboost_python

#for python_test.cpp
##########################
#PYTHON_VERSION =3.6m
#PYTHON_VER=3
#PYTHON_INCLUDE = /usr/include/python$(PYTHON_VERSION)
## location of the Boost Python include files and library
#BOOST_INC = /usr/include
#BOOST_LIB = /usr/lib
## compile mesh classes
#TARGET = python_test
#$(TARGET).so: clean $(TARGET).o
#	g++ -shared -Wl,--export-dynamic $(TARGET).o -L$(BOOST_LIB) -lboost_python$(PYTHON_VER) -L/usr/lib/python$(PYTHON_VERSION)/config -lpython$(PYTHON_VERSION) -o $(TARGET).so
#$(TARGET).o:
#	g++ -I$(PYTHON_INCLUDE) -I$(BOOST_INC) -fPIC -c $(TARGET).cpp -o $(TARGET).o
#
#clean:
#	@rm -f *.o
#	@rm -f *.so
#	@rm -f *.elf
##########################

#for class_test
##########################
#PYTHON_VERSION =3.6m
#PYTHON_VER=3
#PYTHON_INCLUDE = /usr/include/python$(PYTHON_VERSION)
## location of the Boost Python include files and library
#BOOST_INC = /usr/include
#BOOST_LIB = /usr/lib
## compile mesh classes
#TARGET = class_test
#$(TARGET).so: clean $(TARGET).o
#	g++ -shared -Wl,--export-dynamic $(TARGET).o -L$(BOOST_LIB) -lboost_python$(PYTHON_VER) -L/usr/lib/python$(PYTHON_VERSION)/config -lpython$(PYTHON_VERSION) -o $(TARGET).so
#$(TARGET).o:
#	g++ -I$(PYTHON_INCLUDE) -I$(BOOST_INC) -fPIC -c $(TARGET).cpp -o $(TARGET).o
#
#clean:
#	@rm -f *.o
#	@rm -f *.so
#	@rm -f *.elf
##########################

#for deriv_test
##########################
#PYTHON_VERSION =3.6m
#PYTHON_VER=3
#PYTHON_INCLUDE = /usr/include/python$(PYTHON_VERSION)
## location of the Boost Python include files and library
#BOOST_INC = /usr/include
#BOOST_LIB = /usr/lib
## compile mesh classes
#TARGET = deriv_test
#$(TARGET).so: clean $(TARGET).o
#	g++ -shared -Wl,--export-dynamic $(TARGET).o -L$(BOOST_LIB) -lboost_python$(PYTHON_VER) -L/usr/lib/python$(PYTHON_VERSION)/config -lpython$(PYTHON_VERSION) -o $(TARGET).so
#$(TARGET).o:
#	g++ -I$(PYTHON_INCLUDE) -I$(BOOST_INC) -fPIC -c $(TARGET).cpp -o $(TARGET).o
#
#clean:
#	@rm -f *.o
#	@rm -f *.so
#	@rm -f *.elf
##########################

#for virtual_poly
#########################
#PYTHON_VERSION =3.6m
#PYTHON_VER=3
#PYTHON_INCLUDE = /usr/include/python$(PYTHON_VERSION)
## location of the Boost Python include files and library
#BOOST_INC = /usr/include
#BOOST_LIB = /usr/lib
## compile mesh classes
#TARGET = virtual_poly
#$(TARGET).so: clean $(TARGET).o
#	g++ -shared -Wl,--export-dynamic $(TARGET).o -L$(BOOST_LIB) -lboost_python$(PYTHON_VER) -L/usr/lib/python$(PYTHON_VERSION)/config -lpython$(PYTHON_VERSION) -o $(TARGET).so
#$(TARGET).o:
#	g++ -I$(PYTHON_INCLUDE) -I$(BOOST_INC) -fPIC -c $(TARGET).cpp -o $(TARGET).o
#
#clean:
#	@rm -f *.o
#	@rm -f *.so
#	@rm -f *.elf
##########################

##for Klient
############################
#PYTHON_VERSION =3.6m
#PYTHON_VER=3
#PYTHON_INCLUDE = /usr/include/python$(PYTHON_VERSION)
## location of the Boost Python include files and library
#BOOST_INC = /usr/include
#BOOST_LIB = /usr/lib
## compile mesh classes
#TARGET = Klient
#$(TARGET).so: clean gracz.o $(TARGET).o
#	g++ -shared -Wl,--export-dynamic move.o gracz.o $(TARGET).o -L$(BOOST_LIB) -lboost_python$(PYTHON_VER) -L/usr/lib/python$(PYTHON_VERSION)/config -lpython$(PYTHON_VERSION) -o ../$(TARGET).so
#$(TARGET).o:
#	g++ -I$(PYTHON_INCLUDE) -I$(BOOST_INC) -fPIC -c $(TARGET).cpp -o $(TARGET).o
#
#gracz.o: move.o
#	g++ -I$(PYTHON_INCLUDE) -I$(BOOST_INC) -fPIC -c Gracz.cpp -o gracz.o
#
#move.o:
#	g++ -I$(PYTHON_INCLUDE) -I$(BOOST_INC) -fPIC -c Move.cpp -o move.o
#
#clean:
#	@rm -f *.o
#	@rm -f *.so
#	@rm -f ../*.elf
############################

#for deriv_test_list
##########################
#PYTHON_VERSION =3.6m
#PYTHON_VER=3
#PYTHON_INCLUDE = /usr/include/python$(PYTHON_VERSION)
## location of the Boost Python include files and library
#BOOST_INC = /usr/include
#BOOST_LIB = /usr/lib
## compile mesh classes
#TARGET = deriv_list_test
#$(TARGET).so: clean $(TARGET).o
#	g++ -shared -Wl,--export-dynamic $(TARGET).o -L$(BOOST_LIB) -lboost_python$(PYTHON_VER) -L/usr/lib/python$(PYTHON_VERSION)/config -lpython$(PYTHON_VERSION) -o $(TARGET).so
#$(TARGET).o:
#	g++ -I$(PYTHON_INCLUDE) -I$(BOOST_INC) -fPIC -c $(TARGET).cpp -o $(TARGET).o
#
#clean:
#	@rm -f *.o
#	@rm -f *.so
#	@rm -f *.elf
##########################

#for engine
#########################
PYTHON_VERSION =3.6m
PYTHON_VER=3
PYTHON_INCLUDE = /usr/include/python$(PYTHON_VERSION)
# location of the Boost Python include files and library
BOOST_INC = /usr/include
BOOST_LIB = /usr/lib
# compile mesh classes

#all: clean gracz.o plansza.o komputer.o klient.o gra.o
#	 g++ -shared -Wl,--export-dynamic gracz.o klient.o move.o gra.o -L$(BOOST_LIB) -lboost_python$(PYTHON_VER) -L/usr/lib/python$(PYTHON_VERSION)/config -lpython$(PYTHON_VERSION) -o gra.so

engine.so: clean gracz.o klient.o plansza.o komputer.o gra.o engine.o
	g++ -shared -Wl,--export-dynamic plansza.o komputer.o gracz.o klient.o move.o gra.o engine.o -L$(BOOST_LIB) -lboost_python$(PYTHON_VER) -L/usr/lib/python$(PYTHON_VERSION)/config -lpython$(PYTHON_VERSION) -o engine.so

engine.o:
	g++ -I/usr/include/python3.6m -I/usr/include -fPIC -c engine.cpp -o engine.o

gra.o:
	 g++ -I/usr/include/python3.6m -I/usr/include -fPIC -c Gra.cpp -o gra.o

#klient.so: klient.o gracz.o
#	g++ -shared -Wl,--export-dynamic klient.o -L$(BOOST_LIB) -lboost_python$(PYTHON_VER) -L/usr/lib/python$(PYTHON_VERSION)/config -lpython$(PYTHON_VERSION) -o klient.so

klient.o:
	g++ -I$(PYTHON_INCLUDE) -I$(BOOST_INC) -fPIC -c Klient.cpp -o klient.o
#	g++ -c -FPIC Klient.cpp -o klient.o

komputer.o:
	g++ -I$(PYTHON_INCLUDE) -I$(BOOST_INC) -fPIC -c Komputer.cpp -o komputer.o

plansza.o:
	g++ -I$(PYTHON_INCLUDE) -I$(BOOST_INC) -fPIC -c Plansza.cpp -o plansza.o

gracz.o: move.o
	g++ -I$(PYTHON_INCLUDE) -I$(BOOST_INC) -fPIC -c Gracz.cpp -o gracz.o

move.o:
	g++ -I$(PYTHON_INCLUDE) -I$(BOOST_INC) -fPIC -c Move.cpp -o move.o

clean:
	@rm -f *.o
	@rm -f *.so
	@rm -f *.elf
#########################