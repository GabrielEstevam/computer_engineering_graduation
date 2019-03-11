var MongoClient = require('mongodb').MongoClient;
var url = "mongodb://localhost:27017/";

MongoClient.connect(url, function(err, db) {
  if (err) throw err;
  var dbo = db.db("xadrex");
  dbo.createCollection("Usuarios", function(err, res) {
    if (err) throw err;
    console.log("Collection created!");
    db.close();
  });
});
