import time
from multiprocessing import Pool


def test( idx ):
    time.sleep( 0.1 )
    print( f'>>> {idx}' )


def main():
    with Pool( processes = 8 ) as pool:
        pool.map( test, range( 100 ) )


if __name__ == '__main__':
    main()
