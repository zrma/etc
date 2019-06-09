P = 40;  R = 50;  N = P*R;  r = 0:0.004:1
points = rand(ComplexF64, P, R)

mp4(@animate(for t = 0:0.03:13
    # create a simple classifier to return the region for any point (x, y)
    midpoints = vec(sum(points; dims=1)) / P
    classify(x, y) = argmin(abs.(x + y*im .- midpoints))

    # draw decision boundary and points
    contour(r, r, classify, c=:cyclic2, fill=true, nlev=R, leg=:none)
    scatter!(reim(points)..., c=cvec(:cyclic2, R)', lims=(0,1))

    # update position of points
    target(d) = 0.65*cis(4*sin(t/2+d)+d) + 0.5 + 0.5im
    points[:] .+= 0.01*(target.(0:2π/(N-1):2π) .- points[:])
end), "decision.mp4", fps = 30)
