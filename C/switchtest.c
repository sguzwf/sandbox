int main(int argc,char *argv[]){
	switch(atoi(argv[1])){
		case 1:
			switch(atoi(argv[2])){
				case 1:
					printf("A\n");
					break;
				case 2:
					printf("B\n");
					break;
			}
			break;
		case 2:
			printf("C\n");
			break;
	}
	return 0;
}
