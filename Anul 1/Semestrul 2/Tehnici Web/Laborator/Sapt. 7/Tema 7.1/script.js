function init() {
    let elements = [];
    for(let i=0; i<15; ++i) {
        const element = document.createElement('div');
        element.textContent = i+1;
        element.style.position = 'fixed';
        element.style.top = Math.random()*window.innerHeight - 50 + "px";
        element.style.left = Math.random()*window.innerWidth - 50 + "px";
        element.style.width = "50px";
        element.style.height = "50px";
        element.style.border = "1px solid black";
        elements.push(element);
    }

    for(let i=0; i<15; ++i) {
        let timeout = 2000* Math.floor(i/3);
        setTimeout(() => {
            document.body.append(elements[i])
        }, timeout)
    }
    
    let i=0;
    let int = setInterval(() => {
        elements.slice(i, i+3).forEach(element => {
            document.body.append(element);
        })
        i=i+3;
        if(i>=15) {
            clearInterval(int);
        }
    }, 2000);
}


window.addEventListener("load", init);

