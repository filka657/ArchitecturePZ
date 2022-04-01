FROM ubuntu:latest
COPY shablon.cpp /shablon.cpp
RUN apt-get update && apt-get -y install \
	g++ \
	nano
RUN g++ -o test shablon.cpp
CMD ["./test"]