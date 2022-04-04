#include <stdio.h>
#include <string.h>

char buffer[50000];
struct line
{
	int x1;
	int x2;
	int y1;
	int y2;
};

struct line myLines[500];

int main()
{
	FILE *f;
	char fileName[200];
	char arrayName[50];
	char outputFileName[50];
	
	printf("Unesi ime datoteke labirinta (mora biti u istom folderu kao i ovaj file!):\n");
	scanf("%s", fileName);
	printf("Unesi ime arraya (max 50 znakova!):\n");
	scanf("%s", arrayName);
	
	f = fopen(fileName, "r");
	
	if (f != NULL)
	{
		int i = 0;
		int c = 0;
		int x1, y1, x2, y2;
		char* needle = NULL;
		printf("File opened succ!\nReading file...\n");
		
		while(c != EOF)
		{
			c = fgetc(f);
			buffer[i++] = c;
		};
		
		buffer[i] = 0;
		needle = strstr(buffer, "<line x1");
		
		i = 0;
		while(needle != NULL)
		{
			sscanf(needle, "<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" />\n", &(myLines[i].x1), &(myLines[i].y1), &(myLines[i].x2), &(myLines[i].y2));
			needle = strstr(needle + 1, "<line x1");
			i++;
		}
		fclose(f);
		
		sprintf(outputFileName, "%s.h", arrayName);
		f = fopen(outputFileName, "w");
		
		if (f != NULL)
		{
			fprintf(f, "const myline_t %s[] = {", arrayName);
			for (int n = 0; n < i; n++)
			{
				fprintf(f, "{%d, %d, %d, %d}", myLines[n].x1, myLines[n].y1, myLines[n].x2, myLines[n].y2);
				if (n != (i - 1)) fprintf(f, ", ");
			}
			fprintf(f, "};\n");
			printf("Gotovo! :)");
		}
	}
	else
	{
		printf("Nije moguce otvoriti file... :(");
	}
	
	return 0;
}
