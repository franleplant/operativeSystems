#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>




#define MAX_BUFFER 255
#define SUC_NUMBER 10

void hijo();
void padre();

int fd1 [2], fd2 [2];
pid_t pid;

int main() {
	
	int suc = 0;
	
	if ( pipe(fd1) != 0 || pipe(fd2) != 0 ) {
		printf("PIPES: ERROR AL CREARLAS\n");
		exit(0);		
	};
	
	pid = fork();
	switch(pid) {
		case -1:
			printf("FORK: ERROR\n");
			break;
		case 0:
			hijo();
			break;
		default:
			padre(suc);
			break;
		
	};
	
	exit(0);
};

void hijo() {
	char * prog [] = {"./blackBox", "./blackBox", NULL};
	close(fd1 [1]);
	close(fd2 [0]);
	
	dup2(fd1 [0], STDIN_FILENO);	
	close(fd1 [0]);
	dup2(fd2 [1], STDOUT_FILENO);
	close(fd1 [1]);
	
	execvp(prog [0], prog);
	
	printf("EXECVP: ERROR \n");
	exit(0);
};

void padre(int suc) {
	char buffer [MAX_BUFFER];
	int n;
	int status;
	close(fd1 [0]);
	close(fd2 [1]);
	
	snprintf(buffer,MAX_BUFFER,"%d\n",suc);
	write(fd1 [1],buffer, MAX_BUFFER);
	n = read(fd2 [0],buffer, MAX_BUFFER);
	buffer[n]='\0';
	printf("main():lei de prog. hijo: [%s]",buffer);
   
	
	waitpid(pid, &status, WUNTRACED);
	exit(0);
};

