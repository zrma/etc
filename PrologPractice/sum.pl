sum( 0, [] ).
sum( Total, [ Head | Tails ] ) :- sum( Sum, Tails ), Total is Head + Sum.
