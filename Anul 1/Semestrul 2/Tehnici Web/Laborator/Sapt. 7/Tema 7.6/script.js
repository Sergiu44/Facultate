// function getData() {
//   fetch("https://pokeapi.co/api/v2/pokemon", {
//     method: "GET",
//     headers: {
//       "Content-Type": "application/json",
//     },
//   })
//     .then((response) => response.json())
//     .then((data) => {
//       data.results.map((element, index) => {
//         fetch(`https://pokeapi.co/api/v2/pokemon/${index + 1}`, {
//           method: "GET",
//           headers: {
//             "Content-Type": "application/json",
//           },
//         })
//           .then((response) => response.json())
//           .then((data) => {
//             const card = document.createElement("div");
//             card.classList.add("card");

//             const header = document.createElement("h2");
//             header.classList.add("header");
//             header.textContent = element.name;

//             const listMoves = document.createElement("ul");
//             listMoves.classList.add("list");
//             data.moves.map((move) => {
//               const moveElement = document.createElement("li");
//               moveElement.innerHTML = move.move.name;
//               moveElement.classList.add("listElement");

//               listMoves.appendChild(moveElement);
//             });

//             card.appendChild(header);
//             card.appendChild(listMoves);
//             const section = document.getElementsByTagName('section')[0];
//             section.appendChild(card);
//           });
//       });
//     });
// }

// window.addEventListener("load", getData);


function getData(){
  fetch("https://api.jokes.one", {
      method:"GET",
      headers: {
          "Content-Type": "application/json",
        },
  })
  .then((response)=>response.json())
  .then((data)=>{
      console.log(data);
  })
}
window.addEventListener("load",getData);