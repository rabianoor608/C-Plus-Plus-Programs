#include <iostream>
#include <string>
#include <windows.h>
#include <cstdlib>
#include <cctype>
#include <ctime>

using namespace std;

const int ROWS = 14;
const int COLS = 13;
const int MAX_WORDS = 14;
const int MAX_BONUS = 50;

char grid[ROWS][COLS];
bool boxGrid[ROWS][COLS];

string words[MAX_WORDS] = {"BRIDE","DARE","BEG","BEAD","DIE","IDEA","BRAID","BAG","BADGE","BIRD","RIB","GRID","BRIDGE","BEAR"};
int wordRow[MAX_WORDS]  = {1,1,4,4,7,7,10,10,12,10,10,7,7,4};
int wordCol[MAX_WORDS]  = {6,9,8,8,8,9,7,7,4,2,4,5,1,2};
char dir[MAX_WORDS]     = {'H','V','H','V','H','V','H','V','H','H','V','V','H','V'};

// Dictionary including extra bonus words
string dictionaryWords[42] = {
 "BID","RID","BAD","BAR","ERA","DIG","RAD","DAB","GAB","GAD","RAG","AID","ARE","EAR","BED","BIG",
 "AIR","AGE","BIDE","BADE","BRIG","RIDE","RIND","GEAR","READ","GIRD","BARD","RAGE","BEARD"
 "GRAB","DRAG","AGRI","GRIDE","RAGED","AIRED","GRADE","BRIDE","AIDER","BADGER","BREAD","ABIDE"
 "DEAR","RED","BEAR"
};

int playerAttempts[2] = {3,3};
int playerScore[2] = {0,0};
int wordOwner[MAX_WORDS];
string usedBonusWords[MAX_BONUS];
int usedBonusCount = 0;

// Undo stack
int undoStack[MAX_WORDS];
int undoTop = -1;

// Set console color
void setColor(int c){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

// Convert string to uppercase
string toUpper(string s){
    for(int i=0;i<(int)s.length();i++)
        s[i] = toupper((unsigned char)s[i]);
    return s;
}

// Row/Col helpers
int getRow(int idx,int i){ return wordRow[idx] + (dir[idx]=='V'?i:0); }
int getCol(int idx,int i){ return wordCol[idx] + (dir[idx]=='H'?i:0); }

// Initialize grid
void initGrid(){
    for(int r=0;r<ROWS;r++)
        for(int c=0;c<COLS;c++){
            grid[r][c]=' ';
            boxGrid[r][c]=false;
        }

    for(int i=0;i<MAX_WORDS;i++){
        wordOwner[i]=-1;
        for(int k=0;k<(int)words[i].length();k++)
            boxGrid[getRow(i,k)][getCol(i,k)] = true;
    }
}

// Display grid
void displayGrid(){
    for(int r=0;r<ROWS;r++){
        for(int c=0;c<COLS;c++){
            if(!boxGrid[r][c]){
                cout<<"    ";
                continue;
            }
            char ch = grid[r][c];
            if(ch==' '){
                setColor(8);
                cout<<".   ";
            } else {
                setColor(10);
                cout<<ch<<"   ";
            }
        }
        setColor(7);
        cout<<"\n\n";
    }
}

// Display interface
void displayInterface(int p){
    system("cls");
    setColor(11);
    cout<<"=========== CROSSWORD PUZZLE GAME ===========\n\n";
    setColor(14);
    cout<<"Available Letters: B I A D E G R\n\n";
    setColor(13);
    cout<<"Player 1  Attempts: "<<playerAttempts[0]<<"  Score: "<<playerScore[0]<<"\n";
    cout<<"Player 2  Attempts: "<<playerAttempts[1]<<"  Score: "<<playerScore[1]<<"\n\n";
    setColor(11);
    cout<<"CROSSWORD GRID:\n\n";
    setColor(7);
    displayGrid();
    setColor(10);
    cout<<"Player "<<p+1<<" enter word: ";
    setColor(7);
}

// Place/Remove words
void placeWord(int idx,int player){
    for(int i=0;i<(int)words[idx].length();i++)
        grid[getRow(idx,i)][getCol(idx,i)] = words[idx][i];
    wordOwner[idx]=player;
}

void removeWord(int idx){
    for(int i=0;i<(int)words[idx].length();i++)
        grid[getRow(idx,i)][getCol(idx,i)] = ' ';
    wordOwner[idx]=-1;
}

// Check if a word is in dictionary
bool isWordInDictionary(string s){
    s = toUpper(s);
    for(int i=0;i<42;i++)
        if(toUpper(dictionaryWords[i])==s)
            return true;
    return false;
}

// Find word in crossword
int findWord(string s){
    s = toUpper(s);
    for(int i=0;i<MAX_WORDS;i++)
        if(words[i]==s)
            return i;
    return -1;
}

// Check if all words are placed
bool allPlaced(){
    for(int i=0;i<MAX_WORDS;i++)
        if(wordOwner[i]==-1)
            return false;
    return true;
}

// Celebrate winner function
void celebrateWinner(int player){
    for(int i=0;i<5;i++){
        Beep(700 + i*50, 300);
        Sleep(150);
    }

    system("cls");
    setColor(14);
    cout<<"\n\n\t\tPLAYER "<<player+1<<" WINS! CONGRATULATIONS!\n\n";
    setColor(7);
    Sleep(1000);

    const char fireworks[6][40] = {
        "*   *     *  *   *  *   *  *   *",
        "  *   *  *    *  *    *   *   *  ",
        "*    *   *   *   *  *    *   *  ",
        "   *   *  *    *   *   *  *   * ",
        "*   *   *    *   *   *   *   *  ",
        "  *    *   *   *   *    *   *   "
    };

    for(int round=0; round<8; round++){
        system("cls");
        int color = 10 + round % 6;
        setColor(color);
        for(int f=0; f<6; f++){
            for(int space=0; space<round; space++) cout<<" ";
            cout<<fireworks[f]<<"\n";
        }
        Sleep(300);
        Beep(600 + round*50, 150);
    }

    system("cls");
    setColor(13);
    cout<<"\n\n\n";
    cout<<"  ******************\n";
    cout<<"  *                                                *\n";
    cout<<"  *              CONGRATULATIONS!                  *\n";
    cout<<"  *          PLAYER "<<player+1<<" WINS THE GAME!               *\n";
    cout<<"  *                                                *\n";
    cout<<"  ******************\n\n";
    setColor(7);
    Sleep(2000);
}

int main(){
    SetConsoleTitleA("Crossword Puzzle Game");
    initGrid();

    int current=0;
    string input;
    
    while(true){
	 if(playerAttempts[0] <= 0 && playerAttempts[1] <= 0){
            cout << "\nBoth players have no attempts left!\n";
            break;
        }
        if(playerAttempts[current]<=0){
            current=1-current;
            continue;
        }

        displayInterface(current);
        getline(cin,input);
        string cmd = toUpper(input);

        if(cmd=="QUIT") break;

        if(cmd=="UNDO" && undoTop>=0){
            int idx=undoStack[undoTop--];
            removeWord(idx);
            playerScore[current]--;
            continue;
        }

        int idx = findWord(input);

        if(idx!=-1 && wordOwner[idx]!=-1){
            cout << "\nWord already placed in the grid!\n";
            cin.get();
            current=1-current;
            continue;
        }

        // Bonus handling
        if(idx==-1){
            string wordUpper = toUpper(input);
            if(isWordInDictionary(wordUpper)){
                bool alreadyUsed=false;
                for(int i=0;i<usedBonusCount;i++)
                    if(usedBonusWords[i]==wordUpper){ alreadyUsed=true; break; }
                if(alreadyUsed)
                    cout<<"\nBonus already added!\n";
                else{
                    cout<<"\nBonus dictionary word!  +1 score\n";
                    playerScore[current]++;  
                    usedBonusWords[usedBonusCount++] = wordUpper;
                }
            } else {
                cout<<"\nInvalid word! -1 attempt -1 score\n";
                playerAttempts[current]--;
                playerScore[current]--;
            }
            cin.get();
            current=1-current;
            continue;
        }

        // Place word in grid
        if(idx!=-1 && wordOwner[idx]==-1){
            placeWord(idx,current);
            undoStack[++undoTop]=idx;
            playerScore[current]++;
        }

        if(allPlaced()) break;
        current=1-current;
    }

    system("cls");
    cout<<"FINAL PUZZLE:\n\n";
    displayGrid();
    cout<<"\nPlayer 1 Score: "<<playerScore[0];
    cout<<"\nPlayer 2 Score: "<<playerScore[1];

    cout<<"\n\n";
    if(playerScore[0]>playerScore[1]) celebrateWinner(0);
    else if(playerScore[1]>playerScore[0]) celebrateWinner(1);
    else cout<<"It's a tie!\n";

    Sleep(8000);
    return 0;
}
