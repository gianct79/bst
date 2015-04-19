/*
* Copyleft 1979-2015 GTO Inc. All Rights Reversed.
*/

#include <stdio.h>
#include <stdlib.h>

#include <sys/resource.h>

void setLimits(pid_t pid) {

	int result = 0;

	struct rlimit cpu_new = { 3, 3 };
	struct rlimit cpu_old = { 0, 0 };

	result = prlimit(pid, RLIMIT_CPU, &cpu_new, &cpu_old);

	printf("CPU: %d\n", result);

	struct rlimit fsize_new = { 10 * 1024 * 1024, 10 * 1024 * 1024 }; // 10 MiB
	struct rlimit fsize_old = { 0, 0 };

	result = prlimit(pid, RLIMIT_FSIZE, &fsize_new, &fsize_old);

	printf("FSIZE: %d\n", result);

	struct rlimit as_new = { 192 * 1024 * 1024, 192 * 1024 * 1024 }; // 192 MiB
	struct rlimit as_old = { 0, 0 };

	result = prlimit(pid, RLIMIT_AS, &as_new, &as_old);

	printf("ADDRSPACE: %d\n", result);

	struct rlimit stack_new = { 256 * 1024, 256 * 1024 }; // 256 KiB
	struct rlimit stack_old = { 0, 0 };

	result = prlimit(pid, RLIMIT_STACK, &stack_new, &stack_old);

	printf("STACK: %d\n", result);

	struct rlimit nofile_new = { 16, 16 };
	struct rlimit nofile_old = { 0, 0 };

	result = prlimit(pid, RLIMIT_NOFILE, &nofile_new, &nofile_old);

	printf("NUMFILE: %d\n", result);

	struct rlimit noproc_new = { 0, 0 };
	struct rlimit noproc_old = { 0, 0 };

	result = prlimit(pid, RLIMIT_NPROC, &noproc_new, &noproc_old);

	printf("NUMPROC: %d\n", result);
}

int main(int argc, char **argv, char **envp) {

	pid_t pid;
	int status;

	char *envp_[] = { NULL };
	char **argv_ = (char**) malloc(argc * sizeof(char*));

	if (argv_ == NULL) {
		perror("malloc()");
		exit(EXIT_FAILURE);
	}

	int i;
	for (i = 0; i < argc; i++) {
		argv_[i] = argv[i + 1];
	}
	argv[i] = NULL;

	switch (pid = fork()) {
		case -1:
			perror("fork()");
			exit(EXIT_FAILURE);
		case 0:
			status = execve(argv_[0], argv_, envp_);
			free(argv_);			
			perror("execve()");
			exit(status);
		default:
			free(argv_);		
			setLimits(pid);
			if (waitpid(pid, &status, 0) < 0) {
				perror("waitpid()");
				exit(EXIT_FAILURE);
			}

			if (WIFEXITED(status)) {
				printf("\n*** STATUS: %d ***\n", WEXITSTATUS(status));
				exit(WEXITSTATUS(status));
			}

			if (WIFSIGNALED(status)) {
				printf("\n*** STATUS: %d ***\n", WTERMSIG(status));
				exit(WTERMSIG(status));
			}

			if (WIFSTOPPED(status)) {
				printf("\n*** STATUS: %d ***\n", WSTOPSIG(status));
				exit(WSTOPSIG(status));
			}

			printf("\n*** STATUS: %d ***\n", status);
			exit(EXIT_FAILURE);
	}
}
