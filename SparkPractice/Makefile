up:
	docker network create spark-net
	docker-compose -f ./docker/docker-compose.yml build
	docker-compose -f ./docker/docker-compose.yml up

down:
	docker-compose -f ./docker/docker-compose.yml down
	docker network rm spark-net

bash:
	docker exec -it dockerzeppelin_zeppelin_1 bash

run:
	docker build -t zeppelin ./zeppelin/.
	docker run -it --rm --net spark-net -p 80:8080 -v $(shell pwd)/notebook:/opt/zeppelin/notebook -v $(shell pwd)/zeppelin-0.7.2-bin-all:/opt/zeppelin zeppelin /bin/bash
	#docker run -it --rm --net spark-net -p 80:8080 -v $(shell pwd)/notebook:/opt/zeppelin/notebook zeppelin /opt/zeppelin/bin/zeppelin.sh

build:
	docker build -t earthquakesan/zeppelin:0.8.0 ./zeppelin/.
