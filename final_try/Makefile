
CC = g++ -std=c++17

CFLAGS = -g

# On my computer the json header has been linked to path: /usr/include
# and tools libmicrohttpd-0.9.63 is placed in a folder
# This item is retained to facilitate teacher/TA debugging
# LDFLAGS = -ljsoncpp -L/opt/homebrew/lib/ -lmicrohttpd -ljsonrpccpp-common -ljsonrpccpp-server -ljsonrpccpp-client -lcurl
LDFLAGS = -ljsoncpp -lmicrohttpd -ljsonrpccpp-common -ljsonrpccpp-server -ljsonrpccpp-client -lcurl

INC	=	ecs36b_Common.h
INC_CL	=	AutoVehicle.h hw5client.h hw5server.h
OBJ	=	AutoVehicle.o 

all: MiddleCar LeftMotorcycle RightMotorcycle 

hw5client.h:		ecs36b_final.json
	jsonrpcstub ecs36b_final.json --cpp-server=hw5Server --cpp-client=hw5Client

hw5server.h:		ecs36b_final.json
	jsonrpcstub ecs36b_final.json --cpp-server=hw5Server --cpp-client=hw5Client

AutoVehicle.o:		AutoVehicle.cpp AutoVehicle.h $(INC)
	$(CC) -c $(CFLAGS) AutoVehicle.cpp


MiddleCar.o: MiddleCar.cpp $(INC_CL) $(INC)
	$(CC) -c $(CFLAGS) MiddleCar.cpp

LeftMotorcycle.o: LeftMotorcycle.cpp $(INC_CL) $(INC)
	$(CC) -c $(CFLAGS) LeftMotorcycle.cpp

RightMotorcycle.o: RightMotorcycle.cpp $(INC_CL) $(INC)
	$(CC) -c $(CFLAGS) RightMotorcycle.cpp

MiddleCar: MiddleCar.o $(OBJ)
	$(CC) MiddleCar.o $(OBJ) -o MiddleCar $(LDFLAGS)

LeftMotorcycle: LeftMotorcycle.o $(OBJ)
	$(CC) LeftMotorcycle.o $(OBJ) -o LeftMotorcycle $(LDFLAGS)

RightMotorcycle: RightMotorcycle.o $(OBJ)
	$(CC) RightMotorcycle.o $(OBJ) -o RightMotorcycle $(LDFLAGS)

clean:
	rm -f *.o *~ hw5client.h hw5server.h MiddleCar LeftMotorcycle RightMotorcycle 

