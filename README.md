Requirements:
- docker

if you want compile "by hand" look inside Dockerfile

or if you are lazy just run build_me.sh ...

after succesfull build run from your terminal:
```bash
./client
```

if your os doesn't have requeired libraries try run app from docker image
```bash
docker run -i -t --entrypoint /bin/bash ${DOCKER_IMAGE}
```
binaries are in /home/source/build/
