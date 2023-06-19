#ifndef _NIGHTSWATCH_H
#define _NIGHTSWATCH_H
void handler(int sig) {
	stoploop = 1;
}
void check_interrupt() {
	while(1) {
		char ch = fgetc(stdin);
		if(ch == EOF)
			break;
		if(ch == 'q') {
			kill(getppid(),45);
			exit(0);
		}
	}
}
int nightswatch(char **list,int siz) {
	int tdelay = 2;
	if(siz == 4 && strcmp(list[1],"-n") == 0)
		tdelay = atoi(list[2]);
	FILE* fp = fopen("/proc/interrupts","r");
	if(fp == NULL) {
		perror("interrupts");
		return 1;
	}
	char* columns = (char*) malloc(bufsiz);
	getline(&columns,&bufsiz,fp);
	int len = strlen(columns);
	columns[len - 1] = '\0';
	char* part = strtok(columns," ");
	int cpucount = 0;
	while (part != NULL) {
		cpucount++;
		printf("%s ",part);
		part = strtok(NULL," ");
	}
	puts("");
	int id = fork();
	if(id == -1) {
		perror("fork");
		return 1;
	}
	else if(id == 0)
		check_interrupt();
	else {
		while(1) {
			signal(45,handler);
			if(stoploop) {
				stoploop = 0;
				break;
			}
			char* interrupts = (char*) malloc(bufsiz);
			int irq = -1;
			fseek(fp,0,SEEK_SET);
			while(getline(&interrupts,&bufsiz,fp)) {
				if(irq == 1)
					break;
				irq++;
			}
			char* part2 = strtok(interrupts," ");
			int ind = 0;
			while (part2 != NULL) {
				if(ind >= 1 && ind <= cpucount)
					printf("%4s ",part2);
				part2 = strtok(NULL," ");
				ind++;
			}
			puts("");
			sleep(tdelay);
		}
	}
	return 0;
}
#endif