var MongoClient = require('mongodb').MongoClient
var url = 'mongodb://localhost:27017'
var SHA256 = require("crypto-js/sha256");

  if (process.argv.length == 4)
  {
    MongoClient.connect(url, function (err, db) {
      if (err) throw err
      var dbo = db.db("xadrex");
      let nome     = process.argv[2]; 
      let password = SHA256(process.argv[3]).toString();

      var myobj = { nome: nome, password: password }
      dbo.collection('Usuarios').insertOne(myobj, function (err, res) {
        if (err)
        {
          console.log("erro inserindo elemento")
        }
        else {
          console.log('1 document inserted')
        }
        db.close()
      })
    })
  }
  else
  {
    console.log("Forma de usar:   insere nome senha")
    console.log("Exemplo:         insere 'gabriel' 123")
  }

