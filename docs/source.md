```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct
{
	int HEIGHT;
	char CHR;
	char COLOR[32];
	char NAME[32];
	char FILE_[32];
}TRIANGLE_T;

enum {false, true};

const char *red = "\033[31m";	
const char *green = "\033[32m";
const char *yellow = "\033[33m";
const char *blue = "\033[34m";
const char *default_color = "\033[0m";

#define HEIGHT_DEFAULT 15
#define NAME_DEFAULT "NAME"
#define CHR_DEFAULT '#'

void draw_triangle(TRIANGLE_T *triangle, FILE *fp)
{
	if(!triangle->HEIGHT) {
		triangle->HEIGHT = HEIGHT_DEFAULT;
	}
	if(!triangle->NAME[0]) {
		strcpy(triangle->NAME, NAME_DEFAULT);
	}
	if(!triangle->COLOR[0]) {	
		strcpy(triangle->COLOR, default_color);
	}
	if(!triangle->CHR) {
		triangle->CHR = CHR_DEFAULT;
	}
	int n = 1;
	if(fp != NULL) fprintf(fp, "%s", triangle->COLOR);
	printf("%s", triangle->COLOR);
	for(int i = 0; i < triangle->HEIGHT; i++) {
		for(int j = 0; j < n; j++) {
			putchar(triangle->CHR);
			putchar(' ');
			if(fp != NULL) {
				fputc(triangle->CHR, fp);
				fputc(' ', fp);
			}
		}
		putchar('\n');
		if(fp != NULL) fputc('\n', fp);
		n++;
	}
	printf("%s", default_color);
}

void print_info(TRIANGLE_T *triangle, FILE *fp)
{
	printf("Triangle info:\n");
	printf("NAME:      %s\n", triangle->NAME); 
	printf("HEIGHT:      %d\n", triangle->HEIGHT); 
	printf("CHAR:      %c\n", triangle->CHR); 
	if(fp != NULL) {
		printf("FILE:      %s\n", triangle->FILE_);
		fprintf(fp, "%s", default_color);
		fprintf(fp, "Triangle info:\n");
		fprintf(fp, "NAME:      %s\n", triangle->NAME); 
		fprintf(fp, "HEIGHT:      %d\n", triangle->HEIGHT); 
		fprintf(fp, "CHAR:      %c\n", triangle->CHR);
		fprintf(fp, "FILE:      %s\n", triangle->FILE_);
	}
}

int main(int argc, char *argv[])
{
	TRIANGLE_T triangle = {0};
	int info = false;
	FILE *fp = NULL;
	int opt;
	while((opt = getopt(argc, argv, "h:n:f:c:t:il")) != -1) {
		switch(opt) {
			case 'h':
				triangle.HEIGHT = atoi(optarg);
				break;
			case 'n':
				strcpy(triangle.NAME, optarg);
				break;
			case 't':
				if(!strcmp(optarg, "red"))
					strcpy(triangle.COLOR, red);
				else if(!strcmp(optarg, "green"))
					strcpy(triangle.COLOR, green);
				else if(!strcmp(optarg, "yellow"))
					strcpy(triangle.COLOR, yellow);
				else if(!strcmp(optarg, "blue"))
					strcpy(triangle.COLOR, blue);
				else {
					fprintf(stderr, "Unsupported Color:%s.\n",\
					optarg);
					fprintf(stderr, "Use -l option to print "\
					"a list of supported colors\n");
					exit(EXIT_FAILURE);
				}
				break;
			case 'l':
				if(optind == 2) {
					printf("Supported Colors:\n");
					printf("Red, Green, Yellow, Blue\n");
					exit(EXIT_SUCCESS);
				}
				break;
			case 'c':
				triangle.CHR = optarg[0];
				break;
			case 'f':
				strcpy(triangle.FILE_, optarg);
				break;
			case 'i':
				info = true;
				break;
			default:
				printf("Usage:\n%s [-h|-f|-n|-c|-C] args\n", argv[0]);
				exit(EXIT_FAILURE);
		}
	}
	if(triangle.FILE_[0]) {
		fp = fopen(triangle.FILE_, "w+");
		if(fp == NULL) {
			fprintf(stderr, "Failed to open %s\n", triangle.FILE_);
			return 1;
		}
	}
	draw_triangle(&triangle, fp);
	if(info) {
		print_info(&triangle, fp);
	}
	if(fp != NULL) fclose(fp);
	return 0;
}
```
