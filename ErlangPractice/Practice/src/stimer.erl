-module(stimer).
-author("zrma").

%% API
-export([start/2, cancel/1]).

start(Time, Fun) -> spawn(fun() -> timer(Time, Fun) end).

cancel(Pid) -> Pid ! cancel.

timer(Time, Fun) ->
	receive
		cancel ->
			void
	after Time ->
		Fun()
	end.