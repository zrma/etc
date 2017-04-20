-module(shop_calc).
-author("zrma").

%% API
-export([total/1]).

total([{Goods, Count} | Tail]) -> shop:cost(Goods) * Count + total(Tail);
total([]) -> 0.
