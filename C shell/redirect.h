#ifndef _REDIRECT_H
#define _REDIRECT_H
int redirection(char ** list,int indir,int outdir,int outappdir,int inbg) {
	int exit_code = 0;
	char *temp = (char *) malloc(bufsiz);
	strcpy(temp,"");
	if(inbg)
		strcpy(temp," &");
	if(indir != -1 && (outdir != -1 || outappdir != -1)) {
		int savesstdin = dup(0);
		int savesstdout = dup(1);
		int fp = open(list[indir + 1], O_RDONLY);
		if(fp == -1) {
			perror("");
			return 1;
		}
		dup2(fp, STDIN_FILENO);
		close(fp);
		char filname[bufsiz];
		if(outdir != -1)
			sprintf(filname,"%s",list[outdir + 1]);
		else
			sprintf(filname,"%s",list[outappdir + 1]);
		int fd;
		if(outdir != -1)
			fd = open(filname,O_CREAT | O_TRUNC | O_WRONLY,0644);
		else
			fd = open(filname,O_CREAT | O_APPEND | O_WRONLY,0644);
		if(fd == -1) {
			perror("");
			return 1;
		}
		if(outdir != -1) {
			list[outdir] = "%";
			list[outdir+1] = "%";
		}
		else{
			list[outappdir] = "%";
			list[outappdir+1] = "%";
		}
		list[indir] = "%";
		list[indir + 1] = "%";
		dup2(fd,STDOUT_FILENO);
		close(fd);
		exit_code = execute(strcat(makecommand(list),temp));
		dup2(savesstdout,1);
		dup2(savesstdin,0);
	}
	else if(outdir != -1 || outappdir != -1) {
		int savesstdout = dup(1);
		char filname[bufsiz];
		if(outdir != -1)
			sprintf(filname,"%s",list[outdir + 1]);
		else
			sprintf(filname,"%s",list[outappdir + 1]);
		int fd;
		if(outdir != -1)
			fd = open(filname,O_CREAT | O_TRUNC | O_WRONLY,0644);
		else
			fd = open(filname,O_CREAT | O_APPEND | O_WRONLY,0644);
		if(fd == -1) {
			perror("");
			return 1;
		}
		if(outdir != -1) {
			list[outdir] = "%";
			list[outdir+1] = "%";
		}
		else{
			list[outappdir] = "%";
			list[outappdir+1] = "%";
		}
		dup2(fd,STDOUT_FILENO);
		close(fd);
		exit_code = execute(strcat(makecommand(list),temp));
		dup2(savesstdout,1);
	}
	else if(indir != -1) {
		int savesstdin = dup(0);
		int fp = open(list[indir + 1], O_RDONLY);
		if(fp == -1) {
			perror("");
			return 1;
		}
		list[indir] = "%";
		list[indir + 1] = "%";
		dup2(fp, STDIN_FILENO);
		close(fp);
		exit_code = execute(strcat(makecommand(list),temp));
		dup2(savesstdin,0);
	}
	return exit_code;
}
#endif