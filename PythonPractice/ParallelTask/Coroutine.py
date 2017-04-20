import asyncio
import concurrent.futures
import logging


clients = {}


def AcceptClient(reader, writer):
    ''' 서버 소켓에 접속 될 때마다 이 함수를 콜백 호출 '''

    # 1) - 클라이언트 핸들러 Task 등록
    task = asyncio.Task(HandleClient(reader, writer))
    clients[task] = (reader, writer)


    def releaseClient(task):
        ''' 2)에서 등록한 콜백 '''
        clients.pop(task)
        writer.close()
        log.info("End Connection")


    log.info("New Connection")

    # 2) - 1)에서 등록한 클라이언트 핸들러의 Task가 완료 되면 처리할 콜백 등록
    task.add_done_callback(releaseClient)


async def HandleClient(reader, writer):
    ''' 클라이언트 핸들러 '''

    ################################################################################
    # 간단한 handshake
    #
    writer.write("Hello\n".encode())

    data = await asyncio.wait_for(reader.readline(), timeout = 10.0)
    if data is None:
        log.warning("Expected World, received None")
        return

    sdata = data.decode().rstrip()
    log.info("Received %s", sdata)
    if sdata != "World":
        log.warning("Expected World, received '%s'", sdata)
        return
    #
    # 여기까지
    ################################################################################

    i = 0
    writer.write("Ready\n".encode())

    # 간단한 에코백 루프
    while True:
        i = i + 1

        data = await asyncio.wait_for(reader.readline(), timeout = 10.0)
        if data is None:
            log.warning("Received no data")
            return

        sdata = data.decode().rstrip()
        if sdata == 'Quit':
            writer.write("Quit\n".encode())
            break

        response = ("Echo %d: %s\n" % (i, sdata))
        writer.write(response.encode())


def main():
    # executor = concurrent.futures.ThreadPoolExecutor( max_workers = 4 )
    executor = concurrent.futures.ProcessPoolExecutor( max_workers = 4 )
    
    # 이벤트 루프 생성
    loop = asyncio.get_event_loop()
    loop.set_default_executor( executor = executor )
    server = asyncio.start_server(AcceptClient, host = None, port = 8888)
    loop.run_until_complete(server)

    # 여기서 무한루프로 블록 된다
    loop.run_forever()


if __name__ == '__main__':
    log = logging.getLogger("main")
    formatter = logging.Formatter("%(asctime)s %(levelname)s " +
                                  "[%(module)s:%(lineno)d] %(message)s")
    log.setLevel(logging.DEBUG)

    ch = logging.StreamHandler()
    ch.setLevel(logging.DEBUG)
    ch.setFormatter(formatter)

    log.addHandler(ch)

    main()
