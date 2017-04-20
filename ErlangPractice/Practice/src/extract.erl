-module(extract).
-author("zrma").

%% API
-export([attribute/2]).

attribute(File, Key) ->
	case beam_lib:chunks(File, [attributes]) of
		{ok, {_Module, [{attributes, L}]}} ->
			case lookup(Key, L) of
				{ok, Val} ->
					Val;
				error ->
					exit(badAttribute)
			end;
		_ ->
			exit(badFile)
	end.

lookup(Key, [{Key, Val} | _]) -> {ok, Val};
lookup(Key, [_ | Tails]) -> lookup(Key, Tails);
lookup(_, []) -> error.