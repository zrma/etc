concat( [], List, List ).
concat( [ Head | Tails1 ], List, [ Head | Tails2 ] ) :- concat( Tails1, List, Tails2 ).
