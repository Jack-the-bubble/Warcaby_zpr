from flask_socketio import SocketIO, send, emit
# import gra
import engine

clients=[]
clientIDs =[]
socketID = []

#assign a unique ID to a new player
def initialize_player(id):
    k = engine.Gra(0)
    k.play()
    k.get
    print("playing")

    # if (len(clients) == 0):
    #     # TODO: stworzyc klase Gra i niech  se gra
    #     # k = Klient.Klient(0)
    #     k = engine.Gra(0)
    #     # k = gra.Gra()
    #     clients.append(k)
    #     clientIDs.append(0)
    #     socketID.append(id)
    #     emit('init', 0)
    # else:
    #     for i in range(len(clients)):
    #         if i not in clientIDs:
    #             clientIDs.append(i)
    #             socketID.append(id)
    #             k = engine.Gra(i)
    #             clients.append(k)
    #             emit('init', i)
    #             break
    #         if i == len(clients)-1:
    #             i+=1
    #             k = engine.Gra(i)
    #             clientIDs.append(i)
    #             socketID.append(id)
    #             clients.append(k)
    #             emit('init', i)
    # # print("\n\n\nadding\n")
    # id = 0
    # clients[socketID.index(id)].play()
    # print(socketID)
    # print(clientIDs)
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
    clients[socketID.index(id)].play()
    # print(int(clients[socketID.index(id)].player1.getID()))
    # clients[socketID.index(id)].player1.convert_and_update(int_board)
    move = {'px': [1, 0], 'py': [2, 3], 'tx': [0, 1], 'ty': [3, 4], 'rx':[], 'ry':[]}
    move['px'] = input("px")
    move['py'] = input("py")
    move['tx'] = input("tx")
    move['ty'] = input("ty")
    move['rx'] = input("rx")
    move['ry'] = input("ry")
    #send computer response
    emit('moveResp', move)
    
    # pom = int(clients[socketID.index(id)].getID())
    # emit('moveResp', {data: pom})

