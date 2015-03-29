var CartActions = require('../actions/CartActions'), LogActions$ = require('../actions/LogActions$');
CartActions.add({ id: 'foobar ' });
LogActions$.add({ id: 'foobar ' });
function remove(o) {
    CartActions.remove(o);
    LogActions$.remove(o);
}
remove({ id: 'foobar' });
