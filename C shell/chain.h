#ifndef _CHAIN_H
#define _CHAIN_H
 
void handle_chain(char* cmd) {
	int* arr = malloc(sizeof(int) * strlen(cmd));
	int len = 0;
	for(int i = 0; cmd[i] != '\0';i++) {
		if(cmd[i] == '$')
			arr[len++] = 1;
		else if(cmd[i] == '@')
			arr[len++] = 0;
	}
	if(len == 0) {
		int truth_value = handle_pipes(cmd);
		if(flag)
			if(truth_value == 0)
				printf(":')");
			else
				printf(":'(");
		return;
	}
	char* comlist[20];
	char* prt = strtok(cmd,"$@");
	int ind = 0;
	while(prt != NULL) {
		comlist[ind] = (char*)malloc(bufsiz);
		strcpy(comlist[ind],prt);
		ind++;
		prt = strtok(NULL,"$@");
	}
	int off = 0;
	int truth_value = handle_pipes(comlist[0]);
	truth_value = !truth_value;
	for(int i = 1 ; i < ind ; i++) {
		if(truth_value == arr[off]) {
			off++;
			continue;
		}
		int ex = handle_pipes(comlist[i]);
		ex = !ex;
		if(arr[off] == 1)
			truth_value |= ex;
		else
			truth_value &= ex;
		off++;
	}
	if(flag)
		if(truth_value == 1)
			printf(":')");
		else
			printf(":'(");
}
#endif