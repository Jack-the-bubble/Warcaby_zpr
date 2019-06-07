#!/usr/bin/env python
from initialize import socketio, app


'''
jest to główna funkcja programu uruchamiająca cały serwer,
 odpowiedzialna za renderowanie aplikacji oraz zarządzanie logiką gry
 
@param app - obiekt flask
@param host - adres hosta
@:param debug - parametr 
'''
if __name__ == '__main__':
    socketio.run(app, host='127.0.0.1', debug=True)
