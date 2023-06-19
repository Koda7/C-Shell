#ifndef _ISHOME_H
#define _ISHOME_H
int ishomepresent(char *path) {
	int currbufsiz = strlen(path);
	if(currbufsiz < hombufsiz)
		return 0;
	int i = 0;
	int flag = 1;
	while(i < hombufsiz) {
		if(homedir[i] != path[i]) {
			flag = 0;
			break;
		}
		i++;
	}
	return flag;
}

#endif