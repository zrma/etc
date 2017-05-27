import concurrent.futures
import math


PRIMES = [
    112272535095293,
    112582705942171,
    112272535095293,
    115280095190773,
    115797848077099,
    1099726899285419]


def is_prime(n):
    if n % 2 == 0:
        print('False')
        # return False

    sqrt_n = int(math.floor(math.sqrt(n)))
    for i in range(3, sqrt_n + 1, 2):
        if n % i == 0:
            print('False')
            return
    print('True')
    return


def main():
    with concurrent.futures.ProcessPoolExecutor(max_workers = 8) as excutor:

        for number in PRIMES:
            excutor.submit(is_prime, number)


if __name__ == '__main__':
    main()
