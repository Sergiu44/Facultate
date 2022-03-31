window.addEventListener("load", event => {
    const form = document.getElementById("math");
    form.addEventListener("submit", (ev) => {
        ev.preventDefault();
        let result = 0;
        let tipulOperatiei;

        /// Form elements with whom we will work
        const number1 = document.getElementById("number1");
        const number2 = document.getElementById("number2");
        const operator = document.getElementById("operator");

        // The 2 values from inputs
        const n1 = parseInt(number1.value);
        const n2 = parseInt(number2.value);

        if(isNaN(n1) || isNaN(n2)) {
            alert("Nu ati introdus datele cum trebuie sau nu ati introdus deloc date!");
            return;
        }

        switch (operator.options[operator.selectedIndex].value) {
            case "add": {
                result = n1 + n2;
                tipulOperatiei = "(Adunare)";
                break;
            }
            case "subtract": {
                result = n1 - n2;
                tipulOperatiei = "(Scadere)";
                break;
            }
            case "multiply": {
                result = n1 * n2;
                tipulOperatiei = "(Inmultire)";
                break;
            }
            case "divide": {
                result = n1 / n2;
                tipulOperatiei = "(Impartire)";
                break;
            }
            case "pow": {
                result = n1**n2;
                tipulOperatiei = "(Ridicare la putere)";
                break;
            }
            default: return;
        }


        const resultElement = document.getElementById("result");
        resultElement.innerHTML = result.toString() + " " + tipulOperatiei;

        number1.value = '';
        number2.value = '';
        operator.selectedIndex = 0;
    })
})

