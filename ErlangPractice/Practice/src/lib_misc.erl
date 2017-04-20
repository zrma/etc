-module(lib_misc).
-author("zrma").

%% API
-export([sum/1, sum/2, for/3, quick_sort/1, pythagoras/1, perms/1,
	odds_and_evens/1, odds_and_evens_acc/1, sqrt/1,
	sleep/1, flush_buffer/0, priority_receive/0]).

sum(L) -> sum(L, 0).

sum([], N) -> N;
sum([Head | Tails], N) -> sum(Tails, Head + N).

for(Max, Max, Func) -> [Func(Max)];
for(Idx, Max, Func) -> [Func(Idx) | for(Idx + 1, Max, Func)].

quick_sort([]) -> [];
quick_sort([Pivot | Tails]) ->
	quick_sort([X || X <- Tails, X < Pivot]) ++ [Pivot] ++ quick_sort([X || X <- Tails, X >= Pivot]).

pythagoras(N) ->
	[
		{A, B, C} || A <- lists:seq(1, N),
		B <- lists:seq(1, N),
		C <- lists:seq(1, N),
		A + B + C =< N,
		A * A + B * B =:= C * C
	].

perms([]) -> [[]];
perms(L) -> [[Head | Tails] || Head <- L, Tails <- perms(L -- [Head])].

odds_and_evens(L) ->
	Odds = [X || X <- L, (X rem 2) =:= 1],
	Evens = [X || X <- L, (X rem 2) =:= 0],
	{Odds, Evens}.

odds_and_evens_acc(L) ->
	odds_and_evens_acc(L, [], []).

odds_and_evens_acc([Head | Tails], Odds, Evens) ->
	case (Head rem 2) of
		1 -> odds_and_evens_acc(Tails, [Head | Odds], Evens);
		0 -> odds_and_evens_acc(Tails, Odds, [Head | Evens])
	end;
odds_and_evens_acc([], Odds, Evens) ->
	{lists:reverse(Odds), lists:reverse(Evens)}.

sqrt(X) when X < 0 ->
	erlang:error({sqeuareRootNagativeArgument, X});
sqrt(X) ->
	math:sqrt(X).

sleep(T) ->
	receive
	after T ->
		true
	end.

flush_buffer() ->
	receive
		_Any ->
			flush_buffer()
	after 0 ->
		true
	end.

priority_receive() ->
	receive
		{alarm, X} ->
			{alarm, X}
	after 0 ->
		receive
			Any ->
				Any
		end
	end.