#!/usr/bin/env python
from flask import Flask, render_template, request
from flask_socketio import SocketIO, send, emit
import eventlet
import os
#import event_handlers
import events
appDir = os.path.join(os.path.dirname(os.path.dirname(__file__)), 'app')
templateDir = os.path.join(appDir, 'templates')
staticDir = os.path.join(appDir, 'static')

app = Flask(__name__, template_folder=templateDir, static_folder=staticDir)
app.config['SECRET_KEY'] = 'habababa'
socketio = SocketIO(app)


@app.route('/')
def sessions():

	return render_template('w3_test2.html', async_mode=socketio.async_mode)

@socketio.on('moveMsg')
def move_on_server(data):
	print("\n\n\n\nmaking move\n\n\n\n")
	player_id = request.sid
	events.handle_move(data, player_id)
	
	
@socketio.on('con')
def send_response(data):

	# print("\n\n\n\nchecking sockets\n")
	id = request.sid
	# print(id)
	# print("\n\n\n\n\n\n\n")
	# emit('moveResp', id)

	events.initialize_player(id)

	# emit('resp', 'data')

@socketio.on('dis')
def cut_player(data):
	# print("\n\n\n\ndisdis  cut_player\n")
	id = request.sid
	# print(id)
	# print("\n\n\n\n\n\n\n")
	events.delete_player(id)

@socketio.on('disconnect')
def disconnect():
	# print("\n\n\n\n\ndisconnect\n\n")
	id = request.sid
	# print(id)
	# print("\n\n\n\n\n\n\n")
	events.delete_player(id)
# @socketio.on('disconnect')
# def cut_player(id)
# 	events.delete_player(id)
	
