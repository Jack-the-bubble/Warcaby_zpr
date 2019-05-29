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
#$(TARGET).so: clean $(TARGET).o
#	g++ -shared -Wl,--export-dynamic $(TARGET).o -L$(BOOST_LIB) -lboost_python$(PYTHON_VER) -L/usr/lib/python$(PYTHON_VERSION)/config -lpython$(PYTHON_VERSION) -o ../$(TARGET).so
#$(TARGET).o:
#	g++ -I$(PYTHON_INCLUDE) -I$(BOOST_INC) -fPIC -c $(TARGET).cpp -o $(TARGET).o
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

all: clean move.o gracz.o plansza.o komputer.o klient.o gra.o
	 g++ -shared -Wl,--export-dynamic gra.o -L$(BOOST_LIB) -lboost_python$(PYTHON_VER) -L/usr/lib/python$(PYTHON_VERSION)/config -lpython$(PYTHON_VERSION) -o gra.so


gra.o:
	 g++ -I/usr/include/python3.6m -I/usr/include -fPIC -c Gra.cpp -o gra.o

klient.so: klient.o
	g++ -shared -Wl,--export-dynamic klient.o -L$(BOOST_LIB) -lboost_python$(PYTHON_VER) -L/usr/lib/python$(PYTHON_VERSION)/config -lpython$(PYTHON_VERSION) -o klient.so

klient.o:
	g++ -I$(PYTHON_INCLUDE) -I$(BOOST_INC) -fPIC -c Klient.cpp -o klient.o
#	g++ -c -FPIC Klient.cpp -o klient.o

komputer.o:
	g++ -o komputer.o -c Komputer.cpp

plansza.o:
	g++ -o plansza.o -c Plansza.cpp

gracz.o:
	g++ -o gracz.o -c Gracz.cpp

move.o:
	g++ -o move.o -c Move.cpp

clean:
	@rm -f *.o
	@rm -f *.so
	@rm -f *.elf
#########################