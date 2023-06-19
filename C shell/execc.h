#ifndef _EXECC_H
#define _EXECC_H
int execute(char* command) {
	read_history(command);
	char* part = strtok(command," \t\r\n\a");
	char* list[30];
	int ind = 0;
	int inbg = 0;
	int indir = -1;
	int outdir = -1;
	int outappdir = -1;
	while (part != NULL) {
		list[ind] = (char*)malloc(bufsiz);
		strcpy(list[ind],part);
		if(!strcmp(part,"<")) indir = ind;
		if(!strcmp(part,">")) outdir = ind;
		if(!strcmp(part,">>")) outappdir = ind;
		part = strtok(NULL," \t\r\n\a");
		ind++;
	}
	if(ind == 0)
		return -1;
	if(strcmp(list[ind - 1],"&") == 0) {
		inbg = 1;
		list[ind - 1] = NULL;
		ind--;
	}
	else {
		list[ind] = (char*)malloc(2);
		list[ind] = NULL;	
	}
	int ext = 0;
	if(strcmp("quit", list[0]) == 0) exit(0);
	else if(indir > -1 || outdir > -1 || outappdir > -1) ext = redirection(list,indir,outdir,outappdir,inbg);
	else if(strcmp(list[0],"cd") == 0)
		if(ind == 1) ext = process_cd(homedir);
		else if(ind == 2) ext = process_cd(list[1]);
		else { printf("Too many arguments\n");ext = 1;}
	else if(strcmp(list[0],"setenv")   	== 0) ext = process_setenv(list,ind);
	else if(strcmp(list[0],"unsetenv") 	== 0) ext = process_unsetenv(list,ind);
	else if(strcmp(list[0],"pwd") 		== 0) ext = process_pwd();
	else if(strcmp(list[0],"echo") 		== 0) ext = process_echo(list,ind);
	else if(strcmp(list[0],"ls")		== 0) ext = process_ls(list,ind);
	else if(strcmp(list[0],"jobs") 		== 0) ext = process_jobs();
	else if(strcmp(list[0],"kjob") 		== 0) ext = process_kjob(list,ind);
	else if(strcmp(list[0],"fg") 		== 0) ext = process_fg(list,ind);
	else if(strcmp(list[0],"bg") 		== 0) ext = process_bg(list,ind);
	else if(strcmp(list[0],"overkill") 	== 0) ext = process_overkill();
	else if(strcmp(list[0],"pinfo") 	== 0)
		if(ind == 1) ext = process_pinfo(getpid());
		else ext = process_pinfo(atoi(list[1]));
	else if(strcmp(list[0],"history") == 0)
		if(ind == 1) ext = write_history(10);
		else ext = write_history(atoi(list[1]));
	else if(strcmp(list[0],"nightswatch") == 0 && strcmp(list[ind - 1],"interrupt") == 0) ext = nightswatch(list,ind);
	else ext = handle_bg(list,inbg);
	return ext;

}
#endif
