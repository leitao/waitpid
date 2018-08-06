#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <stdlib.h>


void handler(int signal){
	printf("PARENT: Signal (%d) handler received by pid = %d\n", signal, getpid());
}

static struct sigaction sig_action = {
	.sa_handler = handler,
};


int main(){
	pid_t parent, child;
	pid_t pid;

	parent = getpid();
	pid = fork();

	if (pid){
		/* Parent */
		int ret, status;

		child = pid;

		printf("Parent process with child %d\n", pid);

#ifdef SIGACTION
		sigaction(SIGINT, &sig_action, NULL);
#else
		signal(SIGINT, handler);
#endif

		ret = waitpid(pid, &status, 0);
		printf("waitpid() returned ret = %d and status = %d", ret, status);
		if (ret == EINTR) {
			printf(" (EINTR)\n");
		} else
			printf(" (PID)\n");

	} else {
		/* Children */

		/* Put child process on a different process group */
		setpgid(0, 0);

		printf("-> Child process\n");
		sleep(10);
		printf("-> Child process leaving\n");
	}

	printf("End of process %d\n", getpid());
	return 0;
}
