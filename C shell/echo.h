#ifndef _ECHO_H
#define _ECHO_H

int process_echo(char **list,int tot) {
	for(int i = 1 ; i < tot ; i++) {
		printf("%s",list[i]);
		if(i < tot - 1)
			printf(" ");
	}
	puts("");
	return 0;
}

#endif