$(function() {
  var socket = io();

  socket.on('reading', function(msg) {
    console.log(msg);
    var data = msg['data'];
    $('p#content').text(data);
  });
});
