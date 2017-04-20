-module(shop_calc_by_lists).
-author("zrma").

%% API
-export([total/1]).
-import(lists, [map/2, sum/1]).

total(L) -> sum(map(fun({Goods, Count}) -> shop:cost(Goods) * Count end, L)).