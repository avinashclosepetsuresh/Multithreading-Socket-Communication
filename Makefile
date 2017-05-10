all:13_HW2_Q1forkserver 13_HW2_Q1forkclient 13_HW2_Q1threadserver 13_HW2_Q1threadclient 13_HW2_Q1selectserver 13_HW2_Q1selectclient 13_HW2_Q2daytime 13_HW2_Q3echoforkserver 13_HW2_Q3echothreadserver 13_HW2_Q1IOserver 13_HW2_Q1IOclient.c

13_HW2_Q1forkserver:13_HW2_Q1forkserver.o
	gcc -o 13_HW2_Q1forkserver 13_HW2_Q1forkserver.o
13_HW2_Q1forkserver.o:13_HW2_Q1forkserver.c
	gcc -c 13_HW2_Q1forkserver.c

13_HW2_Q1forkclient:13_HW2_Q1forkclient.o
	gcc -o 13_HW2_Q1forkclient 13_HW2_Q1forkclient.o
13_HW2_Q1forkclient.o:13_HW2_Q1forkclient.c
	gcc -c 13_HW2_Q1forkclient.c

13_HW2_Q1threadserver:13_HW2_Q1threadserver.o
	gcc -pthread -o 13_HW2_Q1threadserver 13_HW2_Q1threadserver.o
13_HW2_Q1threadserver.o:13_HW2_Q1threadserver.c
	gcc -c 13_HW2_Q1threadserver.c

13_HW2_Q1threadclient:13_HW2_Q1threadclient.o
	gcc -o 13_HW2_Q1threadclient 13_HW2_Q1threadclient.o
13_HW2_Q1threadclient.o:13_HW2_Q1threadclient.c
	gcc -c 13_HW2_Q1threadclient.c

13_HW2_Q1selectserver:13_HW2_Q1selectserver.o
	gcc -o 13_HW2_Q1selectserver 13_HW2_Q1selectserver.o
13_HW2_Q1selectserver.o:13_HW2_Q1selectserver.c
	gcc -c 13_HW2_Q1selectserver.c

13_HW2_Q1selectclient:13_HW2_Q1selectclient.o
	gcc -o 13_HW2_Q1selectclient 13_HW2_Q1selectclient.o
13_HW2_Q1selectclient.o:13_HW2_Q1selectclient.c
	gcc -c 13_HW2_Q1selectclient.c

13_HW2_Q2daytime:13_HW2_Q2daytime.o
	gcc -o 13_HW2_Q2daytime 13_HW2_Q2daytime.o
13_HW2_Q2daytime.o:13_HW2_Q2daytime.c
	gcc -c 13_HW2_Q2daytime.c

13_HW2_Q3echoforkserver:13_HW2_Q3echoforkserver.o
	gcc -o 13_HW2_Q3echoforkserver 13_HW2_Q3echoforkserver.o
13_HW2_Q3echoforkserver.o:13_HW2_Q3echoforkserver.c
	gcc -c 13_HW2_Q3echoforkserver.c

13_HW2_Q3echothreadserver:13_HW2_Q3echothreadserver.o
	gcc -pthread -o 13_HW2_Q3echothreadserver 13_HW2_Q3echothreadserver.o
13_HW2_Q3echothreadserver.o:13_HW2_Q3echothreadserver.c
	gcc -c 13_HW2_Q3echothreadserver.c

13_HW2_Q1IOserver:13_HW2_Q1IOserver.o
	gcc -o 13_HW2_Q1IOserver 13_HW2_Q1IOserver.o
13_HW2_Q1IOserver.o:13_HW2_Q1IOserver.c
	gcc -c 13_HW2_Q1IOserver.c

13_HW2_Q1IOclient:13_HW2_Q1IOclient.o
	gcc -o 13_HW2_Q1IOclient 13_HW2_Q1IOclient.o
13_HW2_Q1IOclient.o:13_HW2_Q1IOclient.c
	gcc -c 13_HW2_Q1IOclient.c










