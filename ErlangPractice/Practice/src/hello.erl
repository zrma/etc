-module(hello).
-author("zrma").

%% API
-export([start/0]).

start() ->
	io:format("Hello World~n").