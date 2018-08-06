CFLAGS = -g
all:
	gcc $(CFLAGS) waitpid.c -o waitpid_signal
	gcc $(CFLAGS) -D SIGACTION  waitpid.c -o waitpid_sigact
