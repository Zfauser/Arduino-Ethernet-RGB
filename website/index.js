let power = "OFF";

// save power state to local storage
if (localStorage.getItem("power") === null) {
    localStorage.setItem("power", power)
} else {
    power = localStorage.getItem("power")
    if (power === "ON") {
        document.getElementById("powerSlider").checked = true
    } else {
        document.getElementById("powerSlider").checked = false
    }
}
// save color state to local storage
if (localStorage.getItem("red") === null) {
    localStorage.setItem("red", 0)
} else {
    document.getElementById("redSlider").value = localStorage.getItem("red")
    document.getElementById("redValue").innerHTML = "Red: " + localStorage.getItem("red")
}
if (localStorage.getItem("green") === null) {
    localStorage.setItem("green", 0)
} else {
    document.getElementById("greenSlider").value = localStorage.getItem("green")
    document.getElementById("greenValue").innerHTML = "Green: " + localStorage.getItem("green")
}
if (localStorage.getItem("blue") === null) {
    localStorage.setItem("blue", 0)
} else {
    document.getElementById("blueSlider").value = localStorage.getItem("blue")
    document.getElementById("blueValue").innerHTML = "Blue: " + localStorage.getItem("blue")
}

const originalUrl = window.location.href.split('?')[0];
const powerElement = document.getElementById("powerSlider")
const powerValue = document.getElementById("powerValue")
powerElement.addEventListener("change", function () {
    if (powerElement.checked) {
        power = "ON"
        localStorage.setItem("power", power)
        window.location.href = originalUrl + '?button1on';
    } else {
        power = "OFF"
        localStorage.setItem("power", power)
        window.location.href = originalUrl + '?button1off';
    }
    powerValue.innerHTML = "LED: " + power
})

document.getElementById("powerValue").innerHTML = "LED: " + power

function redChange() {
    const red = document.getElementById("redSlider").value
    document.getElementById("redValue").innerHTML = "Red: " + red
    localStorage.setItem("red", red)
    window.location.href = originalUrl + '?red=' + red;
}

function greenChange() {
    const green = document.getElementById("greenSlider").value
    document.getElementById("greenValue").innerHTML = "Green: " + green
    localStorage.setItem("green", green)
    window.location.href = originalUrl + '?green=' + green;
}

function blueChange() {
    const blue = document.getElementById("blueSlider").value
    document.getElementById("blueValue").innerHTML = "Blue: " + blue
    localStorage.setItem("blue", blue)
    window.location.href = originalUrl + '?blue=' + blue;
}

function RESET() {
    document.getElementById("redSlider").value = 0
    document.getElementById("greenSlider").value = 0
    document.getElementById("blueSlider").value = 0
    document.getElementById("redValue").innerHTML = "Red: 0"
    document.getElementById("greenValue").innerHTML = "Green: 0"
    document.getElementById("blueValue").innerHTML = "Blue: 0"
    document.getElementById("powerSlider").checked = false
    document.getElementById("powerValue").innerHTML = "LED: OFF"
    localStorage.setItem("power", "OFF")
    localStorage.setItem("red", 0)
    localStorage.setItem("green", 0)
    localStorage.setItem("blue", 0)
    window.location.href = originalUrl + '?reset';
}