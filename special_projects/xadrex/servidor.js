var express = require('express')
var app = express();
var bodyParser = require('body-parser');
const WebSocket = require('ws');
var vetorClientes=[];
var vetorLogin=[];
var vetorGames=[];
var http = require('http');
var MongoClient = require('mongodb').MongoClient;
var url = 'mongodb://localhost:27017/';
var SHA256 = require("crypto-js/sha256");

const TIMEOUT = 10000;

const wss = new WebSocket.Server({ port: 8080 },function (){
	console.log('SERVIDOR WEBSOCKETS na porta 8080');
});

app.use(bodyParser.json()); 

app.use(express.static(__dirname + '/public'));

app.listen(3000, function(){
	console.log('SERVIDOR WEB na porta 3000');
});

class game {
	constructor(id, player1, player2) {		
		this.id = id;		
		this.player1 = player1;
		this.loadPlayer1 = false;
		this.token1 = SHA256(Date.now().toString()+player1).toString();
		this.player2 = player2;
		this.loadPlayer2 = false;
		this.token2 = SHA256(Date.now().toString()+player2).toString();
		this.board = new Array(8);
		this.turno = "player1";
		for (let i = 0; i < 8; i++) {
			this.board[i] = new Array(8);
		}
		this.board[0][0] = this.board [7][0] = "torreNegro";
		this.board[1][0] = this.board [6][0] = "cavaloNegro";
		this.board[2][0] = this.board [5][0] = "bispoNegro";
		this.board[3][0] = "rainhaNegro";
		this.board[4][0] = "reiNegro";
		this.board[0][7] = this.board [7][7] = "torreBranco";
		this.board[1][7] = this.board [6][7] = "cavaloBranco";
		this.board[2][7] = this.board [5][7] = "bispoBranco";
		this.board[3][7] = "rainhaBranco";
		this.board[4][7] = "reiBranco";
		for (let i = 0; i < 8; i++) {
			this.board[i][1] = "peaoNegro";
			this.board[i][6] = "peaoBranco";
		}
	}
}

function verificaUsuarios () {
	console.log('verificaUsuarios');
	let MSG = {tipo:'ONLINE', valor:'confirmacao'};
	var flag = true;
	for (let i = 0; i < vetorClientes.length; i++) {
		try {
			vetorClientes[i].send(JSON.stringify(MSG));
        } catch (e) {
			vetorLogin.push(vetorClientes[i]);
			removeUser(vetorClientes[i].nome);
			vetorClientes.splice(i, 1);
			flag = false;
        }
	}
	if (flag) {
		for (let i = 0; i < vetorGames.length; i++) {
			try {
				vetorGames[i].ws1.send(JSON.stringify(MSG));
		    } catch (e) {
				vetorGames[i].ws1 = null;
				vetorGames[i].loadPlayer1 = false;
		    }
			try {
				vetorGames[i].ws2.send(JSON.stringify(MSG));
		    } catch (e) {
				vetorGames[i].ws2 = null;
				vetorGames[i].loadPlayer2 = false;
		    }
		}
	}
}

function newUser(id) {
	let MSG = {tipo:'ADD-USER', valor:id};
	for (let i = 0; i < vetorClientes.length; i++) {
		if (vetorClientes[i].nome == id) {
			for (let j = 0; j < vetorClientes.length; j++) {
				if (i != j) {
					MSG.valor = vetorClientes[j].nome;
					try {
						vetorClientes[i].send(JSON.stringify(MSG));
					} catch (e) {

					}
				}
			}
		}
	}
}

function addUser(id) {
	let MSG = {tipo:'ADD-USER', valor:id};
	for (let i = 0; i < vetorClientes.length; i++) {
		if (vetorClientes[i].nome != id) {		
			try {
				vetorClientes[i].send(JSON.stringify(MSG));
		    } catch (e) {

		    }
		}
	}
}

function removeUser(id) {
	let MSG = {tipo:'REMOVE-USER', valor:id};
	for (let i = 0; i < vetorClientes.length; i++) {
		if (vetorClientes[i].nome != id) {		
			try {
				vetorClientes[i].send(JSON.stringify(MSG));
		    } catch (e) {

		    }
		}
	}
}

wss.on('connection', function connection(ws) {

	ws.on('message', function incoming(MSG) {
		MSG = JSON.parse(MSG);
		console.log(MSG);
    	if (MSG.tipo == 'LOGIN') {
        	MSG.valor.password = (SHA256(MSG.valor.password).toString());
			console.log('nome=',MSG.valor.nome+'  password=',MSG.valor.password)
        	MongoClient.connect(url, function (err, db) {
				var query = {nome: MSG.valor.nome};		
				var dbo = db.db("xadrex");
				dbo.collection('Usuarios').find(query).toArray(function(err, result) {
					if (result[0]==undefined) {
		 				console.log('nao existe usuario');
		 				let msgRetorno = {tipo:'ERRO',valor:'login invalido'};
		      			ws.send(JSON.stringify(msgRetorno));
		      			ws.close();
		 			} else {
						var flag = true;
						for (let i = 0; i < vetorClientes.length; i++) {
							if (vetorClientes[i].nome == MSG.valor.nome)
								flag = false;
						}
						if (flag) {
			 				if (result[0].password == MSG.valor.password) {
				 				console.log('validou usuario')
								ws.nome = MSG.valor.nome;
								ws.token = SHA256((Date.now()).toString()).toString();
								vetorLogin.push(ws);
								let msgRetorno = {tipo:'VALIDO', valor:ws.token};
								ws.send(JSON.stringify(msgRetorno));
			  				} else {
								console.log('cliente ',MSG.valor.ID,' nao valido, desconectando...')
								let msgRetorno = {tipo:'ERRO',valor:'login invalido'};
								ws.send(JSON.stringify(msgRetorno));
								ws.close();
			  				}
						} else {
							let msgRetorno = {tipo:'ERRO',valor:'usuario já está logado'};
							ws.send(JSON.stringify(msgRetorno));
							ws.close();
						}
					}
					db.close()
				})
			})    
		} else if (MSG.tipo == 'VERIFICA') {
			var flag = false;
			var nome;
			for (let i = 0; i < vetorLogin.length; i++) {
				if (vetorLogin[i].token == MSG.valor) {
					nome = vetorLogin[i].nome;					
					vetorLogin.splice(i, 1);
					ws.nome = nome;
					ws.token = MSG.valor;
					vetorClientes.push(ws);
					flag = true;
					break;
				}
			}
			if (flag) {
				let msgRetorno = {tipo:'VALIDO', valor:'confirmado'};
				ws.send(JSON.stringify(msgRetorno));
				newUser(nome);
				addUser(nome);
			} else {
				let msgRetorno = {tipo:'INVALIDO', valor:'nao confirmado'};
				ws.send(JSON.stringify(msgRetorno));
			}
		} else if (MSG.tipo == 'SAIR') {
			for (let i = 0; i < vetorClientes.length; i++) {
		    	if (vetorClientes[i].password == MSG.valor) {
					removeUser(vetorClientes[i].nome);		        	
					vetorClientes.splice(i, 1);
		       		break;
		    	}
		  	}
		} else if (MSG.tipo == 'CONVITE') {
			for (let i = 0; i < vetorClientes.length; i++) {
				if (vetorClientes[i].nome == MSG.valor) {
					let msg = {tipo: 'CONVITE', valor:ws.nome};
					vetorClientes[i].send(JSON.stringify(msg));
				}
			}
		} else if (MSG.tipo == 'START-GAME') {
			var g = new game(vetorGames.length, MSG.valor, ws.nome);
			vetorGames.push(g);
			for (let i = 0; i < vetorClientes.length; i++) {
		    	if (vetorClientes[i].nome == g.player1) {
					let msg = {tipo: 'REDIRECIONA-GAME', valor:g.token1+"&&"+g.id};
					vetorClientes[i].send(JSON.stringify(msg));	
					removeUser(vetorClientes[i].nome);
					vetorClientes.splice(i, 1);
		    	}
		  	}
			for (let i = 0; i < vetorClientes.length; i++) {
		    	if (vetorClientes[i].nome == g.player2) {
					let msg = {tipo: 'REDIRECIONA-GAME', valor:g.token2+"&&"+g.id};
					vetorClientes[i].send(JSON.stringify(msg));
					removeUser(vetorClientes[i].nome);
					vetorClientes.splice(i, 1);
		       		break;
		    	}
		  	}
		} else if (MSG.tipo == 'CONVITE-NEGADO') {
			for (let i = 0; i < vetorClientes.length; i++) {
		    	if (vetorClientes[i].nome == MSG.valor) {
					let msg = {tipo: 'CONVITE-NEGADO', valor:ws.nome};
					vetorClientes[i].send(JSON.stringify(msg));
		       		break;
		    	}
		  	}
		} else if (MSG.tipo == 'VERIFICA-GAME') {
			var query = MSG.valor.split("&&");
			var flag = false;
			var player1, player2;
			var cor;
			var board;
			var turno;
			for (let i = 0; i < vetorGames.length; i++) {
				if (vetorGames[i].id == query[1]) {
					if (query[0] == vetorGames[i].token1 && vetorGames[i].loadPlayer1 == false) {
						vetorGames[i].loadPlayer1 = true;
						player1 = vetorGames[i].player1;
						player2 = vetorGames[i].player2;
						cor = "branco";
						turno = vetorGames[i].turno;
						board = vetorGames[i].board;			
						vetorGames[i].ws1 = ws;
						flag = true;
					} else if (query[0] == vetorGames[i].token2 && vetorGames[i].loadPlayer2 == false) {
						vetorGames[i].loadPlayer2 = true;
						player1 = vetorGames[i].player2;
						player2 = vetorGames[i].player1;
						cor = "negro";
						turno = vetorGames[i].turno;
						board = vetorGames[i].board;
						vetorGames[i].ws2 = ws;
						flag = true;
					}
					break;
				}
			}
			if (flag == false) {
				let msg = {tipo: 'INVALIDO', valor:''};
				ws.send(JSON.stringify(msg));
			} else {
				let msg = {tipo: 'VALIDO', player1:player1, player2:player2, cor:cor, board:board, turno:turno};
				ws.send(JSON.stringify(msg));
			}
		} else if (MSG.tipo == 'SAIR-GAME') {
			var query = MSG.valor.split("&&");
			var nome1, nome2;
			var ws1, ws2;
			if (vetorGames[query[1]].token1 == query[0]) {
				nome1 = vetorGames[query[1]].player1;
				nome2 = vetorGames[query[1]].player2;
				ws1 = vetorGames[query[1]].ws1;
				ws2 = vetorGames[query[1]].ws2;
			} else {
				nome1 = vetorGames[query[1]].player2;
				nome2 = vetorGames[query[1]].player1;
				ws1 = vetorGames[query[1]].ws2;
				ws2 = vetorGames[query[1]].ws1;
			}
			ws1.nome = nome1;
			ws1.token = SHA256((Date.now()).toString()).toString();
			vetorLogin.push(ws1);
			let msgRetorno1 = {tipo:'REDIRECIONA', valor:ws1.token};
			ws1.send(JSON.stringify(msgRetorno1));
			ws2.nome = nome2;
			ws2.token = SHA256((Date.now()).toString()).toString();
			vetorLogin.push(ws2);
			let msgRetorno2 = {tipo:'REDIRECIONA', valor:ws2.token};
			ws2.send(JSON.stringify(msgRetorno2));
		} else if (MSG.tipo == 'JOGADA') {
			var query = MSG.valor.split("&&");
			let msg = {tipo: 'JOGADA', origemX:MSG.origemX, origemY:MSG.origemY, destinoX:MSG.destinoX, destinoY:MSG.destinoY};
			if (vetorGames[query[1]].token1 == query[0]) {
				vetorGames[query[1]].board[MSG.destinoX][MSG.destinoY] = vetorGames[query[1]].board[MSG.origemX][MSG.origemY];
				vetorGames[query[1]].board[MSG.origemX][MSG.origemY] = null;
				vetorGames[query[1]].turno = 'player2';
				vetorGames[query[1]].ws2.send(JSON.stringify(msg));
			} else {
				vetorGames[query[1]].board[7-MSG.destinoX][7-MSG.destinoY] = vetorGames[query[1]].board[7-MSG.origemX][7-MSG.origemY];
				vetorGames[query[1]].board[7-MSG.origemX][7-MSG.origemY] = null;
				vetorGames[query[1]].turno = 'player1';
				vetorGames[query[1]].ws1.send(JSON.stringify(msg));
			}
		} else if (MSG.tipo == 'FIM') {
			var query = MSG.valor.split("&&");
			var nome1, nome2;
			var ws1, ws2;
			if (vetorGames[query[1]].token1 == query[0]) {
				nome1 = vetorGames[query[1]].player1;
				nome2 = vetorGames[query[1]].player2;
				ws1 = vetorGames[query[1]].ws1;
				ws2 = vetorGames[query[1]].ws2;
			} else {
				nome1 = vetorGames[query[1]].player2;
				nome2 = vetorGames[query[1]].player1;
				ws1 = vetorGames[query[1]].ws2;
				ws2 = vetorGames[query[1]].ws1;
			}
			ws1.nome = nome1;
			ws1.token = SHA256((Date.now()).toString()).toString();
			vetorLogin.push(ws1);
			let msgRetorno1 = {tipo:'REDIRECIONA-FIM', valor:ws1.token};
			ws1.send(JSON.stringify(msgRetorno1));
			ws2.nome = nome2;
			ws2.token = SHA256((Date.now()).toString()).toString();
			vetorLogin.push(ws2);
			let msgRetorno2 = {tipo:'REDIRECIONA-FIM', valor:ws2.token};
			ws2.send(JSON.stringify(msgRetorno2));
		}
	});

	ws.on('close', function close() {
		verificaUsuarios();
  	});
});


