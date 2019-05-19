from flask_socketio import SocketIO, send, emit
import Klient

clients=[]
clientIDs =[]
socketID = []

#assign a unique ID to a new player
def initialize_player(id):
    if (len(clients) == 0):
        k = Klient.Klient(0)
        clients.append(k)
        clientIDs.append(0)
        socketID.append(id)
        emit('init', 0)
    else:
        for i in range(len(clients)):
            if i not in clientIDs:
                clientIDs.append(i)
                socketID.append(id)
                k = Klient.Klient(i)
                clients.append(k)
                emit('init', i)
                break
            if i == len(clients)-1:
                i+=1
                k = Klient.Klient(i)
                clientIDs.append(i)
                socketID.append(id)
                clients.append(k)
                emit('init', i)
    # print("\n\n\nadding\n")
    print(socketID)
    print(clientIDs)
    # print("\n\n\n\n")


#delete a player that lost connection
def delete_player(player_):
    if player_ in socketID:
        clients.pop(socketID.index(player_))
        clientIDs.pop(socketID.index(player_))
        socketID.remove(player_)
    # print("\n\n\n\nafter deleting")
    print(socketID)
    print(clientIDs)
    # print("\n\n\n\n")

def handle_move(data, id):
    int_board = data['board']
    # print(int_board)
    # k = Klient.Klient(5)
    print(int(clients[socketID.index(id)].getID()))
    
    # pom = int(clients[socketID.index(id)].getID())
    # emit('moveResp', {data: pom})

