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
	char **grid;
	int gridlen;
	char **words;
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
	for (char *s =strsep(&b,"\n");s!=NULL && *s ;s=strsep(&b,"\n")){
		if (data->gridlen%size==0){
			data->grid=realloc(data->grid,sizeof(char*)*(data->gridlen+size));
		}
		data->grid[data->gridlen++]=s;
	}
	
//struct initialization--Word List
	data->words = NULL;
	data->wordslen = 0;

//pointer assignment and tokenization-- Wordlist
	for (char *s = strsep(&b, ","); s != NULL; s = strsep(&b, ",")) {
		while (isspace(*s)){
			s++;
		}
		if (data->wordslen % size == 0){
		   data->words = realloc(data->words, sizeof(char*)*(data->wordslen + size));
		}
		data->words[data->wordslen++] = s;
		while (*s) {//different from 23:21
		  *s = toupper(*s);
		  s++;
		}
	}
}

struct rc_t {
  int row;
  int col;
  struct rc_t *next;
};

int in_path(struct rc_t *path, int row, int col)
{
  return path == NULL ? 0 : path->row == row && path->col == col ? 1 : in_path(path->next, row, col);
}

void search(struct data_t data, int row, int col, char *word, struct rc_t *path){
  if (!*word) {
    for (struct rc_t *rc = path; rc; rc = rc->next) {//pointer name is p in video
      data.grid[rc->row][rc->col] |= 0x80;
    }
  } 
  else if (0 <= row && row < data.gridlen && 0 <= col && col < strlen(data.grid[row]) && !in_path(path, row, col) && (*word == (data.grid[row][col] & 0x7f) || *word == '?')) {
    for (int r = -1; r <= 1; ++r) {
      for (int c = -1; c <= 1; ++c) {
        struct rc_t new_path = { row, col, path };
        search(data, row+r, col+c, word+1, &new_path);
      }
    }
  }
}

int main(int argc, char *argv[]){
	char *buf = readfile(argv[1]);
	struct data_t data;
	parse_data(buf,&data);

	for (int i = 0; i < data.wordslen; ++i) {
		for (int row = 0; row < data.gridlen; ++row) {
			int len = strlen(data.grid[row]);
			for (int col = 0; col < len; ++col) {
				search(data, row, col, data.words[i], NULL);
			}
		}
	}
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
