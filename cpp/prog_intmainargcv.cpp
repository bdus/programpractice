/*************************************************************************
	> File Name: prog_intmainargcv.cpp
	> Author: 
	> Mail: 
	> Created Time: 2017年08月25日 星期五 13时43分00秒
 ************************************************************************/

//#include<iostream>
#include<stdio.h>
#include<string.h>

//using namespace std;

extern void hpet_open_close(int, const char **);
extern void hpet_info(int, const char **);
extern void hpet_poll(int, const char **);
extern void hpet_fasync(int, const char **);
extern void hpet_read(int, const char **);

struct hpet_command {
	char		*command;
	void		(*func)(int argc, const char ** argv);
} hpet_command[] = {
	{
		"open-close",
		hpet_open_close
	},
	{
		"info",
		hpet_info
	},
	{
		"poll",
		hpet_poll
	},
	{
		"fasync",
		hpet_fasync
	},
};

int main(int argc, const char ** argv)
{
	unsigned int	i;

	argc--;
	argv++;

	if (!argc) {
		fprintf(stderr, "-hpet: requires command\n");
		return -1;
	}


	for (i = 0; i < (sizeof (hpet_command) / sizeof (hpet_command[0])); i++)
		if (!strcmp(argv[0], hpet_command[i].command)) {
			argc--;
			argv++;
			fprintf(stderr, "-hpet: executing %s\n",
				hpet_command[i].command);
			hpet_command[i].func(argc, argv);
			return 0;
		}

	fprintf(stderr, "do_hpet: command %s not implemented\n", argv[0]);

	return -1;
}

void hpet_open_close(int argc, const char **argv)
{
	puts("hpet_open_close");
}

void hpet_info(int argc, const char **argv)
{
	puts("hpet_info");
}

void hpet_poll(int argc, const char **argv)
{
	puts("hpet_poll" );
}
void hpet_fasync(int argc, const char **argv)
{
	puts("hpet_fasync");
}
