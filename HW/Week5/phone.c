#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SOURCE "PhoneDB.txt"
#define DEST "PhoneDB.dat"
#define MAX_LEN 80
#define BLOCK 10
#define PAGE 25
#define DIV ' '

//fflush
void clear () {
  while(getchar() != '\n');
}

//Force input value to be int
int mustBeInt () {
  int n;
  while(!scanf("%d", &n)) {
    clear();
    printf("Invalid input, enter again: ");
  }

  return n;
}

typedef struct {
  char model[30];
  int memory;
  float size;
  int price;
} phone;

phone parseLine(FILE *read) {
  phone ph;
  char *line = (char *) malloc(MAX_LEN * sizeof(char));
  if (line == NULL) {
    printf("Memory allocation failed\n");
    ph.price = -1;
    return ph;
  }

  if (fgets(line, MAX_LEN, read) == NULL) {
    ph.price = -1;
    return ph;
  }

  int l = 0;
  char *p_start = line;
  char *p_end = NULL;
  while ((p_end = strchr(p_start, DIV)) != NULL) {
    *p_end = '\0';

    // Do sth with the string p_start
    switch (l) {
      case 0:
        strcpy(ph.model, p_start);
        break;
      case 1:
        ph.memory = atoi(p_start);
        break;
      case 2:
        ph.size = atof(p_start);
        break;
    }

    l++;
    p_start = p_end + 1;
  }

  // Do sth with the string p_start
  *(p_start + strlen(p_start) - 1) = '\0';
  ph.price = atoi(p_start);

  // Done
  free(line);
  return ph;
}

// Text to dat
void text2dat() {
  FILE *src, *dest;
  if ((src = fopen(SOURCE, "r")) == NULL) {
    printf("Cannot open %s\n", SOURCE);
    return;
  }

  if ((dest = fopen(DEST, "w+b")) == NULL) {
    printf("Cannot open %s\n", DEST);
    return;
  }

  int l = 0;
  phone *list = (phone *) malloc(sizeof(phone));
  if (list == NULL) {
    printf("Memory allocation failed\n");
    return;
  }

  // Parse line in file to get data
  phone temp;
  while (1) {
    temp = parseLine(src);

    // Break if end of file
    if (temp.price == -1) {
      break;
    }

    // Increase length, realloc and add to list
    l++;
    list = (phone *) realloc(list, l * sizeof(phone));
    if (list == NULL) {
      printf("Memory reallocation failed\n");
      return;
    }

    list[l - 1] = temp;
  }

  for (int x = 0; x < l; x++) {
    printf(
      "%-30s\t%d GB\t%.2f\"\t%.d VND\n",
      list[x].model, list[x].memory, list[x].size, list[x].price
    );
  }

  // Write to dest file
  fwrite(list, sizeof(phone), l, dest);
  printf("\n%s created\n", DEST);

  free(list);
  fclose(src);
  fclose(dest);
}

// Read .dat file
void readDat() {
  // Open file
  FILE *f;
  if ((f = fopen(DEST, "rb")) == NULL) {
    printf("Cannot open %s\n", DEST);
    return;
  }

  // Choose print mode
  int mode, x, num, page = 0;
  printf("Please choose printing mode:\n");
  printf("- Print all: 0\n");
  printf("- Print n phones from the beginning of the list: n\n");
  printf("- print n phones from the end of the list: -n\n");
  printf("\nYour choice: ");
  mode = mustBeInt();
  getchar();

  // Print all
  if (mode == 0) {
    phone *list = (phone *) malloc(BLOCK * sizeof(phone));
    if (list == NULL) {
      printf("Memory allocation failed\n");
      return;
    }

    while (!feof(f)){
      num = fread(list, sizeof(phone), BLOCK, f);
      for (x = 0; x < num; x++) {
        printf(
          "%-30s\t%d GB\t%.2f\"\t%.d VND\n",
          list[x].model, list[x].memory, list[x].size, list[x].price
        );

        page++;
        if (page >= PAGE) {
          printf("(Press ENTER to see next page)\n");
          getchar();
          system("clear");
          page = 0;
        }
      }
    }
  };

  // Print one part
  if (mode < 0) {
    fseek(f, mode * sizeof(phone), SEEK_END);
    mode *= -1;
  }

  phone *list = (phone *) malloc(mode * sizeof(phone));
  if (list == NULL) {
    printf("Memory allocation failed\n");
    return;
  }

  for (x = 0; x < mode; x++) {
    num = fread(list, sizeof(phone), 1, f);
    if (num == 0) break;
    printf(
      "%-30s\t%d GB\t%.2f\"\t%.d VND\n",
      list[0].model, list[0].memory, list[0].size, list[0].price
    );

    if (page >= PAGE) {
      printf("(Press ENTER to see next page)\n");
      getchar();
      system("clear");
      page = 0;
    }
  }

  free(list);
  fclose(f);
}

void wait () {
  printf("\nEnter anything to return to menu: ");

  //Wait for user to enter anything
  getchar();
}

// Search
void search(int byModel) {
  int num, x, page;
  char man[20], model[30];
  if (byModel) {
    printf("Model: ");
    scanf("%[^\n]", model);
  } else {
    printf("Manufacturer: ");
    scanf("%[^\n]", man);
  }

  getchar();

  // Open file
  FILE *f;
  if ((f = fopen(DEST, "rb")) == NULL) {
    printf("Cannot open %s\n", DEST);
    return;
  }

  phone *list = (phone *) malloc(BLOCK * sizeof(phone));
  if (list == NULL) {
    printf("Memory allocation failed\n");
    return;
  }

  while (!feof(f)){
    num = fread(list, sizeof(phone), BLOCK, f);
    for (x = 0; x < num; x++) {
      if (byModel) {
        if (strcmp(list[x].model, model) == 0) {
          printf(
            "%-30s\t%d GB\t%.2f\"\t%.d VND\n",
            list[x].model, list[x].memory, list[x].size, list[x].price
          );

          break;
        }
      } else {
        if (strstr(list[x].model, man) != NULL) {
          printf(
            "%-30s\t%d GB\t%.2f\"\t%.d VND\n",
            list[x].model, list[x].memory, list[x].size, list[x].price
          );

          page++;
          if (page >= PAGE) {
            printf("(Press ENTER to see next page)\n");
            getchar();
            system("clear");
            page = 0;
          }
        }
      }
    }
  }

  free(list);
  fclose(f);
}

	   
int main()
{
  int choice;
  do
    {
      system("clear");
      printf("Remember to create a .dat file using function 1 before using others functions.\n");

      printf("Welcome to phoneFinder. How can I help you?\n");       // Application menu
      printf("\t1: Import DB From Text.\n\t2: Import From DB.\n\t3: Print All Your Favourite Manufacturer Model In DB.\n\t4: Find Your Dream Phone.\n\t5: Exit.\n");
      printf("Your choice: ");
      scanf("%d", &choice);

      switch(choice)                           // choice handler
	{
	case 1:
	  printf("\tText to .dat\n\n");
	  text2dat();
	  //Done
	  wait();	  
	  break;
	case 2:
	printf("\tRead from db\n\n");
        readDat();
        //Done
        wait();
	  break;
	case 3:
	  //Clear screen
	  system("clear");
	  printf("\tPrint all phones of a manufacturer\n\n");
	  search(0);
	  //Done
	  wait();
	  break;
	case 4:
	  system("clear");
	  printf("\tSearch phone\n\n");
	  search(1);
	  //Done
	  wait();
	  break;
	case 5:
	  printf("Bye Bye! Thank you for choosing our service.\n");
	  break;
	default:
	  printf("Wrong input! Please enter a positive and less than 6 integer number. The menu will be shown again.\n");
	  break;
	}
     }while (choice != 5);
  system("clear");
  return 0;
}
