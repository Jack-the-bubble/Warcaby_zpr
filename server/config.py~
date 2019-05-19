#!/usr/bin/env python
from flask import Flask, render_template, request
from flask_socketio import SocketIO, send, emit
import eventlet
import os
#import event_handlers
appDir = os.path.join(os.path.dirname(os.path.dirname(__file__)), 'app')
templateDir = os.path.join(appDir, 'templates')
staticDir = os.path.join(appDir, 'static')

app = Flask(__name__, template_folder=templateDir, static_folder=staticDir)
app.config['SECRET_KEY'] = 'tajemnica'
socketio = SocketIO(app)

whoNow = 'X'
playNowHere = 1


@app.route('/')
def sessions():
	return render_template('w3_test2.html', async_mode=socketio.async_mode)


@socketio.on('clickedField', namespace='/test')
def handleClick(data):
    socketId = request.sid
    print("clicked")
#    event_handlers.handleClickedField(data, socketId)


@socketio.on('msgSent', namespace='/test')
def handleMessage(data):
    socketId = request.sid
    print("message received")
#    event_handlers.handleReceivedMessage(data, socketId)


@socketio.on('connect', namespace='/test')
def handleConnect():	
    socketId = request.sid
    print("connection handled")
#    event_handlers.handleConnection(socketId)


@socketio.on('disconnect', namespace='/test')
def handleDisconnect():
    socketId = request.sid
    print("disconnection handled")
#    event_handlers.handleDisconnection(socketId)

@socketio.on('message')
def handle_message(message):
	print('received message: '+ message)
	
@socketio.on('moveMsg')
def move_on_server(data):
	emit('moveResp', 'received')
	
	
@socketio.on('myMsg')
def send_response(message):
	emit('resp', 'data')

	
