#
#	Makefile for IPC32
#
#	(c) Fontys 2010, Joris Geurts
#

BINARIES = TCPChatClient TCPChatServer TCPChatServer-Fork TCPChatServer-Thread

#CC = i586-linux-g++
CC = g++
CFLAGS = -g3 -Wall -W -Wshadow -Wcast-qual -Wwrite-strings
LDLIBS = -lrt
CLIENT_AUX_OBJS = Auxiliary.o CreateTCPClientSocket.o
SERVER_AUX_OBJS = Auxiliary.o CreateTCPServerSocket.o AcceptTCPConnection.o HandleTCPClient.o

all:	$(BINARIES)

clean:
	rm *.o $(BINARIES)

TCPChatClient: TCPChatClient.o $(CLIENT_AUX_OBJS)

TCPChatServer: TCPChatServer.o $(SERVER_AUX_OBJS)

TCPChatServer-Fork: TCPChatServer-Fork.o $(SERVER_AUX_OBJS)

TCPChatServer-Thread: TCPChatServer-Thread.o $(SERVER_AUX_OBJS)


