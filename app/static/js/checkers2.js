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
  var computer = false;
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
      //moves the piece
      this.move_com = function (tile) {
          this.element.removeClass('selected');
          console.log("moving piece from server")


          //remove the mark from Board.board and put it in the new spot
          Board.board[this.position[0]][this.position[1]] = 0;
          Board.board[tile.position[0]][tile.position[1]] = this.player;
          this.position = [tile.position[0], tile.position[1]];
          //change the css using board's dictionary

          this.element.css('top', Board.dictionary[this.position[0]]);
          this.element.css('left', Board.dictionary[this.position[1]]);
          //   this.element.animate({'top':Board.dictionary[this.position[0]], 'left':Board.dictionary[this.position[1]]}, {duration:3000, easing:'linear'});
          //   this.element.animate({'left':Board.dictionary[this.position[1]]}, {duration:"slow", easing:'linear'});

          //if piece reaches the end of the row on opposite side crown it a king (can move all directions)
          if(!this.king && (this.position[0] == 0 || this.position[0] == 7 )) {
              this.makeKing();
          }
          // if (this.element.one('webkitTransitionEnd otransitionend oTransitionEnd msTransitionEnd transitionend')){
          console.log("piece moved");
          // gotowe = true;
          return true;
          // }
          // return true;
      };
    //moves the piece
    this.move = function (tile) {
      this.element.removeClass('selected');
      if(!Board.isValidPlacetoMove(tile.position[0], tile.position[1])) {console.log("wrong move "+tile.position[0]+" "+tile.position[1]);
        return false;
      }
        console.log("moving piece from server")


      //remove the mark from Board.board and put it in the new spot
      Board.board[this.position[0]][this.position[1]] = 0;
      Board.board[tile.position[0]][tile.position[1]] = this.player;
      this.position = [tile.position[0], tile.position[1]];
      //change the css using board's dictionary

      this.element.css('top', Board.dictionary[this.position[0]]);
      this.element.css('left', Board.dictionary[this.position[1]]);
      //   this.element.animate({'top':Board.dictionary[this.position[0]], 'left':Board.dictionary[this.position[1]]}, {duration:3000, easing:'linear'});
      //   this.element.animate({'left':Board.dictionary[this.position[1]]}, {duration:"slow", easing:'linear'});

      //if piece reaches the end of the row on opposite side crown it a king (can move all directions)
      if(!this.king && (this.position[0] == 0 || this.position[0] == 7 )) {
          this.makeKing();
      }
            console.log("piece moved");
            // gotowe = true;
            return true;
    };
    
    this.move_regular = function () {
		    
    }

    //tests if piece can jump anywhere
    this.canJumpAny = function () {
      if(this.canOpponentJump([this.position[0]+2, this.position[1]+2]) ||
         this.canOpponentJump([this.position[0]+2, this.position[1]-2]) ||
         this.canOpponentJump([this.position[0]-2, this.position[1]+2]) ||
         this.canOpponentJump([this.position[0]-2, this.position[1]-2])) {
        return true;
      } return false;
    };
	
	this.can_jump_any_regular = function(){
		if (this.can_opponent_jump_regular([this.position[0]+2, this.position[1]+2]) ||
			this.can_opponent_jump_regular([this.position[0]+2, this.position[1]-2]) ||
			this.can_opponent_jump_regular([this.position[0]-2, this.position[1]+2]) ||
			this.can_opponent_jump_regular([this.position[0]-2, this.position[1]-2])) {
				console.log("found another to capture");
			return true;
		}	
		return false;
	};
    //tests if an opponent jump can be made to a specific place
   this.canOpponentJump = function(newPosition) {
      //find what the displacement is
      var dx = newPosition[1] - this.position[1];
      var dy = newPosition[0] - this.position[0];
      //must be in bounds
      if(newPosition[0] > 7 || newPosition[1] > 7 || newPosition[0] < 0 || newPosition[1] < 0) return false;
      //middle tile where the piece to be conquered sits
      var tileToCheckx = this.position[1] + dx/2;
      var tileToChecky = this.position[0] + dy/2;
      if(tileToCheckx > 7 || tileToChecky > 7 || tileToCheckx < 0 || tileToChecky < 0) return false;
      //if there is a piece there and there is no piece in the space after that
      if(!Board.isValidPlacetoMove(tileToChecky, tileToCheckx) && Board.isValidPlacetoMove(newPosition[0], newPosition[1])) {
        //find which object instance is sitting there
        for(pieceIndex in pieces) {
          if(pieces[pieceIndex].position[0] == tileToChecky && pieces[pieceIndex].position[1] == tileToCheckx) {
            if(this.player != pieces[pieceIndex].player) {
              //return the piece sitting there
              return pieces[pieceIndex];
            }
          }
        }
      }
      return false;
    };
    
	this.can_opponent_jump_regular = function (newPosition) {
		//must be in bounds
      if(newPosition[0] > 7 || newPosition[1] > 7 || newPosition[0] < 0 || newPosition[1] < 0) return false;
//      check if newPosition is taken
		for (k of pieces) {
//			if you want to go to place where a piece already is - wrong
			if(k.position[0] == newPosition[0] && k.position[1] == newPosition[1]) {
//				console.log("there is a piece already");
				return false;
			}
		}
      console.log("looking for piece to capture");
//      checking bottom 
      if (newPosition[0] > this.position[0]){
      	console.log("looking for bottom");
//			checking right corner
			if (newPosition[1] > this.position[1]) {
//				look for pieces that may be there
				for (index in pieces) {
					if (pieces[index].position[0] == (this.position[0]+1) && pieces[index].position[1] == (this.position[1]+1)) {
						if (this.player != pieces[index].player) {
							console.log("found in bottom right corner")
							return pieces[index];
						}
					}
				}
			}
			
//			checking left corner
			if (newPosition[1] < this.position[1]) {
//				look for pieces that may be there
				for (index in pieces) {
					if (pieces[index].position[0] == (this.position[0]+1) && pieces[index].position[1] == (this.position[1]-1)) {
						if (this.player != pieces[index].player) {
							console.log("found in bottom left corner")
							return pieces[index];
						}
					}
				}
			}
			
      } 
//      checking top 
      else if (newPosition[0] < this.position[0]){
      	console.log("looking for top");
//			checking right corner
			if (newPosition[1] > this.position[1]) {
				console.log("looking for right");
//				look for pieces that may be there
				for (index in pieces) {
					if (pieces[index].position[0] == (this.position[0]-1) && pieces[index].position[1] == (this.position[1]+1)) {
						if (this.player != pieces[index].player) {
							console.log("found in top right corner")
							return pieces[index];
						}
					}
				}
			}
			
//			checking left corner
			if (newPosition[1] < this.position[1]) {
				console.log("looking for left");
//				look for pieces that may be there
				for (index in pieces) {
					if (pieces[index].position[0] == (this.position[0]-1) && pieces[index].position[1] == (this.position[1]-1)) {
						if (this.player != pieces[index].player) {
							console.log("found in top left corner")
							return pieces[index];
						}
					}
				}
			}
			
      } 
		return false;
	}

    this.opponent_jump_regular = function (tile) {
      var pieceToRemove = this.can_opponent_jump_regular(tile.position);
      captured_y.push(pieceToRemove.position[0])
        captured.push(pieceToRemove.position[1])
        captured.push(pieceToRemove.position[0])

      //if there is a piece to be removed, remove it
      if(pieceToRemove) {
        pieces[index].remove();
        console.log('removed');
        return true;
      }
      console.log('didn\'t move - no opponent');
      return false;
    };    

    this.remove = function () {
      //remove it and delete it from the gameboard
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
      //reset position so it doesn't get picked up by the for loop in the canOpponentJump method
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

  function Tile (element, position) {
    //linked DOM element
    this.element = element;
    //position in gameboard
    this.position = position;
    this.inRange2 = function(piece){
			if (piece.king == false) {
//				console.log("checking range of normal piece");
				for (k of pieces) {
//					if you want to go to place where a piece already is - wrong
					if(k.position[0] == this.position[0] && k.position[1] == this.position[1]) {
//						console.log("there is a piece already");
						return 'wrong';
					}
				}
//				if you want to jump
				if(dist(this.position[0], this.position[1], piece.position[0], piece.position[1]) == 2*Math.sqrt(2)) {
        			return 'jump';
      		}
//      		if you want to make regular move forward
      		else if (piece.player == 1 && this.position[0] > piece.position[0]) {
					if (dist(this.position[0], this.position[1], piece.position[0], piece.position[1]) == Math.sqrt(2)) {
//						console.log("regular move for player 1");
						return 'regular';
     				}
      		}
      		else if (piece.player == 2 && this.position[0] < piece.position[0]) {
					if (dist(this.position[0], this.position[1], piece.position[0], piece.position[1]) == Math.sqrt(2)) {
//						console.log("regular move for player 2");
						return 'regular';
     				}
      		}
      		else {
      			return 'wrong';
      		}
			}
			else {
				console.log("checking range of king");
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
      //initialize the 8x8 board
      initalize: function () {
          var countPieces = 0;
          var countTiles = 0;
          for (row in this.board) { //row is the index
              for (column in this.board[row]) { //column is the index
                  //whole set of if statements control where the tiles and pieces should be placed on the board
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
      //check if the location has an object
      isValidPlacetoMove: function (row, column) {
          if (row < 0 || row > 7 || column < 0 || column > 7) return false;
          if (this.board[row][column] == 0) {
              return true;
          }
          return false;
      },
      //change the active player - also changes div.turn's CSS
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
      checkifAnybodyWon: function () {
          if (this.score.player1 == 12) {
              return 1;
          } else if (this.score.player2 == 12) {
              return 2;
          }
          return false;
      },
      //reset the game
      clear: function () {
          location.reload();
      },
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
          // if jump doesn't exist, all pieces are allowed to move
          if (!this.jumpexist) {
              for (k of pieces) k.allowedtomove = true;
          }
      },


      // Possibly helpful for communication with back-end.
      str_board: function () {
          var ret = []

          for (i in this.board) {
              for (j in this.board[i]) {




                  var found = false
                  for (k of pieces) {
                      if (k.position[0] == i && k.position[1] == j) {
                          if (k.king) {
                              if(k.player == 1) ret.push(2)//ret[i*8+j] = '2';
                              else if (k.player == 2) ret.push(-2)//ret[i*8+j] = '-2';
                              // console.log(ret[i*8+j]);
                          }
                          else {
                              if(k.player == 1) ret.push(1)//ret[i*8+j] = '1';
                              else if (k.player == 2) ret.push(-1)//ret[i*8+j] = '-1';
                              // console.log(ret[2]);
                          }
                          found = true;
                          break;
                      }
                  }
                  if (!found) ret.push(0);//ret[i*8+j]= '0'
                  // console.log(ret);
              }
          }
          // console.log("element"+ret[1]);
          return ret
      }
  }
// }
  //initialize the board
  Board.initalize();

  /***
  Events
  ***/

  //select the piece on click if it is the player's turn
  $('.piece').on("click", function () {
    var selected;
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
        // console.log(pieces[8].position[0]+" "+pieces[8].position[1])

      }
    } else {
      if(isPlayersTurn) {
        if(!Board.continuousjump)
          console.log("jump exist for other pieces, that piece is not allowed to move")
        else
          console.log("continuous jump exist, you have to jump the same piece")
      }
    }
  });

  //reset game when clear button is pressed
  $('#cleargame').on("click", function () {
    Board.clear();
  });


  var find_index = function(array, x, y){
      console.log("looking for place in"+x+" "+y);
      console.log("array length: "+array.length);
      for ( i = 0; i < array.length; i++){
          console.log("pozycja: "+array[i].position);
          if (array[i].position[1] == x && array[i].position[0] == y){
              return i;

          }
      }
      console.log("didn't find position");
      return -1;
    };

  var sendMoveSequence = function(beginMove, destMove, captured){
        console.log("sending a message about a move sequence");
      var data = {
          begMov: beginMove,
          destMov: destMove,
          cap: captured
      };
      console.log(data)
      socket.emit('moveMsg', data);
    };

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
          console.log("finished sequence");
          return;
      }
  };

  socket.on("moveResp", function (data) {
      //move as many times as needed

      var move_list = []
      for(k in data.px) {
          move_list[k] = {'px': data.px[k], 'py': data.py[k], "tx": data.tx[k], 'ty': data.ty[k], 'rx': data.rx[k], 'ry':data.ry[k]};
          console.log(move_list[k]);
      }
      move_with_sequence(move_list);
      Board.changePlayerTurn();
      beginMove = [-1,-1]
      destMove = [-1,-1]
      captured_x = []
      captured_y = []

  });

  socket.on("init", function (data) {console.log("my id = "+data); connectionID=data});

    var computer_move_piece = function(data, callback){
        console.log(data);
        // find piece to move
        for (i in pieces){
            if (pieces[i].position[0] == data['py'] && pieces[i].position[1] == data['px']){
                console.log("found piece")
                for (j in tiles){
                    if (tiles[j].position[0]==data['ty'] && tiles[j].position[1]==data['tx']){
                        // pieces[i].move(tiles[j]);
                        pieces[i].move_com(tiles[j]);

                        if (data.rx > -1 && data.rx <= 7){
                            console.log("removing from coordinates:"+data.rx+" "+data.ry);
                            var index = find_index(pieces, data.rx, data.ry);
                            console.log("found index to remove: "+index)
                            pieces[index].remove();
                        }
                        console.log("removed or not")

                        console.log("moving"+pieces[i].position[0]+" "+pieces[i].position[1]+" to "+tiles[j].position[0]+" "+tiles[j].position[1]);
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
        console.log("didn't find")
        return false;
    };


  //move piece when tile is clicked
  $('.tile').on("click", function () {
    //make sure a piece is selected
    if($('.selected').length != 0) {
      //find the tile object being clicked
      var tileID = $(this).attr("id").replace(/tile/, '');
      var tile = tiles[tileID];
      //find the piece being selected
      var piece = pieces[$('.selected').attr("id")];
      //check if the tile is in range from the object
		var inRange = tile.inRange2(piece);
      if(inRange != 'wrong') {
        //if the move needed is jump, then move it but also check if another move can be made (double and triple jumps)
        if(inRange == 'jump') {
          if(piece.opponent_jump_regular(tile)) {
          	console.log("jump - moving piece");
              if (beginMove[0] == -1) {
                  beginMove[0]=7-piece.position[0];
                  beginMove[1]=piece.position[1];
              }
              destMove[0] = 7-tile.position[0];
              destMove[1] = tile.position[1];
              piece.move(tile);
              send_board = Board.str_board();
              console.log("oto board "+send_board);
            if(piece.can_jump_any_regular()) {
               // Board.changePlayerTurn(); //change back to original since another turn can be made
               piece.element.addClass('selected');

               // exist continuous jump, you are not allowed to de-select this piece or select other pieces
               Board.continuousjump = true;
            } else {
                sendMoveSequence(beginMove, destMove, captured)
                // sendMoveSequence([1, 1], [2, 2], -1, -1)
              Board.changePlayerTurn()
                beginMove = [-1,-1]
                destMove = [-1,-1]
                captured = [-1,-1]
//				wyslij wiadomosc o zakonczeniu ruchu gracza (np skonczyl bić)
              
            }
          }
          //if it's regular then move it if no jumping is available
        } else if(inRange == 'regular' && !Board.jumpexist) {
          if(!piece.canJumpAny()) {
              if (beginMove[0] == -1) {
                  beginMove[0]= 7- piece.position[0];
                  beginMove[1]=piece.position[1];
              }
              destMove[0] = 7 -tile.position[0];
              destMove[1] = tile.position[1];
            piece.move(tile);
            console.log("data tuz przed wyslaniem");
            console.log(beginMove)
            send_board = Board.str_board();
            console.log("oto board "+send_board);
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

