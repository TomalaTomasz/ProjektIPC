all: queue dequeue

queue: queue.c
	gcc -o queue queue.c
dequeue: dequeue.c
	gcc -o dequeue dequeue.c
