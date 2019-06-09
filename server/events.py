from flask_socketio import SocketIO, send, emit
# import gra
import engine
#
# clients=[]
# clientIDs =[]
# socketID = []
k = engine.Gra()
# print("getID to ")
# print(k.getID())
#assign a unique ID to a new player

'''
funkcja tworzy 
'''
def initialize_player(id):
    # k = engine.Gra(0)
    # k.play()
    # k.get
    print("creating new game")
    global k
    k = engine.Gra()
    k.assignID(1)
    print("after init id is ")
    print(k.getID())
    k.play()
    # k.player1notify()
    k.drukuj()
    print("playing")
    return k



#delete a player that lost connection
def delete_player(player_):
    print("deleting player")


def handle_move(data, id):
    global k
    # k.player1notify()
    print("id podczas ruchu to ", k.getID())
    k.klientGet()
    k.klientSet(5)

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
    move = transform(computerMov)

    #send computer response
    emit('moveResp', move)

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
    if(len(data) == 6):
        print("adding one piece to remove ", data[4], " ", data[5])
        rx.append(data[5])
        ry.append(7-data[4])
    elif(len(data)>6):
        print("creating advanced capture move", data[4], " ", data[5])
        tx = []
        ty = []
        i = 4
        while(i < len(data)):
            rx.append(data[i])
            ry.append(7-data[i+1])
            if(px[-1]>rx[-1]):
                px.append(rx[-1] - 1)
                tx.append(rx[-1]-1)
            else:
                px.append(rx[-1] + 1)
                tx.append(rx[-1] + 1)
            if(py[-1]>ry[-1]):
                py.append(7-(ry[-1] - 1))
                ty.append(7-(ry[-1] - 1))
            else:
                py.append(7-(ry[-1] + 1))
                ty.append(7-(ry[-1] + 1))
            i +=2
        del px[-1]
        del py[-1]
        # for i  in range(4, len(data)):
        #     rx.append(data[i])
        #     ry.append(7-data[i+1])
        #     if(px[-1]>rx[-1]):
        #         px.append(rx[-1] - 1)
        #         tx.append(rx[-1]-1)
        #     else:
        #         px.append(rx[-1] + 1)
        #         tx.append(rx[-1] + 1)
        #     if(py[-1]>ry[-1]):
        #         py.append(7-(ry[-1] - 1))
        #         ty.append(7-(ry[-1] - 1))
        #     else:
        #         py.append(7-(ry[-1] + 1))
        #         ty.append(7-(ry[-1] + 1))
        # del px[-1]
        # del py[-1]
    print("transformed to ", px, py, tx, ty, rx, ry)
    return {'px': px, 'py': py, 'tx': tx, 'ty': ty, 'rx': rx, 'ry': ry}