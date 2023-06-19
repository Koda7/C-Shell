#ifndef _HANDLERS_H
#define _HANDLERS_H

void remid(int ind) {
	for(int i = ind ; i + 1 < bgsiz ; i ++) {
		bgid[i] = bgid[i + 1];
		strcpy(nameid[i],nameid[i + 1]);
	}
	bgsiz--;
}
void exit_bgp(int sig) {
	for(int i = 0 ; i < bgsiz ; i++) {
		int status;
		if(waitpid(bgid[i],&status,WNOHANG) > 0) {
			remid(i);
			if(WIFEXITED(status))
				fprintf(stderr,"%s with pid %d exited normally\n",nameid[i],bgid[i]);
			else
				fprintf(stderr,"%s with pid %d exited abnormally\n",nameid[i],bgid[i]);
		}
	}
}
void handle_ctrlc() {
	if(fgpid <= 0) {
		return;
	}
	kill(fgpid,SIGINT);
	fgpid = 0;
}
void handle_ctrlz() {
	if(fgpid <= 0) {
		return;
	}
	kill(fgpid,SIGTSTP);
	fgpid = 0;
}
#endif
