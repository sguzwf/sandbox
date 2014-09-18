#!/usr/bin/env lsc
require! fs
prevs =
  1: [[1 9] [2 8] [3 7] [4 6]]
  2: [[2 9] [3 8] [4 7] [5 6]]
  3: [[3 9] [4 8] [5 7] [2 1]]
  4: [[4 9] [5 8] [6 7] [3 1]]
  5: [[5 9] [6 8] [3 2] [4 1]]
  6: [[6 9] [7 8] [4 2] [5 1]]
  7: [[7 9] [4 3] [5 2] [6 1]]
  8: [[8 9] [5 3] [6 2] [7 1]]
  9: [[5 4] [6 3] [7 2] [8 1]]
todos =
  * [[1 2 3 4 5 6 7 8 9 1] [0 0 1 2 3 4 5 6 7 8] []]
  * [[1 2 3 4 5 6 7 8 9 2] [0 0 1 2 3 4 5 6 7 8] []]
  * [[1 2 3 4 5 6 7 8 9 3] [0 0 1 2 3 4 5 6 7 8] []]
  * [[1 2 3 4 5 6 7 8 9 2] [0 0 1 2 3 4 5 6 7 8] []]
  * [[1 2 3 4 5 6 7 8 9 5] [0 0 1 2 3 4 5 6 7 8] []]
  * [[1 2 3 4 5 6 7 8 9 6] [0 0 1 2 3 4 5 6 7 8] []]
  * [[1 2 3 4 5 6 7 8 9 7] [0 0 1 2 3 4 5 6 7 8] []]
  * [[1 2 3 4 5 6 7 8 9 8] [0 0 1 2 3 4 5 6 7 8] []]
  * [[1 2 3 4 5 6 7 8 9 9] [0 0 1 2 3 4 5 6 7 8] []]
solved = {}
depth = 0

while todos.length isnt 0
  todos-next = []
  for [board, pos, ans] in todos
    prev = board.pop!
    console.log "#{board.join ''}, #prev#{ans.join ''}"
    for [p, q] in prevs[prev]
      pos-new = Array::slice.call pos
      i = pos[p]
      j = pos[q]
      pos-new[p] = j
      pos-new[q] = i
      board-new = Array::slice.call board
      board-new[i] = q
      board-new[j] = p
      board-new.push p
      ans-new = [q]concat ans
      id = board-new.join ''
      if solved[id] is undefined
        solved[id] = ans-new
        todos-next.push [board-new, pos-new, ans-new]
      board-new = Array::slice.call board
      board-new[i] = q
      board-new[j] = p
      board-new.push q
      ans-new = [p]concat ans
      id = board-new.join ''
      if solved[id] is undefined
        solved[id] = ans-new
        todos-next.push [board-new, pos-new, ans-new]
  todos = todos-next
  ++depth
#fs.writeFile './one-nine.json', JSON.stringify(solved, null, 2)
