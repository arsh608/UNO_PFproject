#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cctype>

using namespace std;

struct Card {
    // R, G, Y, B
    // Special Cards
    // Reverse,  Skip,   Draw 2,   Wild  and  Draw_4
    // 'C'11,   'C'12,   'C' 13,   W 14,   W 15
    // 'C' = Color Of That Card

    char color;
    int num;
};


struct Player {
    Card* Dynamic_card;
    int total_card;
};

// GLOBAL
Card Deck[112];
Card last_card;
int DeckTotal;
int DeckCur_card = 0;
int background = 0;

// SCORES
int User1_Score = 0;
int User2_Score = 0;
int User3_Score = 0;
int Bot_Score = 0;

// PROTOTYPES
void ReadDeck();
void ShuffleDeck();
void ShowDeck();
void AllocateMemory(int size, struct Player* player);
void freeArray(struct Player* player);
void Distribute(int len, struct Player* player);
int showcard(struct Player* player, int display);
void Initialize(struct Player* player1, struct Player* player2);
void AddCard(struct Player* player, struct Card card);
struct Card RemoveCard(struct Player* player, int index);
int ValidCard(struct Card card);
void Draw_Four(struct Player* player);
void Draw();
void MultiGameLoop(struct Player* player1, struct Player* player2);
void Draw_two(struct Player* player);
void Lcard();
int color();
void multiplayer();
void ClearBuffer();
void Menu();
int FindValid(struct Player* Bot);
char Color_Special(struct Player* Bot);
void Draw_Four_Bot(struct Player* Bot, struct Player* player);
void SingleGameLoop(struct Player* player1, struct Player* Bot);
void SinglePlayer();
int colorchange();
void ResetScore();
void SaveScore();
void Restore();
void MultiGameLoop_Three(struct Player* player1, struct Player* player2, struct Player* player3);
int FinishCheckThree(struct Player* player1, struct Player* player2, struct Player* player3);
void ThreePlayer();
void submenu();
void other();
void BotWon();
void Player1_Won();
void Player2_Won();
void Player3_Won();
void Menu();

int main() {
    Menu();
    return 0;
}

void Menu() {

    std::cout << "\t\t\t\t\t\t\t\t------------------------------------\n";
    std::cout << "\t\t\t\t\t\t\t\t| *     *  **       *     *****    |\n";
    std::cout << "\t\t\t\t\t\t\t\t| *     *  * *      *    *     *   |\n";
    std::cout << "\t\t\t\t\t\t\t\t| *     *  * *      *   *       *  |\n";
    std::cout << "\t\t\t\t\t\t\t\t| *     *  *  *     *  *         * |\n";
    std::cout << "\t\t\t\t\t\t\t\t| *     *  *   *    *  *         * |\n";
    std::cout << "\t\t\t\t\t\t\t\t| *     *  *    *   *  *         * |\n";
    std::cout << "\t\t\t\t\t\t\t\t| *     *  *     *  *   *       *  |\n";
    std::cout << "\t\t\t\t\t\t\t\t|  *   *   *      * *    *     *   |\n";
    std::cout << "\t\t\t\t\t\t\t\t|    *     *       **     *****    |\n";
    std::cout << "\t\t\t\t\t\t\t\t------------------------------------\n";

    std::cout << "\n\nUser1Score = " << User1_Score << "\t User2Score = " << User2_Score << "\t User3Score = " << User3_Score << "\t BotScore = " << Bot_Score << "\n\n";

    int opp;
    do {
        std::cout << "Menu\n1)Single Player\n2)MultiPlayer\n3)Other Menu\n4)Exit\nOption:";
        while (!(std::cin >> opp)) {
            ClearBuffer();
            std::cout << "Invalid input. Please enter a number: ";
        }
        ClearBuffer();
    } while (false);  // Update the loop condition based on your needs

    switch (opp) {
    case 1: {
        system("cls");
        SinglePlayer();
        break;
    }

    case 2: {
        system("cls");
        submenu();
        break;
    }

    case 3: {
        system("cls");
        other();
        break;
    }

    case 4: {
        std::cout << "\nExiting...";
        std::cout << std::endl;
        exit(1);
        break;
    }

    default: {
        std::cout <<"WRONG INPUT";
        Menu();
        break;
    }
    }
}

void submenu() {
    int opp;
    std::cout << "MENU\n1)Two-Player\n2)Three-Player\n3)Back to Main Menu\n->";
    while (!(std::cin >> opp)) {
        ClearBuffer();
        std::cout << "Invalid input. Please enter a number: ";
    }
    ClearBuffer();

    switch (opp) {
    case 1: {
        multiplayer();
        break;
    }

    case 2: {
        ThreePlayer();
        break;
    }

    case 3: {
        system("cls");
        Menu();
        break;
    }

    default: {
        std::cout << "Wrong Input!";
        submenu();
        break;
    }
    }
}

void other() {
    int opp;
    std::cout <<"1)Color Change\n2)Save Score\n3)Restore Score\n4)Reset Score\n5)Back to Main Menu\n->";
    while (!(std::cin>>opp)) {
        ClearBuffer();
        std::cout <<"Invalid input. Please enter a number: ";
    }
    ClearBuffer();
    switch (opp) {
    case 1: {
        colorchange();
        break;
    }

    case 2: {
        SaveScore();
        break;
    }

    case 3: {
        Restore();
        break;
    }

    case 4: {
        ResetScore();
        break;
    }

    case 5: {
        Menu();
        break;
    }

    default: {
        std::cout <<"Wrong Input!";
        system("cls");
        other();
        break;
    }
    }
}

void multiplayer() {
    Player player1;
    Player player2;
    Initialize(&player1, &player2);
    MultiGameLoop(&player1, &player2);
}

void ThreePlayer() {
    Player player1;
    Player player2;
    Player player3;
    Initialize(&player1, &player2);
    AllocateMemory(6, &player3);
    Distribute(6, &player3);
    MultiGameLoop_Three(&player1, &player2, &player3);
}

void SinglePlayer() {
    Player player1;
    Player Bot;
    Initialize(&player1, &Bot);
    SingleGameLoop(&player1, &Bot);
}

void Initialize(Player* player1, Player* player2) {
    ReadDeck();
    ShuffleDeck();
    DeckCur_card = 0;
    AllocateMemory(6, player1);
    AllocateMemory(6, player2);
    Distribute(6, player1);
    Distribute(6, player2);
    last_card.color = '\0';
    last_card.num = -1;
}

void ReadDeck() {
    std::ifstream file("Cards.txt");
    int i = 0;

    if (!file.is_open()) {
        std::cout << "Unable to open file" << std::endl;
    }
    else {
        while (file >> Deck[i].color >> Deck[i].num) {
            i++;
        }
        DeckTotal = i;
        DeckCur_card = 0;
    }
    file.close();
}

void ShuffleDeck() {
    srand(static_cast<unsigned int>(time(nullptr)));

    for (int i = DeckTotal - 1; i > 0; i--) 
    {
        int j = rand() % (i + 1);
        std::swap(Deck[i], Deck[j]);
    }
}

void ShowDeck() {
    for (int i = 0; i < DeckTotal; i++) {
        std::cout << Deck[i].color << Deck[i].num << std::endl;
    }
}


void AllocateMemory(int size, Player* player) {
    player->Dynamic_card = new Card[size];
    player->total_card = size;
}

void freeArray(Player* player) {
    delete[] player->Dynamic_card;
    player->Dynamic_card = nullptr;
    player->total_card = 0;
}

void Distribute(int len, Player* player) {
    for (int i = 0; i < len; i++) {
        player->Dynamic_card[i].color = Deck[DeckCur_card].color;
        player->Dynamic_card[i].num = Deck[DeckCur_card].num;
        DeckCur_card++;
    }
}

void AddCard(Player* player, Card card) {
    if (DeckCur_card >= 112) {
        std::cout << "\nDraw\nDeck Finished\n"; // To encounter edge case
        Menu();
    }

    player->total_card++;

    Card* newDynamicCard = new Card[player->total_card];
    std::copy(player->Dynamic_card, player->Dynamic_card + (player->total_card - 1), newDynamicCard);

    newDynamicCard[player->total_card - 1] = card;

    delete[] player->Dynamic_card;
    player->Dynamic_card = newDynamicCard;
}

Card RemoveCard(Player* player, int index) {
    Card removedCard = player->Dynamic_card[index];

    for (int i = index; i < player->total_card - 1; i++) {
        player->Dynamic_card[i] = player->Dynamic_card[i + 1];
    }

    player->total_card--;

    Card* newDynamicCard = new Card[player->total_card];
    std::copy(player->Dynamic_card, player->Dynamic_card + player->total_card, newDynamicCard);

    delete[] player->Dynamic_card;
    player->Dynamic_card = newDynamicCard;

    return removedCard;
}

int ValidCard(Card card) {

    // Reverse  Skip  Draw 2 Wild and Wild Draw 4
    // 'C'11   'C'12  'C' 13     W 14     W 15
    // 'C' = Color of that card

    if (card.num == 15) {
        return 6; // Wild_4
    }
    else if (card.num == 14) {
        return 5; // Wild
    }

    if (card.num == 13 && (card.color == last_card.color || card.num == last_card.num || last_card.num == -1)) {
        return 4; // Draw 2
    }

    if (card.num == 12 && (card.color == last_card.color || card.num == last_card.num || last_card.num == -1)) {
        return 3; // Skip
    }

    if (card.num == 11 && (card.color == last_card.color || card.num == last_card.num || last_card.num == -1)) {
        return 2; // Reverse
    }

    if (card.num == 11 || card.num == 12 || card.num == 13) {
        return 0;
    }

    return (card.color == last_card.color || card.num == last_card.num || last_card.num == -1);
}

int FindValid(Player* Bot) {

    // For Single Player
    int special_card = -1;
    for (int i = 0; i < Bot->total_card; i++) {
        int Valid = ValidCard(Bot->Dynamic_card[i]);
        if (Valid == 15 || Valid == 14) {
            special_card = i; // For End
        }
        else if (Valid > 0) {
            return i;
        }
        else {
            continue;
        }
    }
    return special_card; // either -1 meaning no Valid or Index of Special Card
}

char Color_Special(Player* Bot) {
    int Count[4] = { 0, 0, 0, 0 }; // R, G, B, Y
    for (int i = 0; i < Bot->total_card; i++) {
        switch (Bot->Dynamic_card[i].color) {
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

    // Find Max In Array
    int index = 0;
    int Max = Count[0];
    for (int i = 1; i < 4; i++) {
        if (Count[i] > Max) {
            Max = Count[i];
            index = i;
        }
    }

    return (index == 0 ? 'R' : index == 1 ? 'G' : index == 2 ? 'B' : 'Y');
}

void Draw_Four_Bot(Player* Bot, Player* player) {
    last_card.color = Color_Special(Bot);
    last_card.num = 15;
    for (int i = 0; i < 4; i++) {
        AddCard(player, Deck[DeckCur_card]); // Add In Players Deck
        DeckCur_card++;
    }
}

void Draw_Four(Player* player) {
    char col;
    do {
        std::cout << "Enter Color For Card: ";
        if (!(std::cin >> col)) {
            ClearBuffer();
            continue;
        }
        else {
            col = toupper(col);
            ClearBuffer();
        }
    } while (col != 'R' && col != 'G' && col != 'Y' && col != 'B');

    last_card.color = col;
    last_card.num = 15;
    for (int i = 0; i < 4; i++) {
        AddCard(player, Deck[DeckCur_card]);
        DeckCur_card++;
    }
}

void Draw() {
    char col;
    do {
        std::cout << "Enter Color For Card: ";
        if (!(std::cin>>col)) {
            ClearBuffer();
            continue;
        }
        else {
            col = std::toupper(col);
            ClearBuffer();
        }
    } while (col != 'R' && col != 'G' && col != 'Y' && col != 'B');

    last_card.color = col;
    last_card.num = 14;
}

void Draw_two(Player* player) {
    for (int i = 0; i < 2; i++) {
        AddCard(player, Deck[DeckCur_card]);
        DeckCur_card++;
    }
}

int FinishCheck(Player* player1, Player* player2) {
    return (player1->total_card == 0 || player2->total_card == 0 || DeckCur_card >= 112);
}

void ClearBuffer() {
    char c;
    while ((c = std::getchar()) != '\n');
}

void MultiGameLoop(Player* player1, Player* player2) {
    int i = 0;
    int card_ind;
    int valid;
    int Game = 0; // Terminate Game Loop

    while (true) { // Manual Break

        if (i % 2 == 0) { // Player 1 Turn
            do {
                showcard(player1, 1);
                std::cout << "Player 1 Select Card From 1 - " << player1->total_card
                    << "\nOr '0' to Pick Card from Deck\n:";
                if (!(std::cin >> card_ind)) {
                    ClearBuffer();
                    continue;
                }
                else if (card_ind == 0) {
                    AddCard(player1, Deck[DeckCur_card]);
                    DeckCur_card++;
                    showcard(player1, 1);
                    std::cout << "Card Added\n";
                    break;
                }
                else if (card_ind < 1 || card_ind > player1->total_card) {
                    ClearBuffer();
                    continue;
                }
                else {
                    card_ind--;
                    valid = ValidCard(player1->Dynamic_card[card_ind]);
                    if (valid == 0) {
                        std::cout << "Invalid Card\n";
                        continue;
                    }
                    else if (valid == 6) { // Draw_4
                        last_card = RemoveCard(player1, card_ind);
                        showcard(player1, 1);
                        Draw_Four(player2);
                        showcard(player1, 1);
                        std::cout << "Adding Cards to Player 2 Deck\n";
                        break;
                    }
                    else if (valid == 5) { // Wild
                        last_card = RemoveCard(player1, card_ind);
                        showcard(player1, 1);
                        Draw();
                        showcard(player1, 1);
                        break;
                    }
                    else if (valid == 4) { // Draw 2
                        last_card = RemoveCard(player1, card_ind);
                        showcard(player1, 1);
                        Draw_two(player2);
                        std::cout << "Adding Cards to Player 2 Deck\n";
                        break;
                    }
                    else if (valid == 3 || valid == 2) { // Reverse or Skip
                        i++; // Increment Turn So It comes back to player 1
                        last_card = RemoveCard(player1, card_ind);
                        showcard(player1, 1);
                        break;
                    }
                    else {
                        last_card = RemoveCard(player1, card_ind);
                        showcard(player1, 1);
                        break;
                    }
                }
            } while (true); // Manual Break

        }
        else { // Player 2 Turn
            do {
                showcard(player2, 1);
                std::cout << "Player 2 Select Card From 1 - " << player2->total_card
                    << "\nOr '0' to Pick Card from Deck\n:";
                if (!(std::cin >> card_ind)) {
                    ClearBuffer();
                    continue;
                }
                else if (card_ind == 0) {
                    AddCard(player2, Deck[DeckCur_card]);
                    DeckCur_card++;
                    showcard(player2, 1);
                    std::cout << "Card Added\n";
                    break;
                }
                else if (card_ind < 1 || card_ind > player2->total_card) {
                    ClearBuffer();
                    continue;
                }
                else {
                    card_ind--;
                    valid = ValidCard(player2->Dynamic_card[card_ind]);
                    if (valid == 0) {
                        std::cout << "Invalid Card\n";
                        continue;
                    }
                    else if (valid == 6) { // Draw_4
                        last_card = RemoveCard(player2, card_ind);
                        showcard(player2, 1);
                        Draw_Four(player1);
                        showcard(player2, 1);
                        std::cout << "Adding Cards to Player 1 Deck\n";
                        break;
                    }
                    else if (valid == 5) { // Wild
                        last_card = RemoveCard(player2, card_ind);
                        showcard(player2, 1);
                        Draw();
                        showcard(player2, 1);
                        break;
                    }
                    else if (valid == 4) { // Draw 2
                        last_card = RemoveCard(player2, card_ind);
                        showcard(player2, 1);
                        Draw_two(player1);
                        std::cout << "Adding Cards to Player 1 Deck\n";
                        break;
                    }
                    else if (valid == 3 || valid == 2) { // Reverse or Skip
                        i++; // Increment Turn So It comes back to player 2
                        last_card = RemoveCard(player2, card_ind);
                        showcard(player2, 1);
                        break;
                    }
                    else {
                        last_card = RemoveCard(player2, card_ind);
                        showcard(player2, 1);
                        break;
                    }
                }
            } while (true); // Manual Break
        }

        i++; // Increment Turn
        Game = FinishCheck(player1, player2);
        if (Game == 1) {
            break; // Game End
        }
    }

    system("cls");
    if (player1->total_card == 0) {
        Player1_Won();
        User1_Score++;
    }
    else if (player2->total_card == 0) {
        Player2_Won();
        User2_Score++;
    }
    else {
        player1->total_card > player2->total_card ? Player2_Won() : Player1_Won();
        player1->total_card > player2->total_card ? User2_Score++ : User1_Score++;
    }
    freeArray(player1);
    freeArray(player2);
    Menu();
}

void MultiGameLoop_Three(struct Player* player1, struct Player* player2, struct Player* player3) {
    int i = 1; // Turns
    char dir = '+'; // Forward Move
    int card_ind;
    int valid;
    int Game = 0; // Terminate Game Loop 

    while (1) {
        if (i == 1) { // User_1 Turn
            do {
                showcard(player1, 3);
                std::cout << "Player 1 Select Card From 1 - " << player1->total_card << "\nOr '0' to Pick Card from Deck\n:";
                if (!(cin >> card_ind) == 0) {
                    ClearBuffer();
                    continue;
                }
                else if (card_ind == 0) {
                    AddCard(player1, Deck[DeckCur_card]);
                    DeckCur_card++;
                    showcard(player1, 3);
                    std::cout << "Card Added\n";
                    if (dir == '+') {
                        i++;
                    }
                    else {
                        i = 3;
                    }
                    break;
                }
                else if (card_ind < 1 || card_ind > player1->total_card) {
                    ClearBuffer();
                    continue;
                }
                else {
                    card_ind--;
                    valid = ValidCard(player1->Dynamic_card[card_ind]);
                    if (valid == 0) {
                        std::cout << "Invalid Card\n";
                        continue;
                    }
                    else if (valid == 6) { // Draw_4
                        last_card = RemoveCard(player1, card_ind);
                        showcard(player1, 3);
                        if (dir == '+') {
                            Draw_Four(player2);
                            i++;
                        }
                        else {
                            Draw_Four(player3);
                            i = 3;
                        }
                        showcard(player1, 3);
                        break;
                    }
                    else if (valid == 5) { // Wild
                        last_card = RemoveCard(player1, card_ind);
                        showcard(player1, 3);
                        Draw();
                        showcard(player1, 3);
                        if (dir == '+') {
                            i++;
                        }
                        else {
                            i = 3;
                        }
                        break;
                    }
                    else if (valid == 4) { // Draw 2
                        last_card = RemoveCard(player1, card_ind);
                        showcard(player1, 3);
                        if (dir == '+') {
                            Draw_two(player2);
                            i++;
                        }
                        else {
                            Draw_two(player3);
                            i = 3;
                        }
                        break;
                    }
                    else if (valid == 2) { // Reverse
                        if (dir == '+') { // Increment Turn So It comes to player 3
                            dir = '-';
                            i = 3;
                        }
                        else {
                            dir = '+'; // Player 2
                            i++;
                        }
                        last_card = RemoveCard(player1, card_ind);
                        showcard(player1, 3);
                        break;
                    }
                    else if (valid == 3) { // Skip
                        if (dir == '+') {
                            i += 2; // Comes to Player 3
                        }
                        else {
                            i = 2; // Comes to Player 2
                        }
                        last_card = RemoveCard(player1, card_ind);
                        showcard(player1, 3);
                        break;
                    }
                    else {
                        last_card = RemoveCard(player1, card_ind);
                        showcard(player1, 3);
                        if (dir == '+') {
                            i++;
                        }
                        else {
                            i = 3;
                        }
                        break;
                    }

                }

            } while (1); //Manual Break
        }
        else if (i == 2) { // User2 Turn
            do {
                showcard(player2, 3);
                std::cout << "Player 2 Select Card From 1 - " << player2->total_card << "\nOr '0' to Pick Card from Deck\n:";
                if (!(cin >> card_ind) == 0) {
                    ClearBuffer();
                    continue;
                }
                else if (card_ind == 0) {
                    AddCard(player2, Deck[DeckCur_card]);
                    DeckCur_card++;
                    showcard(player2, 3);
                    std::cout << "Card Added\n";
                    if (dir == '+') {
                        i++;
                    }
                    else {
                        i--;
                    }
                    break;
                }
                else if (card_ind < 1 || card_ind > player2->total_card) {
                    ClearBuffer();
                    continue;
                }
                else {
                    card_ind--;
                    valid = ValidCard(player2->Dynamic_card[card_ind]);
                    if (valid == 0) {
                        std::cout << "Invalid Card\n";
                        continue;
                    }
                    else if (valid == 6) { // Draw_4
                        last_card = RemoveCard(player2, card_ind);
                        showcard(player2, 3);
                        if (dir == '+') {
                            Draw_Four(player3);
                            i++;
                        }
                        else {
                            Draw_Four(player1);
                            i--;
                        }
                        showcard(player2, 3);
                        break;
                    }
                    else if (valid == 5) { // Wild
                        last_card = RemoveCard(player2, card_ind);
                        showcard(player2, 3);
                        Draw();
                        showcard(player2, 3);
                        if (dir == '+') {
                            i++;
                        }
                        else {
                            i--;
                        }
                        break;
                    }
                    else if (valid == 4) { // Draw Two
                        last_card = RemoveCard(player2, card_ind);
                        showcard(player2, 3);
                        if (dir == '+') {
                            Draw_two(player3);
                            i++;
                        }
                        else {
                            Draw_two(player1);
                            i--;
                        }
                        break;
                    }
                    else if (valid == 2) { // Reverse
                        if (dir == '+') { // Increment Turn So It comes to player 3
                            dir = '-';
                            i--;
                        }
                        else {
                            dir = '+'; // Player 2
                            i++;
                        }
                        last_card = RemoveCard(player2, card_ind);
                        showcard(player2, 3);
                        break;
                    }
                    else if (valid == 3) { // Skip
                        if (dir == '+') {
                            i = 1; // Comes to Player 1
                        }
                        else {
                            i = 3; // Comes to Player 3
                        }
                        last_card = RemoveCard(player2, card_ind);
                        showcard(player2, 3);
                        break;
                    }
                    else {
                        last_card = RemoveCard(player2, card_ind);
                        showcard(player2, 3);
                        if (dir == '+') {
                            i++;
                        }
                        else {
                            i--;
                        }
                        break;
                    }

                }

            } while (1); // Manual Break

        }
        else { // Player 3 Turn
            do {
                showcard(player3, 3);
                std::cout << "Player 3 Select Card From 1 - " << player3->total_card << "\nOr '0' to Pick Card from Deck\n:";
                if (!(cin >> card_ind)) {
                    ClearBuffer();
                    continue;
                }
                else if (card_ind == 0) {
                    AddCard(player3, Deck[DeckCur_card]);
                    DeckCur_card++;
                    showcard(player3, 3);
                    std::cout << "Card Added\n";
                    if (dir == '+') {
                        i = 1;
                    }
                    else {
                        i--;
                    }
                    break;

                }
                else if (card_ind < 1 || card_ind > player3->total_card) {
                    ClearBuffer();
                    continue;
                }
                else {
                    card_ind--;
                    valid = ValidCard(player3->Dynamic_card[card_ind]);
                    if (valid == 0) {
                        std::cout << "Invalid Card\n";
                        continue;
                    }
                    else if (valid == 6) { // Draw_4
                        last_card = RemoveCard(player3, card_ind);
                        showcard(player3, 3);
                        if (dir == '+') {
                            Draw_Four(player1);
                            i = 1;
                        }
                        else {
                            Draw_Four(player2);
                            i--;
                        }
                        showcard(player3, 3);
                        break;
                    }
                    else if (valid == 5) { // Wild
                        last_card = RemoveCard(player3, card_ind);
                        showcard(player3, 3);
                        Draw();
                        showcard(player3, 3);
                        if (dir == '+') {
                            i = 1;
                        }
                        else {
                            i--;
                        }
                        break;
                    }
                    else if (valid == 4) { // Draw 2
                        last_card = RemoveCard(player3, card_ind);
                        showcard(player3, 3);
                        if (dir == '+') {
                            Draw_two(player1);
                            i = 1;
                        }
                        else {
                            Draw_two(player2);
                            i--;
                        }
                        break;
                    }
                    else if (valid == 2) { // Reverse
                        if (dir == '+') { // Decrement Turn So It comes to player 2
                            dir = '-';
                            i--;
                        }
                        else {
                            dir = '+'; // Player 2
                            i = 1;
                        }
                        last_card = RemoveCard(player3, card_ind);
                        showcard(player3, 3);
                        break;
                    }
                    else if (valid == 3) { // Skip
                        if (dir == '+') {
                            i = 2; // Comes to Player 2
                        }
                        else {
                            i = 1; // Comes to Player 1
                        }
                        last_card = RemoveCard(player3, card_ind);
                        showcard(player3, 3);
                        break;
                    }
                    else {
                        last_card = RemoveCard(player3, card_ind);
                        showcard(player3, 3);
                        if (dir == '+') {
                            i = 1;
                        }
                        else {
                            i--;
                        }
                        break;
                    }

                }

            } while (1); // Manual Break
        }
        Game = FinishCheckThree(player1, player2, player3);
        if (Game == 1) {
            break;
        }

    }
    system("cls");
    if (player1->total_card == 0) {
        Player1_Won();
        User1_Score++;
    }
    else if (player2->total_card == 0) {
        User2_Score++;
        Player2_Won();
    }
    else if (player3->total_card == 0) {
        User3_Score++;
        Player3_Won();
    }
    freeArray(player1);
    freeArray(player2);
    freeArray(player3);
    Menu();

}

void SingleGameLoop(struct Player* player1, struct Player* Bot) {
    int i = 0; // Turns
    int card_ind;
    int valid; // Card removed_card;
    int Game = 0; // Terminate Game Loop 

    while (1) { // Manual Break

        if (i % 2 == 0) { // Player 1 Turn
            do {
                showcard(player1, 2);
                std::cout << "Player 1 Select Card From 1 - " << player1->total_card << "\nOr '0' to Pick Card from Deck\n:";
                if (!(cin >> card_ind)) {
                    ClearBuffer();
                    continue;
                }
                else if (card_ind == 0) {
                    AddCard(player1, Deck[DeckCur_card]);
                    DeckCur_card++;
                    showcard(player1, 2);
                    std::cout << "Player 1 DECK\n";
                    std::cout << "Card Added\n";
                    break;

                }
                else if (card_ind < 1 || card_ind > player1->total_card) {
                    ClearBuffer();
                    continue;
                }
                else {
                    card_ind--;
                    valid = ValidCard(player1->Dynamic_card[card_ind]);
                    if (valid == 0) {
                        std::cout << "Invalid Card\n";
                        std::cout << "Player 1 DECK\n";
                        continue;
                    }
                    else if (valid == 6) { // Draw_4
                        last_card = RemoveCard(player1, card_ind);
                        showcard(player1, 2);
                        std::cout << "Player 1 DECK\n";
                        Draw_Four(Bot);
                        showcard(player1, 2);
                        std::cout << "Player 1 DECK\n";
                        break;
                    }
                    else if (valid == 5) { // Wild
                        last_card = RemoveCard(player1, card_ind);
                        showcard(player1, 2);
                        std::cout << "Player 1 DECK\n";
                        Draw();
                        showcard(player1, 2);
                        std::cout << "Player 1 DECK\n";
                        break;
                    }
                    else if (valid == 4) { // Draw 2
                        last_card = RemoveCard(player1, card_ind);
                        showcard(player1, 2);
                        std::cout << "Player 1 DECK\n";
                        Draw_two(Bot);
                        break;
                    }
                    else if (valid == 3 || valid == 2) { // Reverse or Skip
                        i++; // Increment Turn So It comes back to player 1
                        last_card = RemoveCard(player1, card_ind);
                        showcard(player1, 2);
                        std::cout << "Player 1 DECK\n";
                        break;
                    }
                    else {
                        last_card = RemoveCard(player1, card_ind);
                        showcard(player1, 2);
                        std::cout << "Player 1 DECK\n";
                        break;
                    }

                }

            } while (1); // Manual Break
        }
        else {
            showcard(Bot, 2);
            std::cout << "\nBOT TURN \n";
            valid = FindValid(Bot);
            if (valid == -1) {
                AddCard(Bot, Deck[DeckCur_card]);
                DeckCur_card++;
                showcard(Bot, 2);
                std::cout << "\nCard Added\n";
            }
            else {
                if (Bot->Dynamic_card[valid].num == 14) { // WILD
                    last_card.color = Color_Special(Bot);
                    last_card.num = 14;
                    RemoveCard(Bot, valid);
                    showcard(Bot, 2);
                    std::cout << "BOT DECK\n";
                }
                else if (Bot->Dynamic_card[valid].num == 15) { // DRAW 4
                    Draw_Four_Bot(Bot, player1);
                    RemoveCard(Bot, valid);
                    showcard(Bot, 2);
                    std::cout << "BOT DECK\n";
                }
                else if (Bot->Dynamic_card[valid].num == 13) { // Draw 2
                    last_card = RemoveCard(Bot, valid);
                    showcard(Bot, 2);
                    Draw_two(player1);
                    std::cout << "BOT DECK\n";
                }
                else if (Bot->Dynamic_card[valid].num == 12 || Bot->Dynamic_card[valid].num == 11) {
                    i++; // Increment Turn So It comes back to Bot
                    last_card = RemoveCard(Bot, valid);
                    showcard(Bot, 2);
                    std::cout << "BOT DECK\n";
                }
                else { // No Special Card
                    last_card = RemoveCard(Bot, valid);
                    showcard(Bot, 2);
                    std::cout << "BOT DECK\n";

                }
            }

        }
        i++; // Increment Turn
        Game = FinishCheck(player1, Bot);
        if (Game == 1) {
            break; // Game End
        }
    }
    system("cls");
    if (player1->total_card == 0) {
        Player1_Won();
        User1_Score++;
    }
    else if (Bot->total_card == 0) {
        Bot_Score++;
        BotWon();
    }
    else {
        player1->total_card > Bot->total_card ? BotWon() : Player1_Won();
        player1->total_card > Bot->total_card ? Bot_Score++ : User1_Score++;
    }
    freeArray(player1);
    freeArray(Bot);
    Menu();
}

int FinishCheckThree(Player* player1, Player* player2, Player* player3) {
    return (player1->total_card == 0 || player2->total_card == 0 || player3->total_card == 0 || DeckCur_card >= 112);
}
int color(char x) {
    switch (x) {
    case 'R':
        return 31;  // RED
    case 'G':
        return 32;  // GREEN
    case 'Y':
        return 33;  // YELLOW
    case 'B':
        return 34;  // BLUE
    default:
        return 0;   // Default color or error case
    }
}

int showcard(Player* player, int display) {
    system("cls");  // Adjust this based on your system-specific clear screen command

    if (display == 2) {
        std::cout << "USER 1 Score = " << User1_Score << "\tBOT Score = " << Bot_Score << "\n\n";
    }
    else if (display == 1) {
        std::cout << "USER 1 Score = " << User1_Score << "\tUSER 2 Score = " << User2_Score << "\n\n";
    }
    else {
        std::cout << "USER 1 Score = " << User1_Score << "\tUSER 2 Score = " << User2_Score << "\tUSER 3 SCORE = " << User3_Score << "\n\n";
    }
    std::cout << "\n";

    int i = 0, l = 0, n, o, z;
    int a = 0, b = 0, c = 0, d = 0, e = 0, f = 0;

    // Player 1 Cards
    l = player->total_card % 5;

    if (l != 0) {
        n = player->total_card / 5;
        o = 5;
        for (; i < n; i++) {
            for (; f < o; f++) {
                (f < 9) ? std::cout << "    0" << f + 1 << "      " : std::cout << "    " << f + 1 << "      ";
            }
            std::cout << "\n";

            for (; a < o; a++) {
                std::cout << "----------- ";
            }

            std::cout << "\n";

            for (; b < o; b++) {
                z = player->Dynamic_card[b].num;
                (z < 10) ? std::cout << "|0" << z << "       | " : std::cout << "|         | ";
            }

            std::cout << "\n";

            for (; c < o; c++) {
                z = player->Dynamic_card[c].num;
                if (z < 10) {
                    char coll = player->Dynamic_card[c].color;
                    std::cout << "|    \033[" << color(coll) << "m" << coll << "\033[0m\033[" << background << "m    | ";
                }
                else {
                    char coll = player->Dynamic_card[c].color;
                    switch (z) {
                    case 11: {
                        std::cout << "|   \033[" << color(coll) << "mREV\033[0m\033[" << background << "m   | ";
                        break;
                    }
                    case 12: {
                        std::cout << "|   \033[" << color(coll) << "mSKP\033[0m\033[" << background << "m   | ";
                        break;
                    }
                    case 13: {
                        std::cout << "|   \033[" << color(coll) << "mDR2\033[0m\033[" << background << "m   | ";
                        break;
                    }
                    case 14: {
                        std::cout << "|   WLD   | ";
                        break;
                    }
                    case 15: {
                        std::cout << "|   DR4   | ";
                        break;
                    }
                    }
                }
            }

            std::cout << "\n";

            for (; d < o; d++) {
                z = player->Dynamic_card[d].num;
                (z < 10) ? std::cout << "|       0" << z << "| " : std::cout << "|         | ";
            }

            std::cout << "\n";

            for (; e < o; e++) {
                std::cout << "----------- ";
            }

            std::cout << "\n";
            o += 5;
        }

        for (int i = 0; i < 1; i++) {
            for (int f = 0; f < player->total_card; f++) {
                (f < 9) ? std::cout << "    0" << f + 1 << "      " : std::cout << "    " << f + 1 << "      ";
            }
            std::cout << "\n";
            for (int a = 0; a < player->total_card; a++) {
                std::cout << "----------- ";
            }

            std::cout << "\n";

            for (int b = 0; b < player->total_card; b++) {
                int z = player->Dynamic_card[b].num;
                (z < 10) ? std::cout << "|0" << z << "       | " : std::cout << "|         | ";
            }
            std::cout << "\n";

            for (int c = 0; c < player->total_card; c++) {
                int z = player->Dynamic_card[c].num;
                if (z < 10) {
                    char coll = player->Dynamic_card[c].color;
                    std::cout << "|    \033[" << color(coll) << "m" << coll << "\033[0m\033[" << background << "m    | ";
                }
                else {
                    char coll = player->Dynamic_card[c].color;
                    switch (z) {
                    case 11: {
                        std::cout << "|   \033[" << color(coll) << "mREV\033[0m\033[" << background << "m   | ";
                        break;
                    }
                           break;

                    case 12: {
                        std::cout << "|   \033[" << color(coll) << "mSKP\033[0m\033[" << background << "m   | ";
                        break;
                    }
                           break;

                    case 13: {
                        std::cout << "|   \033[" << color(coll) << "mDR2\033[0m\033[" << background << "m   | ";
                        break;
                    }
                           break;

                    case 14: {
                        std::cout << "|   WLD   | ";
                        break;
                    }
                           break;

                    case 15: {
                        std::cout << "|   DR4   | ";
                        break;
                    }
                           break;
                    }
                }
            }

            std::cout << "\n";

            for (int d = 0; d < player->total_card; d++) {
                int z = player->Dynamic_card[d].num;
                (z <= 9) ? std::cout << "|       0" << z << "| " : std::cout << "|         | ";
            }

            std::cout << "\n";

            for (int e = 0; e < player->total_card; e++) {
                std::cout << "----------- ";
            }
            std::cout << "\n";
        }
    }

    if (l == 0) {

        int n = player->total_card / 5;
        int o = 5;
        for (int i = 0; i < n; i++) {
            for (int f = 0; f < o; f++) {
                (f < 9) ? std::cout << "    0" << f + 1 << "      " : std::cout << "    " << f + 1 << "      ";
            }
            std::cout << "\n";
            for (int a = 0; a < o; a++) {
                std::cout << "----------- ";
            }

            std::cout << "\n";

            for (int b = 0; b < o; b++) {
                int z = player->Dynamic_card[b].num;
                (z < 10) ? std::cout << "|0" << z << "       | " : std::cout << "|         | ";
            }

            std::cout << "\n";

            for (int c = 0; c < o; c++) {
                int z = player->Dynamic_card[c].num;
                if (z < 10) {
                    char coll = player->Dynamic_card[c].color;
                    std::cout << "|    \033[" << color(coll) << "m" << coll << "\033[0m\033[" << background << "m    | ";
                }
                else {
                    char coll = player->Dynamic_card[c].color;
                    switch (z) {
                    case 11: {
                        std::cout << "|   \033[" << color(coll) << "mREV\033[0m\033[" << background << "m   | ";
                        break;
                    }
                           break;

                    case 12: {
                        std::cout << "|   \033[" << color(coll) << "mSKP\033[0m\033[" << background << "m   | ";
                        break;
                    }
                           break;

                    case 13: {
                        std::cout << "|   \033[" << color(coll) << "mDR2\033[0m\033[" << background <<  "m   | ";
                        break;
                    }
                           break;

                    case 14: {
                        std::cout << "|   WLD   | ";
                        break;
                    }
                           break;

                    case 15: {
                        std::cout << "|   DR4   | ";
                        break;
                    }
                           break;
                    }
                }
            }

            std::cout << "\n";

            for (int d = 0; d < o; d++) {
                int z = player->Dynamic_card[d].num;
                (z <= 9) ? std::cout << "|       0" << z << "| " : std::cout << "|         | ";
            }

            std::cout << "\n";

            for (int e = 0; e < o; e++) {
                std::cout << "----------- ";
            }
            std::cout << "\n";
            o += 5;
        }
    }
    Lcard();
    return 0;
}

void Lcard() {
    if (last_card.num == -1) {
        std::cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t  L A S T\n";
        std::cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t-----------\n";
        std::cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t|         |\n";
        std::cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t|         |\n";
        std::cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t|         |\n";
        std::cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t-----------\n";
        std::cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t  C A R D\n";
    }
    else if (last_card.num == 14) {
        std::cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t  L A S T\n";
        std::cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t-----------\n";
        std::cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t|         |\n";
        std::cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t|   \033[" << color(last_card.color) << "mWLD\033[0m\033[" << background << "m   |\n";
        std::cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t|         |\n";
        std::cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t-----------\n";
        std::cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t  C A R D\n";
    }

    else if (last_card.num == 15) {
        std::cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t  L A S T\n";
        std::cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t-----------\n";
        std::cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t|         |\n";
        std::cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t|   \033[" << color(last_card.color) << "mDR4\033[0m\033[" << background << "m   |\n";
        std::cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t|         |\n";
        std::cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t-----------\n";
        std::cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t  C A R D\n";
    }

    else if (last_card.num == 13) {
        std::cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t  L A S T\n";
        std::cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t-----------\n";
        std::cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t|         |\n";
        std::cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t|   \033[" << color(last_card.color) << "mDR2\033[0m\033[" << background << "m   |\n";
        std::cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t|         |\n";
        std::cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t-----------\n";
        std::cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t  C A R D\n";
    }

    else if (last_card.num == 12) {
        std::cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t  L A S T\n";
        std::cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t-----------\n";
        std::cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t|         |\n";
        std::cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t|   \033[" << color(last_card.color) << "mSKP\033[0m\033[" << background << "m   |\n";
        std::cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t|         |\n";
        std::cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t-----------\n";
        std::cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t  C A R D\n";
    }

    else if (last_card.num == 11) {
        std::cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t  L A S T\n";
        std::cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t-----------\n";
        std::cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t|         |\n";
        std::cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t|   \033[" << color(last_card.color) << "mREV\033[0m\033[" << background << "m   |\n";
        std::cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t|         |\n";
        std::cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t-----------\n";
        std::cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t  C A R D\n";
    }

    else {
        std::cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t  L A S T\n";
        std::cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t-----------\n";
        std::cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t|0" << last_card.num << "       |\n";
        std::cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t|    \033[" << color(last_card.color) << "m" << last_card.color << "\033[0m\033[" << background << "m    |\n";
        std::cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t|       0" << last_card.num << "|\n";
        std::cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t-----------\n";
        std::cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t  C A R D\n";
    }
}



void BotWon() {
    system("cls");
    std::cout << "\n\n\n\n\n";
    std::cout << "\t\t\t\t*****      * *     *****        *     *        * *      *       *\n";
    std::cout << "\t\t\t\t*    *   *     *     *          *     *      *     *    **      *\n";
    std::cout << "\t\t\t\t*    *   *     *     *          *     *      *     *    * *     *\n";
    std::cout << "\t\t\t\t*****    *     *     *          *     *      *     *    *  *    *\n";
    std::cout << "\t\t\t\t*    *   *     *     *          * * * *      *     *    *   *   *\n";
    std::cout << "\t\t\t\t*    *    *   *      *          *  *  *       *   *     *    *  *\n";
    std::cout << "\t\t\t\t*****      ***       *          *  *  *        ***      *     * *\n";
}

void Player1_Won() {
    system("cls");
    std::cout << "\n\n\n\n";
    std::cout << "*****    *           *       *       *   *******   *****           *        *     *       * *      *       *\n";
    std::cout << "*    *   *          * *       *     *    *         *    *         **        *     *     *     *    **      *\n";
    std::cout << "*    *   *         *   *       *   *     *         *    *        * *        *     *     *     *    * *     *\n";
    std::cout << "*****    *        *     *       * *      *******   *****           *        *     *     *     *    *  *    *\n";
    std::cout << "*        *       *********       *       *         *   *           *        * * * *     *     *    *   *   *\n";
    std::cout << "*        *      *         *      *       *         *    *          *        *  *  *      *   *     *    *  *\n";
    std::cout << "*        ***** *           *     *       *******   *     *     ********     *  *  *       ***      *     * *\n";
}

void Player2_Won() {
    system("cls");
    std::cout << "\n\n\n\n";
    std::cout << "*****    *           *       *       *   *******   *****        *****         *     *       * *      *       *\n";
    std::cout << "*    *   *          * *       *     *    *         *    *       *    *        *     *     *     *    **      *\n";
    std::cout << "*    *   *         *   *       *   *     *         *    *           *         *     *     *     *    * *     *\n";
    std::cout << "*****    *        *     *       * *      *******   *****          *           *     *     *     *    *  *    *\n";
    std::cout << "*        *       *********       *       *         *   *         *            * * * *     *     *    *   *   *\n";
    std::cout << "*        *      *         *      *       *         *    *       *             *  *  *      *   *     *    *  *\n";
    std::cout << "*        ***** *           *     *       *******   *     *     *******        *  *  *       ***      *     * *\n";
}

void Player3_Won() {
    system("cls");
    std::cout << "\n\n\n\n";
    std::cout << "*****    *           *       *       *   *******   *****        *****        *     *       * *      *       *\n";
    std::cout << "*    *   *          * *       *     *    *         *    *           *        *     *     *     *    **      *\n";
    std::cout << "*    *   *         *   *       *   *     *         *    *          *         *     *     *     *    * *     *\n";
    std::cout << "*****    *        *     *       * *      *******   *****            *        *     *     *     *    *  *    *\n";
    std::cout << "*        *       *********       *       *         *   *            *        * * * *     *     *    *   *   *\n";
    std::cout << "*        *      *         *      *       *         *    *       *   *        *  *  *      *   *     *    *  *\n";
    std::cout << "*        ***** *           *     *       *******   *     *       ***         *  *  *       ***      *     * *\n";
}


int colorchange() {
    system("cls");
    int option;
    std::cout << "1-Reset to Default\n2-Set New Color\n-->";

    if (!(std::cin >> option)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return -1;
    }

    if (option == 1) {
        std::cout << "\033[0m\n";
        Menu();
    }
    else if (option == 2) {
        do {
            std::cout << "Enter Background Color:\n40: Black\n41: Red\n42: Green\n43: Yellow\n44: Blue\n45: Magenta\n46: Cyan\n47: White\n-->";
            if (!(std::cin >> background)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return -1;
            }
            if (background < 40 || background > 47) {
                std::cout << "Out of Range\n";
            }
        } while (background < 40 || background > 47);

        std::cout << "\033[" << background << "m\n";
    }

    Menu();
    return 0;
}

void SaveScore() {
    std::ofstream file("Score.txt");

    if (file.is_open()) {
        file << User1_Score << "\n" << User2_Score << "\n" << User3_Score << "\n" << Bot_Score;
        file.close();
        std::cout << "Score Saved\n";
    }
    else {
        std::cout << "Unable to open file\n";
    }

    Menu();
}

void Restore() {
    std::ifstream file("Score.txt");

    if (!file.is_open()) {
        std::cout << "No Saved Scores\n";
        Menu();
    }

    file >> User1_Score >> User2_Score >> User3_Score >> Bot_Score;
    file.close();
    std::cout << "Progress Restored\n\n";
    Menu();
}

void ResetScore() {
    std::cout << "Score Resetted\n";
    User1_Score = 0;
    User2_Score = 0;
    User3_Score = 0;
    Bot_Score = 0;
    const char* file = "Score.txt";

    if (std::remove(file) == 0) {
        std::cout << "Successfully Deleted Saved Scores\n";
    }
    else {
        std::cout << "Scores file did not exist\n";
    }

    Menu();
}
