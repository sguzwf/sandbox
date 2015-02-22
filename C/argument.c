#include<unistd.h>

int main(int argc,char *argv[]){
	int i,c;
	extern char *optarg;
	extern int optind, optopt;
	if((c = getopt(argc, argv, ":abc:d:"))!=-1){
		switch(c){
		case 'a':
			printf("a\n");
			break;
		case 'b':
			printf("b\n");
			break;
		case 'c':
			printf("%s,c\n",optarg);
			break;
		case 'd':
			printf("%s,d\n",optarg);
			break;
		case ':':
			printf("Option -%c requires an operand\n",optopt);
			break;
		case '?':
			printf("Unrecognized option: -%c\n",optopt);
			break;
		}
		printf("optind = %d\n",optind);
		printf("argc = %d\n",argc);
		for(i=0;i<optind;i++)
			printf("argv = %s\n",argv[i]);
		printf("%c\n",optopt);
	}
	return 0;
}
