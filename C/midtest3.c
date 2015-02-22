int main(){
	int i,j=0;

	for(i=0;i<8;i++){
		switch(i){
			case 1:
				j=1;
			case 2:
				j=2;	
				break;
				case 3:
				j=3;	
				break;
			case 4:
				if(j=4)
					j=9;
				else
					j=8;
				break;
			case 5:
				if(j=4)j=7;
				break;
			case 6:j=6;
			default:j=7;
		}
		printf("i=%d,j=%d\n",i,j);
	}
}
