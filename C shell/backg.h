#ifndef _BACKG_H
#define _BACKG_H
int handle_bg(char **list,int inbg) {
	int id = fork();
	int stat;
	int exit_stat = 0;
	if(id == -1) {
		perror("");
		return 1;
	}
	else {
		if(!inbg) {
			if(id == 0)  {
				if(setpgid(0,0) < 0)
					perror("");
				if(execvp(list[0],list) < 0) {
					perror("execvp");
				}
				exit(1);
			}
			else {
				fgpid = id;
				signal(SIGTTOU,SIG_IGN);
				signal(SIGTTIN,SIG_IGN);
				tcsetpgrp(STDIN_FILENO,id);
				waitpid(id,&stat,WUNTRACED);
				if(WIFEXITED(stat))
					if(WEXITSTATUS(stat) != 0)
						exit_stat = 1;
					else{}
				else
					exit_stat = 1;
				tcsetpgrp(STDIN_FILENO,getpgrp());
				if(WIFSTOPPED(stat)) {
					bgid[bgsiz] = id;
					strcpy(nameid[bgsiz],list[0]);
					bgsiz++;
				}
				signal(SIGTTOU,SIG_DFL);
				signal(SIGTTIN,SIG_DFL);
				fgpid = 0;
			}
		}
		else {
			if(id == 0) {
				if(setpgid(0,0) < 0)
					perror("");
				if(execvp(list[0],list) < 0) {
					perror("execvp");
				}
				exit(1);
			}
			else {
				bgid[bgsiz] = id;
				strcpy(nameid[bgsiz],list[0]);
				bgsiz++;
				fprintf(stderr,"[%d] %d\n",bgsiz,id);
			}
		}
	}
	return exit_stat;
}
#endif
