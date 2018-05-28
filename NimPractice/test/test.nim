var total = 0

for i in 0..9999999:
    if i mod 2 == 0:
        total += 1

echo( "total : ", total )

proc pr() =
    echo  "Hello World"
pr()