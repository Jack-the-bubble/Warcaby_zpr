'''
@
'''

from flask_socketio import SocketIO, send, emit
import engine

k = engine.Gra()

'''
funkcja tworzy 
'''
def initialize_player(id):
    print("creating new game")
    global k
    k = engine.Gra()

#delete a player that lost connection
def delete_player(player_):
    print("deleting player")


def handle_move(data, id):
    global k
    begMov = data['begMov']
    destMov = data['destMov']
    cap = data['cap']
    k.klientMoveUpdate(begMov[1], begMov[0], destMov[1], destMov[0], cap)
    k.changePlansza()
    k.player2notify()
    computerMov = k.convertAndSend()
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
        # print("adding one piece to remove ", data[4], " ", data[5])
        rx.append(data[5])
        ry.append(7-data[4])
    elif(len(data)>6):
        # print("creating advanced capture move", data[4], " ", data[5])
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
    # print("transformed to ", px, py, tx, ty, rx, ry)
    return {'px': px, 'py': py, 'tx': tx, 'ty': ty, 'rx': rx, 'ry': ry}