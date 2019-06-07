from flask_socketio import SocketIO, send, emit
# import gra
import engine

clients=[]
clientIDs =[]
socketID = []
k = engine.Gra()

#assign a unique ID to a new player
def initialize_player(id):
    # k = engine.Gra(0)
    # k.play()
    # k.get
    k = engine.Gra()
    # k.player1notify()
    k.drukuj()
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
    k.player1notify()
    begMov = data['begMov']
    destMov = data['destMov']
    # rowC = data['capY']
    # colC = data['capX']
    cap = data['cap']
    print(begMov)
    print("\n\n\nprzekazywanie ruchu do enginu\n\n\n")
    k.klientMoveUpdate(begMov[1], begMov[0], destMov[1], destMov[0], cap)
    k.changePlansza()
    k.drukuj()
    # k = Klient.Klient(5)
    # k.player1notify()
    print ("drukowanie planszy po odpowiedzi komputera")

    k.player2notify()
    computerMov = k.convertAndSend()
    print("board after computer move:")
    k.drukuj()
    print ("oto najlepszy ruch komputera: ", computerMov)

    print("\n\nsending response\n\n")
    # print(int(clients[socketID.index(id)].player1.getID()))
    # clients[socketID.index(id)].player1.convert_and_update(int_board)
    move = transform(computerMov)
    # move = {'px': [1, 0], 'py': [2, 3], 'tx': [0, 1], 'ty': [3, 4], 'rx':[], 'ry':[]}

    #send computer response
    emit('moveResp', move)
    
    # pom = int(clients[socketID.index(id)].getID())
    # emit('moveResp', {data: pom})

def transform(data):
    px = []
    py = []
    tx = []
    ty = []
    rx = []
    ry = []

    px.append(data[1])
    py.append(7-data[0])
    tx.append(data[3])
    ty.append(7-data[2])

    return {'px': px, 'py': py, 'tx': tx, 'ty': ty, 'rx': rx, 'ry': ry}