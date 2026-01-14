// Maze Game
#include <iostream>
#include <stack>
#include <conio.h>
using namespace std;

// 1 = path, 0 = wall
int maze[10][10] = {
    {1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,1,0,0,0,1},
    {1,1,1,1,0,1,1,1,0,1},
    {1,0,0,1,0,0,0,1,0,1},
    {1,1,0,1,1,1,0,1,1,1},
    {1,1,0,0,0,1,0,0,0,1},
    {1,1,1,1,0,1,1,1,0,1},
    {1,0,0,1,0,0,0,1,0,1},
    {1,1,1,1,1,1,1,1,0,1},
    {1,0,0,0,0,0,0,1,1,1}
};

bool visited[10][10];
char display[10][10];

int pr = 0, pc = 0; // Player Row, Player Column
int er = 9, ec = 9; // Exit Row, Exit Column

struct Cell {
    int r, c;
};

// Convert maze into display grid
void prepareDisplay() {
    for(int r=0; r<10; r++) {
        for(int c=0; c<10; c++) {
            if (maze[r][c] == 0)
                display[r][c] = '#';
            else
                display[r][c] = '.';
        }
    }
    display[pr][pc] = 'P';
    display[er][ec] = 'E';
}

// Print the game grid
void printMaze() {
    system("cls");
    cout << "=== MAZE GAME ===\n";
    cout<<endl;
    cout << "Move: W A S D | Press X to Auto-Solve\n\n";

    for(int r=0; r<10; r++) {
        for(int c=0; c<10; c++) {
            cout << display[r][c] << " ";
        }
        cout << endl;
    }
}

// Check boundaries + path
bool isValid(int r, int c) {
    return (r >= 0 && r < 10 && c >= 0 && c < 10 &&
            maze[r][c] == 1 && !visited[r][c]);
}

// Auto solver using DFS + STACK
bool autoSolve() {
    stack<Cell> st;

    st.push({pr, pc}); // start

    while(!st.empty()) {
        Cell cur = st.top();
        st.pop();

        int r = cur.r, c = cur.c;

        if (visited[r][c]) continue;
        visited[r][c] = true;

        // Mark solved path
        display[r][c] = '*';

        if (r == er && c == ec) {
            return true; // reached exit
        }

        // Try directions
        if (isValid(r, c+1)) st.push({r, c+1}); // right
        if (isValid(r+1, c)) st.push({r+1, c}); // down
        if (isValid(r, c-1)) st.push({r, c-1}); // left
        if (isValid(r-1, c)) st.push({r-1, c}); // up
    }

    return false;
}

int main() {
    char move;

    prepareDisplay();
    printMaze();
    
    while(true) {
        move = getch();
        int nr = pr, nc = pc;

        if(move == 'x' || move == 'X') {
            bool solved = autoSolve();
            printMaze();
            if (solved)
                cout << "\nAuto-solver found the path!\n";
            else
                cout << "\nNo path found!\n";
            return 0;
        }

        // Player Movement
        if(move == 'w') nr--;
        if(move == 's') nr++;
        if(move == 'a') nc--;
        if(move == 'd') nc++;

        // Can player move?
        if(nr>=0 && nr<10 && nc>=0 && nc<10 && maze[nr][nc]==1) {
            display[pr][pc] = '.';
            pr = nr; pc = nc;
            display[pr][pc] = 'P';
        }

        printMaze();

        // Win condition
        if(pr == er && pc == ec) {
            cout << "\nYOU WON!\n";
            break;
        }
    }
    return 0;
}
