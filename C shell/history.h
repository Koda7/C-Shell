#ifndef _HISTORY_H
#define _HISTORY_H
void intialize_history() {
	char path[bufsiz];
	sprintf(path,"%s/history.data",homedir);
	if( access(path, F_OK ) != -1 )
		return;
	char history[25][bufsiz];
	strcpy(history[0],"%");
	FILE* fp = fopen(path,"w");
	fwrite(history,sizeof(char),sizeof(history),fp);
	fclose(fp);
}
void read_history(char* command) {
	intialize_history();
	char path[bufsiz];
	sprintf(path,"%s/history.data",homedir);
	char history[25][bufsiz];
	FILE* fr = fopen(path,"r");
	fread(history,sizeof(char),sizeof(history),fr);
	int len = 0;
	while(1) {
		if(history[len][0] == '%')
			break;
		len++;
	}
	fclose(fr);
	if(len > 0 && strcmp(history[len - 1],command) == 0)
		return;
	if(len == 20) {
		for(int i = 0 ; i < len ; i++) {
			strcpy(history[i],history[i+1]);
		}
		len--;
	}
	strcpy(history[len],command);
	strcpy(history[len + 1],"%");
	FILE *fp = fopen(path,"w+");
	fwrite(history,sizeof(char),sizeof(history),fp);
	fclose(fp);
}
int write_history(int num) {
	if(num > 20)
		num = 20;
	char path[bufsiz];
	sprintf(path,"%s/history.data",homedir);
	char history[25][bufsiz];
	FILE* fr = fopen(path,"r");
	if(fr == NULL) {
		fprintf(stderr,"Failed to read history file\n");
		return 1;
	}
	fread(history,sizeof(char),sizeof(history),fr);
	int len = 0;
	while(1) {
		if(history[len][0] == '%')
			break;
		len++;
	}
	int ind = len - num;
	if(ind < 0) ind = 0;
	while(1) {
		if(num == 0 || ind == len)
			break;
		printf("%s\n",history[ind]);
		num--;
		ind++;
	}
	fclose(fr);
	return 0;
}
#endif
