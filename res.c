#include <stdio.h>
#include <stdio.h>
#include <time.h>

void reserve_room();
void list_rooms();
void cancel_room();

main(int argc, char **argv)
{
  int i, j, k, l, n, m, status;

  char name[80], *time_string, c;

  time_t *t;
  struct tm *tp;

  FILE *fp;

  t = (time_t*)malloc(sizeof(time_t));
  tp = (struct tm*)malloc(sizeof(struct tm));


  time(t);
  tp= localtime(t);
  time_string=asctime(tp);
  printf("%s", time_string);

  
  printf("What is your name ?");
  scanf("%s", &name);

  time(t);
  tp= localtime(t);
  time_string=asctime(tp);
  printf("%s", time_string);

  status=1;
  while(status==1)
    {
      printf("You can [r]eserve a room, [c]ancel a reservation, [l]ist all reservations, [q]quit.\n"); 
      printf("==> ");

      c=getchar();

      switch (c) {
      case 'q': status=0; break;
      case 'r': (void)reserve_room(); break;
      case 'c': (void)cancel_room(); break;
      case 'l': (void)list_rooms(); break;
      }

    }
  printf("Bye.\n");  

}


void list_rooms()
{
  FILE *fp;
  char word_in_file[80];

  if((fp=fopen("room.data","r"))==NULL)
    {
      printf("Couldn't open rooms.data for reading.\n");
    }
  else
    {
      while(strcmp("----", word_in_file)!=0)
	{
	  fscanf(fp,"%s", &word_in_file);
	  if((strcmp(word_in_file, "----")!=0)&&(strcmp(word_in_file, "|")!=0)&&(strcmp(word_in_file, "+")))
	    printf(" %s", word_in_file);
	  if(strcmp(word_in_file, "|")==0)
	    printf("\n");	  
	}
      fclose(fp);  
    }
}

void reserve_room()
{
  FILE *fp;
  char c;
  char beg_time[80], end_time[80];

  printf("Which room would you like to reserve (a, b, or c)?\n=>");
  c=getchar();

  printf("Beginning time: ?\n=>");
  scanf("%s", &beg_time);
  printf("Ending time: ?\n=>");
  scanf("%s", &end_time);
}

void cancel_room()
{
  int n, i, j, line_number;
  FILE *fp;
  char line[80];
  char all_lines[10][80];

  list_rooms();

  printf("Which reservation would you like to cancel?\n=>");
  scanf("%d", n);  

  if((fp=fopen("room.data", "r"))==NULL)
    printf("Couldn't open room.data for reading.\n");
  else
    {
      i=1;
      while(strcmp(line,"----")!=0)
	{
	  fgets(line, 80, fp);
	  getchar();
	  sscanf(line,"%d", &line_number);
	  if(line_number!=n)
	    strcpy(all_lines[i++], line);
	}
      fclose(fp);

      if((fp=fopen("room1.data", "w"))==NULL)
	printf("Couldn't open room.data for writing.\n");
      else
	{
	  for(j=1;j<i;j++)	  
	    fputs(all_lines[j], fp);
	  fputs("----", fp);
	  fclose(fp);
	}
    }
}
