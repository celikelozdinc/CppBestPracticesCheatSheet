CC = g++
CFLAGS = -Wall -g

csd:
	$(CC) $(CFLAGS) -c link_time_polymorphism/CSDevice.cpp -o link_time_polymorphism/obj/CSDevice.o
