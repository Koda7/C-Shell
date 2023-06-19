#ifndef _KJOB_H
#define _KJOB_H

int process_kjob(char **list , int ind) {
	if(ind != 3) {
		fprintf(stderr,"Invalid number of arguments\n");
		return 1;
	}
	int index = atoi(list[1]);
	if(index > bgsiz || index == 0) {
		fprintf(stderr,"No such process exists\n");
		return 1;
	}
	int pid = bgid[index - 1];
	int sig = atoi(list[2]);
	if(kill(pid,sig) == -1) {
		perror("kill");
		return 1;
	}	
	return 0;
}
#endif
