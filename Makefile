# Alice Karatchentzeff de Vienne
# 22707181
# alice.karatchentzeff@ucdconnect.ie

CC = gcc
CFLAGS = -I

all : server client

server : server.c socketUtil.c socketUtil.h server_quiz.c server_quiz.h QuizDB.h
	gcc server.c socketUtil.c server_quiz.c -o server

client : client.c socketUtil.c socketUtil.h client_quiz.c client_quiz.h
	gcc client.c socketUtil.c client_quiz.c -o client

clean:
	rm server client


