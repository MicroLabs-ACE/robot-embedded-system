var gamepadControllers;
var controllerDevice = 0;
var gamepadIndex = 0;

const Direction = {
  FORWARD: 4,
  BACKWARD: 6,
  RIGHT: 1,
  LEFT: 3,
};

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
  if (gamepad) {
    let buttons = gamepad.buttons;
    if (buttons[Direction.FORWARD].pressed) {
      console.log("Forward");
    }
    if (buttons[Direction.BACKWARD].pressed) {
      console.log("Backward");
    }
    if (buttons[Direction.RIGHT].pressed) {
      console.log("Right");
    }
    if (buttons[Direction.LEFT].pressed) {
      console.log("Left");
    }
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
