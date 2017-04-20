# coding=utf-8

def func():
    cdef:
        int total = 0
        int i

    for i in range( 10000000 ):
        if i % 2 == 0:
            total += 1

    print( 'total : {}'.format( total ) )
