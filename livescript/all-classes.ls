win = this
this.document.getAllClasses = !(blacklist = []) ->
  classes = []
  should-remove = []
  elements = document.getElementsByTagName?(\*) or document.all
  for e in elements
    for c in e.className.split ' '
      should-remove.push c if c in blacklist and not (c in should-remove)
      classes.push c if c.length > 0 and not (c in classes)
  alert JSON.stringify should-remove
  win.prompt "classes", JSON.stringify classes
