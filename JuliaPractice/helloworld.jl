using Match

function qsort( list::Array{Int64,1} )
  @match list begin
    [] => []
    [ pivot, tails... ] => vcat(
      qsort( [ x for x in tails if x < pivot ] ),
      pivot,
      qsort( [ x for x in tails if x > pivot ] ) )
  end
end

datas = [3, 2, 9, 1, 5, 4]
println( datas )
@time result = qsort( datas )
println( result )
