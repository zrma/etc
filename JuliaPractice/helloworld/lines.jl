using Plots
x = 1:10; y = rand(10); # These are the plotting data
plot(x,y)

x = 1:10; y = rand(10,2) # 2 columns means two lines
plot(x,y)

z = rand(10)
plot!(x,z)

x = 1:10; y = rand(10,2) # 2 columns means two lines
p = plot(x,y)
z = rand(10)
plot!(p,x,z)

x = 1:10; y = rand(10,2) # 2 columns means two lines
plot(x,y,title="Two Lines",label=["Line 1" "Line 2"],lw=3)

xlabel!("My x label")

x = 1:10; y = rand(10,2) # 2 columns means two lines
plotly() # Set the backend to Plotly
plot(x,y,title="This is Plotted using Plotly") # This plots into the web browser via Plotly
gr() # Set the backend to GR
plot(x,y,title="This is Plotted using GR") # This plots using GR

savefig("myplot.png") # Saves the CURRENT_PLOT as a .png
savefig(p,"myplot.pdf") # Saves the plot from p as a .pdf vector graphic

gr() # We will continue onward using the GR backend
plot(x,y,seriestype=:scatter,title="My Scatter Plot")

scatter(x,y,title="My Scatter Plot")

display(plot(x,y))

y = rand(10,4)
plot(x,y,layout=(4,1))

p1 = plot(x,y) # Make a line plot
p2 = scatter(x,y) # Make a scatter plot
p3 = plot(x,y,xlabel="This one is labelled",lw=3,title="Subtitle")
p4 = histogram(x,y) # Four histograms each with 10 points? Why not!
plot(p1,p2,p3,p4,layout=(2,2),legend=false)


# Pkg.add("StatsPlots")
using StatsPlots # Required for the DataFrame user recipe
# Now let's create the DataFrame
using DataFrames
df = DataFrame(a = 1:10, b = 10*rand(10), c = 10 * rand(10))
# Plot the DataFrame by declaring the points by the column names
@df df plot(:a, [:b :c]) # x = :a, y = [:b :c]. Notice this is two columns!

@df df scatter(:a, :b, title="My DataFrame Scatter Plot!") # x = :a, y = :b


using Distributions
plot(Normal(3,5),lw=3)


#Pkg.add("RDatasets")
using RDatasets
iris = dataset("datasets","iris")

@df iris marginalhist(:PetalLength, :PetalWidth)

y = rand(100,4) # Four series of 100 points each
violin(["Series 1" "Series 2" "Series 3" "Series 4"],y,leg=false)

boxplot!(["Series 1" "Series 2" "Series 3" "Series 4"],y,leg=false)
