const char htmlPage[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
  <title>WebSocket Example</title>
  <script>
    var socket = new WebSocket("ws://192.168.1.157:81/");

    socket.onopen = function(event) {
      console.log("WebSocket opened:", event);
      socket.send("Hello from the client!");
    };

    socket.onmessage = function(event) {
      console.log("WebSocket message:", event.data);
    };

    socket.onclose = function(event) {
      console.log("WebSocket closed:", event);
    };
  </script>
</head>
<body>
  <h1>WebSocket Example</h1>
</body>
</html>

)=====";