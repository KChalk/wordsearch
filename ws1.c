/*
Kendra Chalkley
November 2 2016
NEW BEGINNINGS Theory II
Programming Assignment 3
*/

// this code was taken from Chong Kim video and used for educational purposes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


/*
Readfile opens a file, determines its size, and allocates space and copies the file into a character array, closes the file, and returns a pointer to the copy. 
*/
char *readfile(char *filename){ 
	FILE *fp=fopen(filename, "r");
	fseek(fp,0,SEEK_END);
	long fsize=ftell(fp);
	fseek(fp,0,SEEK_SET);
	char * buf=malloc(fsize+1);
	fread(buf,1,fsize,fp);
	buf[fsize]=0;
	fclose(fp);
	return buf;
}

/*
The data_t struct points to a array of characters and a list of words, and stores the number of characters in the array and the number of words. 
*/
struct data_t{
	char **grid;//array of pointers to heads of rows
	int gridlen;
	char **words;//array of pointers to words
	int wordslen;
};

/*
Parse data assigns pointers in data_t structure to the appropriate positions in the character array created by read_file
*/
void parse_data(char *buf, struct data_t *data){//names in this file differ from those in the video. This text is copied from Chong Kim's github. 

	int size=1;
	char *b=buf;//unclear why this is needed...

//struct initialization--Grid

	data->gridlen=0;
	data->grid=NULL;

//pointer assignment and tokenization-- Grid
	//make each line/row into a string, with mildly recursive progression through buffer, and add pointer to that string to data->grid array. 

	for (char *s =strsep(&b,"\n");s != NULL&&(s[0] != '\n');s=strsep(&b,"\n")){ 
	printf("seriously\r\n");
		printf("s0 is [%c] s1 is [%c] s is %s ...\r\n",s[0],s[1],s);
	printf("wtf\r\n");
		if (data->gridlen%size==0){//always true, if size were larger would reduce allocations at expense of memory
			data->grid=realloc(data->grid,sizeof(char*)*(data->gridlen+size));//allocate space for an addtional char pointer in the grid array
		}
		//
		data->grid[data->gridlen++]=s;//put pointer to this row into appropriate space in grid, which is really an array of row pointers. 
	}
	
//struct initialization--Word List
	data->words = NULL;
	data->wordslen = 0;

//pointer assignment and tokenization-- Wordlist
	//make each word into a string and add pointer to that string to data->words array. 
	
	for (char *s = strsep(&b, ","); s != NULL; s = strsep(&b, ",")) {
		printf("thisfar\n");
		while (isspace(*s)){ //skips white space
			s++;
		}
		if (data->wordslen % size == 0){//allocates space for new pointer
		   data->words = realloc(data->words, sizeof(char*)*(data->wordslen + size));
		}
		data->words[data->wordslen++] = s;//adds pointer to array
		
		while (isalpha(*s)) {//folds to caps
			printf("%c to...",*s);
		   *s = toupper(*s);
			printf("%c!\n",*s);
		  s++;
		}
	}
}


/*
rc_t struct is a node in a linked list of grid positions-- used to record paths through wordsearch. 
*/
struct rc_t {
  int row;
  int col;
  struct rc_t *next;
};

int in_path(struct rc_t *path, int row, int col){
	//translated to if statments...
	/*
	if (path==NULL){
		return 0;
	}
	else if (path->row==row && path->col==col){
		return 1;
		else {
			inpath_(path->next, row, col);
		}
	}
	*/
	
	//ie, recursive transversal over path returns 1 if row and coloum index are found in list, 0 if reaches end of list without matching.  
  return (path == NULL ? 0 : path->row == row && path->col == col ? 1 : in_path(path->next, row, col));
}

//search 
void search(struct data_t data, int row, int col, char *word, struct rc_t *path){
	
  // at end of word list transverse path with rc pointer, set signbit to 1 
  if (!*word) {
	for (struct rc_t *rc = path; rc; rc = rc->next) {
      data.grid[rc->row][rc->col] |= 0x80;
    }
  }
 
	//if row and col are in bounds and not in path (ie, not already found for this word) and if characters in word and at this index match....
  else if (0 <= row && row < data.gridlen && 0 <= col && col < strlen(data.grid[row]) && !in_path(path, row, col) && (*word == (data.grid[row][col] & 0x7f) || *word == '?')) {//mistake in casting should be inconsequential
	 //depth first recursive check each adjacent position to match next char. 
    for (int r = -1; r <= 1; ++r) {
      for (int c = -1; c <= 1; ++c) {
        struct rc_t new_path = { row, col, path };
        search(data, row+r, col+c, word+1, &new_path);
      }
    }
  }
}

int main(int argc, char *argv[]){

	char *buf = readfile(argv[1]); //copy data to array.
	struct data_t data; //create struct for meta data
	parse_data(buf,&data); //create pointers for grid[0][0], and words[0];

	//for each word in word list, search each column and each row for the word
	for (int i = 0; i < data.wordslen; ++i) {
		for (int row = 0; row < data.gridlen; ++row) {
			int len = strlen(data.grid[row]);
			for (int col = 0; col < len; ++col) {
				search(data, row, col, data.words[i], NULL);//null argument will be used in recursions.
			}
		}
	}
	
	//for each col in each row, if sign bit is set, print the character there, otherwise, print . (+other formatting)
	for(int row=0;row<data.gridlen;++row){
		int len= strlen(data.grid[row]);
		char* sep="";
		for (int col=0;col<len;++col){
			char ch = data.grid[row][col];
			printf("%s%c",sep,ch&0x80?ch&0x7f:'.');
			sep=" ";
		}
		puts("");
	}
	puts("");
	char *sep = "";
	
	for (int i = 0; i < data.wordslen; ++i) {
		printf("%s%s", sep, data.words[i]);
		sep = ", ";
	}
	puts("");
	
	free(buf);
	return 0;
}
