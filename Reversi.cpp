#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <graphics.h>
#include <time.h>
#include <math.h>
#include <windows.h>
#include <MMsystem.h>
#include <string.h>



#define SCREEN_HEIGHT 500 //設定遊戲視窗高度 
#define SCREEN_WIDTH 500 //設定遊戲視窗寬度
#define GRID_NUM 8 //設定遊戲方陣每邊格子數量 
#define LEFT_MARGINE 30 //設定左邊界 
#define TOP_MARGINE 45 //設定上邊界 
#define INIT_SPEED  80 //設定初始速度 
#define PLAYONE_COLOR  BLUE //設定玩家一顏色
#define PLAYTWO_COLOR  RED //設定玩家二顏色
#define PLAYTIME 10;



//宣告棋子種類 
enum Chess {
	EMPTY, //空白 
	PLAY_ONE, //玩家一 
	PLAY_TWO //玩家二 
};

enum Mode {
	PLAYER,
	AI_FIRST,
	AI_SECOND,
	AI_BOTH 
};

//宣告棋子位子 
struct Location{
	int row; 
	int col;
};

//宣告紀錄落子位置的節點結構 
struct Node {
	Location loc; //棋盤位置 
	struct Node *next;	//指向下一個節點 
};

//定義指向節點結構的指標變數 
typedef struct Node *NodePointer;

void openWindow(); //開啟游戲視窗 
void closeGame(); //處理遊戲結束邏輯 
void playGame(int field[][GRID_NUM]); //遊戲進行邏輯 
void initChessboard(int field[][GRID_NUM]); //初始化棋盤狀態 
Location* getChessDown(int field[][GRID_NUM], Location *focusPtr); //取得玩家落子位置 
void setChess(int field[][GRID_NUM], Location chessLoc); //設定落子 
void drawChessboard(int field[][GRID_NUM]); //繪製遊戲區域 
void printBoardState(int field[][GRID_NUM]); //印出棋盤狀態 
bool checkValidation(NodePointer list, Location loc); //檢查該位置是否為合法的落子位置 
NodePointer getValidatedLocs(int field[][GRID_NUM]); //獲得所有合法下子的所有座標節點 
NodePointer addNode(NodePointer list, Location loc); //新增合法下子的座標資訊節點
void drawValidatedLocs(NodePointer list); //標記出所有該玩家所有合法的下棋位置 
void cleanValidatedLocs(NodePointer list); //清理標記 
void doReverse(int field[][GRID_NUM], Location chessLoc); //進行黑白棋翻轉 
int reverse(int field[][GRID_NUM], Location chessLoc, bool checkOnly); //計算某下子座標所有可以翻轉的棋子數量， check_only = true 只進行計算，false 會進行棋子的翻轉 
void drawSquare(int row, int col, int color); //繪製色塊 
void drawFocus(int field[][GRID_NUM], Location focus); //繪製目標十字  
void cleanFocus(int field[][GRID_NUM], Location focus);//清除十字 
void drawCircle(int row, int col, int color); //繪製圓點 
void showGameWinMsg(); //遊戲結束訊息
void showInfo(); //顯示遊戲相關資訊 
void menu();
int menu_AI();
void entername();
void clearname();
void store_playerRecord();
int expectnum[][8]= {
					{90, -60, 10, 10, 10, 10, -60, 90}, // 0
					{-60, -80, 5, 5, 5, 5, -80, -60}, // 1
					{10, 5,   1, 1, 1, 1, 5, 10}, // 2
					{10, 5,   1, 1, 1, 1, 5, 10},  // 3
					{10, 5,   1, 1, 1, 1, 5, 10}, //4
					{10, 5,   1, 1, 1, 1, 5, 10}, //5
					{-60, -80, 5, 5, 5, 5, -80, -60}, // 6
					{90, -60, 10, 10, 10, 10, -60, 90}};// 7


Location* PLAYONE_AI(int field[][GRID_NUM], Location *focusPtr, NodePointer validated_locs);//實作電腦控制邏輯 

char key; //操作按鍵 
int speed; //移動速度 
int currentPlayer = PLAY_ONE; //設定玩家 
int modeCount = 0; //控制模式紀錄 
int totalTime = 0; //紀錄遊戲時間 
int playMode = PLAYER; // 設定控制模式，玩家模式或AI模式 
int play1Score = 0; //玩家一分數 
int play2Score = 0; //玩家二分數 
int stepCount = 0; //回合計數器 
int play1time=PLAYTIME;//剩餘時間 
int play2time=PLAYTIME;
int totalTime_2 = 0;
int bgmopen=0;
char player1name[50]="";
char player2name[50]="";
int namecount=0;
int name1count=0;
int name2count=0;
unsigned int AI_mode;



int main( )
{  	
	openWindow();
	
	
	while(TRUE){
		
		speed = INIT_SPEED;
		
		//設定遊戲場
	   	int field[GRID_NUM][GRID_NUM] = {0};
		int copyfield[GRID_NUM][GRID_NUM]={0};
		playGame(field); //進行遊戲
		if (key == '\b')
			closeGame(); //如果玩家輸入'q'離開遊戲	
		else if (key == '+'||key == '='){
			//playMode = PLAYER;
			continue;
		}
		
			 //如果玩家輸入's' 繼續遊戲 		    
	}
}

//開啟游戲視窗
void openWindow(){
	initwindow(SCREEN_WIDTH + LEFT_MARGINE * 3, SCREEN_HEIGHT + TOP_MARGINE * 3, "Backgammon");
}

//處理遊戲結束邏輯 
void closeGame(){
	exit(0);
}

//遊戲進行邏輯
void playGame(int field[][GRID_NUM]){
	menu();
	drawChessboard(field); //繪製遊戲區域 
	if(bgmopen!=1){
		PlaySound("BGM.wav",NULL,SND_FILENAME| SND_ASYNC|SND_LOOP);
		bgmopen=1;
	}
	
	totalTime =0;
	NodePointer validated_locs = NULL;
	play1Score = 0, play2Score = 0;
	stepCount = 0;
	play1time=PLAYTIME;//剩餘時間 
	play2time=PLAYTIME;
	clearname();
	
	initChessboard(field); //初始化棋盤狀態 
   	printBoardState(field); //印出棋盤狀態，用於debug使用 
   	
   	validated_locs = getValidatedLocs(field); //計算所有合法座標  
   	drawValidatedLocs(validated_locs); //在棋盤上繪製這回合合法的座標 
	   	
	Location focus = {0, 0};
	Location* chessLocPtr;
	key = 0;
	int endPoint = 0;
	int time_1=0;
	totalTime_2 = 0;
	
	while(true){

		delay(speed); //決定每回合下棋速度 

		showInfo();//顯示時間和分數資訊
		
		
		if(time_1<=0){
			time_1=clock();
		}
	
		if(key == '\b' || key == '+' || key == '='){
			playMode = modeCount % 4;
			//modeCount=0;
		}
		
		if(endPoint == 1){
			if(play1Score ==0||play2Score ==0 ||(play1Score +play2Score)== GRID_NUM * GRID_NUM){
				showInfo();
				 showGameWinMsg(); //顯示遊戲結束訊息，並等待玩家輸入選項
				 return;
			}
		}
		
		if(playMode == PLAYER){
			chessLocPtr = getChessDown(field, &focus);
			
		}else if(playMode == AI_FIRST){
			if(currentPlayer == PLAY_ONE){
				chessLocPtr = getChessDown(field, &focus);
			}
			else{
				
				chessLocPtr = PLAYONE_AI(field, &focus, validated_locs);
				
			}				
		}else if(playMode == AI_SECOND){
			if(currentPlayer == PLAY_TWO){
				chessLocPtr = getChessDown(field, &focus);
			}
			else{
				chessLocPtr = PLAYONE_AI(field, &focus, validated_locs);
			}		
		
		}else { // playMode == AI_BOTH
			chessLocPtr = PLAYONE_AI(field, &focus, validated_locs);
		}
		
		if(chessLocPtr == NULL){
			//只有輸入大小寫的a, q 和 s，系統才有反應並將輸入結果拋到外層等待處理 
			if (key == '\b' || key == '+' || key == '='){
				modeCount=0;
				return;	
			}
							
			/*else if (key == 'a' || key == 'A'){ 
				//決定是否改變模式 ，主要有玩家模式和電腦操控的AI模式 
				modeCount++;
				playMode = modeCount % 4;
				key = 0;
			}*/
			
			if (endPoint < 2)
				continue;
		}
	
		//玩家只能下在合法位置 
		if(chessLocPtr != NULL && checkValidation(validated_locs, *chessLocPtr) == false){
			continue;
		} 
		cleanValidatedLocs(validated_locs);
		//清理合法位置標記 
		
		if(chessLocPtr != NULL){
			setChess(field, *chessLocPtr);
		}
		//如果玩家按下space，就在目標十字座標繪製棋子，並改變棋盤狀態 
 
 		//如果不是賽末點，進行吃子判斷，並翻轉棋子 
		if(endPoint < 2){
			doReverse(field, *chessLocPtr);
		
		}
		
		int time_2=(clock()-time_1)/1000;
		//printf("%d",time_2);
		if(currentPlayer == PLAY_ONE){
			play1time-=time_2;
			if(play1time<=0){
				showInfo();
			    showGameWinMsg(); //顯示遊戲結束訊息，並等待玩家輸入選項
			    return;
			}
		}else{
			play2time-=time_2;
			if(play2time<=0){
				showInfo();
			    showGameWinMsg(); //顯示遊戲結束訊息，並等待玩家輸入選項
			    return;
			}
		}
		time_1=0;
		
		if(currentPlayer == PLAY_ONE){
			currentPlayer = PLAY_TWO;
			play1time=PLAYTIME;
			//printf("%d",totalTime_2);
			totalTime_2 = 0;
			stepCount++;
		}else{
			currentPlayer = PLAY_ONE;
			play2time=PLAYTIME;
			//printf("%d",totalTime_2);
			totalTime_2 = 0;
			stepCount++;
		}
		
		
		printBoardState(field);
		
		// 取得下一回合的合法位置 
		validated_locs = getValidatedLocs(field);
		//如果該回合無法獲得合法的下子位置，賽末點+1 
		if(validated_locs == NULL){
			if(currentPlayer == PLAY_TWO){
				currentPlayer = PLAY_ONE; 
				validated_locs = getValidatedLocs(field);
			}else{
				currentPlayer = PLAY_TWO;
				validated_locs = getValidatedLocs(field);
			} 
			endPoint++;
			//continue;
		}
		else{
			endPoint = 0;	
		}
		
		//連續兩回合都無法獲得合法座標，或者已經沒有可以下子的位置，遊戲結束 
		if(endPoint == 2||(play1Score + play2Score) == GRID_NUM * GRID_NUM ){
			
			showInfo();
			showGameWinMsg(); //顯示遊戲結束訊息，並等待玩家輸入選項
			return;
		}
		
		//繪製合法座標標記 
		drawValidatedLocs(validated_locs);
		printf("end point: %d\n", endPoint);
		
		
							
	}		
}

// 初始化棋盤狀態 
void initChessboard(int field[][GRID_NUM]){
	Location loc;
   	currentPlayer = PLAY_ONE;
   	loc.row = GRID_NUM/2 - 1, loc.col = GRID_NUM/2 - 1;
   	setChess(field, loc);
   	
   	currentPlayer = PLAY_TWO;
   	loc.row = GRID_NUM/2, loc.col = GRID_NUM/2 - 1;
   	setChess(field, loc);
   	
   	currentPlayer = PLAY_ONE;
   	loc.row = GRID_NUM/2, loc.col = GRID_NUM/2;
   	setChess(field, loc);
   	
   	currentPlayer = PLAY_TWO;
   	loc.row = GRID_NUM/2 - 1, loc.col = GRID_NUM/2;
   	setChess(field, loc);
   	currentPlayer = PLAY_ONE;	
}

//繪製遊戲區域，依據遊戲場矩陣設定繪製物件 
void drawChessboard(int field[][GRID_NUM]){
   	int row = 0, col = 0;
   	int startX = 0, startY = 0, endX = 0, endY = 0;
   	cleardevice(); //清理螢幕畫面 
   	int squareHeight = SCREEN_HEIGHT / GRID_NUM;
   	int squareWidth = SCREEN_WIDTH / GRID_NUM;
   	setlinestyle(SOLID_LINE, 0, 1); 
   	setcolor(YELLOW);
	for(row = 0; row <= GRID_NUM; row ++){
		startX = LEFT_MARGINE + 0 * squareWidth + 0;
		startY =  TOP_MARGINE + row * squareHeight;
		endX = startX + GRID_NUM * squareWidth;
		line(startX, startY, endX, startY);
	}
	
	for(col = 0; col <=  GRID_NUM; col++){
		startX = LEFT_MARGINE + col * squareWidth;
		startY =  TOP_MARGINE + 0 * squareHeight + 0;
		endY = startY + GRID_NUM * squareHeight;
		line(startX, startY, startX, endY);
	}
}

//列印棋盤狀態 
void printBoardState(int field[][GRID_NUM]){
	int i,j;
	
	for(i=0;i<GRID_NUM;i++){
		for(j=0;j<GRID_NUM;j++)
			printf("%d ", field[i][j]);
		printf("\n");	
	}
}

//取得玩家落子位置
Location* getChessDown(int field[][GRID_NUM], Location *focusPtr){
		  
	char keyPress;
	if(kbhit()) 
		keyPress = getch();
		
	if(keyPress == ' ' && field[focusPtr->row][focusPtr->col] == EMPTY){
		return focusPtr;
	} 
		
	cleanFocus(field, *focusPtr);
	//decide focus moving direction	
	switch(keyPress){
		case KEY_RIGHT:
			if(focusPtr->col < GRID_NUM - 1)
				focusPtr->col = focusPtr->col + 1;
			break;			
		case KEY_LEFT:
			if(focusPtr->col > 0)
				focusPtr->col = focusPtr->col - 1;
			break;		
		case KEY_UP:
			if(focusPtr->row > 0)
				focusPtr->row = focusPtr->row - 1;
			break;				
		case KEY_DOWN:
			if(focusPtr->row < GRID_NUM - 1)
				focusPtr->row = focusPtr->row + 1;
			break;				
	}
	
	drawFocus(field, *focusPtr);
	//只有輸入大小寫的a, q 和 s，系統才有反應並將輸入結果拋到外層等待處理 
	if (keyPress == 'q' || keyPress == 'Q' || keyPress == 's' || keyPress == 'S' || keyPress == 'a' || keyPress == 'A'){
		key = keyPress;
	}
	return NULL;
}

//設定落子
void setChess(int field[][GRID_NUM], Location chessLoc){
	
	if(currentPlayer == PLAY_ONE){
		drawSquare(chessLoc.row, chessLoc.col, PLAYONE_COLOR);
		play1Score++;
		if(field[chessLoc.row][chessLoc.col]==PLAY_TWO)
			play2Score--;
	}else{
		drawSquare(chessLoc.row, chessLoc.col, PLAYTWO_COLOR);
		play2Score++;
		if(field[chessLoc.row][chessLoc.col]==PLAY_ONE)
			play1Score--;		
	}
	field[chessLoc.row][chessLoc.col] = currentPlayer;
	//stepCount++;
}

//檢查該位置是否為合法的落子位置 
bool checkValidation(NodePointer list, Location loc){
	
	while(list != NULL){
		if(list->loc.row == loc.row && list->loc.col == loc.col)
			return true;
		list = list -> next;	
	}
	return false;
}

//獲得所有合法下子的所有座標節點 
NodePointer getValidatedLocs(int field[][GRID_NUM]){
	int row, col;
	NodePointer reversible_list = NULL;
	Location checkLoc;
	for(row=0; row < GRID_NUM; row++){
		for(col=0; col < GRID_NUM; col++){
			if(field[row][col] != EMPTY)
				continue;
			checkLoc.row = row, checkLoc.col = col;
			if(reverse(field, checkLoc, true) > 0){
				reversible_list = addNode(reversible_list, checkLoc);
			}		
		}
	}
	return reversible_list;
}

//新增合法下子的座標資訊節點
NodePointer addNode(NodePointer list, Location loc){
	NodePointer tail = NULL;
	NodePointer newNode = (NodePointer) malloc(sizeof(Node)); //初始化一個新節點 
	newNode -> loc = loc;
	newNode -> next = NULL;	
	if(list == NULL)
		return newNode;
	else{
		//尋找串列的尾巴 
		tail = list;
		while(tail -> next != NULL){
			tail = tail -> next;
		}
		tail -> next = newNode; //將尾巴節點連接到新節點 
		return list;
	}
}

//標記出所有該玩家所有合法的下棋位置 
void drawValidatedLocs(NodePointer list){
	
	if (list==NULL){
		printf("validated location do not exist!!\n");
		return;
	}

	printf("validated location: ");
	while(list != NULL){
		printf("(%d, %d) ",  list -> loc.row, list -> loc.col);
		
		if(currentPlayer == PLAY_ONE)
			drawCircle(list -> loc.row, list -> loc.col, PLAYONE_COLOR);
		else
			drawCircle(list -> loc.row, list -> loc.col, PLAYTWO_COLOR);
		
		list = list -> next;
	}
	printf("\n");

}

//清理標記 
void cleanValidatedLocs(NodePointer list){
	if(list == NULL){
		return;
	}
	while(list != NULL){
		drawCircle(list -> loc.row, list -> loc.col, BLACK);
		list = list -> next;
	}
	printf("\n");

}

//進行黑白棋翻轉 
void doReverse(int field[][GRID_NUM], Location chessLoc){
	reverse(field, chessLoc, false);
}

//計算某下子座標所有可以翻轉的棋子數量， check_only = true 只進行計算，false 會進行棋子的翻轉 
int reverse(int field[][GRID_NUM], Location chessLoc, bool checkOnly){
	int dirSize = 8;
	int rowDir[] = {-1, -1, -1,  0, 0,  1, 1, 1};
	int colDir[] = {-1,  0,  1, -1, 1, -1, 0, 1};
	int i, rowNext, colNext;
	int totalReversed = 0;
	Location loc;
	
	for(i = 0; i<dirSize; i++){
		rowNext = chessLoc.row;
		colNext = chessLoc.col;
		int reverseCount = 0, count = 0;
		while(true){
			rowNext += rowDir[i];
			colNext += colDir[i];		
			if(field[rowNext][colNext] == EMPTY || rowNext < 0 || colNext < 0 || rowNext > GRID_NUM-1 || colNext > GRID_NUM-1){
				break;
			} else if(field[rowNext][colNext] != currentPlayer){
				count++;
			} else if(field[rowNext][colNext] == currentPlayer){
				reverseCount = count;
				break;
			}	
		}
		
		if(reverseCount > 0 && checkOnly == false){
			int j;
			rowNext = chessLoc.row;
			colNext = chessLoc.col;
			for(j = 0; j < reverseCount; j++){
				rowNext += rowDir[i];
				colNext += colDir[i];
				loc.row = rowNext;
				loc.col = colNext;
				setChess(field, loc);
			}
		}
		
		totalReversed += reverseCount; 
	}
	return totalReversed;
}

//繪製目標十字
void drawFocus(int field[][GRID_NUM], Location focus){
	int focusX = 0, focusY = 0;
	int squareHeight = SCREEN_HEIGHT / GRID_NUM;
   	int squareWidth = SCREEN_WIDTH / GRID_NUM;
   	focusX = LEFT_MARGINE + focus.col * squareWidth + squareWidth / 2;
   	focusY =  TOP_MARGINE + focus.row * squareHeight + squareHeight / 2;
   	setlinestyle(SOLID_LINE, 0, 1); 
   	setcolor(YELLOW);
   	line(focusX -5, focusY, focusX + 5, focusY);
   	line(focusX, focusY - 5, focusX, focusY + 5);
}

//清除目標十字
void cleanFocus(int field[][GRID_NUM], Location focus){
	if(field[focus.row][focus.col] == PLAY_ONE)
		setcolor(PLAYONE_COLOR);
	else if(field[focus.row][focus.col] == PLAY_TWO)
		setcolor(PLAYTWO_COLOR);	
	else
		setcolor(BLACK);
			
	int focusX = 0, focusY = 0;
	int squareHeight = SCREEN_HEIGHT / GRID_NUM;
   	int squareWidth = SCREEN_WIDTH / GRID_NUM;
   	focusX = LEFT_MARGINE + focus.col * squareWidth + squareWidth / 2;
   	focusY =  TOP_MARGINE + focus.row * squareHeight + squareHeight / 2;
   	setlinestyle(SOLID_LINE, 0, 1); 
   	
   	line(focusX -5, focusY, focusX + 5, focusY);
   	line(focusX, focusY - 5, focusX, focusY + 5);
}

//繪製方塊
void drawSquare_ex(int row, int col, int color){
	
	int squareHeight = SCREEN_HEIGHT / GRID_NUM;
   	int SquareWidth = SCREEN_WIDTH / GRID_NUM;
	int left = 0, right = 0, bottom = 0, top = 0;
	left = LEFT_MARGINE + col * SquareWidth + 1;
   	top =  TOP_MARGINE + row * squareHeight + 1;
	right = left + SquareWidth - 1;
   	bottom = top + squareHeight - 1;
   	 
	setfillstyle(SOLID_FILL,color); //設定繪製物件的為實心和顏色 
   	bar(left , top, right, bottom);	//設定繪製方塊的位置 
}

void drawSquare(int row, int col, int color){
	int squareHeight = SCREEN_HEIGHT / GRID_NUM;
   	int SquareWidth = SCREEN_WIDTH / GRID_NUM;
	int left = 0, right = 0, bottom = 0, top = 0;
	left = LEFT_MARGINE + col * SquareWidth + 3;
   	top =  TOP_MARGINE + row * squareHeight + 3;
	right = left + SquareWidth - 3;
	bottom = top + squareHeight - 3;
	int lr_center = (left + right)/2;
	int td_center = (top + bottom)/2;

	int r = 20;   	
   	setcolor(color);
	setfillstyle(SOLID_FILL,color); //設定繪製物件的為實心和顏色 
	circle(lr_center,td_center,r); 
	floodfill(lr_center,td_center,color);
}

//繪製圓點 
void drawCircle(int row, int col, int color){
	int squareHeight = SCREEN_HEIGHT / GRID_NUM;
   	int SquareWidth = SCREEN_WIDTH / GRID_NUM;
	int left = 0, right = 0, bottom = 0, top = 0;
	left = LEFT_MARGINE + col * SquareWidth + 3;
   	top =  TOP_MARGINE + row * squareHeight + 3;
	right = left + SquareWidth - 3;
	bottom = top + squareHeight - 3;
	int lr_center = (left + right)/2;
	int td_center = (top + bottom)/2;

	int r = 10;   	
   	setcolor(color);
//	setfillstyle(SOLID_FILL,color); //設定繪製物件的為實心和顏色 
	circle(lr_center,td_center,r);
}

//遊戲結束訊息
void showGameWinMsg(){
   	//cleardevice(); //清理所有螢幕資料，如果希望只顯示訊息時，取消註解 
   	if(play1time<=0||play2time<=0){
   		PlaySound("countdown.wav",NULL,SND_FILENAME| SND_ASYNC|SND_LOOP);
   		bgmopen=0;
	   }else{
	   	PlaySound("shots.wav",NULL,SND_FILENAME| SND_ASYNC|SND_LOOP);
	   	bgmopen=0;
	   }
   	
   	
   	//playMode = PLAYER;
    //modeCount=0;
	int i = 0;
	char msg[20]="";
	if(play1time<=0){
		strcat(msg, "Player Two Win!!");
	}else if(play2time<=0){
		strcat(msg, "Player One Win!!");
	}else{
		if(play1Score == play2Score){
		strcat(msg, "End In A Draw!!");
	}else if(play1Score > play2Score){
		strcat(msg, "Player One Win!!");
	}else
		strcat(msg, "Player Two Win!!");
	}
	
	entername();
	store_playerRecord(); 		
	char msg2[] = "press backspace to quit or + to restart!!";
	//char msg3[40] ="Enter name:";
   	for(; ; i++){
	   	setcolor(i%13+1);
	   	settextstyle(TRIPLEX_FONT, HORIZ_DIR , 5);
	   	outtextxy(0, SCREEN_HEIGHT / 2, msg);
	   	
	   	setcolor(WHITE);
	   	settextstyle(TRIPLEX_FONT, HORIZ_DIR , 2);
	   	outtextxy(20, SCREEN_HEIGHT / 2 + 100, msg2);
	   	
	   	delay(200);
	   	
	   	setcolor(BLACK);
	   	settextstyle(TRIPLEX_FONT, HORIZ_DIR , 5);
	   	outtextxy(0, SCREEN_HEIGHT / 2, msg);
		   
		   	
	   	if(kbhit()) {
			key = getch();
			if (key == '\b' || key == '+' || key == '=' ) {
				return; 				
			}
		}
	}	
}

void entername(){
	if(playMode == AI_BOTH){
		return;
	}
	char msg2[40] = "Press space to confirm";
	char msg3[40] ="Enter Player";int i;
	char msg4[40] ="Enter Player2 name:";
	char msg[20]="";
	if(play1time<=0){
		strcat(msg, "Player Two Win!!");
	}else if(play2time<=0){
		strcat(msg, "Player One Win!!");
	}else{
		if(play1Score == play2Score){
		strcat(msg, "End In A Draw!!");
	}else if(play1Score > play2Score){
		strcat(msg, "Player One Win!!");
	}else
		strcat(msg, "Player Two Win!!");
	}
	if(playMode == PLAYER||playMode==AI_FIRST){
		strcat(msg3, "1 name:");
	}
	if(playMode == AI_SECOND){
		strcat(msg3, "2 name:");
	}
	for(;;i++){
		setcolor(i%13+1);
	   	settextstyle(TRIPLEX_FONT, HORIZ_DIR , 5);
	   	outtextxy(0, SCREEN_HEIGHT / 2, msg);
		setcolor(WHITE);
		settextstyle(TRIPLEX_FONT, HORIZ_DIR , 2);
		outtextxy(20, SCREEN_HEIGHT / 2 + 50, msg3);
		setcolor(WHITE);
		settextstyle(TRIPLEX_FONT, HORIZ_DIR , 2);
		outtextxy(20, SCREEN_HEIGHT / 2 + 100, msg2);
		delay(200);
		setcolor(BLACK);
	   	settextstyle(TRIPLEX_FONT, HORIZ_DIR , 5);
	   	outtextxy(0, SCREEN_HEIGHT / 2, msg);
		if(kbhit()) {
			key = getch();
			if (key == ' ') {
				break; 				
			}else if((key >= 'A'&& key<='Z')||(key >= 'a'&& key<='z'||key>='0'&&key<='9')){
				namecount=0;
				while(1){
					if(msg3[namecount]!=NULL){
						namecount++;
						continue;
					}
					break;
				}
				while(namecount>19){
					msg3[namecount-1]=NULL;
					namecount--;
				}
				if(playMode == AI_SECOND){
					strcat(msg3,player2name);
				}else if(playMode == PLAYER||playMode==AI_FIRST){
					strcat(msg3,player1name);
				}
				
				namecount=0;
				while(1){
					if(msg3[namecount]!=NULL){
						namecount++;
						continue;
					}
					break;
				}
				
				msg3[namecount]=key;
				
				if(playMode == AI_SECOND){
					player2name[name2count]=key;
					name2count++;
					printf("%s!\n",player2name);
				}else if(playMode == PLAYER||playMode==AI_FIRST){
					player1name[name1count]=key;
					name1count++;
					printf("%s!\n",player1name);
				}
				
				
			}else if(key=='\b'){
				namecount=0;
				while(1){
					if(msg3[namecount]!=NULL){
						namecount++;
						continue;
					}
					break;
				}
				while(namecount>19){
					msg3[namecount-1]=NULL;
					namecount--;
				}
				if(playMode == AI_SECOND){
					player2name[name2count-1]=NULL;
					if(name2count>0){
						name2count--;
					}
					strcat(msg3,player2name);
					printf("%s!\n",player2name);
				}else if(playMode == PLAYER||playMode==AI_FIRST){
					player1name[name1count-1]=NULL;
					if(name1count>0){
						name1count--;
					}
					strcat(msg3,player1name);
					printf("%s!\n",player1name);
				}
				
				
				strcat(msg3,"   ");
				
			}
		}
	}
	for(;;i++){
		//printf("NUMBER2");
		if(playMode != PLAYER){
	   		return;
			   }
		setcolor(i%13+1);
	   	settextstyle(TRIPLEX_FONT, HORIZ_DIR , 5);
	   	outtextxy(0, SCREEN_HEIGHT / 2, msg);
		setcolor(WHITE);
		settextstyle(TRIPLEX_FONT, HORIZ_DIR , 2);
		outtextxy(20, SCREEN_HEIGHT / 2 + 75, msg4);
		delay(200);
		setcolor(BLACK);
	   	settextstyle(TRIPLEX_FONT, HORIZ_DIR , 5);
	   	outtextxy(0, SCREEN_HEIGHT / 2, msg);
	   	
		if(kbhit()) {
			key = getch();
			if (key == ' ') {
				return; 				
			}else if((key >= 'A'&& key<='Z')||(key >= 'a'&& key<='z'||key>='0'&&key<='9')){
				namecount=0;
				while(1){
					if(msg4[namecount]!=NULL){
						namecount++;
						continue;
					}
					break;
				}
				while(namecount>19){
					msg4[namecount-1]=NULL;
					namecount--;
				}
				strcat(msg4,player2name);
				namecount=0;
				while(1){
					if(msg4[namecount]!=NULL){
						namecount++;
						continue;
					}
					break;
				}
				
				msg4[namecount]=key;
				
				if(playMode == PLAYER){
					player2name[name2count]=key;
					name2count++;
				}
				printf("%s!\n",player2name);
				
			}else if(key=='\b'){
				namecount=0;
				while(1){
					if(msg4[namecount]!=NULL){
						namecount++;
						continue;
					}
					break;
				}
				while(namecount>19){
					msg4[namecount-1]=NULL;
					namecount--;
				}
				if(playMode == PLAYER){
					player2name[name2count-1]=NULL;
					if(name2count>0){
						name2count--;
					}
					
				}
				strcat(msg4,player2name);
				printf("%s!\n",player2name);
				strcat(msg4,"   ");
				
			}
		}
	}
	
}

//顯示遊戲相關資訊
void showInfo(){
	totalTime += 95;
	totalTime_2 +=95;
	char timeMsg[45] = " Counting down:";
	char modeMsg[20] = "";
	char optMsg1[50] = "press backspace to quit, + to restart or";
	//char optMsg2[50] = "press [a] to change mode.";
	char optMsg3[50] = "press [space] to set chess.";
	char play1RoundMsg[20] = "PLAYER ONE ROUND";
	char play2RoundMsg[20] = "PLAYER TWO ROUND";	
	char stepCountMsg[10] = "STEP:";
	char timeout[10] ="Time out!";
	char time[10];
	char step[10];
	char score1Msg[10];
	char score2Msg[10];
	int left, top;
	sprintf(time, "%d", 10-totalTime_2/1000);
	//strcat(timeMsg, time);
	strcat(time, " sec. ");
	//if(10-totalTime_2/1000<0){
	
	
	sprintf(score1Msg, "%3d", play1Score);
	sprintf(score2Msg, "%3d", play2Score);
	sprintf(step, "%3d", stepCount);
	strcat(stepCountMsg, step);
	
	setcolor(WHITE); //設定文字顏色 
   	settextstyle(COMPLEX_FONT, HORIZ_DIR , 1); //設定字型，水平或垂直和字型大小 
   	outtextxy(0, 0, timeMsg); //依據坐標輸出文字到螢幕
   	if(10-totalTime_2/1000<=0){
   		setcolor(12);
		outtextxy(200, 0, timeout);
		setcolor(WHITE);
	}else{
		setcolor(10);
		outtextxy(200, 0, time);
		setcolor(WHITE);
	}
   	
   	if(currentPlayer == PLAY_ONE){
   		outtextxy(30, 20, play1RoundMsg);
		setfillstyle(SOLID_FILL,PLAYONE_COLOR);  	  
	}else{
		outtextxy(30, 20, play2RoundMsg); 
		setfillstyle(SOLID_FILL,PLAYTWO_COLOR);  
	}
	
	left = 5, top = 20;
   	bar(left , top, left + 20, top + 20);		
	   		
   	if(playMode == PLAYER){
   		strcat(modeMsg, "Player Mode      ");
   				
	}else if(playMode == AI_FIRST){
   		strcat(modeMsg, "P1 player, P2 AI");    
		
	}else if(playMode == AI_SECOND){
		strcat(modeMsg, "P1 AI, P2 player"); 
	
	}else{
		strcat(modeMsg, "P1, P2 AI both   ");
	}
		

   	setcolor(LIGHTMAGENTA);
   	settextstyle(COMPLEX_FONT, HORIZ_DIR , 1);
   	outtextxy(SCREEN_WIDTH - LEFT_MARGINE * 4, 0, modeMsg);
	
	setcolor(WHITE); //設定文字顏色
	left = LEFT_MARGINE * 2 + GRID_NUM * SCREEN_WIDTH / GRID_NUM / 3;
	top = 20;	      	
	outtextxy(left + 25, 20, stepCountMsg);	
	//printf("%d",left + 25);
	
	left = LEFT_MARGINE * 4 + GRID_NUM * SCREEN_WIDTH / GRID_NUM / 2;
	top = 20;
	setfillstyle(SOLID_FILL,PLAYONE_COLOR);
	bar(left , top, left + 20, top + 20);	      	
	outtextxy(left + 25, 20, score1Msg);
	
	left = LEFT_MARGINE * 4 + GRID_NUM * SCREEN_WIDTH / GRID_NUM / 2 + 100;
	setfillstyle(SOLID_FILL,PLAYTWO_COLOR);
	bar(left, top, left + 20, top + 20);	      	
	outtextxy(left + 25, 20, score2Msg);
   	
   	setcolor(LIGHTGREEN);
   	settextstyle(COMPLEX_FONT, HORIZ_DIR , 1);
   	//outtextxy(0, TOP_MARGINE + (GRID_NUM) * SCREEN_HEIGHT / GRID_NUM, optMsg1);
	//outtextxy(0, TOP_MARGINE + (GRID_NUM) * SCREEN_HEIGHT / GRID_NUM + 20, optMsg2);	      	
	outtextxy(0, TOP_MARGINE + (GRID_NUM) * SCREEN_HEIGHT / GRID_NUM , optMsg3);
}

//電腦玩家，請在此function實作AI功能 (stupid ai)
Location* PLAYONE_AI(int field[][GRID_NUM],  Location *focusPtr, NodePointer validated_locs){
	Location tmp= {0, 0}; int maxx = 0;//定義及初始化最優解
	int max = 0;Location tmp_2= {0, 0};
	for (int i = 0; i < GRID_NUM; ++i){
		for (int j = 0; j < GRID_NUM; ++j)
		{
			tmp = {i, j};
			int a=focusPtr->row; int b=focusPtr->col ;
			tmp_2 = { a,b};
			if (expectnum[i][j] >= max && checkValidation(validated_locs, tmp) == true&&reverse(field, tmp, true) >= maxx )
			{
				focusPtr->row = i ;focusPtr->col = j ;
				maxx = reverse(field, tmp, true);
				max = expectnum[i][j];
				
				
			}
			
		}
	}
	if(max<=0||AI_mode%2==1){
		for (int i = 0; i < GRID_NUM; ++i){
		for (int j = 0; j < GRID_NUM; ++j)
		{
			tmp = {i, j};
			if (reverse(field, tmp, true) >= maxx && checkValidation(validated_locs, tmp) == true )
			{
				maxx = reverse(field, tmp, true);
				focusPtr->row = i ;focusPtr->col = j ;
				
				
			}
			
		}
		}
	}
	
		
	//printf(" %d  %d %d",focusPtr->row,focusPtr->col,expectnum[focusPtr->row][focusPtr->col]);	
	return focusPtr;
}
void menu(){
	
   	cleardevice(); //清理所有螢幕資料，如果希望只顯示訊息時，取消註解 
   	if(bgmopen!=1){
   		PlaySound("BGM.wav",NULL,SND_FILENAME| SND_ASYNC|SND_LOOP);
   		bgmopen=1;
		   }
   	
   	
   	playMode = PLAYER;
    modeCount=0;
	int i = 0;
	char msg1[20] = "奇魂";
			
	char msg2[40] = "Choose mode:";
	char msg21[40] = "Player vs Player";
	char msg22[40] = "Player first to go";
	char msg23[40] = "Player second to go";
	char msg24[40] = "Ai vs Ai";
   	for(; ; i++){
	   	setcolor(i%14);
	   	settextstyle(TRIPLEX_FONT, HORIZ_DIR , 7);
	   	outtextxy(175, SCREEN_HEIGHT / 2-100, msg1);
	   	
	   	setcolor(WHITE);
	   	settextstyle(TRIPLEX_FONT, HORIZ_DIR , 2);
	   	outtextxy(20, SCREEN_HEIGHT / 2 + 30, msg2);
	   	settextstyle(TRIPLEX_FONT, HORIZ_DIR , 4);
	   	
	   	outtextxy(100, SCREEN_HEIGHT / 2 + 70, msg21);
	   	outtextxy(100, SCREEN_HEIGHT / 2 + 110, msg22);
	   	outtextxy(100, SCREEN_HEIGHT / 2 + 150, msg23);
	   	outtextxy(100, SCREEN_HEIGHT / 2 + 190, msg24);
	   	setcolor(YELLOW);
	   	if(modeCount==0){
			 outtextxy(100, SCREEN_HEIGHT / 2 + 70, msg21);
		   }else if(modeCount==1){
			 outtextxy(100, SCREEN_HEIGHT / 2 + 110, msg22);
		   }else if(modeCount==2){
		   	outtextxy(100, SCREEN_HEIGHT / 2 + 150, msg23);
		   }else{
		   	outtextxy(100, SCREEN_HEIGHT / 2 + 190, msg24);
		   }
	   	
	   	setcolor(WHITE);
	   	settextstyle(TRIPLEX_FONT, HORIZ_DIR , 2);
	   	outtextxy(20, SCREEN_HEIGHT / 2 + 230, "Press space to choose mode       ");
	   	outtextxy(20, SCREEN_HEIGHT / 2 + 250, "Press backspace to close");
	   	
	   	delay(200);
	   	
	   	setcolor(BLACK);
	   	settextstyle(TRIPLEX_FONT, HORIZ_DIR , 5);
	   	outtextxy(0, SCREEN_HEIGHT / 2, msg1);
			   
		   	
	   	if(kbhit()) {
			key = getch();
			if (key == ' '||key =='\b') {
				if(key=='\b'){
					closeGame();
				}
				playMode = modeCount%4;
				
				if(!menu_AI()){
					continue;
				}
				return; 				
			}else{
				switch(key){
					case KEY_UP:
						if(modeCount>=0&&modeCount<=3){
							modeCount --;
							if(modeCount ==-1){
								modeCount =0;
							}
						}
						
						printf("%d",modeCount);
						break;
					case KEY_DOWN:	
						 if(modeCount>=0&&modeCount<=3){
							modeCount ++;
							if(modeCount ==4){
								modeCount =3;
							}
						}
						 printf("%d",modeCount);
						 break;
					}
			}
		}
	}	
}

void clearname(){
	while(name1count>=0){
		player1name[name1count]=NULL;
		name1count--;
	}
	while(name2count>=0){
		player2name[name2count]=NULL;
		name2count--;
	}
	name1count=0;
 	name2count=0;

}


void store_playerRecord(){
	if(playMode == AI_BOTH){
		return;
	}
	FILE *fptr1;
	FILE *fptr2;// file pointer

	if((fptr1 = fopen("AllplayersRecord.txt", "r")) == NULL){// 沒有檔案則創最新紀錄 
		fclose(fptr1);
		fptr1 = fopen("AllplayersRecord.txt", "w");
		fclose(fptr1);
	}
	
	if( (fptr1 = fopen("AllplayersRecord.txt", "a")) == NULL ){  // open file with "append" mode
		
		printf("\nError: the file cannot be opened.");
	
		return ;
		
	}
	else{  // record player's name, score, bombs
		fprintf(fptr1, "\n%s", "~~Players Record~~");
		//puts("");
		if(playMode == PLAYER){
			fprintf(fptr1, "\n%s vs %s\n", player1name,player2name);
		}else if(playMode == AI_FIRST){
			if(AI_mode%2==1){
				fprintf(fptr1, "\n%s vs Easy AI\n", player1name);
			}else{
				fprintf(fptr1, "\n%s vs Hard AI\n", player1name);
			}
			
		}else if(playMode == AI_SECOND){
			if(AI_mode%2==1){
				fprintf(fptr1, "\nEasy AI vs %s\n", player2name);
			}else{
				fprintf(fptr1, "\nHard AI vs %s\n", player2name);
			}
			
		}
		
		fprintf(fptr1, "Total score: %d vs %d\n",play1Score,play2Score);
		if(play1time<=0){
			fprintf(fptr1, "%s out of time.\n", player1name);
		}else if(play2time<=0){
			fprintf(fptr1, "%s out of time.\n", player2name);
		}
		fclose(fptr1);   // close the file
		
		return ;
	}
	
}

int menu_AI(){
	if(modeCount==0||modeCount==3){
		return 1;
	}
	char msg2[]="Difficulty:          ";int i;
	setcolor(WHITE);
	settextstyle(TRIPLEX_FONT, HORIZ_DIR , 2);
	outtextxy(20, SCREEN_HEIGHT / 2 + 30, msg2);
	settextstyle(TRIPLEX_FONT, HORIZ_DIR , 2);
	outtextxy(20, SCREEN_HEIGHT / 2 + 230, "Press space to choose difficulty");
	outtextxy(20, SCREEN_HEIGHT / 2 + 250, "Press backspace to back      ");
	AI_mode=0;
	for(;;i++){
		setcolor(WHITE);
	   	settextstyle(TRIPLEX_FONT, HORIZ_DIR , 4);
		outtextxy(100, SCREEN_HEIGHT / 2 + 70, "Easy                           ");
	   	outtextxy(100, SCREEN_HEIGHT / 2 + 110, "                              ");
	   	outtextxy(100, SCREEN_HEIGHT / 2 + 150, "Hard                           ");
	   	outtextxy(100, SCREEN_HEIGHT / 2 + 190, "                               ");
	   	setcolor(YELLOW);
	   	//delay(200);
	   	if(AI_mode%2==1){
			 outtextxy(100, SCREEN_HEIGHT / 2 + 70, "Easy");
		   }else{
			 outtextxy(100, SCREEN_HEIGHT / 2 + 150, "Hard");
		   }
	   delay(200);
	   if(kbhit()) {
			key = getch();
			if (key == ' '||key =='\b') {
				if(key == ' '){
					return 1;
				}else{
					return 0;
				}
								
			}else{
				switch(key){
					case KEY_UP:
						AI_mode++;
						
						//printf("%d",AI_mode%2);
						break;
					case KEY_DOWN:	
						 AI_mode--;
						 //printf("%d",AI_mode%2);
						 break;
					}
			}
		}
	}

	
	
}

void copy(int field[][GRID_NUM],int copyfield[][GRID_NUM]){
	int i=0,j=0;
	for(i;i<GRID_NUM;i++){
		for(j;j<GRID_NUM;j++){
			copyfield[i][j]=field[i][j] ;
		}
	}
}
	
