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

datas = [3, 2, 9, 1, 5, 4, 7]
println( datas )
@time result = quick_sort( datas )
@time result = quick_sort( datas )
println( result )
