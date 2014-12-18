{ div, h3, textarea } = React.DOM

converter = new Showdown.converter

MarkdownEditor = React.createClass do
  displayName: \MarkdownEditor
  getInitialState: ->
    value: 'Type some *markdown* here!'
  handleChange: !->
    @setState value: @refs.textarea.getDOMNode!value
  render: ->
    div do
      className: \MarkdownEditor
      h3 {} \Input
      textarea do
        onChange: @handleChange
        ref: \textarea
        defaultValue: @state.value
      h3 {} \Output
      div do
        className: \content
        dangerouslySetInnerHTML:
          __html: converter.makeHtml @state.value
MarkdownEditor = React.createFactory MarkdownEditor

React.render MarkdownEditor!, mountNode

