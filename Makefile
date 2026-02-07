
# MT25029
CC=gcc
CFLAGS=-O2 -pthread

all:
	$(CC) $(CFLAGS) MT25029_Part_A1_Server.c -o a1_server
	$(CC) $(CFLAGS) MT25029_Part_A1_Client.c -o a1_client
	$(CC) $(CFLAGS) MT25029_Part_A2_Server.c -o a2_server
	$(CC) $(CFLAGS) MT25029_Part_A2_Client.c -o a2_client
	$(CC) $(CFLAGS) MT25029_Part_A3_Server.c -o a3_server
	$(CC) $(CFLAGS) MT25029_Part_A3_Client.c -o a3_client

clean:
	rm -f a1_client a1_server a2_client a2_server a3_client a3_server *.o \
	      MT25029_Raw.csv 
