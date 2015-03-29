var CartActions = require('../actions/CartActions');

CartActions.add({ id: 'foobar '});

function remove(o) {
  CartActions.remove(o);
}

remove({ id: 'foobar' });

