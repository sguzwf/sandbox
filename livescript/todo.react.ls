converter = new Showdown.converter

MarkdownEditor = React.createClass do
  displayName: \MarkdownEditor
  getInitialState: ->
    value: 'Type some *markdown* here!'
  handleChange: !->
    @setState value: @refs.textarea.getDOMNode!value
  render: ->
    React.DOM.div do
      className: \MarkdownEditor
      React.DOM.h3 null, \Input
      React.DOM.textarea do
        onChange: @handleChange
        ref: \textarea
        defaultValue: @state.value
      React.DOM.h3 null, \Output
      React.DOM.div do
        className: \content
        dangerouslySetInnerHTML:
          __html: converter.makeHtml @state.value

React.renderComponent MarkdownEditor!, mountNode

