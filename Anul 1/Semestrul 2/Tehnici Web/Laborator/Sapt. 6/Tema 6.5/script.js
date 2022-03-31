window.addEventListener("load", (event) => {
    document.getElementById("form").addEventListener("submit", (ev) => {
        ev.preventDefault();
        const input = document.createElement("input");
        const form = document.getElementById("form");
        input.type = "text";
        input.addEventListener("keyup", e => {
            // Verificam daca valoarea inputului este compatibila pentru o culoare de tip hex
            const culoare = input.value;
            console.log(culoare);
            const verifyRegexColor = new RegExp('#((\\d|[a-f]|[A-F]){3}|(\\d|[a-f]|[A-F]){6})');
            if(verifyRegexColor.test(culoare) && (culoare.length === 4 || culoare.length === 7)) {
                input.style.backgroundColor = culoare;
            } else {
                input.style.backgroundColor = "";
            }
        })
        form.appendChild(input);
    })
})