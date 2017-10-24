#!/bin/bash

docker build . -t efun_task
DOCKER_ID=`docker ps -alq`
docker cp ${DOCKER_ID}:/root/source/build/client .
docker cp ${DOCKER_ID}:/root/source/build/server .
