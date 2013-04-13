//	Copyright (C) 2007, 2008, 2012 Vaptistis Anogeianakis <nomad@cornercase.gr>
/*
 *	This file is part of Packman.
 *
 *	Packman is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	Packman is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with Packman.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

#define MAXROWS 		11
#define MAXCOLS 		13
#define BRICK   		219
#define DOT				250
#define DIAMOND 		4
#define DOT_SCORE		1
#define DIAMONT_SCORE	20
typedef struct point_tag Point;
struct point_tag
{
	int row;
	int col;
};

static unsigned char level[MAXROWS][MAXCOLS];
Point pacman;
int score=0;
int moves=0;

void initialize_level(void);
void redraw_level(void);
void draw_line(Point p1,Point p2);

int main()
{
	int c;
	
	initialize_level();
	redraw_level();
	
	while(1)
	{
		if((c=getch())==224)
			if((c=getch())==72){
				if(level[pacman.row-1][pacman.col]!=BRICK)
				{
					if(level[pacman.row-1][pacman.col]==DOT)
						score+=DOT_SCORE;
					else if(level[pacman.row-1][pacman.col]==DIAMOND)
						score+=DIAMONT_SCORE;
					moves+=1;
					level[pacman.row-1][pacman.col]=1;
					level[pacman.row][pacman.col]=' ';
					pacman.row-=1;
					redraw_level();
					continue;
				}
			}
			else if(c==77){
				if(level[pacman.row][pacman.col+1]!=BRICK)
				{
					if(level[pacman.row][pacman.col+1]==DOT)
						score+=DOT_SCORE;
					else if(level[pacman.row][pacman.col+1]==DIAMOND)
						score+=DIAMONT_SCORE;
					moves+=1;
					level[pacman.row][pacman.col+1]=1;
					level[pacman.row][pacman.col]=' ';
					pacman.col+=1;
					redraw_level();
					continue;
				}
			}
			else if(c==80){
				if(level[pacman.row+1][pacman.col]!=BRICK)
				{
					if(level[pacman.row+1][pacman.col]==DOT)
						score+=DOT_SCORE;
					else if(level[pacman.row+1][pacman.col]==DIAMOND)
						score+=DIAMONT_SCORE;
					moves+=1;
					level[pacman.row+1][pacman.col]=1;
					level[pacman.row][pacman.col]=' ';
					pacman.row+=1;
					redraw_level();
					continue;
				}
			}
			else if(c==75){
				if(level[pacman.row][pacman.col-1]!=BRICK)
				{
					if(level[pacman.row][pacman.col-1]==DOT)
						score+=DOT_SCORE;
					else if(level[pacman.row][pacman.col-1]==DIAMOND)
						score+=DIAMONT_SCORE;
					moves+=1;
					level[pacman.row][pacman.col-1]=1;
					level[pacman.row][pacman.col]=' ';
					pacman.col-=1;
					redraw_level();
					continue;
				}
			}
		putchar('\a');
	}
	system("PAUSE");
	return 0;
}

void redraw_level(void)
{
	unsigned char *p,*end;
	int c;
	
	system("CLS");
	printf("score:%7d\tmoves:%7d\ttime:%7.2f\n\n",score,moves,(double)clock()/CLOCKS_PER_SEC);
	for(c=0,p=(unsigned char*)level,end=(unsigned char*)level+MAXROWS*MAXCOLS;p<end;p++)
	{
		putchar(*p);
		c++;
		if(c==MAXCOLS)
		{
			putchar('\n');
			c=0;
		}		
	}
}

void initialize_level(void)
{
	Point p1,p2;
	unsigned char *p,*end;
	
	for(p=(unsigned char*)level,end=(unsigned char*)level+MAXROWS*MAXCOLS;p<end;p++)
	{
		*p=DOT;
	}
	
	p1.row=0;
	p1.col=0;
	p2.row=0;
	p2.col=MAXCOLS-1;
	draw_line(p1,p2);
	p2.row=MAXROWS-1;
	p2.col=0;
	draw_line(p1,p2);
	p1.row=MAXROWS-1;
	p2.col=MAXCOLS-1;
	draw_line(p1,p2);
	p1.row=0;
	p1.col=MAXCOLS-1;
	p2.row=MAXROWS-1;
	p2.col=MAXCOLS-1;	
	draw_line(p1,p2);
	/* end of frame drawing. */
	
	p1.row=2;
	p2.row=2;
	p1.col=2;
	p2.col=5;
	draw_line(p1,p2);
	p1.col=7;
	p2.col=10;
	draw_line(p1,p2);
	p1.row=8;
	p2.row=8;
	p1.col=2;
	p2.col=5;
	draw_line(p1,p2);
	p1.col=7;
	p2.col=10;
	draw_line(p1,p2);
	
	p1.row=2;
	p2.row=4;
	p1.col=2;
	p2.col=2;
	draw_line(p1,p2);
	p1.row=6;
	p2.row=8;
	draw_line(p1,p2);
	p1.row=2;
	p2.row=4;
	p1.col=10;
	p2.col=10;
	draw_line(p1,p2);
	p1.row=6;
	p2.row=8;
	draw_line(p1,p2);

	p1.row=4;
	p2.row=4;
	p1.col=4;
	p2.col=5;
	draw_line(p1,p2);
	p1.col=7;
	p2.col=8;
	draw_line(p1,p2);
	p1.row=6;
	p2.row=6;
	p1.col=4;
	p2.col=5;
	draw_line(p1,p2);
	p1.col=7;
	p2.col=8;
	draw_line(p1,p2);
	level[1][1]=DIAMOND;
	level[1][11]=DIAMOND;
	level[9][1]=DIAMOND;
	level[9][11]=DIAMOND;
	level[5][6]=1;
	pacman.row=5;
	pacman.col=6;
}

void draw_line(Point p1,Point p2)
{
	unsigned char *p,*end;
	
	if(p1.row==p2.row)
		for(p=&level[p1.row][p1.col],end=p+(p2.col-p1.col+1);p<end;p++)
		{
			*p = BRICK;
		}
	else if(p1.col==p2.col)
		for(p=&level[p1.row][p1.col],end=p+(p2.row-p1.row+1)*MAXCOLS;p<end;p+=MAXCOLS)
		{
			*p = BRICK;
		}
}

