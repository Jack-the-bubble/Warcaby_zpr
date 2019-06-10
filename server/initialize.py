#!/usr/bin/env python
from flask import Flask, render_template, request
from flask_socketio import SocketIO, send, emit
import eventlet
import os
import events
appDir = os.path.join(os.path.dirname(os.path.dirname(__file__)), 'app')
templateDir = os.path.join(appDir, 'templates')
staticDir = os.path.join(appDir, 'static')

app = Flask(__name__, template_folder=templateDir, static_folder=staticDir)
app.config['SECRET_KEY'] = 'habababa'
socketio = SocketIO(app)


'''
funkcja zwraca obiekt do renderowania na stronie przegladarki
@:returns zwraca opisany obiekt
'''
@app.route('/')
def sessions():

	return render_template('w3_test2.html', async_mode=socketio.async_mode)

'''
funkcja wywolywana w momencie uzyskania eventu od klienta, 
uruchamia proces logiki komputera oraz wysyla ruch przeciwnika do klienta 
'''
@socketio.on('moveMsg')
def move_on_server(data):
	player_id = request.sid
	events.handle_move(data, player_id)
	
'''
funkcja inicjuje gre po otrzymaniu polaczenia z klientem
'''
@socketio.on('con')
def send_response(data):
	id = request.sid
	events.initialize_player(id)

'''
funkcja ma za zadanie usunac wsyzstkie obiekty zwiazane z gra w przypadku odlaczenia klienta
'''
@socketio.on('dis')
def cut_player(data):
	id = request.sid
	events.delete_player(id)

@socketio.on('disconnect')
def disconnect():
	id = request.sid
	events.delete_player(id)

	
