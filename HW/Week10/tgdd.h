#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct dataType{
  char model[20];
  char storage[20];
  float screensize;
  char price[20];
} dataType;
dataType *parr;


int importDB(FILE *fin, FILE *fout);
int importfromDB(FILE *fin, int numLine);
void printData();
void searchModel();
dataType typehand();

phone_inf *parr; //phone array
int result;
//import DB
int importDB (FILE *fin , FILE *fout)
{
  int numLine;
  char line;
  while (!feof(fin))
    {
      if (fgetc(fin) == '\n')
	numLine++;
    }
  rewind (fin);
  parr = (phone_inf*) malloc (numLine * sizeof(phone_inf));
  for (int i = 0; i < numLine; ++i)
    {
      fscanf (fin, "%[^|]|%s|%f|%s\n", parr[i].model, parr[i].storage, &parr[i].screensize, parr[i].price);
    }
  printf ("Done.\n");
  return fwrite(parr, sizeof(phone_inf), numLine, fout);
}

//import data from  DB
int importfromDB (FILE *f, int numLine)
{
  	int result; // number of lines have been read
	parr = (phone_inf*)malloc(numLine * sizeof(phone_inf));
	result = fread(parr, sizeof(phone_inf), numLine, f);
	printf("\nRead all data success\n");
	rewind(f);
	return result;
	free(parr);
}

void printData() {
	int pageNum = 0;
	if (result < 20)
	  for (int i = 0; i < result; ++i)
	    printf("%-30s|%-3s|%-4.2f|%-8s\n", parr[i].model, parr[i].storage, parr[i].screensize, parr[i].price);
	else
	{
	  int curNum; //the line which is the end of the corresponding page
		do {
		  curNum = 20 + 20 * pageNum;
		  if (curNum >= result)
		    curNum = result;
		  printf("\n\nPage number %d\n\n", pageNum + 1);
		  for (int i = pageNum * 20; i < curNum; ++i)
		    printf("%-30s|%-3s|%-4.2f|%-8s\n", parr[i].model, parr[i].storage, parr[i].screensize, parr[i].price);
		  pageNum++;
		} while (curNum < result);
	}
}

void searchModel() {
	char s[40];
	printf("\nSearch by phone model\n");
	printf("Enter the model: ");
	while (getchar() != '\n');
	scanf("%[^\n]", s);
	printf("\nSearch result: \n");
	for (int i = 0; i < result; ++i)
		if (strstr(parr[i].model, s) != NULL)
		{
			printf("%-30s\t%-3s\t%-4.2f\t%-8s\n", parr[i].model, parr[i].storage, parr[i].screensize, parr[i].price);
		}
}

phone_inf typehand() {
	phone_inf p;
	printf("Model: ");
	while (getchar() != '\n');
	scanf("%s", p.model);
	printf("Storage(GB): "); scanf("%s", p.storage);
	printf("Screen size(inches):"); scanf("%f", &p.screensize);
	printf("Price(VND): "); scanf("%s", p.price);
	return p;
}
  
