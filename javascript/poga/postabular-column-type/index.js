"use strict"

let postabular = require("postabular")
let _ = require("lodash")
let moment = require("moment")

// XXX: why mixed " with ' ?
module.exports = postabular.plugin('column-type', function(tabular, result) {
    let derived = {}
    // initialized derived table
    tabular.echoColumn((col, colIdx) => { derived[colIdx] = {boolean: 0, datetime: 0, number: 0, text: 0, time: 0, date: 0} })

    tabular.echoColumn((col, colIdx) => {
        col.eachCell((cell, rowIdx) => {
            if (moment(cell.value, moment.ISO_8601, true).isValid()) {
                derived[colIdx]["datetime"] += 1
            } else if (moment(cell.value, 'YYYY-MM-DD', true).isValid()) {
                derived[colIdx]["date"] += 1
            } else if (moment(cell.value, 'HH:mm:ss', true).isValid()) {
                derived[colIdx]["time"] += 1
            } else if (!isNaN(cell.value)) { // XXX: I'd remember that `isNaN` is not reliable
                derived[colIdx]["number"] += 1
            } else if (cell.value === "true" || cell.value === "false") {
                derived[colIdx]["boolean"] += 1
            } else {
                derived[colIdx]["text"] += 1
            }
        })
        // XXX: I may abuse arrow functions: `sortBy(keys.map(t => [t, derived[colIdx][t]]), x => -1*x[1])`
        //                                                           tuple: (type,          typeCount)                        DESC
        let result = _.sortBy(Object.keys(derived[colIdx]).map((t) => { return [t, derived[colIdx][t]] }), (x) => { return -1*x[1] })
        // XXX: abuse the destructuring assignment: `let [[t,],] = ...`
        //                            type with the max count
        tabular.setMeta(`column_type_${colIdx}`, result[0][0])
    })
})
