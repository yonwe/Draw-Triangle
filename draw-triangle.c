#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct
{
	int HEIGHT;
	int ACREAGE;
	char CHR;
	char COLOR[32];
	char NAME[32];
	char FILE_[32];
}TRIANGLE_T;

enum {false, true,};

const char *red = "\033[31m";	
const char *green = "\033[32m";
const char *yellow = "\033[33m";
const char *blue = "\033[34m";
const char *default_color = "\033[0m";

#define HEIGHT_DEFAULT 15
#define NAME_DEFAULT "NAME"
#define CHR_DEFAULT '#'

void draw_triangle(TRIANGLE_T *triangle)
{
	int file = false;
	FILE *fp = NULL;
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
	if(triangle->FILE_[0]) {
		file = true;
		fp = fopen(triangle->FILE_, "w+");
		if(fp == NULL) {
			fprintf(stderr, "Failed to open %s", triangle->FILE_);
			exit(EXIT_FAILURE);
		}
	}
	triangle->ACREAGE = (triangle->HEIGHT * triangle->HEIGHT) / 2;
	int n = 1;
	if(file) fprintf(fp, "%s", triangle->COLOR);
	printf("%s", triangle->COLOR);
	for(int i = 0; i < triangle->HEIGHT; i++) {
		for(int j = 0; j < n; j++) {
			putchar(triangle->CHR);
			putchar(' ');
			if(file) {
				fputc(triangle->CHR, fp);
				fputc(' ', fp);
			}
		}
		putchar('\n');
		if(file) fputc('\n', fp);
		n++;
	}
	if(fp) fclose(fp);
	printf("%s", default_color);
	printf("Triangle Info:\n");
	printf("NAME:	%s\n", triangle->NAME);
	printf("HEIGHT  %d\n", triangle->HEIGHT);
	printf("WIDTH  %d\n", triangle->HEIGHT);
	printf("ACREAGE  %d\n", triangle->ACREAGE);
}

int main(int argc, char *argv[])
{
	TRIANGLE_T triangle = {0};
	int opt;
	while((opt = getopt(argc, argv, "h:n:f:c:C:")) != -1) {
		switch(opt) {
			case 'h':
				triangle.HEIGHT = atoi(optarg);
				break;
			case 'n':
				strcpy(triangle.NAME, optarg);
				break;
			case 'C':
				if(!strcmp(optarg, "red"))
					strcpy(triangle.COLOR, red);
				else if(!strcmp(optarg, "green"))
					strcpy(triangle.COLOR, green);
				else if(!strcmp(optarg, "yellow"))
					strcpy(triangle.COLOR, yellow);
				else if(!strcmp(optarg, "blue"))
					strcpy(triangle.COLOR, blue);
				break;
			case 'c':
				triangle.CHR = optarg[0];
				break;
			case 'f':
				strcpy(triangle.FILE_, optarg);
				break;
			default:
				printf("ERROR:Unknown Option\n");
				exit(EXIT_FAILURE);
		}
	}
	draw_triangle(&triangle);
	return 0;
}
