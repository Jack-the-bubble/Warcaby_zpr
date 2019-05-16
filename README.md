# ZPR - Warcaby wariant rosyjski

## Technologie
Technologie wykorzystywane w projekcie:
- Python -> Flask, Flask-SocketIO, eventlet, PyTest
- C++ -> boost_unit_test_framework, Boost.Python
- JavaScript

## Budowanie i uruchamianie aplikacji
W celu uruchomienia aplikacji należy:
1. zainstalować odpowiednie biblioteki określone w punkcie ###Wymagania wstępne (skrypty do instalacji znajdują się w folderze /scripts)
2. wejść do folderu /server
3. uruchomić serwer (python3 run.py)
4. w przeglądarce otworzyć stronę pod adresem localhost:5000


### Wymagania wstępne
- **Windows**
  1. msvc (min. 14.0)
  2. Python 3.7 (zlokalizowany w C:\Python37 , jeśli scons ma zadziałać bez modyfikacji)
  3. boost 1_70_0 (biblioteki linkowane dynamicznie; zlokalizowany w C:\boost_1_70_0 , jeśli scons ma zadziałać bez modyfikacji)
  4. pip3 (powinien być domyślnie zainstalowany wraz z Pythonem)
  5. scons (powinien być domyślnie zainstalowany wraz z Pythonem)
  6. Flask, flask-socketio, eventlet, pyd, pytest 
- **Linux (Ubuntu 18.04 Bionic)**
  1. g++
  2. Python 3.5 
  3. libboost-all-dev (boost), scons, python3-pip, Flask, flask-socketio, eventlet, pytest 

### Kompilacja

### Czyszczenie plików utworzonych przez SConst
Należy wywołać z poziomu głównego katalogu projektu:
**sconst --clean**

