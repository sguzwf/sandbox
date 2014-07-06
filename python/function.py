#!/usr/bin/python

def foo(x=0, y=0):
    "Amazing pydoc!"
    t = (x, y)
    print "foo called with parameter: %s, %s" % t

d = {
    "foo": foo,
    "bar": lambda: foo(1, 2),
}

foo()
d["foo"]()
d["bar"]()
foo(1)
foo(y=2)
