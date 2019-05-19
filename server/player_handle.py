import Klient

clients=[]
clientIDs =[]

#assign a unique ID to a new player
def initialize_player():
	if (len(clients) == 0):
		k = Klient.Klient(0)
		clients.append(k)
		clientIDs.append(0)
	else:
		for i in range(len(clients)):
			if i not in clientIDs:
				clientIDs.append(i)
				k = Klient.Klient(i)
				clients.append(k)
				break
			if i == len(clients)-1:
				i+=1
				k = Klient.Klient(i)
				clientIDs.append(i)
				clients.append(k)
	print(clients)

#delete a player that lost connection
def delete_player(player_):
	if player_ in clientIDs:
		clients.pop(clientIDs.index(player_))
		clientIDs.remove(player_)
	print(clients)


if __name__ == "__main__":
	initialize_player()
	initialize_player()
	initialize_player()

	delete_player(1)
	initialize_player()
	initialize_player()
	delete_player(0)
	initialize_player()
	print(clients[0].getID())
	print(clientIDs)
