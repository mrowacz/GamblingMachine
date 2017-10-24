FROM ubuntu:16.04

RUN apt-get update && apt-get -y install \
         build-essential \
         cmake \
		 libboost-all-dev

COPY . /root/source/
RUN cd /root/source && mkdir -p build && cd build && cmake .. && make


