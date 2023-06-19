#ifndef _PRINT_PROMPT_H
#define _PRINT_PROMPT_H
void print_shell_prompt(){
	printf("\033[1;32m");
	printf("<%s@%s:",username,sysname);
	char* cwd = (char*)malloc(bufsiz);
	getcwd(cwd,bufsiz);
	int flag = ishomepresent(cwd); 
	printf("\033[1;34m");
	if(flag == 0)
		printf("%s",cwd);
	else
		printf("~%s",cwd + hombufsiz);
	printf("\033[0m");
	printf(">");
}
#endif