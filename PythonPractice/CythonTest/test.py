# coding=utf-8

import pythran

%%pythran
def func():
    for i in range( 10000000 ):
        if i % 2 == 0:
            total += 1

    print( 'total : {}'.format( total ) )
