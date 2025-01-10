#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <unistd.h>


struct Card{
	//R,G,Y,B
	//Special Cards
	//Reverse  Skip   Draw 2   Wild and Draw 4
	//'C'11   'C'12  'C' 13     W 14     W 15
	//'C' = Color of that card
	char color;
	int num;

};

struct Player{

	struct Card *Dynamic_card;
	//int cur_card;
	int total_card;

};
//Global

struct Card Deck[112];
struct Card last_card;
int DeckTotal;
int DeckCur_card = 0;
int background = 0; //Black

//Scores
int User1_Score = 0;
int User2_Score = 0;
int User3_Score = 0;
int Bot_Score = 0;


//prototypes
void ReadDeck();
void ShuffleDeck();
void ShowDeck();
void AllocateMemory(int size,struct Player* player);
void freeArray(struct Player* player);
void Distribute(int len,struct Player* player);
int showcard(struct Player* player,int display);
void Initialize(struct Player* player1,struct Player* player2);
void AddCard(struct Player* player,struct Card card);
struct Card RemoveCard(struct Player* player,int index);
int ValidCard(struct Card card);
void Draw_Four(struct Player* player);
void Draw();
void MultiGameLoop(struct Player* player1,struct Player* player2);
void Draw_two(struct Player* player);
void Lcard();
int color();
void multiplayer();
void ClearBuffer();
void Menu();
int FindValid(struct Player* Bot);
char Color_Special(struct Player* Bot);
void Draw_Four_Bot(struct Player* Bot,struct Player* player);
void SingleGameLoop(struct Player* player1,struct Player* Bot);
void SinglePlayer();
int colorchange();
void ResetScore();
void SaveScore();
void Restore();
void ResetScore();
void MultiGameLoop_Three(struct Player* player1,struct Player* player2,struct Player* player3);
int FinishCheckThree(struct Player* player1,struct Player* player2,struct Player* player3);
void ThreePlayer();
void submenu();
void other();
void BotWon();
void Player1_Won();
void Player2_Won();
void Player3_Won();

int main(){
	
	Menu();
	
	return 0;
}

void Menu(){
	system("cls");
	printf("\t\t\t\t\t\t\t\t------------------------------------\n");
	printf("\t\t\t\t\t\t\t\t| *     *  **       * \t  *****    |\n");
	printf("\t\t\t\t\t\t\t\t| *     *  * *      *    *     *   |\n");
	printf("\t\t\t\t\t\t\t\t| *     *  * *      *   *       *  |\n");
	printf("\t\t\t\t\t\t\t\t| *     *  *  *     *  *         * |\n");
	printf("\t\t\t\t\t\t\t\t| *     *  *   *    *  *         * |\n");
	printf("\t\t\t\t\t\t\t\t| *     *  *    *   *  *         * |\n");
	printf("\t\t\t\t\t\t\t\t| *     *  *     *  *   *       *  |\n");
	printf("\t\t\t\t\t\t\t\t|  *   *   *      * *    *     *   |\n");
	printf("\t\t\t\t\t\t\t\t|    *     *  \t   **\t  *****    |\n");
	printf("\t\t\t\t\t\t\t\t------------------------------------\n");
	
	printf("\n\nUser1Score = %d \t User2Score = %d\t User3Score = %d\t BotScore = %d\n\n",User1_Score,User2_Score,User3_Score,Bot_Score);



	int opp;
	do{
		printf("Menu\n1)Single Player\n2)MultiPlayer\n3)Other Menu\n4)Exit\nOption:");
	}while(scanf("%d",&opp) ==0);
	ClearBuffer();
	switch(opp){
		case 1:{
			system("cls");
			SinglePlayer();
			break;
		}
		
		case 2:{
			system("cls");
			submenu();
			break;
		}
		
		case 3:{
			system("cls");
			other();
			break;
		}
		
		case 4:{
			printf("\nExiting...");
			sleep(1.5);
			exit(1);
			break;
		}
				
		default:{
			printf("WRONG INPUT");
			Menu();
			break;
		}
	}
	
}

void submenu(){
	
	int opp;
	printf("MENU\n1)Two-Player\n2)Three-Player\n3)Back to Main Manu\n->");
	scanf("%d",&opp);
	ClearBuffer();
	switch(opp){
		case 1:{
			multiplayer();
			break;
		}
		
		case 2:{
			ThreePlayer();
			break;
		}
		
		case 3:{
			system("cls");
			Menu();
			break;
		}
		
		default:{
			printf("Wrong Input!");
			sleep(1);
			system("cls");
			submenu();
			break;
		}
			
	}

}

void other(){
	
	
	int opp;
	printf("1)Color Change\n2)Save Score\n3)Restore Score\n4)Reset Score\n5)Back to Main Manu\n->");
	scanf("%d",&opp);
	ClearBuffer();
	
	switch(opp){
		
		case 1:{
			colorchange();
			break;
		}
		
		case 2:{
			SaveScore();
			break;
		}
		
		case 3:{
			Restore();
			break;
		}
		
		case 4:{
			ResetScore();
			break;
		}
		case 5:{
			system("cls");
			Menu();
			break;
		}
		
		default:{
			printf("Wrong Input!");
			sleep(1);
			system("cls");
			other();
			break;
		}
	}
	

	
	
}



void multiplayer(){
	struct Player player1;
	struct Player player2;
	system("cls");
	Initialize(&player1,&player2);	
	MultiGameLoop(&player1,&player2);


}

void ThreePlayer(){
	struct Player player1;
	struct Player player2;
	struct Player player3;
	system("cls");
	Initialize(&player1,&player2);	
	AllocateMemory(6,&player3);
	Distribute(6,&player3);
	MultiGameLoop_Three(&player1,&player2,&player3);
	

}


void SinglePlayer(){
	struct Player player1;
	struct Player Bot;
	system("cls");
	Initialize(&player1,&Bot);	
	SingleGameLoop(&player1,&Bot);


}

void Initialize(struct Player* player1,struct Player* player2){
	ReadDeck();
	ShuffleDeck();
	DeckCur_card = 0;
	AllocateMemory(6,player1);
	AllocateMemory(6,player2);
	Distribute(6,player1);
	Distribute(6,player2);
	last_card.color = '\0';
	last_card.num = -1;


}

void ReadDeck() {
    FILE *fptr = fopen("Cards.txt", "r");
    int i = 0;

    if (fptr == NULL) {
        printf("Unable to open file\n");
    } else {
        while (fscanf(fptr, " %c%d", &Deck[i].color, &Deck[i].num) == 2) { // sucessful read
            i++;
        }
        DeckTotal = i;
        DeckCur_card = 0;


    }
    fclose(fptr);
}

void ShuffleDeck(){

	srand(time(NULL));
	int i;

	for (i=DeckTotal-1;i>0;i--){
		int j = rand() % (i+1);

		char temp1 = Deck[i].color;
		int temp2 = Deck[i].num;
		Deck[i].color = Deck[j].color;
		Deck[i].num = Deck[j].num;
		Deck[j].color = temp1;
		Deck[j].num = temp2;
	}
}

void ShowDeck(){

	int i;
	for (i=0;i<DeckTotal;i++){
		printf("%c%d\n",Deck[i].color,Deck[i].num);
	}
}

void AllocateMemory(int size,struct Player* player) {
    player->Dynamic_card = (struct Card*)malloc(sizeof(struct Card) * size);
    player->total_card = size;
}

void freeArray(struct Player* player) {
    free(player->Dynamic_card);
    player->Dynamic_card = NULL;
    player->total_card = 0;
}

void Distribute(int len,struct Player* player){
	int i;
	for (i=0;i<len;i++){
		player->Dynamic_card[i].color = Deck[DeckCur_card].color;
		player->Dynamic_card[i].num = Deck[DeckCur_card].num;
		DeckCur_card++;
	}

}

void AddCard(struct Player* player,struct Card card){

	if (DeckCur_card >=112){
		printf("\nDraw\nDeck Finished\n"); //To encounter edge case
		Menu();
	}
	
	player->total_card++;

	player->Dynamic_card = (struct Card*)realloc(player->Dynamic_card,player->total_card*sizeof(struct Card));
	//Increase Size of Array by one

	player->Dynamic_card[player->total_card - 1] = card;
	//Add New Card in that place

}

struct Card RemoveCard(struct Player* player,int index){

	struct Card RemovedCard = player->Dynamic_card[index];

	int i;

	for (i=index;i<player->total_card-1;i++){
		player->Dynamic_card[i] = player->Dynamic_card[i+1];//shift card back to remove empty space
	}
	player->total_card--;
	player->Dynamic_card = (struct Card*)realloc(player->Dynamic_card,player->total_card*sizeof(struct Card));

	return RemovedCard;

}

int ValidCard(struct Card card){
	//Reverse  Skip  Draw 2 Wild and Wild Draw 4
	//'C'11   'C'12  'C' 13     W 14     W 15
	//'C' = Color of that card 
	if (card.num == 15){
		return 6; // Wild Four 
	}else if (card.num == 14){
		return 5; // Wild
	}
	if (card.num == 13 && (card.color == last_card.color || card.num == last_card.num || last_card.num == -1)){
		return 4; // Draw 2
	}
	if (card.num == 12 && (card.color == last_card.color || card.num == last_card.num  || last_card.num == -1)){
		return 3; // Skip
	}
	if (card.num == 11 && (card.color == last_card.color || card.num == last_card.num  || last_card.num == -1)){
		return 2; //Reverse
	}
	if (card.num == 11 || card.num == 12 || card.num == 13){
		return 0;
	}
	return (card.color == last_card.color || card.num == last_card.num || last_card.num == -1);
	
}

int FindValid(struct Player* Bot){
	//For Single Player
	int i;
	int special_card = -1;
	for (i=0;i<Bot->total_card;i++){
		int Valid = ValidCard(Bot->Dynamic_card[i]);
		if (Valid == 15 || Valid == 14){
			special_card = i; // Keep It For End
		}else if (Valid > 0){
			return i;
		}else{
			continue;
		}
		
	}
	return special_card; // either -1 meaning no Valid or Index of Special Card
}

char Color_Special(struct Player* Bot){
	//When Use Special Card_ Select Color that he have most
	int i;
	int Count[4] = {0,0,0,0}; // R,G,B,Y
	for (i=0;i<Bot->total_card;i++){
		switch(Bot->Dynamic_card[i].color){
			case 'R':
				Count[0]++;
				break;
			case 'G':
				Count[1]++;
				break;
			case 'B':
				Count[2]++;
				break;
			case 'Y':
				Count[3]++;
				break;
		}
		
	}
	//Find Max In Array
	int index = 0;
	int Max = Count[0];
	for (i=1;i<4;i++){
		if (Count[i] > Max){
			Max = Count[i];
			index = i;
		}
	}
	return (index == 0 ? 'R' : index == 1 ? 'G' : index == 2 ? 'B' : 'Y');
}

void Draw_Four_Bot(struct Player* Bot,struct Player* player){
	last_card.color = Color_Special(Bot);
	last_card.num = 15;
	int i;
	for (i=0;i<4;i++){
		AddCard(player,Deck[DeckCur_card]); // Add in Players Deck
		DeckCur_card++;
	}
}

void Draw_Four(struct Player* player){
	
	char col;
	do{
		printf("Enter Color For Card: ");
		if (scanf(" %c",&col) == 0){
			continue;
		}else{
			col = toupper(col);
			ClearBuffer();
		}
	}while (col != 'R' && col !='G' && col != 'Y' && col != 'B');
	
	last_card.color = col;
	last_card.num = 15; 
	int i;
	for (i=0;i<4;i++){
		AddCard(player,Deck[DeckCur_card]);
		DeckCur_card++;
	}
	
	
}

void Draw(){
	char col;
	do{
		printf("Enter Color For Card: ");
		if (scanf(" %c",&col) == 0){
			continue;
		}else{
			col = toupper(col);
			ClearBuffer();
		}
	}while (col != 'R' && col !='G' && col != 'Y' && col != 'B');
	
	last_card.color = col;
	last_card.num = 14; 
	
}

void Draw_two(struct Player* player){
	int i;
	for (i=0;i<2;i++){
		AddCard(player,Deck[DeckCur_card]);
		DeckCur_card++;
	}
	
}

int FinishCheck(struct Player* player1,struct Player* player2){
	return (player1->total_card == 0 || player2->total_card == 0|| DeckCur_card >=112);
}

void ClearBuffer(){
	char c;
	while ((c = getchar()) != '\n');
}

void MultiGameLoop(struct Player* player1,struct Player* player2){
	int i = 0; // Turns
	int card_ind;
	int valid;
	int Game = 0; //Terminate Game Loop 
	
	while (1){ // Manual Break
		
		if (i % 2 ==0 ){ // Player 1 Turn
			do{			
				showcard(player1,1);
				printf("Player 1 Select Card From 1 - %d\nOr '0' to Pick Card from Deck\n:",player1->total_card);
				if (scanf("%d",&card_ind) == 0){
					ClearBuffer();
					continue;
				}else if (card_ind == 0){
					AddCard(player1,Deck[DeckCur_card]);
					DeckCur_card++;
					showcard(player1,1);
					printf("Card Added\n");
					sleep(1);
					break;

				}else if (card_ind < 1 || card_ind > player1->total_card){
					ClearBuffer();
					continue;
				}else{
					card_ind--;
					valid = ValidCard(player1->Dynamic_card[card_ind]);
					if (valid == 0){
						printf("Invalid Card\n");
						sleep(1);
						continue;
					}else if (valid == 6){// Draw_4
						last_card = RemoveCard(player1,card_ind);
						showcard(player1,1);
						Draw_Four(player2);
						showcard(player1,1);
						printf("Adding Cards to Player 2 Deck\n");
						sleep(1.5);
						break;
					}else if (valid == 5){ // Wild
						last_card = RemoveCard(player1,card_ind);
						showcard(player1,1);
						Draw();
						showcard(player1,1);
						sleep(1);
						break;
					}else if (valid == 4){ // Draw Two
						last_card = RemoveCard(player1,card_ind);
						showcard(player1,1);
						Draw_two(player2);
						printf("Adding Cards to Player 2 Deck\n");
						sleep(1);
						break;
					}else if (valid == 3 || valid == 2){ // reverse or skip
						i++; // Inc Turn So It comes back to player 1
						last_card = RemoveCard(player1,card_ind);
						showcard(player1,1);
						sleep(1);
						break;
					}else{
						last_card = RemoveCard(player1,card_ind);
						showcard(player1,1);
						sleep(1);
						break;
					}
					
				}
				
			}while (1); //Manual Break
			
		}else{ // Player 2 Turn
			do{
				showcard(player2,1);			
				printf("Player 2 Select Card From 1 - %d\nOr '0' to Pick Card from Deck\n:",player2->total_card);
				if (scanf("%d",&card_ind) == 0){
					ClearBuffer();
					continue;
				}else if (card_ind == 0){
					AddCard(player2,Deck[DeckCur_card]);
					DeckCur_card++;
					showcard(player2,1);
					printf("Card Added\n");
					sleep(1);
					break;

				}else if (card_ind < 1 || card_ind > player2->total_card){
					ClearBuffer();
					continue;
				}else{
					card_ind--;
					valid = ValidCard(player2->Dynamic_card[card_ind]);
					if (valid == 0){
						printf("Invalid Card\n");
						sleep(1);
						continue;
					}else if (valid == 6){// Draw_4
						last_card = RemoveCard(player2,card_ind);
						showcard(player2,1);
						Draw_Four(player1);
						showcard(player2,1);
						printf("Adding Cards to Player 1 Deck\n");
						sleep(1.5);
						break;
					}else if (valid == 5){ // Wild
						last_card = RemoveCard(player2,card_ind);
						showcard(player2,1);
						Draw();
						showcard(player2,1);
						sleep(1);
						break;
					}else if (valid == 4){ // Draw Two
						last_card = RemoveCard(player2,card_ind);
						showcard(player2,1);
						Draw_two(player1);
						printf("Adding Cards to Player 1 Deck\n");
						sleep(1.5);
						break;
					}else if (valid == 3 || valid == 2){ // reverse or skip
						i++; // Inc Turn So It comes back to player 2
						last_card = RemoveCard(player2,card_ind);
						showcard(player2,1);
						sleep(1);
						break;
					}else{
						last_card = RemoveCard(player2,card_ind);
						showcard(player2,1);
						sleep(1);
						break;
					}
					
				}
				
			}while (1); //Manual Break
			
			
		}
		i++; //Increase Turn
		Game = FinishCheck(player1,player2);
		if (Game == 1){
			break; // Game Finished
		}
		
	}
	system("cls");
	if (player1->total_card == 0){
		Player1_Won();
		User1_Score++;
	}else if (player2->total_card == 0){
		Player2_Won();
		User2_Score++;
	}else{
		player1->total_card>player2->total_card ? Player2_Won(): Player1_Won();
		player1->total_card>player2->total_card ? User2_Score++ : User1_Score++;
	}
	sleep(2);
	freeArray(player1);
	freeArray(player2);
	Menu();
	
}


void MultiGameLoop_Three(struct Player* player1,struct Player* player2,struct Player* player3){
	int i = 1; // Turns
	char dir = '+'; // Forward Move
	int card_ind;
	int valid;
	int Game = 0; //Terminate Game Loop 
	
	while (1){
		if (i == 1){ // User_1 Turn
			do{
				showcard(player1,3);
				printf("Player 1 Select Card From 1 - %d\nOr '0' to Pick Card from Deck\n:",player1->total_card);
				if (scanf("%d",&card_ind) == 0){
					ClearBuffer();
					continue;
				}else if (card_ind == 0){
					AddCard(player1,Deck[DeckCur_card]);
					DeckCur_card++;
					showcard(player1,3);
					printf("Card Added\n");
					sleep(1);
					if (dir == '+'){
						i++;
					}else{
						i = 3;
					}
					break;

				}else if (card_ind < 1 || card_ind > player1->total_card){
					ClearBuffer();
					continue;
				}else{
					card_ind--;
					valid = ValidCard(player1->Dynamic_card[card_ind]);
					if (valid == 0){
						printf("Invalid Card\n");
						sleep(1);
						continue;
					}else if (valid == 6){// Draw_4
						last_card = RemoveCard(player1,card_ind);
						showcard(player1,3);
						if (dir == '+'){
							Draw_Four(player2);
							i++;
						}else{
							Draw_Four(player3);
							i = 3;
						}
						showcard(player1,3);
						sleep(1);
						break;
					}else if (valid == 5){ // Wild
						last_card = RemoveCard(player1,card_ind);
						showcard(player1,3);
						Draw();
						showcard(player1,3);
						sleep(1);
						if (dir == '+'){
							i++;
						}else{
							i = 3;
						}
						break;
					}else if (valid == 4){ // Draw Two
						last_card = RemoveCard(player1,card_ind);
						showcard(player1,3);
						sleep(1);
						if (dir == '+'){
							Draw_two(player2);
							i++;
						}else{
							Draw_two(player3);
							i = 3;
						}
						break;
					}else if (valid == 2){ // reverse
						if (dir == '+'){ // Inc Turn So It comes to player 3
							dir = '-';
							i=3;
						}else{
							dir = '+'; // Player 2
							i++;
						}
						last_card = RemoveCard(player1,card_ind);
						showcard(player1,3);
						sleep(1);
						break;
					}else if(valid == 3){ // skip
						if (dir == '+'){
							i+=2; // comes to player 3
						}else{
							i = 2; // Comes to player 2
						}
						last_card = RemoveCard(player1,card_ind);
						showcard(player1,3);
						sleep(1);
						break;
						
					}else{
						last_card = RemoveCard(player1,card_ind);
						showcard(player1,3);
						sleep(1);
						if (dir == '+'){
							i++;
						}else{
							i = 3;
						}
						break;
					}
					
				}
				
			}while (1); //Manual Break
		}else if (i==2){ // User 2 Turn
			do{
				showcard(player2,3);
				printf("Player 2 Select Card From 1 - %d\nOr '0' to Pick Card from Deck\n:",player2->total_card);
				if (scanf("%d",&card_ind) == 0){
					ClearBuffer();
					continue;
				}else if (card_ind == 0){
					AddCard(player2,Deck[DeckCur_card]);
					DeckCur_card++;
					showcard(player2,3);
					printf("Card Added\n");
					sleep(1);
					if (dir == '+'){
						i++;
					}else{
						i--;
					}
					break;

				}else if (card_ind < 1 || card_ind > player2->total_card){
					ClearBuffer();
					continue;
				}else{
					card_ind--;
					valid = ValidCard(player2->Dynamic_card[card_ind]);
					if (valid == 0){
						printf("Invalid Card\n");
						sleep(1);
						continue;
					}else if (valid == 6){// Draw_4
						last_card = RemoveCard(player2,card_ind);
						showcard(player2,3);
						if (dir == '+'){
							Draw_Four(player3);
							i++;
						}else{
							Draw_Four(player1);
							i --;
						}
						showcard(player2,3);
						sleep(1);
						break;
					}else if (valid == 5){ // Wild
						last_card = RemoveCard(player2,card_ind);
						showcard(player2,3);
						Draw();
						showcard(player2,3);
						sleep(1);
						if (dir == '+'){
							i++;
						}else{
							i --;
						}
						break;
					}else if (valid == 4){ // Draw Two
						last_card = RemoveCard(player2,card_ind);
						showcard(player2,3);
						sleep(1);
						if (dir == '+'){
							Draw_two(player3);
							i++;
						}else{
							Draw_two(player1);
							i --;
						}
						break;
					}else if (valid == 2){ // reverse
						if (dir == '+'){ // Inc Turn So It comes to player 3
							dir = '-';
							i--;
						}else{
							dir = '+'; // Player 2
							i++;
						}
						last_card = RemoveCard(player2,card_ind);
						showcard(player2,3);
						sleep(1);
						break;
					}else if(valid == 3){ // skip
						if (dir == '+'){
							i = 1; // comes to player 1
						}else{
							i = 3; // Comes to player 3
						}
						last_card = RemoveCard(player2,card_ind);
						showcard(player2,3);
						sleep(1);
						break;
						
					}else{
						last_card = RemoveCard(player2,card_ind);
						showcard(player2,3);
						sleep(1);
						if (dir == '+'){
							i++;
						}else{
							i--;
						}
						break;
					}
					
				}
				
			}while (1); //Manual Break
			
		}else{//Player 3 Turn
			do{
				showcard(player3,3);
				printf("Player 3 Select Card From 1 - %d\nOr '0' to Pick Card from Deck\n:",player3->total_card);
				if (scanf("%d",&card_ind) == 0){
					ClearBuffer();
					continue;
				}else if (card_ind == 0){
					AddCard(player3,Deck[DeckCur_card]);
					DeckCur_card++;
					showcard(player3,3);
					printf("Card Added\n");
					sleep(1);
					if (dir == '+'){
						i = 1;
					}else{
						i--;
					}
					break;

				}else if (card_ind < 1 || card_ind > player3->total_card){
					ClearBuffer();
					continue;
				}else{
					card_ind--;
					valid = ValidCard(player3->Dynamic_card[card_ind]);
					if (valid == 0){
						printf("Invalid Card\n");
						sleep(1);
						continue;
					}else if (valid == 6){// Draw_4
						last_card = RemoveCard(player3,card_ind);
						showcard(player3,3);
						if (dir == '+'){
							Draw_Four(player1);
							i = 1;
						}else{
							Draw_Four(player2);
							i --;
						}
						showcard(player3,3);
						sleep(1);
						break;
					}else if (valid == 5){ // Wild
						last_card = RemoveCard(player3,card_ind);
						showcard(player3,3);
						Draw();
						showcard(player3,3);
						sleep(1);
						if (dir == '+'){
							i = 1;
						}else{
							i --;
						}
						break;
					}else if (valid == 4){ // Draw Two
						last_card = RemoveCard(player3,card_ind);
						showcard(player3,3);
						sleep(1);
						if (dir == '+'){
							Draw_two(player1);
							i=1;
						}else{
							Draw_two(player2);
							i --;
						}
						break;
					}else if (valid == 2){ // reverse
						if (dir == '+'){ // Dec Turn So It comes to player 2
							dir = '-';
							i--;
						}else{
							dir = '+'; // Player 2
							i =1 ;
						}
						last_card = RemoveCard(player3,card_ind);
						showcard(player3,3);
						sleep(1);
						break;
					}else if(valid == 3){ // skip
						if (dir == '+'){
							i = 2; // comes to player 2
						}else{
							i = 1; // Comes to player 1
						}
						last_card = RemoveCard(player3,card_ind);
						showcard(player3,3);
						sleep(1);
						break;
						
					}else{
						last_card = RemoveCard(player3,card_ind);
						showcard(player3,3);
						sleep(1);
						if (dir == '+'){
							i = 1;
						}else{
							i--;
						}
						break;
					}
					
				}
				
			}while (1); //Manual Break
		}
		Game = FinishCheckThree(player1,player2,player3);
		if (Game == 1){
			break;
		}
		
	}
	system("cls");
	if (player1->total_card == 0){
		Player1_Won();
		User1_Score++;
	}else if (player2->total_card == 0){
		User2_Score++;
		Player2_Won();
	}else if (player3->total_card == 0){
		User3_Score++;
		Player3_Won();
	}
	freeArray(player1);
	freeArray(player2);
	freeArray(player3);
	sleep(2);
	Menu();
	
}

void SingleGameLoop(struct Player* player1,struct Player* Bot){
	int i = 0; // Turns
	int card_ind;
	int valid;
	struct Card removed_card;
	int Game = 0; //Terminate Game Loop 
	
	while (1){ // Manual Break
		
		if (i % 2 ==0 ){ // Player 1 Turn
			do{			
				showcard(player1,2);
				printf("Player 1 Select Card From 1 - %d\nOr '0' to Pick Card from Deck\n:",player1->total_card);
				if (scanf("%d",&card_ind) == 0){
					ClearBuffer();
					continue;
				}else if (card_ind == 0){
					AddCard(player1,Deck[DeckCur_card]);
					DeckCur_card++;
					showcard(player1,2);
					printf("Player 1 DECK\n");
					printf("Card Added\n");
					sleep(2);
					break;

				}else if (card_ind < 1 || card_ind > player1->total_card){
					ClearBuffer();
					continue;
				}else{
					card_ind--;
					valid = ValidCard(player1->Dynamic_card[card_ind]);
					if (valid == 0){
						printf("Invalid Card\n");
						printf("Player 1 DECK\n");
						sleep(2);
						continue;
					}else if (valid == 6){// Draw_4
						last_card = RemoveCard(player1,card_ind);
						showcard(player1,2);
						printf("Player 1 DECK\n");
						Draw_Four(Bot);
						showcard(player1,2);
						printf("Player 1 DECK\n");
						sleep(2);
						break;
					}else if (valid == 5){ // Wild
						last_card = RemoveCard(player1,card_ind);
						showcard(player1,2);
						printf("Player 1 DECK\n");
						Draw();
						showcard(player1,2);
						printf("Player 1 DECK\n");
						sleep(2);
						break;
					}else if (valid == 4){ // Draw Two
						last_card = RemoveCard(player1,card_ind);
						showcard(player1,2);
						printf("Player 1 DECK\n");
						Draw_two(Bot);
						sleep(2);
						break;
					}else if (valid == 3 || valid == 2){ // reverse or skip
						i++; // Inc Turn So It comes back to player 1
						last_card = RemoveCard(player1,card_ind);
						showcard(player1,2);
						printf("Player 1 DECK\n");
						sleep(2);
						break;
					}else{
						last_card = RemoveCard(player1,card_ind);
						showcard(player1,2);
						printf("Player 1 DECK\n");
						sleep(2);
						break;
					}
					
				}
				
			}while (1); //Manual Break
		}else{
			showcard(Bot,2);
			printf("\nBOT TURN \n");
			sleep(2);
			valid = FindValid(Bot);
			if (valid == -1){
				AddCard(Bot,Deck[DeckCur_card]);
				DeckCur_card++;
				showcard(Bot,2);
				printf("\nCard Added\n");
				sleep(3);
			}else{ 
				if (Bot->Dynamic_card[valid].num == 14){ // WILD
					last_card.color = Color_Special(Bot);
					last_card.num = 14;
					RemoveCard(Bot,valid);
					showcard(Bot,2);
					printf("BOT DECK\n");
					sleep(3);
				}else if (Bot->Dynamic_card[valid].num == 15){ // DRAW 4
					Draw_Four_Bot(Bot,player1);
					RemoveCard(Bot,valid);
					showcard(Bot,2);
					printf("BOT DECK\n");
					sleep(3);
				}else if (Bot->Dynamic_card[valid].num == 13){ //Draw 2
					last_card = RemoveCard(Bot,valid);
					showcard(Bot,2);
					Draw_two(player1);
					printf("BOT DECK\n");
					sleep(3);				
				}else if (Bot->Dynamic_card[valid].num == 12 || Bot->Dynamic_card[valid].num == 11){
					i++; // Inc Turn So It comes back to Bot
					last_card = RemoveCard(Bot,valid);
					showcard(Bot,2);
					printf("BOT DECK\n");
					sleep(3);
				}else{ // No Special Card
					last_card = RemoveCard(Bot,valid);
					showcard(Bot,2);
					printf("BOT DECK\n");
					sleep(3);
					
				}
			}
					
		}
	i++; //Increase Turn
	Game = FinishCheck(player1,Bot);
	if (Game == 1){
			break; // Game Finished
		}
	}
	system("cls");
	if (player1->total_card == 0){
		Player1_Won();
		User1_Score++;
	}else if (Bot->total_card == 0){
		Bot_Score++;
		BotWon();
	}else{
		player1->total_card>Bot->total_card ? BotWon(): Player1_Won();
		player1->total_card>Bot->total_card ? Bot_Score++ : User1_Score++;
	}
	freeArray(player1);
	freeArray(Bot);
	sleep(2);
	Menu();
	
		
	
}

int FinishCheckThree(struct Player* player1,struct Player* player2,struct Player* player3){
	return (player1->total_card == 0 || player2->total_card == 0|| player3->total_card == 0 ||DeckCur_card >=112);
}

int showcard(struct Player* player,int display){
	system("cls");
	
	if (display == 2){
	printf("USER 1 Score = %d\tBOT Score = %d\n\n",User1_Score,Bot_Score);
	}
	else if (display == 1)
	{
		printf("USER 1 Score = %d\tUSER 2 Score = %d\n\n",User1_Score,User2_Score);
	}else{
		printf("USER 1 Score = %d\tUSER 2 Score = %d\tUSER 3 SCORE = %d\n\n",User1_Score,User2_Score,User3_Score);
	}
	printf("\n");
	
	int i=0,l = 0,n,o,z;
	int a = 0,b = 0,c = 0,d = 0,e = 0,f=0;

// Player 1 Cards

	l = player->total_card % 5;

	if(l != 0){
		n = player->total_card/5;
		o = 5;
		for(; i < n; i++){
			for(; f < o; f++){
            (f<9)?printf("    0%d      ",f+1):printf("    %d      ",f+1);
        }
        printf("\n");

		for(; a < o; a++){
			printf("----------- ");
		}

		printf("\n");

		for(; b < o; b++){
			z = player->Dynamic_card[b].num;
			(z<10)?printf("|0%d       | ",z):printf("|         | ");
		}
		
			printf("\n");

		for(; c < o; c++){
			z = player->Dynamic_card[c].num;
			if (z<10){
			char coll = player->Dynamic_card[c].color;
					printf("|    \033[%dm%c\033[0m\033[%dm    | ",color(coll),coll,background);
			}
			else{
				char coll = player->Dynamic_card[c].color;
				switch(z){
					case 11:{
							printf("|   \033[%dmREV\033[0m\033[%dm   | ",color(coll),background);
							break;
						}
						break;	
				
				case 12:{
							printf("|   \033[%dmSKP\033[0m\033[%dm   | ",color(coll),background);
							break;
						}
						break;
				
				case 13:{
							printf("|   \033[%dmDR2\033[0m\033[%dm   | ",color(coll),background);
							break;
						}
						break;
						
				case 14:{
						printf("|   WLD   | ");
							break;	
						}
						break;
				
				case 15:{
						printf("|   DR4   | ");
							break;	
						}
						break;
				
			}
			
		}
	}

			printf("\n");

		for(; d < o; d++){
			z = player->Dynamic_card[d].num;
			(z<10)?printf("|       0%d| ",z):printf("|         | ");
			}

				printf("\n");

		for(; e < o; e++){
			printf("----------- ");
		}
			printf("\n");
			o += 5;
	}

//------------------------------------------------------------------------

	for(i = 0; i < 1 ; i++){
		for(; f < player->total_card; f++){
            (f<9)?printf("    0%d      ",f+1):printf("    %d      ",f+1);
        }
        printf("\n");
		for(; a < player->total_card; a++){
			printf("----------- ");
		}

		printf("\n");

		for(; b < player->total_card; b++){
			z = player->Dynamic_card[b].num;
			(z<10)?printf("|0%d       | ",z):printf("|         | ");
		}
			printf("\n");

		for(; c < player->total_card; c++){
			z = player->Dynamic_card[c].num;
			if (z<10){
			char coll = player->Dynamic_card[c].color;
					printf("|    \033[%dm%c\033[0m\033[%dm    | ",color(coll),coll,background);
			}
			else{
				char coll = player->Dynamic_card[c].color;
				switch(z){
					case 11:{
							printf("|   \033[%dmREV\033[0m\033[%dm   | ",color(coll),background);
							break;
						}
						break;	
				
				case 12:{
							printf("|   \033[%dmSKP\033[0m\033[%dm   | ",color(coll),background);
							break;
						}
						break;
				
				case 13:{
							printf("|   \033[%dmDR2\033[0m\033[%dm   | ",color(coll),background);
							break;
						}
						break;
						
				case 14:{
						printf("|   WLD   | ");
							break;	
						}
						break;
				
				case 15:{
						printf("|   DR4   | ");
							break;	
						}
						break;
				
			}
			
		}
	}
	

			printf("\n");

		for(; d < player->total_card; d++){
			z = player->Dynamic_card[d].num;
			(z<=9)?printf("|       0%d| ",z):printf("|         | ");
			}
		
			printf("\n");

		for(; e < player->total_card; e++){
			printf("----------- ");
		}
			printf("\n");

		}
	}

	if(l == 0){
		
		n = player->total_card/5;
		o = 5;
		for(; i < n; i++){
		for(; f < o; f++){
            (f<9)?printf("    0%d      ",f+1):printf("    %d      ",f+1);
        }
        printf("\n");
		for(; a < o; a++){
			printf("----------- ");
		}

		printf("\n");

		for(; b < o; b++){
			z = player->Dynamic_card[b].num;
			(z<10)?printf("|0%d       | ",z):printf("|         | ");
		}
		
			printf("\n");

		for(; c < o; c++){
			z = player->Dynamic_card[c].num;
			if (z<10){
			char coll = player->Dynamic_card[c].color;
					printf("|    \033[%dm%c\033[0m\033[%dm    | ",color(coll),coll,background);
			}
			else{
				char coll = player->Dynamic_card[c].color;
				switch(z){
					case 11:{
							printf("|   \033[%dmREV\033[0m\033[%dm   | ",color(coll),background);
							break;
						}
						break;	
				
				case 12:{
							printf("|   \033[%dmSKP\033[0m\033[%dm   | ",color(coll),background);
							break;
						}
						break;
				
				case 13:{
							printf("|   \033[%dmDR2\033[0m\033[%dm   | ",color(coll),background);
							break;
						}
						break;
						
				case 14:{
						printf("|   WLD   | ");
							break;	
						}
						break;
				
				case 15:{
						printf("|   DR4   | ");
							break;	
						}
						break;
				
			}
			
		}
	}

			printf("\n");

		for(; d < o; d++){
			z = player->Dynamic_card[d].num;
			(z<=9)?printf("|       0%d| ",z):printf("|         | ");
			}

				printf("\n");

		for(; e < o; e++){
			printf("----------- ");
		}
			printf("\n");
			o += 5;
	}
	}
	Lcard();

}

int color(int x){
	return (x == 'R') ? 31 :(x == 'G') ? 32 :(x == 'Y') ? 33 :(x == 'B') ? 34 :0;
}

void Lcard(){
	if(last_card.num == -1){
	printf("\t\t\t\t\t\t\t\t\t\t\t\t\t  L A S T\n");
	printf("\t\t\t\t\t\t\t\t\t\t\t\t\t-----------\n");
	printf("\t\t\t\t\t\t\t\t\t\t\t\t\t|         |\n");
	printf("\t\t\t\t\t\t\t\t\t\t\t\t\t|         |\n");
	printf("\t\t\t\t\t\t\t\t\t\t\t\t\t|         |\n");
	printf("\t\t\t\t\t\t\t\t\t\t\t\t\t-----------\n");
	printf("\t\t\t\t\t\t\t\t\t\t\t\t\t  C A R D\n");
		
	}
	else if(last_card.num == 14){
	//last_card.num
	printf("\t\t\t\t\t\t\t\t\t\t\t\t\t  L A S T\n");
	printf("\t\t\t\t\t\t\t\t\t\t\t\t\t-----------\n");
	printf("\t\t\t\t\t\t\t\t\t\t\t\t\t|         |\n");
	printf("\t\t\t\t\t\t\t\t\t\t\t\t\t|   \033[%dmWLD\033[0m\033[%dm   |\n",color(last_card.color),background);
	printf("\t\t\t\t\t\t\t\t\t\t\t\t\t|         |\n");
	printf("\t\t\t\t\t\t\t\t\t\t\t\t\t-----------\n");
	printf("\t\t\t\t\t\t\t\t\t\t\t\t\t  C A R D\n");
}

else if(last_card.num == 15){

	printf("\t\t\t\t\t\t\t\t\t\t\t\t\t  L A S T\n");
	printf("\t\t\t\t\t\t\t\t\t\t\t\t\t-----------\n");
	printf("\t\t\t\t\t\t\t\t\t\t\t\t\t|         |\n");
	printf("\t\t\t\t\t\t\t\t\t\t\t\t\t|   \033[%dmDR4\033[0m\033[%dm   |\n",color(last_card.color),background);
	printf("\t\t\t\t\t\t\t\t\t\t\t\t\t|         |\n");
	printf("\t\t\t\t\t\t\t\t\t\t\t\t\t-----------\n");
	printf("\t\t\t\t\t\t\t\t\t\t\t\t\t  C A R D\n");
}

else if(last_card.num == 13){

	printf("\t\t\t\t\t\t\t\t\t\t\t\t\t  L A S T\n");
	printf("\t\t\t\t\t\t\t\t\t\t\t\t\t-----------\n");
	printf("\t\t\t\t\t\t\t\t\t\t\t\t\t|         |\n");
	printf("\t\t\t\t\t\t\t\t\t\t\t\t\t|   \033[%dmDR2\033[0m\033[%dm   |\n",color(last_card.color),background);
	printf("\t\t\t\t\t\t\t\t\t\t\t\t\t|         |\n");
	printf("\t\t\t\t\t\t\t\t\t\t\t\t\t-----------\n");
	printf("\t\t\t\t\t\t\t\t\t\t\t\t\t  C A R D\n");
}

else if(last_card.num == 12){

	printf("\t\t\t\t\t\t\t\t\t\t\t\t\t  L A S T\n");
	printf("\t\t\t\t\t\t\t\t\t\t\t\t\t-----------\n");
	printf("\t\t\t\t\t\t\t\t\t\t\t\t\t|         |\n");
	printf("\t\t\t\t\t\t\t\t\t\t\t\t\t|   \033[%dmSKP\033[0m\033[%dm   |\n",color(last_card.color),background);
	printf("\t\t\t\t\t\t\t\t\t\t\t\t\t|         |\n");
	printf("\t\t\t\t\t\t\t\t\t\t\t\t\t-----------\n");
	printf("\t\t\t\t\t\t\t\t\t\t\t\t\t  C A R D\n");
}
else if(last_card.num == 11){

	printf("\t\t\t\t\t\t\t\t\t\t\t\t\t  L A S T\n");
	printf("\t\t\t\t\t\t\t\t\t\t\t\t\t-----------\n");
	printf("\t\t\t\t\t\t\t\t\t\t\t\t\t|         |\n");
	printf("\t\t\t\t\t\t\t\t\t\t\t\t\t|   \033[%dmREV\033[0m\033[%dm   |\n",color(last_card.color),background);
	printf("\t\t\t\t\t\t\t\t\t\t\t\t\t|         |\n");
	printf("\t\t\t\t\t\t\t\t\t\t\t\t\t-----------\n");
	printf("\t\t\t\t\t\t\t\t\t\t\t\t\t  C A R D\n");
}
else{

	printf("\t\t\t\t\t\t\t\t\t\t\t\t\t  L A S T\n");
	printf("\t\t\t\t\t\t\t\t\t\t\t\t\t-----------\n");
	printf("\t\t\t\t\t\t\t\t\t\t\t\t\t|0%d       |\n",last_card.num);
	printf("\t\t\t\t\t\t\t\t\t\t\t\t\t|    \033[%dm%c\033[0m\033[%dm    |\n",color(last_card.color),last_card.color,background);
	printf("\t\t\t\t\t\t\t\t\t\t\t\t\t|       0%d|\n",last_card.num);
	printf("\t\t\t\t\t\t\t\t\t\t\t\t\t-----------\n");
	printf("\t\t\t\t\t\t\t\t\t\t\t\t\t  C A R D\n");
}
	
}

void BotWon(){
	system("cls");
	printf("\n\n\n\n\n");
    printf("\t\t\t\t*****      * *     *****        *     *        * *      *       *\n");
    printf("\t\t\t\t*    *   *     *     *          *     *      *     *    **      *\n");
    printf("\t\t\t\t*    *   *     *     *          *     *      *     *    * *     *\n");
    printf("\t\t\t\t*****    *     *     *          *     *      *     *    *  *    *\n");
    printf("\t\t\t\t*    *   *     *     *          * * * *      *     *    *   *   *\n");
    printf("\t\t\t\t*    *    *   *      *          *  *  *       *   *     *    *  *\n");
    printf("\t\t\t\t*****      ***       *          *  *  *        ***      *     * *\n");
    sleep(3);
}

void Player1_Won(){
	system("cls");
	printf("\n\n\n\n");
    printf("*****    *           *       *       *   *******   *****           *        *     *       * *      *       *\n");
    printf("*    *   *          * *       *     *    *         *    *         **        *     *     *     *    **      *\n");
    printf("*    *   *         *   *       *   *     *         *    *        * *        *     *     *     *    * *     *\n");
    printf("*****    *        *     *       * *      *******   *****           *        *     *     *     *    *  *    *\n");
    printf("*        *       *********       *       *         *   *           *        * * * *     *     *    *   *   *\n");
    printf("*        *      *         *      *       *         *    *          *        *  *  *      *   *     *    *  *\n");
    printf("*        ***** *           *     *       *******   *     *     ********     *  *  *       ***      *     * *\n");
    sleep(3);
}

void Player2_Won(){
	system("cls");
	printf("\n\n\n\n");
    printf("*****    *           *       *       *   *******   *****        *****         *     *       * *      *       *\n");
    printf("*    *   *          * *       *     *    *         *    *       *    *        *     *     *     *    **      *\n");
    printf("*    *   *         *   *       *   *     *         *    *           *         *     *     *     *    * *     *\n");
    printf("*****    *        *     *       * *      *******   *****          *           *     *     *     *    *  *    *\n");
    printf("*        *       *********       *       *         *   *         *            * * * *     *     *    *   *   *\n");
    printf("*        *      *         *      *       *         *    *       *             *  *  *      *   *     *    *  *\n");
    printf("*        ***** *           *     *       *******   *     *     *******        *  *  *       ***      *     * *\n");
	sleep(3);
}

void Player3_Won(){
	system("cls");
	printf("\n\n\n\n");
    printf("*****    *           *       *       *   *******   *****        *****        *     *       * *      *       *\n");
    printf("*    *   *          * *       *     *    *         *    *           *        *     *     *     *    **      *\n");
    printf("*    *   *         *   *       *   *     *         *    *          *         *     *     *     *    * *     *\n");
    printf("*****    *        *     *       * *      *******   *****            *        *     *     *     *    *  *    *\n");
    printf("*        *       *********       *       *         *   *            *        * * * *     *     *    *   *   *\n");
    printf("*        *      *         *      *       *         *    *       *   *        *  *  *      *   *     *    *  *\n");
    printf("*        ***** *           *     *       *******   *     *       ***         *  *  *       ***      *     * *\n");
	sleep(3);
	
}

int colorchange(){
	system("cls");
    int option;
    printf("1-Reset to Default\n2-Set New Color\n-->");
    if (scanf("%d",&option) != 1){
		ClearBuffer();
    	return -1;
	}
	if (option == 1){
    	printf("\033[0m\n");
    	Menu();
	}
	else if (option == 2){
		do {
			printf("Enter Background Color:\n40: Black\n41: Red\n42: Green\n43: Yellow\n44: Blue\n45: Magenta\n46: Cyan\n47: White\n-->");
	    	if (scanf("%d",&background) != 1){
	    		ClearBuffer();
	    		return -1;
			}
			if (background < 40 || background > 47){
				printf("Out of Range\n");
			}
		}
		while (background < 40 || background > 47);
		printf("\033[%dm\n",background);
	}
		
		Menu();
   	 	
   	 	return 0;
}

void SaveScore(){
	FILE *file = fopen("Score.txt","w");
	fprintf(file,"%d\n%d\n%d\n%d",User1_Score,User2_Score,User3_Score,Bot_Score);
	fclose(file);
	printf("Score Saved\n");
	sleep(1);
	Menu();
}

void Restore(){
	FILE *file = fopen("Score.txt","r");
	if (file == NULL){
		printf("No Saved Scores");
		sleep(1);
		Menu();
	}
	fscanf(file,"%d\n%d\n%d\n%d",&User1_Score,&User2_Score,&User3_Score,&Bot_Score);
	printf("Progress Restored\n\n");
	fclose(file);
	sleep(1);
	Menu();
}

void ResetScore(){
	printf("Score Resetted\n");
	User1_Score = 0;
	User2_Score = 0;
	User3_Score = 0;
	Bot_Score = 0;
	const char *file = "Score.txt";
	if (remove(file) == 0){
		printf("Succesfully Deleted Saved Scores");
	}else{
		printf("Scores file did not exists");
	}
	sleep(1.5);
	Menu();
}