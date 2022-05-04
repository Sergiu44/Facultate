const elements = [...document.querySelectorAll("input")]
const times = [];

elements.forEach((element, index) => {
    const time = (times[index-1] || 0) + Math.random()*50+50;
    times[index] = time;
    setTimeout(() => {
        element.click()
    }, time);
});