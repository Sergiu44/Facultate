let persoane = [];
function citire() {
  let nume = prompt("Introduceti nume: ");
  let cnp = prompt("Introduceti CNP(incepe cu 1|2|5|6 si contine 11 caractere in total): ");
  let dataNasterii = prompt("Introduceti data nasterii(format: DD/MM/YYYY): ");

  var pers={
    nume:nume,
    cnp:cnp,
    dataNasterii:dataNasterii
  };

  // Regex validation
  const dataFormatata = new RegExp(
    /^(3[01]|[12][0-9]|0[1-9])[/](1[0-2]|0[1-9])[/][0-9]{4}$/
  );
  if (dataFormatata.test(dataNasterii)){
    window.alert("Data valida !");
    const cnpFormatat = new RegExp(
      /^([0-9][0-9](1[0-2]|0[1-9])(3[01]|[12][0-9]|0[1-9])[0-9]{6})$/
    );
    if (cnpFormatat.test(cnpFormatat)) {
      window.alert("Cnp valid !");
      persoane.push(pers);
      const informatii = formatare(pers);
      console.log(informatii);
    
      let listaOrdonata = document.getElementById('lista');
      let listItem = document.createElement('li');
      listItem.appendChild(document.createTextNode(informatii));
      listaOrdonata.appendChild(listItem);
    }
    else window.alert("Cnp invalid!");
  }
   else 
    window.alert("Data invalida ");

}

function formatare(persoana) {
  let infoPers = `${persoana.nume} este nascuta pe data de ${persoana.dataNasterii} si are CNP-ul ${persoana.cnp}`;
  return infoPers;
}