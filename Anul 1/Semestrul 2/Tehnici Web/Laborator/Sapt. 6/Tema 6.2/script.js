let toggle = true;

function handleKeyDown(event) {
    if(!toggle) return;
    const box = document.querySelector(".box");
    const top = parseInt(getComputedStyle(box).top);
    const left = parseInt(getComputedStyle(box).left);

    switch (event.key) {
        case "ArrowUp":
            box.style.top = top - 10 + "px";        
            break;
    
        case "ArrowDown":
            box.style.top = top + 10 + "px";
            break;
        
        case "ArrowLeft":
            box.style.left = left - 10 + "px";
            break;

        case "ArrowRight":
            box.style.left = left + 10 + "px";
            break;
        
        default:
            break;
    }
}

function init() {
    document.addEventListener("keydown", handleKeyDown);
    const box = document.querySelector('.box');
    box.addEventListener('click', () => { toggle = !toggle})
}

window.onload = init;