# coding=utf-8

total = 0
for i in range( 10000000 ):
    if i % 2 == 0:
        total += 1

print( 'total : {}'.format( total ) )
