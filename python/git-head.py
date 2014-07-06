#!/usr/bin/python

from git import *

repo = Repo("../")
origin = repo.remotes.origin
print origin.refs.master.commit

print origin.refs
