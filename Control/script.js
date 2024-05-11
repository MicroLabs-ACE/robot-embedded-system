var gamepadControllers;
var controllerDevice = 0;
var gamepadIndex = 0;

const ipAddress = "192.168.4.1";

const Direction = {
  FORWARD: 4,
  BACKWARD: 6,
  RIGHT: 1,
  LEFT: 3,
};

function move(commands) {
  fetch(`http://${ipAddress}/move`, {
    method: "POST",
    body: JSON.stringify(commands),
    headers: { "Content-Type": "application/json" },
  })
    .then((response) => response.json())
    .then((data) => console.log(data));
}

function listGamepads() {
  gamepadControllers = [];

  var container = document.getElementById("listGamepads");
  container.innerHTML = "";
  var ul = document.createElement("ul");

  getGamepads();
  for (const [index, gpName] of gamepadControllers.entries()) {
    if (gpName) {
      var li = document.createElement("li");
      li.textContent = `${index}: ${gpName}`;
      ul.appendChild(li);
    }
  }
  container.appendChild(ul);
}

function gamepadController() {
  let gamepad = navigator.getGamepads()[gamepadIndex];
  let dirNorthSouth = 0;
  let dirEastWest = 0;

  if (gamepad) {
    let buttons = gamepad.buttons;
    if (buttons[Direction.FORWARD].pressed) {
      dirNorthSouth = 1;
    }
    if (buttons[Direction.BACKWARD].pressed) {
      dirNorthSouth = -1;
    }
    if (buttons[Direction.RIGHT].pressed) {
      dirEastWest = 1;
    }
    if (buttons[Direction.LEFT].pressed) {
      dirEastWest = -1;
    }

    console.log([dirNorthSouth, dirEastWest]);
  }
}

function getGamepads() {
  const gamepads = navigator.getGamepads();
  for (const gp of gamepads) {
    if (gp) {
      const gpName = gp.id.split("(")[0];
      gamepadControllers.push(gpName);
    }
  }
}

window.addEventListener("DOMContentLoaded", listGamepads);
window.addEventListener("gamepadconnected", listGamepads);
window.addEventListener("gamepaddisconnected", listGamepads);
setInterval(gamepadController, 500);
