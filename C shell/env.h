#ifndef _ENV_H
#define _ENV_H
int process_setenv(char **args,int len) {
	if(len != 2 && len != 3) {
		fprintf(stderr,"Invalid number of arguments\n");
		return 1;
	}
	char val[bufsiz];
	strcpy(val,"");
	if(len == 3)
		sprintf(val,"%s",args[2]);
	if(setenv(args[1],val,1) == -1) {
		perror("setenv");
		return 1;
	}
	return 0;
}
int process_unsetenv(char **args,int len) {
	if(len != 2) {
		fprintf(stderr,"Invalid number of arguments\n");
		return 1;
	}
	if(unsetenv(args[1]) == -1) {
		perror("unsetenv");
		return 1;
	}
	return 0;
}
#endif
