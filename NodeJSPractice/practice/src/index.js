'using strict';

const _ = require( 'underscore' );


(function start() {
    let total = 0;

    _.times( 10000000, function( idx ) {
        if( idx % 2 == 0 ) {
            ++total;
        }
    } );

    console.log( 'total : ' + total );
})();