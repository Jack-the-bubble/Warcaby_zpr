import Klient

# clients=[]
# clientIDs =[]
#
# #assign a unique ID to a new player
# def initialize_player():
# 	if (len(clients) == 0):
# 		k = Klient.Klient(0)
# 		clients.append(k)
# 		clientIDs.append(0)
# 	else:
# 		for i in range(len(clients)):
# 			if i not in clientIDs:
# 				clientIDs.append(i)
# 				k = Klient.Klient(i)
# 				clients.append(k)
# 				break
# 			if i == len(clients)-1:
# 				i+=1
# 				k = Klient.Klient(i)
# 				clientIDs.append(i)
# 				clients.append(k)
# 	print(clients)

clients=[]
clientIDs =[]
socketID = []

#assign a unique ID to a new player
def initialize_player(id):
	print(Object.keys(io.sockets.sockets))
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
    print(clientIDs)


#delete a player that lost connection
def delete_player(player_):
    if player_ in socketID:
        clients.pop(socketID.index(player_))
        clientIDs.pop(socketID.index(player_))
        socketID.remove(player_)
    print(clientIDs)

# def delete_player(player_):
# 	if player_ in clientIDs:
# 		clients.pop(clientIDs.index(player_))
# 		clientIDs.remove(player_)
# 	print(clients)


if __name__ == "__main__":
	initialize_player(112233)
	initialize_player(15335)
	initialize_player(55468)

	delete_player(112233)
	initialize_player(6548)
	initialize_player(2351)
	delete_player(55468)
	initialize_player(2)
	print(clients[0].getID())
	print(clientIDs)
