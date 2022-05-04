const classes = ['c1', 'c2', 'c3', 'c4', 'c5'];

function randomPick(array) {
  const index = Math.floor(Math.random()*(array.length-1))
  return array[index];
}

function init() {
  const N = Math.max(10, new Date().getMinutes());
  for(let i=0; i<N; ++i) {
    const p = document.createElement("p");
    p.classList.add(randomPick(classes));
    p.innerHTML = "Sergiu-Nicolas";
    p.addEventListener("click", (e) => {
      e.stopPropagation();
      const clasa = e.target.className;
      Array.from(document.getElementsByClassName(clasa)).forEach(el => el.remove())
    })
  	document.body.append(p);
  }
  document.addEventListener("click", e => {
    alert(e.clientX);
  })
}


window.addEventListener("load", init);