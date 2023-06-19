#ifndef _PINFO_H
#define _PINFO_H

int process_pinfo(int pid) {
	char path[bufsiz];
	char linkpath[bufsiz];
	sprintf(path,"/proc/%d/stat",pid);
	sprintf(linkpath,"/proc/%d/exe",pid);
	FILE* fd = fopen(path,"r");
	if(fd == NULL) {
		fprintf(stderr,"No such process exists\n");
		return 1;
	}
	printf("pid -- %d\n",pid);
	int cnt = 0;
	char str[bufsiz];
	char exp[bufsiz];
	while(fscanf(fd,"%s",str)) {
		cnt++;
		if(cnt == 3) {
			printf("PROCESS STATUS -- %s\n",str);
		}
		if(cnt == 23) {
			printf("memory -- %s\n",str);
			break;
		}
	}
	int bytes = readlink(linkpath,exp,bufsiz);
	if(bytes < 0) {
		perror("Executable Path");
		return 1;
	}
	exp[bytes] = '\0';
	if(ishomepresent(exp))
		printf("Executable Path -- ~%s\n",exp + hombufsiz);
	else		
		printf("Executable Path -- %s\n",exp);
	fclose(fd);
	return 0;
}
#endif
