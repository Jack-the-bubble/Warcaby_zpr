#!/usr/bin/env python
from initialize import socketio, app


'''
jest to glowna funkcja programu uruchamiajaca caly serwer,
 odpowiedzialna za renderowanie aplikacji oraz zarzadzanie logika gry
@param app - obiekt flask
@param host - adres hosta
@:param debug - parametr 
'''
if __name__ == '__main__':
    socketio.run(app, host='127.0.0.1', debug=False)
