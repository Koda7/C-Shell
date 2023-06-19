#ifndef _PIPES_H
#define _PIPES_H

int handle_pipes(char *cmd) {
	char* prt = strtok(cmd,"|");
	char* comlist[20];
	int ind = 0;
	int savestdin = dup(0);
	while(prt != NULL) {
		comlist[ind] = (char*)malloc(bufsiz);
		strcpy(comlist[ind],prt);
		ind++;
		prt = strtok(NULL,"|");
	}
	int ext = 0;
	for(int i = 0 ; i < ind ; i++) {
		if(i == ind - 1) {  
			ext = execute(comlist[i]);
		}
		else {
			int fd[2];
			pipe(fd);
			int id = fork();
			if(id == 0) {
				close(fd[0]);
				dup2(fd[1],1);
				execute(comlist[i]);
				exit(0);		
			}
			else if(id > 0) {
				wait(NULL);
				close(fd[1]);
				dup2(fd[0],0);
			}
			close(fd[0]);
			close(fd[1]);
		}
	}
	dup2(savestdin,0);
	return ext;
}
#endif