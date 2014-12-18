this.classes = (...excluded) ->
  cs = {}
  for e in document.getElementsByTagName?('*') or document.all
    for c in e.className.split ' ' when c.length
      cs[c] = true unless c in excluded
  Object.keys cs .sort!
