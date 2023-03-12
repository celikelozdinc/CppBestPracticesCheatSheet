CC = g++
CFLAGS = -Wall -g

RM = rm
RMFLAGS = -rfv

CSD_CPP = link_time_polymorphism/CSDevice.cpp
CSD_OUT = link_time_polymorphism/obj/CSDevice.o

EFD_CPP = link_time_polymorphism/EFDevice.cpp
EFD_OUT = link_time_polymorphism/obj/EFDevice.o

MAIN_CPP = link_time_polymorphism/main.cpp
MAIN_OUT = link_time_polymorphism/obj/main.o

PRODUCTION_W_CSD = link_time_polymorphism/obj/production_w_csd
PRODUCTION_W_EFD = link_time_polymorphism/obj/production_w_efd

csd:
	$(CC) $(CFLAGS) -c $(CSD_CPP) -o $(CSD_OUT)

efd:
	$(CC) $(CFLAGS) -c $(EFD_CPP) -o $(EFD_OUT)

main:
	$(CC) $(CFLAGS) -c $(MAIN_CPP) -o $(MAIN_OUT)

production_w_csd: csd main
	$(CC) $(MAIN_OUT) $(CSD_OUT) -o $(PRODUCTION_W_CSD)

run_csd: production_w_csd
	./$(PRODUCTION_W_CSD)

production_w_efd: efd main
	$(CC) $(MAIN_OUT) $(EFD_OUT) -o $(PRODUCTION_W_EFD)

run_efd: production_w_efd
	./$(PRODUCTION_W_EFD)

clean:
	$(RM) $(RMFLAGS)  link_time_polymorphism/obj/*.o link_time_polymorphism/obj/production_w*
