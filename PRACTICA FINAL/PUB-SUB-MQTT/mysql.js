//variables de mqtt

var mqtt = require('mqtt');// obtener el paquete mqtt
var hostMqtt = "localhost";
var port = 1883;
var clientMqtt;

//Variables SQL

var mysql = require('mysql');   
var conexion = mysql.createConnection({  //Creamos un objeto de conexi�n hacia la base de datos SQL
    host : 'localhost',
    database : 'registrosmart',
    user : 'root',
    password : '',
});

var topicSubscribe = "casa/habitacion/+";

function conectionCreate(error, cliente) {
    
    if (error) throw error;
    console.log('Conectado con el identificador ' + conexion.threadId);

    clientMqtt = mqtt.connect({ host: hostMqtt, port: port });
    clientMqtt.subscribe(topicSubscribe);
    clientMqtt.on("message", function (topic, message) {
        var messageDecrypt = message.toString('utf8');

        try {
            console.log(messageDecrypt);
            messageDecrypt = JSON.parse(messageDecrypt);
            console.log(message, messageDecrypt);
            //var objToInsert = { topic: topic, data: messageDecrypt };
            var sql = "INSERT INTO registros SET ?";
            conexion.query(sql, messageDecrypt, function (error, results) {
                if (error) throw error;
            
                console.log("1 record inserted");
                //process.exit();
            });

            /*collection.insertOne(objToInsert, function (err, res) {
                if (err) throw err;
                */console.log("El valor :" + messageDecrypt + " est� en la db");
            //});*/
        } catch (e) {
            console.log("existe un error en los datos");
        }
    });
}

conexion.connect(conectionCreate);