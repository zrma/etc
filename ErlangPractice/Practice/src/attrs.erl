-module(attrs).
-vsn(1).
-author("zrma").
-purpose("example of attributes").

%% API
-export([fac/1]).

fac(1) -> 1;
fac(N) -> N * fac(N - 1).
