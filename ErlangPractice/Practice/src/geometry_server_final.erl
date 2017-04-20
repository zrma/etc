-module(geometry_server_final).
-author("zrma").

%% API
-export([start/0, area/2]).

start() -> spawn(fun loop/0).

area(Pid, Request) ->
	rpc(Pid, Request).

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
