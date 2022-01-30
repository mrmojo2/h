#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_WORD_LENGTH 20
#define MAX_WORDS 20

void readfile(char* buffer){                                                    //this reads wrods from words file and store in buffer
        FILE * fd=fopen("words.txt","r");                                        

        fseek(fd,0L,SEEK_END);													//this sets the file position indicator to the end of the file to read the size of file
        int filesize=ftell(fd);                                                 //this uptains the current value of file position and since it is in the end this gives us size of file
        fseek(fd,0L,SEEK_SET);													//setting the file position back to the starting of the file to read from file

        int size=fread(buffer,1,filesize,fd);
        //printf("buffer :%s\n",buffer);
}

int seperator(char *input,char output[MAX_WORD_LENGTH][MAX_WORDS]){         //this seperates the words in buffer into array of words
	int i=0,c=0;
	for(int row=0;row<MAX_WORDS;row++){
		for(int col=0;col<MAX_WORD_LENGTH;col++){
			if(input[i]=='\n'){
				output[row][col]='\0';
				i++;c++;
				break;
			}else{
				output[row][col]=input[i++];
			}

		}
	}
	return c;
}

void my_print(char* arr,int i){
        for(int k=0;k<i;k++){
                printf("%c ",arr[k]);
        }
	printf("\n");
}

void game(char *w){
	//printf("%s\n",w);
	int i=0,lives=5,gameState=0,u=0;
	
	for(;w[i]!='\0';i++){}                                     //counting our size of word and storing in i
	char dash[i],used[26]={'0'},inp;			               //dash is for printing in screen as the user answers correctly we update dash accordingly....used is to store entered character...inp is to store user input
	for(int j=0;j<i;j++){ dash[j]='_';} 			           //filling dash array with dashesh initially
	
	while(1){
		int matched=0,contn=0;
		
		if(lives==0){                                         //checking if life has run out
			printf("Game Over!! The word was %s\n",w);
			break;
		}
		my_print(dash,i); 
		
		if(gameState==i){					                   //checking if user has guessed all the words
			printf("Congratulations!!\n");
			break;
		}

		scanf(" %c",&inp);										//taking input
		
		for(int q=0;q<26;q++){									//checking if user has already entered the character
			if(used[q]==inp){
				printf("You have already selected %c!\n",inp);
				contn=1;
			}
		}

		if(contn){								               //if the user has entered the character already then skip other process if not then store the inp in used and proceed
			continue;
		}else{
			used[u++]=inp;
		}

		for(int k=0;k<i;k++){							       //checking if input matches any letters in our word
			if(w[k]==inp){
				dash[k]=inp;
				gameState++;
				matched=1;
			}
		}
		if(matched){								          //what to do if input matches or doesn't match any letters in words
			printf("Correct!!\n");
		}else{
			printf("Wrong!!");
			lives--;
			printf("You have %d lives remaining \n",lives);
		}
	}
}

int main(){
	char buffer[500],words[MAX_WORD_LENGTH][MAX_WORDS]={'\0'};
	int fd,wordcount;
	
	readfile(buffer);						          //reads all words form the file and stores to buffer	
	wordcount=seperator(buffer,words);				  //seperates the words in buffer into array of words

	srand(time(NULL));						          //wee need to set seed to create random number in c and we are using the time() ( which is always unique ) value as seed
	char choice='y';
	while(choice=='y'||choice=='Y'){
		int r=rand()%(wordcount-1);				      //creating a random no... rand() creates a totally random no and to get it within our range we use % for example if we need random form 0 to 9 we use rand()%10
		game(words[r]);
		printf("play again?(y/n): ");
		scanf(" %c",&choice);	
	}
}
