-module(geometry_server2).
-author("zrma").

%% API
-export([loop/0, rpc/2]).

rpc(Pid, Request) ->
	Pid ! {self(), Request},
	receive
		{Pid, Response} ->
			Response
	end.

loop() ->
	receive
		{From, {rectangle, Width, Height}} ->
			From ! {self(), Width * Height},
			loop();
		{From, {circle, Radius}} ->
			From ! {self(), 3.141592654 * Radius * Radius},
			loop();
		{From, Other} ->
			From ! {self(), {error, Other}},
			loop()
	end.
