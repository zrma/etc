-module(chat_client).

-import(io_widget,
[get_state/1, insert_str/2, set_prompt/2, set_state/2, set_title/2, set_handler/2, update_state/3]).

-export([start/0, test/0, connect/5]).

start() ->
	connect("localhost", 2223, "asDT67aQ", "general", "joe").

test() ->
	connect("localhost", 2223, "asDT67aQ", "general", "joe"),
	connect("localhost", 2223, "asDT67aQ", "general", "jane"),
	connect("localhost", 2223, "asDT67aQ", "general", "jim"),
	connect("localhost", 2223, "asDT67aQ", "general", "sue").

connect(Host, Port, HostPasswd, Group, Nick) ->
	process_flag(trap_exit, true),
	Widget = io_widget:start(self()),
	set_title(Widget, Nick),
	set_state(Widget, Nick),
	set_prompt(Widget, [Nick, " > "]),
	set_handler(Widget, fun parse_command/1),
	start_connector(Host, Port, HostPasswd),
	disconnected(Widget, Group, Nick).

disconnected(Widget, Group, Nick) ->
	receive

	% 접속 성공
		{connected, MM} ->
			insert_str(Widget, "connected to server \nsending data \n"),

			% 로그인 시도
			MM ! {login, Group, Nick},

			% 로그인 응답 대기기
			wait_login_response(Widget, MM);

	% 위젯 소멸 시 프로세스 종료
		{Widget, destroyed} ->
			exit(died);

	% 허트 비트 출력
		{status, S} ->
			insert_str(Widget, to_str(S)),
			disconnected(Widget, Group, Nick);

		Other ->
			io:format("chat_client disconnected unexpected:~p~n", [Other]),
			disconnected(Widget, Group, Nick)
	end.

wait_login_response(Widget, MM) ->
	receive
	% 로그인 성공에 따른 위젯 활성화
		{MM, ack} ->
			active(Widget, MM);

		Other ->
			io:format("chat_client login unexpected:~p~n", [Other]),
			wait_login_response(Widget, MM)
	end.

active(Widget, MM) ->
	receive

	% 위젯 입력을 받아서 전달
		{Widget, Nick, Str} ->
			MM ! {relay, Nick, Str},

			% 테일 리커시브
			ctive(Widget, MM);


	% 메세지를 받음
		{MM, {msg, From, Pid, Str}} ->

			% 받은 메세지를 위젯에 출력
			insert_str(Widget, [From, "@", pid_to_list(Pid), " ", Str, " \n"]),
			active(Widget, MM);

	% 위젯 소멸 시 접속 종료 메세지 보내기
		{'EXIT', Widget, windowDestroyed} ->
			MM ! close;

	% 접속 종료시 처리
		{close, MM} ->
			exit(serverDied);

		Other ->
			io:format("chat_client active unexpected:~p~n", [Other]),
			active(Widget, MM)
	end.

start_connector(Host, Port, Passwd) ->
	S = self(),
	spawn_link(fun() -> try_to_connect(S, Host, Port, Passwd) end).

try_to_connect(Parent, Host, Port, Passwd) ->
	% Parent는 이 프로세스를 띄운 프로세스의 Pid
	case lib_chan:connect(Host, Port, chat, Passwd, []) of

		% 접속 실패하면 2초간 기다리고 재접속 시도
		{error, _Why} ->
			Parent ! {status, {cannot, connect, Host, Port}},
			sleep(2000),
			try_to_connect(Parent, Host, Port, Passwd);

		% 접속 성공하면 성공한 메세지와 응답 받은 MM(Middle Man)을 부모에게 전달
		{ok, MM} ->
			lib_chan_mm:controller(MM, Parent),
			Parent ! {connected, MM},
			exit(connectorFinished)
	end.

sleep(T) ->
	receive
	after T -> true
	end.

to_str(Term) ->
	io_lib:format("~p~n", [Term]).

parse_command(Str) -> skip_to_gt(Str).

skip_to_gt(">" ++ T) -> T;
skip_to_gt([_ | T]) -> skip_to_gt(T);
skip_to_gt([]) -> exit("no >").