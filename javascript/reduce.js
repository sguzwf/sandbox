[0, 1, 2, 3, 4, 5, 6].reduce(function(prev, current) {
  console.log(prev);
  console.log(current);
  console.log("===");
  return current;
});

words.reverse().reduce(function(next, current) {
  return function() {
    current.draw.then next
  };
});

word[0].draw().then(function() {
  word[1].draw().then(function() {
    word[2].draw();
  })
});
