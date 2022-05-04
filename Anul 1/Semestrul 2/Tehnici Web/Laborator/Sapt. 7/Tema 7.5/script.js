function init() {
    const inputs = [...document.querySelectorAll("input")];
    setInterval(() => {
        const index = Math.floor(Math.random()*4);
        inputs[index].checked = true;
        const color = inputs[index].id;
        switch (color) {
            case "rosu": {
                document.body.style.backgroundColor = "red";
                break;
            }
            case "galben": {
                document.body.style.backgroundColor = "yellow";
                break;
            }
            case "albastru": {
                document.body.style.backgroundColor = "blue";
                break;
            }
            case "verde": {
                document.body.style.backgroundColor = "green";
                break;
            }
            case "portocaliu": {
                document.body.style.backgroundColor = "orange";
            }
            default:{
                document.body.style.backgroundColor = "white";
                break;
            }
        }
    }, 3000)
}


window.addEventListener("load", () => {
    setTimeout(() => {
        init();
    }, 2000);
})