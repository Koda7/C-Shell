#ifndef _FBG_H
#define _FBG_H

int process_fg(char **list,int ind){
	if(ind != 2) {
		fprintf(stderr,"Invalid arguments\n");
		return 1;
	}
	int index = atoi(list[1]);
	if(index > bgsiz || index == 0) {
		fprintf(stderr,"Invalid job number\n");
		return 1;
	}
	int pid = bgid[index - 1];
	if(kill(pid,SIGCONT) == -1) {
		fprintf(stderr,"signal failed\n");
		return 1;
	}
	fgpid = pid;
	signal(SIGTTOU,SIG_IGN);
	signal(SIGTTIN,SIG_IGN);
	tcsetpgrp(STDIN_FILENO,pid);
	int status;
	waitpid(pid,&status,WUNTRACED);
	int exit_stat = 0;
	if(WIFEXITED(status))
		if(WEXITSTATUS(status))
			exit_stat = 1;
		else {}
	else
		exit_stat = 1;
	tcsetpgrp(STDIN_FILENO,getpgrp());
	if(!WIFSTOPPED(status)) {
		fgpid = 0;
		remid(index - 1);
	}
	signal(SIGTTOU,SIG_DFL);
	signal(SIGTTIN,SIG_DFL);
	return exit_stat;
}
int process_bg(char **list,int ind) {
	if(ind != 2) {
		fprintf(stderr,"Invalid arguments\n");
		return 1;
	}
	int index = atoi(list[1]);
	if(index > bgsiz || index == 0) {
		fprintf(stderr,"Invalid job number\n");
		return 1;
	}
	int pid = bgid[index - 1];
	if(kill(pid,SIGCONT) == -1) {
		fprintf(stderr,"signal failed\n");
		return 1;
	}
	return 0;
}
#endif
