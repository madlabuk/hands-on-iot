const express = require('express')
const app = express()
const server = require('http').Server(app)
const io = require('socket.io')(server)
const Particle = require('particle-api-js')
const particle = new Particle()

// particle credentials, swap 'em out for yours!
const credentials = {
  username: 'bob@example.com',
  password: 'unguess4ble',
  deviceId: 'scraper_ranger'
}

// this is the interface between particle and our inbound websockets
const weatherbot = {
  sockets: [],

  registerSocket (socket) {
    this.sockets.push(socket)
  },

  emit (data) {
    this.sockets.map((socket) => {
      socket.emit('reading', data)
    })
  }
}

app.use(express.static('public'))

// wait for incoming websocket connections then throw 'em on over to weatherbot
io.on('connection', (socket) => {
  weatherbot.registerSocket(socket)
})

// particle stuff! logs in, registers to receive a stream of reading events
// then, when we receive something new, tell the weatherbot to send it out
particle.login({
  username: credentials.username,
  password: credentials.password
}).then(
  (data) => {
    const accessToken = data.body.access_token

    particle.getEventStream({
      auth: accessToken,
      deviceId: credentials.deviceId,
      name: 'reading'
    }).then((stream) => {
      stream.on('event', (data) => {
        weatherbot.emit(data)
      })
    })
  },
  (err) => {
    console.log('Fale: ', err)
  }
)

// fire up our webserver on port 3000
server.listen(3000, () => {
  console.log('Weather now live at http://localhost:3000')
})
