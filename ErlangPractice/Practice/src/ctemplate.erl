%% 병행 프로그래밍 템플릿

-module(ctemplate).
-compile(export_all).
-author("zrma").

start() ->
	spawn(fun() -> loop([]) end).

rpc(Pid, Request) ->
	Pid ! {self(), Request},
	receive
		{Pid, Response} ->
			Response
	end.

loop(X) ->
	receive
		Any ->
			io:format("Received:~p~n", [Any]),
			loop(X)
	end.