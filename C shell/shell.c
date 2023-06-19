#include "header.h"
int main() {
	signal(SIGINT,handle_ctrlc);
	signal(SIGTSTP,handle_ctrlz);
	signal(SIGCHLD,exit_bgp);
	assign_global();
	while(1){
		print_shell_prompt();
		takeinput();	
	}
	return 0;
}
