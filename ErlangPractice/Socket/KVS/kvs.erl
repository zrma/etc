-module(kvs).
-export([start/0, store/2, lookup/1]).

start() -> register(kvs, spawn(fun() -> loop() end)).

store(Key, Value) -> rpc({store, Key, Value}).

lookup(Key) -> rpc({lookup, Key}).

rpc(Query) ->
	% start에서 register(등록)한 kvs 프로세스에 메세지를 전달한다
	kvs ! {self(), Query},

	% 메세지 수신 대기
	receive
		{ kvs, Reply } -> Reply
	end.

% start에서 등록한 kvs 프로세스의 무한 루프 로직
loop() ->
	% 메세지 수신 대기
	receive

		% 저장 메세지
		{From, {store, Key, Value}} ->

			% 저장 하고
			put(Key, {ok, Value}),

			% 저장 결과를 회신
			From ! {kvs, true},

			% 꼬리 재귀
			loop();

		% 검색 메세지
		{From, {lookup, Key}} ->

			% 검색 결과를 회신
			From ! {kvs, get(Key)},

			% 꼬리 재귀
			loop()
	end.
