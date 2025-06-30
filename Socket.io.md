# Socket.io

> each user has a seperate room that is their ID
> .on is to recieve
> .emit is to send

## backend

### install

`npm i stocket.io`

```javascript
const io = require(socket.io)(8080, {
  cors: {
    origin: ["http://localhost:3000"],
  },
});

// const userIo = io.of('/user') you can perform same tasks with userIo object good for authentication

// const userIo.use((socket, next) => {
            // middleware used commonly for authentication
            // if(socket.handshake.auth.token){
            //      socket.username = getUsernameFromToken(socket.handshake.auth.token);
            // next();
            // }
            // else{
            //     next(new Error("Token not Found"))
            // }
//})

function getUsernameFromToken(token){
    return token;
}

io.on("connectoin", (socket) => {
  console.log(socket.id);
  // recieve event
  socket.on('coustom-event', (number, string, ....) => {
    console.log('hihii');
  })
  // send message to all clients
  socket.on('send-message', message => {
    io.emit('recieve-message', message);
  })

  // send to all clients except current
  socket.broadcast.emit('send-message', message => {
    io.emit('recieve-message', message);
  })

  // recieve and send to a room
  socket.broadcast.emit('send-message', (message, room) => {
    if (room === ''){
        socket.broadcast.emit("recieve-message", message);
    }
    else {
        const toRoom = socket.to(room); // broadcast built in
        toRoom.emit("recieve-message", message);
    }
  });

  //join a room and call a callback
  socket.on("join-room", (room, callback) => {
    socket.join(room);
    callback("sucssessful");
  });

  // you can also call a server method from client in the same way

});
```

## frontend

### install

`npm i socket.io-client`

```javascript

import { io } from `socket.io-client`

const socket = io('http://localhost:8080');

// const userSocket = io('http://localhost:8080/user', {auth: {token: "Test"}});

// userSocket.on("connect_error", error => {
    // console.log("error");
//}


// connect & disconnect (when you disconnect and reconnect socket.io will remember all the messages not sent during disconnection and send them all at once) if you don't want this use .volatile before .emit like socket.volatile.emit

document.addEventListener('Keydown', e => {
    if (e.target.matches('input')) return;
    if (e.key === 'c') socket.connect()
    if (e.key === 'd') socket.disconnect();
})

await socket.on('connect', () => {
    console.log(`you connected with id: ${socket.id}`);
});
// send request to server
socket.emit('coustome-event', 10, 'hi', ....);

//recieve message from server
socket.on('recieve-message', message => {
    console.log(message);
})

socket.emit('send-message', "Hiii");

// send to a room
socket.emit("send-message", message, room);

// join a room
socket.emit("join-room", room, message => { document.getElementById('a').innerHTML = message; });
//                             ^ ^ ^ ^ ^
// passing a callback to server so server can call a client function


```

for further information review : [Documentation](https://socket.io/docs/v4/tutorial/introduction)

Follow me on:

# Profiles

<div align="left">
  <a href="mailto:rbharadwaj022@gmail.com" target="_blank">
    <img src="https://img.shields.io/static/v1?message=Gmail&logo=gmail&label=&color=D14836&logoColor=white&labelColor=&style=for-the-badge" height="35" alt="gmail logo"  />
  </a>
  <a href="https://www.linkedin.com/in/bharadwaj-rachakonda-b36658258/" target="_blank">
    <img src="https://img.shields.io/static/v1?message=LinkedIn&logo=linkedin&label=&color=0077B5&logoColor=white&labelColor=&style=for-the-badge" height="35" alt="linkedin logo"  />
  </a>
  <a href="https://www.hackerrank.com/profile/rbharadwaj022" target="_blank">
    <img src="https://img.shields.io/static/v1?message=HackerRank&logo=hackerrank&label=&color=2EC866&logoColor=white&labelColor=&style=for-the-badge" height="35" alt="hackerrank logo"  />
  </a>
  <a href="https://bharadwajrachakonda.github.io/Portfolio/" target="_blank">
    <img src="https://img.shields.io/static/v1?message=Portfolio&logo=codepen&label=&color=000000&logoColor=white&labelColor=&style=for-the-badge" height="35" alt="codepen logo"  />
  </a>
  <a href="https://leetcode.com/u/BharadwajRachakonda/" target="_blank">
    <img src="https://img.shields.io/static/v1?message=LeetCode&logo=leetcode&label=&color=FFA116&logoColor=white&labelColor=&style=for-the-badge" height="35" alt="leetcode logo"  />
</a>
</div>
