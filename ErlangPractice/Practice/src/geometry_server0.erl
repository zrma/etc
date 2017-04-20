-module(geometry_server0).
-author("zrma").

%% API
-export([loop/0]).

loop() ->
	receive
		{rectangle, Width, Height} ->
			io:format("Area of Rectangle is ~p~n", [Width * Height]),
			loop();
		{circle, Radius} ->
			io:format("Area of Circle is ~p~n", [3.141592654 * Radius * Radius]),
			loop();
		Other ->
			io:format("I don't know what the area of a ~p is ~n", [Other]),
			loop()
	end.
