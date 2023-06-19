#ifndef _GLOABAL_H
#define _GLOABAL_H
char *username,*sysname,*homedir;
size_t bufsiz = 256;
int hombufsiz;
int stoploop = 0;
int *bgid,bgsiz = 0;
char *nameid[30];
int fgpid = 0;
char* lwd;
int flag = 0;
int execute(char*);
char* makecommand(char **list) {
	char* cmd = (char*)malloc(sizeof(char) * bufsiz);
	strcpy(cmd,"");
	for(int i = 0 ; list[i] != NULL;i++) {
		if(strcmp(list[i],"%") == 0)
			continue;
		strcat(cmd,list[i]);
		strcat(cmd," ");
	}
	return cmd;
}
void assign_global() {
	username = (char*)malloc(bufsiz);
	sysname = (char*)malloc(bufsiz);
	homedir = (char*)malloc(bufsiz);
	lwd = (char*)malloc(bufsiz);
	strcpy(lwd,"");
	bgid = (int*)malloc(bufsiz * sizeof(int));
	username = getpwuid(getuid())->pw_name;
	gethostname(sysname,bufsiz);
	getcwd(homedir,bufsiz);
	hombufsiz = strlen(homedir);
	for(int i = 0 ; i < 30 ; i ++)
		nameid[i] = (char*)malloc(bufsiz);
}
#endif