r3 = require("node-libr3");

n = new r3.Tree(10);
route_data = 3;

n.insert("/zoo", route_data);
n.insert("/foo/bar", route_data);
n.insert("/post/{id}", route_data);
n.insert("/user/{id:\\d+}", route_data);
//n.insert("/foo/bar", route_data);

n.compile();

//should be 3
console.log(n.match("/foo/bar"));

n = new r3.Tree(10);

n.insertRoute(r3.METHOD_GET | r3.METHOD_POST, "/blog/post", route_data);
n.compile();

e = new r3.MatchEntry("/blog/post");
//e.requestMethod is r3.METHOD_GET by default
e.requestMethod = r3.METHOD_GET;

//should be 3
console.log(n.matchRoute(e));

