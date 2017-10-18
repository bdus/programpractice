/*************************************************************************
	> File Name: unistdtry.c
	> Author: 
	> Mail: 
	> Created Time: 2017年08月25日 星期五 15时16分33秒
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
int main(int argc, char** argv)
{
   int ch;
   opterr = 0;
   while((ch = getopt(argc, argv, "p:d:")) != -1)
   switch(ch)
   {
      case 'p':
         printf("path='%s'\n", optarg);  break;
      case 'd':
         printf("dest:%s\n",optarg);  break;
      default:
         printf("other option :%c\n", ch);
   }
   printf("optopt +%c\n", optopt);
}

