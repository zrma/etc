using HTTP;
using UUIDs;
using Random;

rng = MersenneTwister(1234);
uuid = uuid4(rng);

HTTP.serve() do request::HTTP.Request
   @show request
   @show request.method
   @show HTTP.header(request, "Content-Type")
   @show HTTP.payload(request)
   try
       return HTTP.Response(string(uuid))
   catch e
       return HTTP.Response(404, "Error: $e")
   end
end
