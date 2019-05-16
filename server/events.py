from flask_socketio import SocketIO, send, emit

def handle_move(data):
    board = data['board']
    for i in range(8):
        print(board[i*8:i*8+8])
    print("\n")
