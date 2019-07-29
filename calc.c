#include <stdio.h>
#include <dlfcn.h>
#include "complexNum.h"

void output(struct complexNum num)
{
  printf("(%f + %fi)", num.real, num.img);
}

void scan_num(struct complexNum * num, char str[])
{
  printf("Enter the real part of the %s number\n> ", str);
  scanf("%f",&num->real);
  getchar();
  printf("Enter the imaginary part of the %s number\n> ", str);
  scanf("%f",&num->img);
  getchar();
}

void main()
{ 
  int i, k = 4, j = 0, n = 0;
  _Bool temp;
  void * lib[4];
  char * name[4];
  struct complexNum one, two, num;
  void (* func[4])(struct complexNum *, struct complexNum *, struct complexNum *);
  char operation[4];
  int menu;
  char path[50] = "./libs/";
  char library_name[40];
  do 
  {
    for (i = 0; i <= 40; i++)
    {
      library_name[i] = '\0';
    }
    printf("Enter library name\n");
    printf("to finish entering libraries, enter '0'\n> ");
    scanf("%s", (char *)&library_name);
    getchar();
    if (library_name[0] == '0' && library_name[1] == '\0')
    {
      k = 0;
    }
    else
    { 
      for (i = 0; i <= 40; i++)
      {
        path[i + 7] = library_name[i];
      }
      if ((lib[j] = dlopen(path, RTLD_LAZY)) > 0)
      {
        k--; j++; n++;
        printf("Library '%s' successfully added\n", path);
      }
      else
      {
        printf("Error: %s\n",dlerror());
      }
    }
  }while(k > 0);
  for (i = 0; i < n; i++)
  {
    name[i] = dlsym(lib[i], "name");
    func[i] = dlsym(lib[i], name[i]);
    switch (name[i][0])
    {
      case 'A':
      {
        operation[i] = '+';
        break;
      }
      case 'S':
      {
        operation[i] = '-';
        break;
      }
      case 'M':
      {
        operation[i] = '*';
        break;
      }
      case 'D':
      {
        operation[i] = '/';
        break;
      }
      default:
      {
        break;
      }
    }
  }
  while(1)
  {
    printf("MENU\n");
    for (i = 0; i < n; i++)
    {
      printf("%d. %s\n",i + 1, name[i]);
    }
    printf("%d. Exit\n", i + 1);
    printf("Enter the number of\n");
    printf("the selected menu item\n> ");
    scanf("%d", &menu);
    getchar();
    if (menu > 0 && menu <= n + 1)
    {
      if (menu == n + 1) return;
      scan_num(&one, "first");
      scan_num(&two, "second");
      func[menu - 1](&num, &one, &two);
      output(one);
      printf(" %c ", operation[menu - 1]);
      output(two);
      printf(" = ");
      output(num);
      printf("\nEnter 'Enter' to continue\n");
      getchar();
    }
    else
    {
      printf("Error: Invalid menu item entered\n");
    }
  }
  for (i = 0; i < n; i++)
  {
    dlclose(lib[i]);
  }
}
