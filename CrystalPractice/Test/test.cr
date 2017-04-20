total = 0

(1..10000000).each do |i|
    if i % 2 == 0
        total += 1
    end
end

puts "total : #{total}"
