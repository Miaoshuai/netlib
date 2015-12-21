CC = clang++ -std=c++11
CFLAGS = -Wall -g
LDFLAGS = -pthread

hehe:server_test.o server.o base_loop.o event_loop.o event_loop_thread_pool.o epoll.o buffer.o
	${CC} server_test.o server.o base_loop.o event_loop.o event_loop_thread_pool.o epoll.o buffer.o ${LDFLAGS}
server_test.o:
	${CC} -c server_test.cpp
server.o:
	${CC} -c server.cpp
base_loop.o:
	${CC} -c base_loop.cpp
event_loop.o:
	${CC} -c event_loop.cpp
event_loop_thread_pool.o:
	${CC} -c event_loop_thread_pool.cpp
epoll.o:
	${CC} -c epoll.cpp
buffer.o:
	${CC} -c buffer.cpp
.PHONY:clean
clean:
	rm *.o

