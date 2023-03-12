CC = g++
CFLAGS = -Wall -g

RM = rm
RMFLAGS = -rfv

SOURCE_DIR = link_time_polymorphism
OUT_DIR = $(SOURCE_DIR)/obj

CSD_CPP = $(SOURCE_DIR)/CSDevice.cpp
CSD_OUT = $(OUT_DIR)/CSDevice.o

EFD_CPP = $(SOURCE_DIR)/EFDevice.cpp
EFD_OUT = $(OUT_DIR)/EFDevice.o

MAIN_CPP = $(SOURCE_DIR)/main.cpp
MAIN_OUT = $(OUT_DIR)/main.o

PRODUCTION_W_CSD = $(OUT_DIR)/production_w_csd
PRODUCTION_W_EFD = $(OUT_DIR)/production_w_efd

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
	@echo "Cleaning directory : "$(OUT_DIR)
	$(RM) $(RMFLAGS) $(OUT_DIR)/*.o $(OUT_DIR)/production_w*