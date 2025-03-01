#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

/* structure for the triangle */
typedef struct
{
	int tall;
	char chr;
	int color;
	char name[32];
	char filename[32];
}TRIANGLE_T;

enum {false, true};

/* set default values */
enum
{
	tall_default = 15,
	chr_default = '#',
};

/* set colors */
enum
{
	color_red = 31,
	color_green = 32,
	color_yellow = 33,
	color_blue = 34,
	color_purple = 35,
	color_cyan = 36,
	color_white = 37,
	color_default = 0,
};

void draw_triangle(TRIANGLE_T *triangle, FILE *fp)
{
	int n = 1;
	int t = triangle->tall;
	if(fp != NULL) {
		fprintf(fp, "\033[%dm", triangle->color);
	}
	printf("\033[%dm", triangle->color);
	for(int i = 0; i < triangle->tall; i++) {
		for(int s = 0; s < t; s++) {
			putchar(' ');
			if(fp != NULL) fputc(' ', fp);
		}
		for(int k = 0; k < n; k++) {
			putchar(triangle->chr);
			if( fp != NULL) fputc(triangle->chr, fp);
		}
		t--;
		n += 2;
		putchar('\n');
		if(fp != NULL) fputc('\n', fp);
	}

	/* reset color */
	printf("\033[%dm", color_default);
}

void print_info(TRIANGLE_T *triangle, FILE *fp)
{
	puts("");
	printf("Triangle info:\n");
	printf("name:        %s\n", triangle->name); 
	printf("tall:      %d\n", triangle->tall); 
	printf("character:   %c\n", triangle->chr); 
	if(fp != NULL) {
		printf("file:      %s\n", triangle->filename);

		/* reset color */
		fprintf(fp, "\033[%dm", color_default);

		fprintf(fp, "Triangle info:\n");
		fprintf(fp, "name:        %s\n", triangle->name); 
		fprintf(fp, "tall:      %d\n", triangle->tall); 
		fprintf(fp, "character:   %c\n", triangle->chr);
		fprintf(fp, "file:        %s\n", triangle->filename);
	}
}

int main(int argc, char *argv[])
{
	TRIANGLE_T triangle = {0};
	triangle.tall = tall_default;
	triangle.chr = chr_default;
	triangle.color = color_default;
	FILE *fp = NULL;
	int info = false;
	int opt;
	while((opt = getopt(argc, argv, "t:n:f:c:C:rilh")) != -1) {
		switch(opt) {
			case 't':
				triangle.tall = atoi(optarg);
				if(triangle.tall == 0) {
					fprintf(stderr, "error:%s: unknown tall\n", \
					optarg);
					exit(EXIT_FAILURE);
				}
				break;
			case 'n':
				if(strlen(optarg) > sizeof(triangle.name)) {
					fprintf(stderr, "error:%s: too long.\n", \
					optarg);
					exit(EXIT_FAILURE);
				} else {
				strcpy(triangle.name, optarg);
				}
				break;
			case 'c':
				if(!strcasecmp(optarg, "red"))
					triangle.color = color_red;
				else if(!strcasecmp(optarg, "green"))
					triangle.color = color_green;
				else if(!strcasecmp(optarg, "yellow"))
					triangle.color = color_yellow;
				else if(!strcasecmp(optarg, "blue"))
					triangle.color = color_blue;
				else if(!strcasecmp(optarg, "purple"))
					triangle.color = color_purple;
				else if(!strcasecmp(optarg, "cyan"))
					triangle.color = color_cyan;
				else if(!strcasecmp(optarg, "white"))
					triangle.color = color_white;
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
					printf("Red, Green, Yellow, Blue, Purple, Cyan, White.\n");
					exit(EXIT_SUCCESS);
				}
				break;
			case 'C':
				triangle.chr = optarg[0];
				break;
			case 'f':
				strcpy(triangle.filename, optarg);
				fp = fopen(triangle.filename, "w");
				if(fp == NULL) {
					fprintf(stderr, "Failed to open %s\n", triangle.filename);
					exit(EXIT_FAILURE);
				}
				break;
			case 'r':
				srand((unsigned int)time(NULL));
				triangle.tall = rand() % 50;
				triangle.color = 30 + (rand() % 7);
				triangle.chr = 41 + (rand() % 38);
				break;
			case 'i':
				info = true;
				break;
			case 'h':
				printf("Usage:\n%s [-t|-f|-n|-c|-C] args [-i|-l|-r|-h]\n", argv[0]);
				exit(EXIT_FAILURE);
			default:
				printf("Usage:\n%s [-t|-f|-n|-c|-C] args [-i|-l|-r|-h]\n", argv[0]);
				exit(EXIT_FAILURE);
		}
	}
	draw_triangle(&triangle, fp);
	if(info) {
		print_info(&triangle, fp);
	}
	if(fp != NULL) fclose(fp);
	return 0;
}
