-module(records).
-author("zrma").

%% API
-record(todo, {status = reminder, name = zrma, text}).