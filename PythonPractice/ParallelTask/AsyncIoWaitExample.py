import asyncio
import concurrent.futures
import random


async def test( idx ):
    r = random.random()
    await asyncio.sleep( r )
    print( f'>>> {idx} : {r}' )


def main():
    with concurrent.futures.ThreadPoolExecutor( max_workers = 8 ) as excutor:
        loop = asyncio.get_event_loop()
        loop.set_default_executor( executor = excutor )

        tasks = [ asyncio.ensure_future( test( x ) ) for x in range( 100 ) ]

        loop.run_until_complete( asyncio.wait( tasks ) )


if __name__ == '__main__':
    main()
