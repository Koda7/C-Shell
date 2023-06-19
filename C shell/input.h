#ifndef _INPUT_H
#define _INPUT_H

void takeinput() {
	flag = 0;
	char* commands = (char*)malloc(bufsiz);
	int bytes = getline(&commands,&bufsiz,stdin);
	if(bytes == -1)
		exit(0);
	commands[bytes - 1] = '\0';
	char* comm = strtok(commands,";");
	char* list[30];
	int ind = 0;
	while(comm != NULL) {
		list[ind] = (char*)malloc(bufsiz);
		strcpy(list[ind],comm);
		ind++;
		comm = strtok(NULL,";");
	}
	for(int i = 0 ; i < ind ; i++) {
		if(i == ind - 1)
			flag = 1;
		handle_chain(list[i]);
	}
}

#endif