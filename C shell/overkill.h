#ifndef _OVERKILL_H
#define _OVERKILL_H

int process_overkill() {
	int exit_stat = 0;
	signal(SIGCHLD, SIG_IGN);
	for(int i = 0; i < bgsiz ; i++) {
		if(kill(bgid[i],SIGKILL) == -1)
			exit_stat = 1;
		else
			printf("%s with pid %d exited abnormally\n",nameid[i],bgid[i]);
	}
	bgsiz = 0;
	signal(SIGCHLD, exit_bgp);
	return exit_stat;
}
#endif
