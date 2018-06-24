function test( n::Int64 )
    total = 0

    for i in 1:n
        if i % 2 == 0
            total += 1
        end
    end

    return total
end

@time result = test( 10 )
println( result )

@time result = test( 1000000000 )
println( result )
