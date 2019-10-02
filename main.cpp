#include <iostream>
#include <vector>

using namespace std;
class Board{
    public:
        vector<vector<char> > board;
        vector<char> row1;
        vector<char> row2;
        vector<char> row3;

        Board(){
            //Fill each row with values
            row1.push_back('1');
            row1.push_back('2');
            row1.push_back('3');
            row2.push_back('4');
            row2.push_back('5');
            row2.push_back('6');
            row3.push_back('7');
            row3.push_back('8');
            row3.push_back('9');

            //Add the rows to the board
            board.push_back(row1);
            board.push_back(row2);
            board.push_back(row3);
        };

        void printBoard(){
            //Iterate through the 2d vector to print each value
            cout<<endl;
            for(int i=0; i<3; i++)
            {
                for(int j=0; j<3; j++){
                    cout << board[i][j]<<"     ";
                }
                cout<<endl<<endl;
            }
        }

    bool parseInput(int cell, char symbol){

            int row;
            int col;
            switch(cell)
            {
                case 1:
                    row = 0; col = 0;
                    break;
                case 2:
                    row = 0; col = 1;
                    break;
                case 3:
                    row = 0; col = 2;
                    break;
                case 4:
                    row = 1; col = 0;
                    break;
                case 5:
                    row = 1; col = 1;
                    break;
                case 6:
                    row = 1; col = 2;
                    break;
                case 7:
                    row = 2; col = 0;
                    break;
                case 8:
                    row = 2; col = 1;
                    break;
                case 9:
                    row = 2; col = 2;
                    break;
            }
            if(board[row][col] == 'X' || board[row][col] == 'O'){
                //Cell already filled
                return false;
            }else{
                updateBoard(row,col, symbol);
                return true;
            }
        }

    private:
        void updateBoard(int row, int col, char player){
            //Update the value at a specific index
            board.at(row).at(col) = player;
            printBoard();
        }
};

class AI{
    //AI implementation
};

int main()
{
    string promptMove = "Please select a number from the board.";
    char playerSymbol;
    char AISymbol;

    //See if the player wants to go first or second.
    char playerTurn = '0';
    cout << "Welcome to Tic Tac Toe!"<<endl<<"Would you like to go first or second (1 or 2): "<<endl;
    playerTurn = cin.get();
    //Make sure the player doesn't enter something stupid.
    while(playerTurn != '1' && playerTurn != '2'){
        playerTurn = cin.get();
        cout<<"That is not a valid selection."<<endl<<"Please enter either 1 or 2:"<<endl;
    }
    cout<<"Okay! Here we go, printing board..."<<endl<<endl;

    Board board;
    board.printBoard();

    if(playerTurn == '1'){
        playerSymbol = 'X';
        AISymbol ='O';
        cout<<promptMove<<endl;
        int cell;
        cell = (int)cin.get();
        //Make sure the cell is valid
        while(cell<1 || cell>9)
        {
            cout<<"That is not a valid cell."<<endl<<promptMove;
            cell=(int)cin.get();
        }
        //Ask the board if the cell is filled
        while(!board.parseInput(cell, playerSymbol)){
            cout<<"That is not a valid cell."<<endl<<promptMove;
            cell=(int)cin.get();
        }
        //Commented until implemented
        //AI.turn();

    }else{
        playerSymbol = 'O';
        AISymbol = 'X';
        //Commented until implemented
        //AI.firstMove();
    }

    return 0;
}