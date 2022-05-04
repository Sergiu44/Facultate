function init() {
    let count = parseInt(localStorage.getItem("count")) || 0;
    count++;
    localStorage.setItem("count", count);
    let header = document.querySelector("h1");
    while(count-1) {
        header.textContent += "o";
        count--;
    } 
}

window.addEventListener('load', init)