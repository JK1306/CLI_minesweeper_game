#include <iostream>
#include <random>
#include <ctime>
#define N 9
#define MINE 10
#define MINE_PROB 10
#define ZERO_CHAR 48

using namespace std;

bool add_mine_count(char playboard[N][N], int i, int j){
    int mineCount = 0;
    // cout<<"came to function\n";
    if(playboard[i][j] != '*' && N>i && i>=0 && N>j && j>=0){
        // up
        if(i>0 && playboard[i-1][j] == '*')
            mineCount++;
        // down
        if(i<N && playboard[i+1][j] == '*')
            mineCount++;
        // right
        if(j<N && playboard[i][j+1] == '*')
            mineCount++;
        // left
        if(j>0 && playboard[i][j-1] == '*')
            mineCount++;
        // left up
        if(j>0 && i>0 && playboard[i-1][j-1] == '*')
            mineCount++;
        // left down
        if(j>0 && i<N && playboard[i+1][j-1] == '*')
            mineCount++;
        // right up
        if(j<N && i>0 && playboard[i-1][j+1] == '*')
            mineCount++;
        // right down
        if(j<N && i<N && playboard[i+1][j+1] == '*')
            mineCount++;
        playboard[i][j] = (char)(ZERO_CHAR + mineCount);
    }
    if((bool)mineCount){
        return true;
    }
    return false;
}

void printPlayBorad(char playBoard[N][N], bool exposeMines=false){
    for(int i=0; i<N; i++){
        cout<<'\t'<<i+1;
    }
    cout<<endl;
    for(int i=0; i<N; i++){
        cout<<i+1<<'\t';
        for(int j=0; j<N; j++){
            if(playBoard[i][j] != '*' || exposeMines)
                cout<<playBoard[i][j]<<'\t';
            else{
                cout<<" \t";
            }
        }
        cout<<endl;
        cout<<endl;
    }
}

void displayEmptySpace(char playBoard[N][N], int row, int column){
    // cout<<"Row : "<<row<<endl;
    // cout<<"Column : "<<column<<endl;
    // if(playBoard[row][column] != '*' && N>row>=0 && N>column>=0){
    if(playBoard[row][column] != '*' && !playBoard[row][column] && N>row && row>=0 && N>column && column>=0){
        if(add_mine_count(playBoard, row, column)){
            // cout<<"Executed if statement\n";
            return;
        }
        // cout<<"Came out of case\n";
        // four sides
        displayEmptySpace(playBoard, row+1, column);
        displayEmptySpace(playBoard, row, column+1);
        displayEmptySpace(playBoard, row-1, column);
        displayEmptySpace(playBoard, row, column-1);

        // four corners
        displayEmptySpace(playBoard, row+1, column+1);
        displayEmptySpace(playBoard, row+1, column-1);
        displayEmptySpace(playBoard, row-1, column+1);
        displayEmptySpace(playBoard, row-1, column-1);
    }
}

void generateMines(char playBoard[N][N], int row, int column){
    int mineCount = 0,
    max = 100;
    srand(time(0));
    while(true){
        for(int i=0; i<N; i++){
            for(int j=0; j<N; j++){
                if(playBoard[i][j] != '*' && (i != row || j != column)){
                    if(rand()%max <= MINE_PROB){
                        cout<<"Mines in : "<<i<<" "<<j<<endl;
                        playBoard[i][j] = '*';
                        mineCount++;
                    }
                    if(mineCount == MINE){
                        return;
                    }
                }
            }
        }
    }
}

bool checkWon(char playBoard[N][N]){
    for(int i=0; i<N; i++){
        for(int j=-0; j<N; j++){
            if(playBoard[i][j] == '\0'){
                return false;
            }
        }
    }
    return true;
}

int main(){
    char playBoard[N][N] = {
        {'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'},
        {'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'},
        {'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'},
        {'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'},
        {'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'},
        {'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'},
        {'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'},
        {'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'},
        {'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'},
    };
    int row, column;
    bool first_run=true;
    while (true)
    {
        printPlayBorad(playBoard);
        cout<<"Enter row and column value : \n";
        cin>>row;
        cin>>column;
        if(first_run){
            generateMines(playBoard, row-1, column-1);
            first_run = false;
        }
        cout<<"Value : "<<playBoard[row-1][column-1]<<endl;
        if(playBoard[row-1][column-1] != '*'){
            displayEmptySpace(playBoard, row-1, column-1);
        }else{
            cout<<"Ooopss... you stepped into a MINE.....\n";
            printPlayBorad(playBoard, true);
            break;
        }
        if(checkWon(playBoard)){
            cout<<"Congrats you won the game..\n";
            break;
        }
    }
    return 0;
}