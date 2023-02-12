#include<iostream>
#include<graphics.h>
#include<conio.h>
#include<dos.h>
#include<time.h>
#include<stdio.h> 

#define ScWidth 1400
#define ScHeight 700
#define OpWidth 400
#define SPACEBAR 32

using namespace std;

// Global Variables
char option, txtScore[5];
int score = 0; 

// Enemy Variables
// Enemy (x, y, height, type)
int Enemy[5][4] = { {0,0,0,0}, {0,0,0,0}, {0,0,0,0}, {0,0,0,0} };
// ei-Enemy Index, eGap-Enemy Gap, ew-Enemy Width, eStep-Enemy Step
int ei = 1, eGap = 100, ew = 20, eStep = 12, NoEnemies = 5;

// Player Variables
// px-Player X, py-Player Y, pSize-Player Size, pStep-Player Step
int px = (ScWidth-400)/2, py = 200, pSize = 40;

// Line Variables
int linex = px+pSize, liney = 400;


void GameOver(){
	cleardevice(); // clear screen
	
	setcolor(WHITE);
	// Print Game Over Text
	settextstyle(4,0,9);
	outtextxy(300,300,"Game Over");

	settextstyle(4,0,2);
	outtextxy(500,420,"Press any key to quit...");
	getch();
	score = 0; // reset score
} 
//Drawing Triangle for bottom of nail
void DrawTriangleDown(int x1, int y1, int x2, int y2){
	fillpoly(4, new int[8]{x1, y1, x2, y1, (x1+x2)/2, y2, x1, y1} );
}
// Drawing Nail
void DrawNail(int i){
	// Drawing head of nail
	bar(Enemy[i][0]-ew/2, Enemy[i][1]-ew, Enemy[i][0]+ew+ew/2, Enemy[i][1]);
	// Drawing bar of nail
	bar(Enemy[i][0], Enemy[i][1], Enemy[i][0]+ew, Enemy[i][1]+100);
	// Drawing sharp bottom edge of nail
	DrawTriangleDown(Enemy[i][0], Enemy[i][1]+100,Enemy[i][0]+ew, Enemy[i][1]+100+ew);
}
void DrawPlayer(){
	// Draw Player  
	setcolor(WHITE);
	setfillstyle(1,WHITE);
	bar(px-pSize/2,py-pSize*2,px+pSize+pSize/2,py);
	bar(px,py,px+pSize,py+pSize);
}

// Checking if player hit red nail or blue nail
int PlayerHitEnemy(){
	
	for(int i=0; i<ei; i++){
		if( px+pSize >= Enemy[i][0]-ew && px+pSize <= Enemy[i][0]+ew ){
			if( Enemy[i][3]==1 ){
				  return -2;
			}else{
				  score++;
				  return i;	
			}
		}
		if( px >= Enemy[i][0] && px <= Enemy[i][0]+ew ){
			if( Enemy[i][3]==1 ){
				  return -2;
			}else{
				  score++;
				  return i;	
			}
		}
		if( px+pSize/2 >= Enemy[i][0] && px+pSize/2 <= Enemy[i][0]+ew ){
			if( Enemy[i][3]==1 ){
				  return -2;
			}else{
				  score++;
				  return i;	
			}
		}
	}
	return -1;
}

int main(){
	srand((unsigned) time(0));
		
	int gd = DETECT, gm, err, tmp;
	initgraph( & gd, & gm, "C:\\tc\\bgi");
    
	
	// Generate First Enemy
	Enemy[0][0] = ScWidth-OpWidth; // set Initial X Pos of Enemy
	Enemy[0][1] = liney-100; // generate random y position of enemy
	Enemy[0][2] = 100; // set height of enemy
	
	while(1){
		setcolor(WHITE);
		// draw borders
		rectangle(0,0,ScWidth-OpWidth,ScHeight);
		rectangle(ScWidth-OpWidth,0,ScWidth,ScHeight);
		
		// draw Line
		line(0,liney,ScWidth-OpWidth,liney );
		
		// print score
		// itoa function converts number to character array
		settextstyle(4,0,9);
		if( score<10 )
			outtextxy(ScWidth-270, 250, itoa(score,txtScore,10));
		else if( score>=10 )
			outtextxy(ScWidth-320, 250, itoa(score,txtScore,10));
		
		settextstyle(4,0,1);
		outtextxy(ScWidth-375, 500, "Use Spacebar to hammer"); 
		
		//Draw Enemies
		for(int i=0; i<ei; i++){
			 
			//Draw Red or Blue Nail
			if( Enemy[i][3] == 0 ){
				setcolor(LIGHTBLUE);
	  		    setfillstyle(1, LIGHTBLUE);
			}else{
				setcolor(LIGHTRED);
	  		    setfillstyle(1, LIGHTRED);	
			}
			DrawNail(i); 
			
			Enemy[i][0] -= eStep; // update enemy position 
		 	
 			// if enemy covers 1/4 distance generate new enemy
			if( Enemy[i][0] <= 820 && Enemy[i][0] > 820-eStep ){
				if( ei < NoEnemies ){// generate enemy if enemies are less than total enemies
					ei++; // increment enemy index
					break;
				}
			}
			
			// if enemy goes through left border of screen
			if( Enemy[i][0] < 0 ){
				Enemy[i][0] = ScWidth-OpWidth; //reset enemy x postion
				Enemy[i][3] = rand()%2; // generate random enemy type
				// for even enemies generate random enemy
				Enemy[i][1] = liney-100;
				Enemy[i][2] = pSize;
			} 
		} 
		
		if(kbhit()){ // if any key is pressed
			option = getch(); // catch character in options variable
			if(option == SPACEBAR){ // if spacebar is pressed
				int tmpEi = PlayerHitEnemy();
				if( tmpEi == -2 ){ // if player hit red nail
					GameOver();
					break;
				}
				if( tmpEi != -1 ){ // if player hit blue nail
					Enemy[tmpEi][1] += 100;
				}
				py += 200;// hit hammer down
				DrawPlayer(); 
				delay(200);
				py -= 200; // reset hammer position
			}
		}
  		
		DrawPlayer();	
		 
		delay(20);
		cleardevice();
	}
	 
	closegraph();
}
