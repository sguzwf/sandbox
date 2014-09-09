#!/bin/sh
# http://stackoverflow.com/questions/3497123/run-git-pull-over-all-subdirectories
find . -type d -maxdepth 1 -exec git --git-dir={}/.git --work-tree=$PWD/{} pull \;
