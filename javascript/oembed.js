var oembed = require("oembed");

oembed.fetch("http://localhost:15000/channel/830033/2013-10-18/3", {}, function(err, result) {
  if (err)
    console.log(err);
  else
    console.log(result);
});
