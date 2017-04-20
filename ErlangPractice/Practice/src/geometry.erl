-module(geometry).
-author("zrma").

%% API
-export([area/1]).

area({rectangle, Width, Height}) -> Width * Height;
area({circle, Radius}) -> Radius * Radius * 3.14159265427.