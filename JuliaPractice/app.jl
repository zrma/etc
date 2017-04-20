using HttpServer

uuid = Base.Random.uuid1()

http = HttpHandler() do req::Request, res::Response
    Response( ismatch(r"/", req.resource) ?
    string("Dockerized with julia - ", uuid ) : 404 )
end

server = Server( http )
run(server, host=IPv4(0,0,0,0), port=8888)
