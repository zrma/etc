using Plots; gr()

# 10 data points in 4 series
xs = 0 : 2π/10 : 2π
data = [sin.(xs) cos.(xs) 2sin.(xs) 2cos.(xs)]

# We put labels in a row vector: applies to each series
labels = ["Apples" "Oranges" "Hats" "Shoes"]

# Marker shapes in a column vector: applies to data points
markershapes = [:circle, :star5]

# Marker colors in a matrix: applies to series and data points
markercolors = [:green :orange :black :purple
                :red   :yellow :brown :white]

plot(xs, data, label = labels, shape = markershapes, color = markercolors,
     markersize = 10)



# using Plots; plotly()

function rectangle_from_coords(xb,yb,xt,yt)
 [
     xb yb
     xt yb
     xt yt
     xb yt
     xb yb
     NaN NaN
 ]
end

some_rects=[
 rectangle_from_coords(1 ,1 ,5 ,5 )
 rectangle_from_coords(10,10,15,15)
 ]
other_rects=[
 rectangle_from_coords(1 ,10,5 ,15)
 rectangle_from_coords(10,1 ,15,5 )
 ]

plot(some_rects[:,1], some_rects[:,2],label="some group")
plot!(other_rects[:,1], other_rects[:,2],label="other group")



using StatsPlots, RDatasets
iris = dataset("datasets", "iris")
@df iris scatter(:SepalLength, :SepalWidth, group=:Species,
        m=(0.5, [:+ :h :star7], 12), bg=RGB(.2,.2,.2))



using Plots
tmin = 0
tmax = 4π
tvec = range(tmin, stop=tmax, length=100)

plot(sin.(tvec), cos.(tvec))
plot(sin, cos, tvec)
plot(sin, cos, tmin, tmax)



using Plots,Images
img = load("image.png")
plot(img)
