from flask_socketio import SocketIO, send, emit
import Klient

clients=[]
clientIDs =[]

#assign a unique ID to a new player
def initialize_player(id):
    if (len(clients) == 0):
        k = Klient.Klient(0)
        clients.append(k)
        clientIDs.append(0)
        emit('init', 0)
    else:
        for i in range(len(clients)):
            if i not in clientIDs:
                clientIDs.append(i)
                k = Klient.Klient(i)
                clients.append(k)
                emit('init', i)
                break
            if i == len(clients)-1:
                i+=1
                k = Klient.Klient(i)
                clientIDs.append(i)
                clients.append(k)
                emit('init', i)
    print(clientIDs)

#delete a player that lost connection
def delete_player(player_):
    if player_ in clientIDs:
        clients.pop(clientIDs.index(player_))
        clientIDs.remove(player_)
    print(clientIDs)

def handle_move(data):
    board = data['board']
    print(int_board+"\n")
    k = Klient.Klient(5)
    emit('moveResp', 'received')
