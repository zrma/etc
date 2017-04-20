-module(custom_lists).
-author("zrma").

%% API
-export([sum/1, map/2]).

sum([Head | Tails]) -> Head + sum(Tails);
sum([]) -> 0.

map(_, []) -> [];
%% map(Func, [Head | Tails]) -> [Func(Head) | map(Func, Tails)].
%% 리스트 해석(list comprehension)
map(Func, Lists) -> [Func(X) || X <- Lists].