var express = require('express');
var spark = require('spark');
var app = express();
var http = require('http').Server(app);
var io = require('socket.io')(http);

// !!! swap these for yours !!! //
var sokkit = {
  deviceId: '43002e001547343433313338',
  accessToken: 'e1720a62d1448b4ba10116dc423ad0a7002b731b'
};

// express setup
app.use(express.static(__dirname + '/public'));

// spark setup
spark.on('login', function(err, body) {
  spark.getDevice(sokkit.deviceId, function(err, device) {
    sokkit.device = device;
  });
});
spark.login({accessToken: sokkit.accessToken});

// socket.io setup
io.on('connection', function(socket){
  console.log('a user connected');
  if (!sokkit.subscribed) {
    var device = sokkit.device;
    device.subscribe('reading', function(data) {
      console.log(data);
      io.emit('reading', data);
    });
    sokkit.subscribed = true;
  }
});

// launch the app
http.listen(3000, function(){
  console.log('listening on *:3000');
});
