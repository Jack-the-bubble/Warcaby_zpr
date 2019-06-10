window.onload = function() {
  var connectionID = -1
    //  fields to send move to engine
  var beginMove = [-1,-1]
  var destMove = [-1,-1]
  var captured = [-1,-1]
  //The initial setup
  var gameBoard = [
    [  0,  1,  0,  1,  0,  1,  0,  1 ],
    [  1,  0,  1,  0,  1,  0,  1,  0 ],
    [  0,  1,  0,  1,  0,  1,  0,  1 ],
    [  0,  0,  0,  0,  0,  0,  0,  0 ],
    [  0,  0,  0,  0,  0,  0,  0,  0 ],
    [  2,  0,  2,  0,  2,  0,  2,  0 ],
    [  0,  2,  0,  2,  0,  2,  0,  2 ],
    [  2,  0,  2,  0,  2,  0,  2,  0 ]
  ];
  //arrays to store the instances
  var pieces = [];
  var tiles = [];
  var computer = true;
  //distance formula
  var dist = function (x1, y1, x2, y2) {
    return Math.sqrt(Math.pow((x1-x2),2)+Math.pow((y1-y2),2));
  }
  //Piece object - there are 24 instances of them in a checkers game
  function Piece (element, position) {
    // when jump exist, regular move is not allowed
    // since there is no jump at round 1, all pieces are allowed to move initially
    this.allowedtomove = true;
    //linked DOM element
    this.element = element;
    //positions on gameBoard array in format row, column
    this.position = position;
    //which player's piece i it
    this.player = '';
    //figure out player by piece id
    if(this.element.attr("id") < 12)
      this.player = 1;
    else
      this.player = 2;
    //makes object a king
    this.king = false;
    this.makeKing = function () {
      this.element.css("backgroundImage", "url('/static/img/king"+this.player+".png')");
      this.king = true;
    }
      /**
       * funkcja przemieszczajaca pionek od strony komputera
       * @param tile - miejsce, w ktore chcemy przemiescic pionek
       * */
      this.move_com = function (tile) {
          this.element.removeClass('selected');
          console.log("moving piece from server")


          //przenies pionek w tablicy logiki gry
          Board.board[this.position[0]][this.position[1]] = 0;
          Board.board[tile.position[0]][tile.position[1]] = this.player;
          this.position = [tile.position[0], tile.position[1]];

          //zmien plik CSS
          this.element.css('top', Board.dictionary[this.position[0]]);
          this.element.css('left', Board.dictionary[this.position[1]]);
          //jesli pionek przejdzie na drugi koniec planszy, promuj na damke
          if(!this.king && (this.position[0] == 0 || this.position[0] == 7 )) {
              this.makeKing();
          }
          return true;
      };
      /**
       * funkcja przemieszczajaca pionek od strony klienta
       * @param tile - miejsce, w ktore chcemy przemiescic pionek
       * */
    this.move = function (tile) {
      this.element.removeClass('selected');
      if(!Board.isValidPlacetoMove(tile.position[0], tile.position[1])) {
        return false;
      }
        // console.log("moving piece from server")


      Board.board[this.position[0]][this.position[1]] = 0;
      Board.board[tile.position[0]][tile.position[1]] = this.player;
      this.position = [tile.position[0], tile.position[1]];
      this.element.css('top', Board.dictionary[this.position[0]]);
      this.element.css('left', Board.dictionary[this.position[1]]);
      if(!this.king && (this.position[0] == 0 || this.position[0] == 7 )) {
          this.makeKing();
      }
            return true;
    };
    
    this.move_regular = function () {
		    
    }

    /**
     * sprawdza czy pionek moze skoczyc w ktoryms kierunku
     * @return - moze skoczyc lub nie
     * */
    this.canJumpAny = function () {
      if(this.canOpponentJump([this.position[0]+2, this.position[1]+2]) ||
         this.canOpponentJump([this.position[0]+2, this.position[1]-2]) ||
         this.canOpponentJump([this.position[0]-2, this.position[1]+2]) ||
         this.canOpponentJump([this.position[0]-2, this.position[1]-2])) {
        return true;
      } return false;
    };

    /**
     * sprawdza czy w zasiegu jest kolejny pionek do zbicia (funkcja dla zwyklego pionka, nie damy)
     * @return istnieje bicie lub nie
     * */
	this.can_jump_any_regular = function(){
		if (this.can_opponent_jump_regular([this.position[0]+2, this.position[1]+2]) ||
			this.can_opponent_jump_regular([this.position[0]+2, this.position[1]-2]) ||
			this.can_opponent_jump_regular([this.position[0]-2, this.position[1]+2]) ||
			this.can_opponent_jump_regular([this.position[0]-2, this.position[1]-2])) {
			return true;
		}	
		return false;
	};
    /**
     * sprawdza czy skok pionka moze zostac wykonany w konkretne miejsce
     * @param newPosition - nowa pozycja do sprawdzenia
     * @return indeks pionka ktory znajduje sie na danej pozycji lub false jesli nic tam nie ma
     * */
   this.canOpponentJump = function(newPosition) {
      var dx = newPosition[1] - this.position[1];
      var dy = newPosition[0] - this.position[0];
      //czy nowa pozycja jest na szachownicy
      if(newPosition[0] > 7 || newPosition[1] > 7 || newPosition[0] < 0 || newPosition[1] < 0) return false;
      var tileToCheckx = this.position[1] + dx/2;
      var tileToChecky = this.position[0] + dy/2;
      if(tileToCheckx > 7 || tileToChecky > 7 || tileToCheckx < 0 || tileToChecky < 0) return false;
      // jesli obok jest pionek do zbicia to czy jest miejsce za nim na skok
      if(!Board.isValidPlacetoMove(tileToChecky, tileToCheckx) && Board.isValidPlacetoMove(newPosition[0], newPosition[1])) {
        // znajdz indeks pionka ktory tu jest
        for(pieceIndex in pieces) {
          if(pieces[pieceIndex].position[0] == tileToChecky && pieces[pieceIndex].position[1] == tileToCheckx) {
            if(this.player != pieces[pieceIndex].player) {
              return pieces[pieceIndex];
            }
          }
        }
      }
      return false;
    };

   /**
    * sprawdza czy pionek moze skoczyc w konkretne miejsce
    * @param newPosition - miejsce do sprawdzenia
    * @return -
    * */
	this.can_opponent_jump_regular = function (newPosition) {
      if(newPosition[0] > 7 || newPosition[1] > 7 || newPosition[0] < 0 || newPosition[1] < 0) return false;
		for (k of pieces) {
//			jesli miejsce jest zaete - zwroc false
			if(k.position[0] == newPosition[0] && k.position[1] == newPosition[1]) {
				return false;
			}
		}
//      dol
      if (newPosition[0] > this.position[0]){
//			prawy rog
			if (newPosition[1] > this.position[1]) {
//				szukaj pionkow
				for (index in pieces) {
					if (pieces[index].position[0] == (this.position[0]+1) && pieces[index].position[1] == (this.position[1]+1)) {
						if (this.player != pieces[index].player) {
							console.log("found in bottom right corner")
							return pieces[index];
						}
					}
				}
			}
			
//			lewy rog
			if (newPosition[1] < this.position[1]) {
				for (index in pieces) {
					if (pieces[index].position[0] == (this.position[0]+1) && pieces[index].position[1] == (this.position[1]-1)) {
						if (this.player != pieces[index].player) {
							return pieces[index];
						}
					}
				}
			}
			
      } 
//      sprawdzanie gory
      else if (newPosition[0] < this.position[0]){
//			prawy rog
			if (newPosition[1] > this.position[1]) {
				for (index in pieces) {
					if (pieces[index].position[0] == (this.position[0]-1) && pieces[index].position[1] == (this.position[1]+1)) {
						if (this.player != pieces[index].player) {
							return pieces[index];
						}
					}
				}
			}
			
//			lewy rog
			if (newPosition[1] < this.position[1]) {
				for (index in pieces) {
					if (pieces[index].position[0] == (this.position[0]-1) && pieces[index].position[1] == (this.position[1]-1)) {
						if (this.player != pieces[index].player) {
							return pieces[index];
						}
					}
				}
			}
			
      } 
		return false;
	}
    /**
     * funkcja do zbicia pionka
     * @param tile - miejsce skoku pionka bijacego
     * @return true - usunieto, false - nie usunieto
     * */
    this.opponent_jump_regular = function (tile) {
      var pieceToRemove = this.can_opponent_jump_regular(tile.position);
        captured.push(pieceToRemove.position[1])
        captured.push(pieceToRemove.position[0])

      // usun pionek jesli jest
      if(pieceToRemove) {
        pieces[index].remove();
        return true;
      }
      return false;
    };    
    /**
     * funkcja usuwa dany pionek z gry
     * */
    this.remove = function () {
      this.element.css("display", "none");
      if(this.player == 1) {
        $('#player2').append("<div class='capturedPiece'></div>");
        Board.score.player2 += 1;
      }
      if(this.player == 2) {
        $('#player1').append("<div class='capturedPiece'></div>");
        Board.score.player1 += 1;
      }
      if (captured[0] == -1){
          captured[0] = 7-this.position[0];
          captured[1] = this.position[1];
      }
      else {
          captured.push(7-this.position[0]);
          captured.push(this.position[1]);
      }

      Board.board[this.position[0]][this.position[1]] = 0;
      //wyzreuj pozycje
      this.position = [];
      var playerWon = Board.checkifAnybodyWon();
      if(playerWon == 1) {
        $('#winner').html("Player "+2+" has won!");
      }
      else if (playerWon == 2){
          $('#winner').html("Player "+1+" has won!");
      }
    }
  }

  /**
   * klasa pozycji na planszy, po nich poruszaja sie wszystkie pionki
   *
   * */
  function Tile (element, position) {
    //linked DOM element
    this.element = element;
    //position in gameboard
    this.position = position;
    /**
     * funkcja sprawdza, czy miejsce, w ktore chcemy przejsc jest w zasiegu
     * */
    this.inRange2 = function(piece){
			if (piece.king == false) {
				for (k of pieces) {
//					jesli w tym miejscu uz jest pionek
					if(k.position[0] == this.position[0] && k.position[1] == this.position[1]) {
						return 'wrong';
					}
				}
//				jesli chcesz skoczyc
				if(dist(this.position[0], this.position[1], piece.position[0], piece.position[1]) == 2*Math.sqrt(2)) {
        			return 'jump';
      		}
//      	standardowy ruch do przodu
      		else if (piece.player == 1 && this.position[0] > piece.position[0]) {
					if (dist(this.position[0], this.position[1], piece.position[0], piece.position[1]) == Math.sqrt(2)) {
						return 'regular';
     				}
      		}
      		else if (piece.player == 2 && this.position[0] < piece.position[0]) {
					if (dist(this.position[0], this.position[1], piece.position[0], piece.position[1]) == Math.sqrt(2)) {
						return 'regular';
     				}
      		}
      		else {
      			return 'wrong';
      		}
			}
			else {
				return 'long_jump';
			}			
    }
  }

  //Board object - controls logistics of game
  var Board = {
      board: gameBoard,
      score: {player1: 0, player2: 0},
      playerTurn: 2,
      jumpexist: false,
      continuousjump: false,
      tilesElement: $('div.tiles'),
      //dictionary to convert position in Board.board to the viewport units
      dictionary: ["0vmin", "10vmin", "20vmin", "30vmin", "40vmin", "50vmin", "60vmin", "70vmin", "80vmin", "90vmin"],
      /**
       * funkcja inicjujaca plansze zaraz po zaladowaniu strony
       * */
      initalize: function () {
          var countPieces = 0;
          var countTiles = 0;
          for (row in this.board) { //rzad
              for (column in this.board[row]) { //kolumna
                  //ulozenie pol i pionow na planszy
                  if (row % 2 == 1) {
                      if (column % 2 == 0) {
                          this.tilesElement.append("<div class='tile' id='tile" + countTiles + "' style='top:" + this.dictionary[row] + ";left:" + this.dictionary[column] + ";'></div>");
                          tiles[countTiles] = new Tile($("#tile" + countTiles), [parseInt(row), parseInt(column)]);
                          countTiles += 1;
                      }
                  } else {
                      if (column % 2 == 1) {
                          this.tilesElement.append("<div class='tile' id='tile" + countTiles + "' style='top:" + this.dictionary[row] + ";left:" + this.dictionary[column] + ";'></div>");
                          tiles[countTiles] = new Tile($("#tile" + countTiles), [parseInt(row), parseInt(column)]);
                          countTiles += 1;
                      }
                  }
                  if (this.board[row][column] == 1) {
                      $('.player1pieces').append("<div class='piece' id='" + countPieces + "' style='top:" + this.dictionary[row] + ";left:" + this.dictionary[column] + ";'></div>");
                      pieces[countPieces] = new Piece($("#" + countPieces), [parseInt(row), parseInt(column)]);
                      countPieces += 1;
                  } else if (this.board[row][column] == 2) {
                      $('.player2pieces').append("<div class='piece' id='" + countPieces + "' style='top:" + this.dictionary[row] + ";left:" + this.dictionary[column] + ";'></div>");
                      pieces[countPieces] = new Piece($("#" + countPieces), [parseInt(row), parseInt(column)]);
                      countPieces += 1;
                  }
              }
          }
      },
      /**
       * funkcja sprawdza, czy pole docelowe jest w granicach planszy
       * @return true - jest, false - nie jest
       * */
      isValidPlacetoMove: function (row, column) {
          if (row < 0 || row > 7 || column < 0 || column > 7) return false;
          if (this.board[row][column] == 0) {
              return true;
          }
          return false;
      },
      /**
       * funkcja zmienia kolejnosc graczy, jednoczesnie zmieniajac pasek kolejnosci gracza pod tablica wynikow
       * */
      changePlayerTurn: function () {
          if (this.playerTurn == 1) {
              this.playerTurn = 2;
              $('.turn').css("background", "linear-gradient(to right, transparent 50%, #00a700 50%)");
              this.check_if_jump_exist()
              return;
          }
          if (this.playerTurn == 2) {
              this.playerTurn = 1;
              $('.turn').css("background", "linear-gradient(to right, #00a700 50%, transparent 50%)");
              this.check_if_jump_exist()
              return;
          }
      },

      /**
       * funkcja sprawdza, czy pojawil sie zwyciezca
       * @return 1 - gracz1, 2 - gracz 2, false - nie wygral nikt
       * */
      checkifAnybodyWon: function () {
          if (this.score.player1 == 12) {
              return 1;
          } else if (this.score.player2 == 12) {
              return 2;
          }
          return false;
      },
      /**
       * resetuje gre
       * */
      clear: function () {
          location.reload();
      },

      /**
       * sprawdza czy istnieje skok, a wiec czy jest przymus bicia
       * */
      check_if_jump_exist: function () {
          this.jumpexist = false
          this.continuousjump = false;
          for (k of pieces) {
              k.allowedtomove = false;
              // if jump exist, only set those "jump" pieces "allowed to move"
              if (k.position.length != 0 && k.player == this.playerTurn && k.canJumpAny()) {
                  this.jumpexist = true
                  k.allowedtomove = true;
              }
          }
          // jesli jest skok, to istnieje przymus bicia
          if (!this.jumpexist) {
              for (k of pieces) k.allowedtomove = true;
          }
      },


      // Possibly helpful for communication with back-end.
      // str_board: function () {
      //     var ret = []
      //
      //     for (i in this.board) {
      //         for (j in this.board[i]) {
      //
      //
      //
      //
      //             var found = false
      //             for (k of pieces) {
      //                 if (k.position[0] == i && k.position[1] == j) {
      //                     if (k.king) {
      //                         if(k.player == 1) ret.push(2)//ret[i*8+j] = '2';
      //                         else if (k.player == 2) ret.push(-2)//ret[i*8+j] = '-2';
      //                         // console.log(ret[i*8+j]);
      //                     }
      //                     else {
      //                         if(k.player == 1) ret.push(1)//ret[i*8+j] = '1';
      //                         else if (k.player == 2) ret.push(-1)//ret[i*8+j] = '-1';
      //                         // console.log(ret[2]);
      //                     }
      //                     found = true;
      //                     break;
      //                 }
      //             }
      //             if (!found) ret.push(0);//ret[i*8+j]= '0'
      //             // console.log(ret);
      //         }
      //     }
      //     // console.log("element"+ret[1]);
      //     return ret
      // }
  }
// }
  //iinicjuj plansze
  Board.initalize();

  /***
  Events
  ***/

  /**
   * klasa pionka - to nim posluguje sie gracz oraz komputer podczas rozgrywki
   * */
  $('.piece').on("click", function () {
    var selected;
     //jesli tryb komputera jest wylaczony, klient moze manipulowac obydwiema stronami rozgrywki
     if (computer == true) {
         var isPlayersTurn = ($(this).parent().attr("class").split(' ')[0] == "player2pieces");
     }
    else{
         var isPlayersTurn = ($(this).parent().attr("class").split(' ')[0] == "player"+Board.playerTurn+"pieces");
     }
    if(isPlayersTurn && !Board.continuousjump && pieces[$(this).attr("id")].allowedtomove) {
      if($(this).hasClass('selected')) selected = true;
      $('.piece').each(function(index) {$('.piece').eq(index).removeClass('selected')});
      if(!selected) {
        $(this).addClass('selected');
      }
    } else {
      if(isPlayersTurn) {
        if(!Board.continuousjump)
          console.log("istnieje skok dla innych pionkow, ten nie moze sie ruszyc")
        else
          console.log("istnieje kilkukrotne bicie, musisz poruszac sie tym samym pionkiem")
      }
    }
  });

  //resetuj gre po wcisnieciu przycisku
  $('#cleargame').on("click", function () {
    Board.clear();
  });

    /**
     * znajdz indeks pionka o podanych wspolrzednych
     * @param array - list w ktorej nalezy szukac indeksu
     * @param x - pierwsza wspolrzedna
     * @param y - druga wspolrzedna
     * @return i - indeks znalezionego pionka lub -1 gdy nie znalazl
     * */
  var find_index = function(array, x, y){
      for ( i = 0; i < array.length; i++){
          if (array[i].position[1] == x && array[i].position[0] == y){
              return i;
          }
      }
      return -1;
    };

  /**
   * funkcja wysyla do serwera sekwencje ruchu klienta razem z tablica zbitych pionkow
   * @param beginMove - miejsce poczatkowe piona
   * @param destMove - wspolrzedne docelowe piona
   * @param captured - lista wpsolrzednych zbitych pionow
   * */
  var sendMoveSequence = function(beginMove, destMove, captured){
      var data = {
          begMov: beginMove,
          destMov: destMove,
          cap: captured
      };
      socket.emit('moveMsg', data);
    };
  /**
   * funkcja wykonujaca sie rekurencyjnie do animacji i ruchu pionow komputera
   * @param param list - lista z parametrami ruchu piona oraz lista pionow do zbicia
   * */
  var move_with_sequence = function(param_list){
      if (param_list.length > 0) {
          console.log("current move to make: ");
          console.log(param_list[0]);
          computer_move_piece(param_list[0], function () {
                  param_list.splice(0, 1);
                  move_with_sequence(param_list);
          });
      }
      else {
          return;
      }
  };

    /**
     *funkcja reagujaca na wiadomosc o ruchu komputera od serwera
     * @param data - dane o ruchu
     * */
  socket.on("moveResp", function (data) {
      //move as many times as needed

      var move_list = []
      for(k in data.px) {
          move_list[k] = {'px': data.px[k], 'py': data.py[k], "tx": data.tx[k], 'ty': data.ty[k], 'rx': data.rx[k], 'ry':data.ry[k]};
      }
      move_with_sequence(move_list);
      Board.changePlayerTurn();
      beginMove = [-1,-1]
      destMove = [-1,-1]
      captured = [-1, -1]
  });

  socket.on("init", function (data) {console.log("my id = "+data); connectionID=data});

    /**
     * funkcja do przemieszczenia jednego pionka i usuniecia ewentualnie zbitego piona
     * @return true - udalo sie znalezc i przeniesc pion false - nie znaleziono piona
     *
     * */
    var computer_move_piece = function(data, callback){
        console.log(data);
        // znajdz pion do przeniesienia
        for (i in pieces){
            if (pieces[i].position[0] == data['py'] && pieces[i].position[1] == data['px']){
                for (j in tiles){
                    if (tiles[j].position[0]==data['ty'] && tiles[j].position[1]==data['tx']){
                        pieces[i].move_com(tiles[j]);
                        if (data.rx > -1 && data.rx <= 7){
                            var index = find_index(pieces, data.rx, data.ry);
                            pieces[index].remove();
                        }
                        // console.log("moving"+pieces[i].position[0]+" "+pieces[i].position[1]+" to "+tiles[j].position[0]+" "+tiles[j].position[1]);
                        pieces[i].element.one('webkitTransitionEnd otransitionend oTransitionEnd msTransitionEnd transitionend',
                            function () {
                                callback();
                            }
                        );
                        return true;
                    }
                }
            }
        }
        return false;
    };


  /**
   * przenies pion na pole, gdy to zostanie klikniete
   * */
  $('.tile').on("click", function () {
    //make sure a piece is selected
    if($('.selected').length != 0) {
      //znajdz klikniety obiekt
      var tileID = $(this).attr("id").replace(/tile/, '');
      var tile = tiles[tileID];
      //znajdz zaznaczony pion
      var piece = pieces[$('.selected').attr("id")];
      //sprawdz czy jest w zasiegu
		var inRange = tile.inRange2(piece);
      if(inRange != 'wrong') {
        //sprawdzenie wieloktotnych skokow
        if(inRange == 'jump') {
          if(piece.opponent_jump_regular(tile)) {
              //  zapis ruchu do wyslania do serwera
              if (beginMove[0] == -1) {
                  beginMove[0]=7-piece.position[0];
                  beginMove[1]=piece.position[1];
              }
              destMove[0] = 7-tile.position[0];
              destMove[1] = tile.position[1];
              piece.move(tile);
            if(piece.can_jump_any_regular()) {
               piece.element.addClass('selected');
               //zmuszenie do bicia dalej tym samym pionem
               Board.continuousjump = true;
            } else {
                sendMoveSequence(beginMove, destMove, captured)
                Board.changePlayerTurn()
                beginMove = [-1,-1]
                destMove = [-1,-1]
                captured = [-1,-1]
//				wyslij wiadomosc o zakonczeniu ruchu gracza (np skonczyl bić)
              
            }
          }
          //zwykly ruch - wykonaj jesli nie ma bicia
        } else if(inRange == 'regular' && !Board.jumpexist) {
          if(!piece.canJumpAny()) {
              if (beginMove[0] == -1) {
                  beginMove[0]= 7- piece.position[0];
                  beginMove[1]=piece.position[1];
              }
              destMove[0] = 7 -tile.position[0];
              destMove[1] = tile.position[1];
              piece.move(tile);
              sendMoveSequence(beginMove, destMove, captured)
              Board.changePlayerTurn()
              beginMove = [-1,-1]
              destMove = [-1,-1]
              captured = [-1, -1]
//				wyslac wiadomosc o zakonczeniu ruchu gracza            
            
          } else {
            alert("You must jump when possible!");
          }
        }
      }
    }
  });
  
  

}

