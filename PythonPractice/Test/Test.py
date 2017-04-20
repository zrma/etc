from patterns import patterns


@patterns
def quick_sort():
    if []: []
    if [ pivot ] + tails:
        quick_sort( [ x for x in tails if x < pivot ] ) \
        + [ pivot ] \
        + quick_sort( [ x for x in tails if x > pivot ] )


def main():
    print( quick_sort( [ 5, 3, 2, 1, 4, 6, 9, 10, 7 ] ) )


if __name__ == '__main__':
    main()
