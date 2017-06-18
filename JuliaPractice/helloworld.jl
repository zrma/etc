total = 0

for i in 1:10000000
    if i % 2 == 0
        total += 1
    end
end

println( "total : ", total )

