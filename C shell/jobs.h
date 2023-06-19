#ifndef _JOBS_H
#define _JOBS_H

int process_jobs() {
	int exit_stat = 0;
	for(int i = 0 ; i < bgsiz ; i++) {
		printf("[%d] ",i + 1);
		char path[bufsiz];
		sprintf(path,"/proc/%d/stat",bgid[i]);
		FILE* fd = fopen(path,"r");
		if(fd == NULL) {
			perror("jobs");
			exit_stat = 1;
			continue;
		}
		int pid;
		char pname[bufsiz];
		char status;
		fscanf(fd,"%d %s %c",&pid,pname,&status);
		if(status == 'T')
			printf("Stopped ");
		else if(status == 'S' || status == 'R')
			printf("Running ");
		else
			printf("Unknown");
		printf("%s [%d]\n",nameid[i],bgid[i]);
		fclose(fd);
	}
	return exit_stat;
}

#endif
