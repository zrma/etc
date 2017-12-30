using Match

function quick_sort( list::Array{Int64,1} )
  @match list begin
    [] => []
    [ pivot, tails... ] => vcat(
      quick_sort( [ x for x in tails if x < pivot ]::Array{Int64, 1} ),
      pivot,
      quick_sort( [ x for x in tails if x > pivot ]::Array{Int64, 1} ) )
  end
end

datas = [3, 2, 1]
@time result = quick_sort( datas )
println( datas )
datas = unique([rand(1:1000) for r in 1:1000])
@time result = quick_sort( datas )
