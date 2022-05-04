let input, select;
let intervalID = null;
function init() {
    input = document.getElementById("date");
    select = document.getElementsByTagName('select')[0];
    input.value = new Date().toISOString();

    const color = localStorage.getItem("color") || "red";
    input.style.color = color;
    select.value = color;

    intervalID = setInterval(changeColor, 3000);

    document.addEventListener("keypress", stopInterval);
}

function changeColor() {
    const options = document.querySelectorAll("select option");
    let index = options.findIndex(option => option.value == select.value);
    index=(index+1)%options.length;
    const color = options[index].value;
    input.style.color = color;
    select.value = color;
    localStorage.setItem("color", color);
}
function stopInterval(e) {
    if(e.key.toLowerCase() == "s" && intervalID != null) {
        clearInterval(intervalID);
    } 
}


window.addEventListener("load", init);