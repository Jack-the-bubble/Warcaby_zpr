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
	emit('moveResp', 'received')
	events.handle_move(data)
	
	
@socketio.on('myMsg')
def send_response(message):
	emit('resp', 'data')

	
