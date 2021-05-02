var mqtt = require('mqtt')
var hostMqtt = "localhost";
var port = 1883;
var client = mqtt.connect({ host: hostMqtt, port: port })

client.on('connect', function() {
    client.subscribe('casa/patio/+', function(err) {
        if (!err) {
            for (let i = 0; i < 2; i++) {
                n = retorno();
                client.publish('casa/patio/', n), 20000
            }
        }
    })
})

client.on('message', function(topic, message) {
    console.log(message.toString())
    client.end()
})

function retorno() {
    var num = Math.floor(Math.random() * (54 - 1)) + 1;
    return num.toString()
}