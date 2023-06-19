#ifndef _LS_H
#define _LS_H
char* func(char* str, time_t val)
{
        strftime(str, bufsiz, "%b %d %H:%M", localtime(&val));
        return str;
}
int process_ls(char **list,int siz) {
	DIR *currdir;
	int take_hidden = 0;
	int print_big = 0;
	char dirpath[10][bufsiz];
	int ind = 0;
	for(int i = 1 ; i < siz ; i++) {
		if(list[i][0] == '&')
			continue;
		if(list[i][0] != '-') {
			if(list[i][0] == '~')
				if(strlen(list[i]) > 1)
					sprintf(dirpath[ind],"%s%s",homedir,list[i] + 1);
				else
					sprintf(dirpath[ind],"%s",homedir);
			else
				strcpy(dirpath[ind],list[i]);
			ind++;
		}
		else {
			for(int j = 1 ; list[i][j] != '\0' ; j++) {
				if(list[i][j] ==  'a')
					take_hidden = 1;
				else if(list[i][j] == 'l')
					print_big = 1;
				else {
					fprintf(stderr,"Invalid option\n");
					return 1;
				}
			}
		}
	}
	if(ind == 0) {
		getcwd(dirpath[0],bufsiz);
		ind++;
	}
	for(int k = 0 ; k < ind ; k++) {
		if(ind > 1) {
			if(k > 0)
				puts("");
			printf("%s:\n",dirpath[k]);
		}
		struct stat fil;
		struct dirent **filelist;
		int numfiles;
		char filpath[bufsiz],mtime[bufsiz];
		numfiles = scandir(dirpath[k],&filelist,NULL,alphasort);
		if(numfiles < 0) {
			perror("");
			puts("");
			continue;
		}
		if(print_big == 1) {
			int total = 0;
			int width = 0;
			char num[50];
			for(int i = 0; i < numfiles; i++) {
				if(filelist[i]->d_name[0] == '.' && !take_hidden)
					continue;
				sprintf(filpath,"%s/%s",dirpath[k],filelist[i]->d_name);
				stat(filpath,&fil);
				int wid = sprintf(num,"%ld",fil.st_size);
				if(width < wid)
					width = wid;
				total += fil.st_blocks / 2;
			}
			printf("total %d\n",total);
			for(int i = 0; i < numfiles; i++) {
				if(filelist[i]->d_name[0] == '.' && !take_hidden)
					continue;
				sprintf(filpath,"%s/%s",dirpath[k],filelist[i]->d_name);
				stat(filpath,&fil);
			    printf( (S_ISDIR(fil.st_mode)) ? "d" : "-");
			    printf( (fil.st_mode & S_IRUSR) ? "r" : "-");
			    printf( (fil.st_mode & S_IWUSR) ? "w" : "-");
			    printf( (fil.st_mode & S_IXUSR) ? "x" : "-");
			    printf( (fil.st_mode & S_IRGRP) ? "r" : "-");
			    printf( (fil.st_mode & S_IWGRP) ? "w" : "-");
			    printf( (fil.st_mode & S_IXGRP) ? "x" : "-");
			    printf( (fil.st_mode & S_IROTH) ? "r" : "-");
			    printf( (fil.st_mode & S_IWOTH) ? "w" : "-");
			    printf( (fil.st_mode & S_IXOTH) ? "x" : "-");
			    struct passwd *user = getpwuid(fil.st_uid);
			    struct group *g = getgrgid(fil.st_gid);
			    printf(" %ld",fil.st_nlink);
			    printf(" %s %s",user->pw_name,g->gr_name);
			    printf(" %*ld",width,fil.st_size);
			    printf(" %s",func(mtime,fil.st_mtim.tv_sec));
			    printf(" %s",filelist[i]->d_name);
				free(filelist[i]);
				puts("");
			}
		}
		else {
			int numfiles = scandir(dirpath[k],&filelist,NULL,alphasort);
			for(int i = 0; i < numfiles; i++) {
				if(filelist[i]->d_name[0] == '.' && !take_hidden)
					continue;
				printf("%s ",filelist[i]->d_name);
				free(filelist[i]);
				puts("");
			}
		}
		free(filelist);
	}
	return 0;
}

#endif
