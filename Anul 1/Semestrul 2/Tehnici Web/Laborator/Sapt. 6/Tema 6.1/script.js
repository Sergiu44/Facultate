function init() {
    for(let i=0; i<=9; ++i) {
        const div = document.createElement('div');
        div.innerHTML = i;
        div.id = i;
        div.className = 'box';
        document.body.appendChild(div);
    }
    document.addEventListener('keydown', handleKeyDown);
    document.addEventListener('keyup', handleKeyUp);
}

window.onload = init;


function handleKeyDown (event) {
    if(parseInt(event.key) == NaN) 
        return;
    const selectedDiv = document.getElementById(event.key);
    selectedDiv.classList.add('pressed');
}

function handleKeyUp (event) {
    if(parseInt(event.key) == NaN) 
        return;
    const selectedDiv = document.getElementById(event.key);
    selectedDiv.classList.remove('pressed');
}