#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEAMSIZE 10
#define TYPE_BATSMAN       1
#define TYPE_BOWLER        2
#define TYPE_ALLROUNDER    3
#define TYPE_WICKETKEEPER  4

struct _players_t{
	char *name;
	int type;
} players[TEAMSIZE];

unsigned char secret_player[32];

void addplayer()
{
	int i=0, typei;
	char *p = (char *) malloc(16);
	char type[2];

	printf("Enter player name\n");
	gets(p);

	printf("Enter player type\n");
	printf("(Enter 1 for batsman, 2 for bowler, 3 for all rounder, or 4 for wicketkeeper\n");

	gets(type);
	typei = atoi(type);
	if (typei < 1 || typei > 4){
		printf("Invalid type... player not added\n");
	}

	while(i != TEAMSIZE){
		if(players[i].type == 0){
			players[i].name = p;
			players[i].type = typei;
			p = NULL;
			break;
		}
		i++;
	}
	if (p != NULL){
		printf("Team full... player not added\n");
	}
}

void printplayers()
{
	int i, j=1;
	char type[16];

	for(i=0; i<TEAMSIZE; ++i){
		switch(players[i].type){
		case TYPE_BATSMAN:      strcpy(type, "Batsman"); break;
		case TYPE_BOWLER:       strcpy(type, "Bowler");  break;
		case TYPE_ALLROUNDER:   strcpy(type, "All Rounder"); break;
		case TYPE_WICKETKEEPER: strcpy(type, "Wicketkeeper"); break;
		default: players[i].type = 0;
		}
		if (players[i].type != 0){
			printf("%d %s (%s) %p\n", j++, players[i].name, type, players[i].name);	
		}
	}
}

void removeplayer()
{
	char n[2];
	int ni;

	printf("Enter player number to remove : ");
	gets(&n);
	ni = atoi(n)-1;
	if (ni >= TEAMSIZE){
		printf("Invalid number\n");
		return;	
	}

	free(players[ni].name);
	players[ni].type = 0;
}

char mainmenu()
{
	char end=0;
	char option;

	while(!end){
		printf("....................\n");
		printf("[a]dd a player\n");
		printf("[r]emove a player\n");
		printf("[p]rint team\n");
		printf("e[x]it program\n");
		gets(&option);


		switch(option){
		case 'a': addplayer(); break;
		case 'r': removeplayer(); break;
		case 'p': printplayers("p\n"); break;
		case 'x': printf("That's all folks!\n"); end=1; break;
		default : printf("Invalid option\n"); break;
		}
	}
	return option;
}


int main(int argc, char **argv)
{
	char name[10];
	printf("-----------------------------------\n");
	printf("   Build your dream team\n\n");
	printf("-----------------------------------\n");
	printf("Enter the name of your team\n");
	gets(name);


	mainmenu();
	printf("My Secret Player is %s\n", secret_player);
}

