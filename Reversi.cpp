#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <graphics.h>
#include <time.h>
#include <math.h>
#include <windows.h>
#include <MMsystem.h>
#include <string.h>



#define SCREEN_HEIGHT 500 //�]�w�C���������� 
#define SCREEN_WIDTH 500 //�]�w�C�������e��
#define GRID_NUM 8 //�]�w�C����}�C���l�ƶq 
#define LEFT_MARGINE 30 //�]�w����� 
#define TOP_MARGINE 45 //�]�w�W��� 
#define INIT_SPEED  80 //�]�w��l�t�� 
#define PLAYONE_COLOR  BLUE //�]�w���a�@�C��
#define PLAYTWO_COLOR  RED //�]�w���a�G�C��
#define PLAYTIME 10;



//�ŧi�Ѥl���� 
enum Chess {
	EMPTY, //�ť� 
	PLAY_ONE, //���a�@ 
	PLAY_TWO //���a�G 
};

enum Mode {
	PLAYER,
	AI_FIRST,
	AI_SECOND,
	AI_BOTH 
};

//�ŧi�Ѥl��l 
struct Location{
	int row; 
	int col;
};

//�ŧi�������l��m���`�I���c 
struct Node {
	Location loc; //�ѽL��m 
	struct Node *next;	//���V�U�@�Ӹ`�I 
};

//�w�q���V�`�I���c�������ܼ� 
typedef struct Node *NodePointer;

void openWindow(); //�}�Ҵ������� 
void closeGame(); //�B�z�C�������޿� 
void playGame(int field[][GRID_NUM]); //�C���i���޿� 
void initChessboard(int field[][GRID_NUM]); //��l�ƴѽL���A 
Location* getChessDown(int field[][GRID_NUM], Location *focusPtr); //���o���a���l��m 
void setChess(int field[][GRID_NUM], Location chessLoc); //�]�w���l 
void drawChessboard(int field[][GRID_NUM]); //ø�s�C���ϰ� 
void printBoardState(int field[][GRID_NUM]); //�L�X�ѽL���A 
bool checkValidation(NodePointer list, Location loc); //�ˬd�Ӧ�m�O�_���X�k�����l��m 
NodePointer getValidatedLocs(int field[][GRID_NUM]); //��o�Ҧ��X�k�U�l���Ҧ��y�и`�I 
NodePointer addNode(NodePointer list, Location loc); //�s�W�X�k�U�l���y�и�T�`�I
void drawValidatedLocs(NodePointer list); //�аO�X�Ҧ��Ӫ��a�Ҧ��X�k���U�Ѧ�m 
void cleanValidatedLocs(NodePointer list); //�M�z�аO 
void doReverse(int field[][GRID_NUM], Location chessLoc); //�i��¥մ�½�� 
int reverse(int field[][GRID_NUM], Location chessLoc, bool checkOnly); //�p��Y�U�l�y�ЩҦ��i�H½�઺�Ѥl�ƶq�A check_only = true �u�i��p��Afalse �|�i��Ѥl��½�� 
void drawSquare(int row, int col, int color); //ø�s��� 
void drawFocus(int field[][GRID_NUM], Location focus); //ø�s�ؼФQ�r  
void cleanFocus(int field[][GRID_NUM], Location focus);//�M���Q�r 
void drawCircle(int row, int col, int color); //ø�s���I 
void showGameWinMsg(); //�C�������T��
void showInfo(); //��ܹC��������T 
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


Location* PLAYONE_AI(int field[][GRID_NUM], Location *focusPtr, NodePointer validated_locs);//��@�q�������޿� 

char key; //�ާ@���� 
int speed; //���ʳt�� 
int currentPlayer = PLAY_ONE; //�]�w���a 
int modeCount = 0; //����Ҧ����� 
int totalTime = 0; //�����C���ɶ� 
int playMode = PLAYER; // �]�w����Ҧ��A���a�Ҧ���AI�Ҧ� 
int play1Score = 0; //���a�@���� 
int play2Score = 0; //���a�G���� 
int stepCount = 0; //�^�X�p�ƾ� 
int play1time=PLAYTIME;//�Ѿl�ɶ� 
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
		
		//�]�w�C����
	   	int field[GRID_NUM][GRID_NUM] = {0};
		int copyfield[GRID_NUM][GRID_NUM]={0};
		playGame(field); //�i��C��
		if (key == '\b')
			closeGame(); //�p�G���a��J'q'���}�C��	
		else if (key == '+'||key == '='){
			//playMode = PLAYER;
			continue;
		}
		
			 //�p�G���a��J's' �~��C�� 		    
	}
}

//�}�Ҵ�������
void openWindow(){
	initwindow(SCREEN_WIDTH + LEFT_MARGINE * 3, SCREEN_HEIGHT + TOP_MARGINE * 3, "Backgammon");
}

//�B�z�C�������޿� 
void closeGame(){
	exit(0);
}

//�C���i���޿�
void playGame(int field[][GRID_NUM]){
	menu();
	drawChessboard(field); //ø�s�C���ϰ� 
	if(bgmopen!=1){
		PlaySound("BGM.wav",NULL,SND_FILENAME| SND_ASYNC|SND_LOOP);
		bgmopen=1;
	}
	
	totalTime =0;
	NodePointer validated_locs = NULL;
	play1Score = 0, play2Score = 0;
	stepCount = 0;
	play1time=PLAYTIME;//�Ѿl�ɶ� 
	play2time=PLAYTIME;
	clearname();
	
	initChessboard(field); //��l�ƴѽL���A 
   	printBoardState(field); //�L�X�ѽL���A�A�Ω�debug�ϥ� 
   	
   	validated_locs = getValidatedLocs(field); //�p��Ҧ��X�k�y��  
   	drawValidatedLocs(validated_locs); //�b�ѽL�Wø�s�o�^�X�X�k���y�� 
	   	
	Location focus = {0, 0};
	Location* chessLocPtr;
	key = 0;
	int endPoint = 0;
	int time_1=0;
	totalTime_2 = 0;
	
	while(true){

		delay(speed); //�M�w�C�^�X�U�ѳt�� 

		showInfo();//��ܮɶ��M���Ƹ�T
		
		
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
				 showGameWinMsg(); //��ܹC�������T���A�õ��ݪ��a��J�ﶵ
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
			//�u����J�j�p�g��a, q �M s�A�t�Τ~�������ñN��J���G�ߨ�~�h���ݳB�z 
			if (key == '\b' || key == '+' || key == '='){
				modeCount=0;
				return;	
			}
							
			/*else if (key == 'a' || key == 'A'){ 
				//�M�w�O�_���ܼҦ� �A�D�n�����a�Ҧ��M�q���ޱ���AI�Ҧ� 
				modeCount++;
				playMode = modeCount % 4;
				key = 0;
			}*/
			
			if (endPoint < 2)
				continue;
		}
	
		//���a�u��U�b�X�k��m 
		if(chessLocPtr != NULL && checkValidation(validated_locs, *chessLocPtr) == false){
			continue;
		} 
		cleanValidatedLocs(validated_locs);
		//�M�z�X�k��m�аO 
		
		if(chessLocPtr != NULL){
			setChess(field, *chessLocPtr);
		}
		//�p�G���a���Uspace�A�N�b�ؼФQ�r�y��ø�s�Ѥl�A�ç��ܴѽL���A 
 
 		//�p�G���O�ɥ��I�A�i��Y�l�P�_�A��½��Ѥl 
		if(endPoint < 2){
			doReverse(field, *chessLocPtr);
		
		}
		
		int time_2=(clock()-time_1)/1000;
		//printf("%d",time_2);
		if(currentPlayer == PLAY_ONE){
			play1time-=time_2;
			if(play1time<=0){
				showInfo();
			    showGameWinMsg(); //��ܹC�������T���A�õ��ݪ��a��J�ﶵ
			    return;
			}
		}else{
			play2time-=time_2;
			if(play2time<=0){
				showInfo();
			    showGameWinMsg(); //��ܹC�������T���A�õ��ݪ��a��J�ﶵ
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
		
		// ���o�U�@�^�X���X�k��m 
		validated_locs = getValidatedLocs(field);
		//�p�G�Ӧ^�X�L�k��o�X�k���U�l��m�A�ɥ��I+1 
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
		
		//�s���^�X���L�k��o�X�k�y�СA�Ϊ̤w�g�S���i�H�U�l����m�A�C������ 
		if(endPoint == 2||(play1Score + play2Score) == GRID_NUM * GRID_NUM ){
			
			showInfo();
			showGameWinMsg(); //��ܹC�������T���A�õ��ݪ��a��J�ﶵ
			return;
		}
		
		//ø�s�X�k�y�маO 
		drawValidatedLocs(validated_locs);
		printf("end point: %d\n", endPoint);
		
		
							
	}		
}

// ��l�ƴѽL���A 
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

//ø�s�C���ϰ�A�̾ڹC�����x�}�]�wø�s���� 
void drawChessboard(int field[][GRID_NUM]){
   	int row = 0, col = 0;
   	int startX = 0, startY = 0, endX = 0, endY = 0;
   	cleardevice(); //�M�z�ù��e�� 
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

//�C�L�ѽL���A 
void printBoardState(int field[][GRID_NUM]){
	int i,j;
	
	for(i=0;i<GRID_NUM;i++){
		for(j=0;j<GRID_NUM;j++)
			printf("%d ", field[i][j]);
		printf("\n");	
	}
}

//���o���a���l��m
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
	//�u����J�j�p�g��a, q �M s�A�t�Τ~�������ñN��J���G�ߨ�~�h���ݳB�z 
	if (keyPress == 'q' || keyPress == 'Q' || keyPress == 's' || keyPress == 'S' || keyPress == 'a' || keyPress == 'A'){
		key = keyPress;
	}
	return NULL;
}

//�]�w���l
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

//�ˬd�Ӧ�m�O�_���X�k�����l��m 
bool checkValidation(NodePointer list, Location loc){
	
	while(list != NULL){
		if(list->loc.row == loc.row && list->loc.col == loc.col)
			return true;
		list = list -> next;	
	}
	return false;
}

//��o�Ҧ��X�k�U�l���Ҧ��y�и`�I 
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

//�s�W�X�k�U�l���y�и�T�`�I
NodePointer addNode(NodePointer list, Location loc){
	NodePointer tail = NULL;
	NodePointer newNode = (NodePointer) malloc(sizeof(Node)); //��l�Ƥ@�ӷs�`�I 
	newNode -> loc = loc;
	newNode -> next = NULL;	
	if(list == NULL)
		return newNode;
	else{
		//�M���C������ 
		tail = list;
		while(tail -> next != NULL){
			tail = tail -> next;
		}
		tail -> next = newNode; //�N���ڸ`�I�s����s�`�I 
		return list;
	}
}

//�аO�X�Ҧ��Ӫ��a�Ҧ��X�k���U�Ѧ�m 
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

//�M�z�аO 
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

//�i��¥մ�½�� 
void doReverse(int field[][GRID_NUM], Location chessLoc){
	reverse(field, chessLoc, false);
}

//�p��Y�U�l�y�ЩҦ��i�H½�઺�Ѥl�ƶq�A check_only = true �u�i��p��Afalse �|�i��Ѥl��½�� 
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

//ø�s�ؼФQ�r
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

//�M���ؼФQ�r
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

//ø�s���
void drawSquare_ex(int row, int col, int color){
	
	int squareHeight = SCREEN_HEIGHT / GRID_NUM;
   	int SquareWidth = SCREEN_WIDTH / GRID_NUM;
	int left = 0, right = 0, bottom = 0, top = 0;
	left = LEFT_MARGINE + col * SquareWidth + 1;
   	top =  TOP_MARGINE + row * squareHeight + 1;
	right = left + SquareWidth - 1;
   	bottom = top + squareHeight - 1;
   	 
	setfillstyle(SOLID_FILL,color); //�]�wø�s���󪺬���ߩM�C�� 
   	bar(left , top, right, bottom);	//�]�wø�s�������m 
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
	setfillstyle(SOLID_FILL,color); //�]�wø�s���󪺬���ߩM�C�� 
	circle(lr_center,td_center,r); 
	floodfill(lr_center,td_center,color);
}

//ø�s���I 
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
//	setfillstyle(SOLID_FILL,color); //�]�wø�s���󪺬���ߩM�C�� 
	circle(lr_center,td_center,r);
}

//�C�������T��
void showGameWinMsg(){
   	//cleardevice(); //�M�z�Ҧ��ù���ơA�p�G�Ʊ�u��ܰT���ɡA�������� 
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

//��ܹC��������T
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
	
	setcolor(WHITE); //�]�w��r�C�� 
   	settextstyle(COMPLEX_FONT, HORIZ_DIR , 1); //�]�w�r���A�����Ϋ����M�r���j�p 
   	outtextxy(0, 0, timeMsg); //�̾ڧ��п�X��r��ù�
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
	
	setcolor(WHITE); //�]�w��r�C��
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

//�q�����a�A�Цb��function��@AI�\�� (stupid ai)
Location* PLAYONE_AI(int field[][GRID_NUM],  Location *focusPtr, NodePointer validated_locs){
	Location tmp= {0, 0}; int maxx = 0;//�w�q�Ϊ�l�Ƴ��u��
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
	
   	cleardevice(); //�M�z�Ҧ��ù���ơA�p�G�Ʊ�u��ܰT���ɡA�������� 
   	if(bgmopen!=1){
   		PlaySound("BGM.wav",NULL,SND_FILENAME| SND_ASYNC|SND_LOOP);
   		bgmopen=1;
		   }
   	
   	
   	playMode = PLAYER;
    modeCount=0;
	int i = 0;
	char msg1[20] = "�_��";
			
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

	if((fptr1 = fopen("AllplayersRecord.txt", "r")) == NULL){// �S���ɮ׫h�г̷s���� 
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
	
