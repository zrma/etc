var total = 0

for i in 0..9999999:
    if i mod 2 == 0:
        total += 1

proc pr() =
    echo  "aaa"

echo( "total : ", total )
pr()