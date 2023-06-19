#ifndef _DIROP_H
#define _DIROP_H
int process_cd(char* arg) {
	char* cwd = (char*)malloc(bufsiz);
	getcwd(cwd,bufsiz);
	int check;
	if(arg[0] == '-') {
		if(strcmp(lwd,"") == 0) {
			printf("%s\n",cwd);
			return 0;
		}
		printf("%s\n",lwd);
		check = chdir(lwd) == -1;
	}
	else if(arg[0] == '~') {
		check = chdir(homedir);
		if(strlen(arg) > 2)
		chdir(arg + 3);
	}
	else
		check = chdir(arg);
	if(check == -1) {
		perror("");
		return 1;
	}
	else 
		strcpy(lwd,cwd);
	return 0;
}
int process_pwd() {
	char* cwd = (char*)malloc(bufsiz);
	getcwd(cwd,bufsiz);
	if(cwd == NULL) {
		perror("pwd");
		return 1;
	}
	printf("%s\n",cwd);
	return 0;
}
#endif