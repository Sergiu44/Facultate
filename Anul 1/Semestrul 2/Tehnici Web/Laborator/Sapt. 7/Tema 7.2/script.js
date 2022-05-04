function init() {
  const items = [...document.querySelectorAll("li")];
  items.forEach((item) => {
    item.dataset.text = item.textContent;
  });

  let i = 0;
  const int = setInterval(() => {
    let img = document.createElement('img');
    img.src = items[i].textContent;
    items[i].innerHTML = "";
    items[i].append(img);
    items.at(i-1).innerHTML = items.at(i).dataset.text;
   i=(i+1)%items.length;
  }, 3000);
}

window.addEventListener("load", init);
