-module(processes).
-author("zrma").

%% API
-export([process_test/1]).

%% process_test(N)
%% 프로세스를 N개 생성하고 곧바로 제거한다
%% 시간이 얼마나 걸리는지 측정한다

process_test(N) ->
	Max = erlang:system_info(process_limit),
	io:format("Maximum allowed processes : ~p~n", [Max]),
	statistics(runtime),
	statistics(wall_clock),
	L = for(1, N, fun() -> spawn(fun() -> wait() end) end),
	{_, Time1} = statistics(runtime),
	{_, Time2} = statistics(wall_clock),
	lists:foreach(fun(Pid) -> Pid ! die end, L),
	U1 = Time1 * 1000 / N,
	U2 = Time2 * 1000 / N,
	io:format("Process spawn time = ~p (~p) microseconds~n", [U1, U2]),
	io:format("Totally spent time = ~p (~p) milliseconds~n", [Time1, Time2]).

wait() ->
	receive
		die -> void
	end.

for(N, N, F) -> [F()];
for(I, N, F) -> [F() | for(I + 1, N, F)].
