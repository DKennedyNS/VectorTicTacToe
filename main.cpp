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
        }

    virtual ~Board()= default;

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

    bool checkWin(){

            if(board[0][0]==board[1][1]==board[2][2]){
                winner = board[0][0];
                return true;
            }else if(board[0][2]==board[1][1]==board[2][0]){
                winner = board[0][2];
                return true;
            }else if(board[0][0]==board[0][1]==board[0][2]){
                winner = board[0][0];
                return true;
            }else if(board[1][0]==board[1][1]==board[1][2]){
                winner = board[1][0];
                return true;
            }else if(board[2][0]==board[2][1]==board[2][2]){
                winner = board[2][0];
                return true;
            }else if(board[0][0]==board[1][0]==board[2][0]){
                winner = board[0][0];
                return true;
            }else if(board[0][1]==board[1][1]==board[2][1]){
                winner = board[0][1];
                return true;
            }else if(board[0][2]==board[1][2]==board[2][2]){
                winner = board[0][2];
                return true;
            }else{
                return false;}
    }

    char getWinner(){
        return winner;
        }

    private:
        char winner;
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
    //VARIABLE DECLARATION
    string promptMove = "Please select a number from the board.";
    char playerSymbol;
    char AISymbol;
    int move = 0;
    char playAgain = '0';
    char playerTurn = '0';

    //INTRO PRINTS
    //See if the player wants to go first or second.
    cout << "Welcome to Tic Tac Toe!"<<endl<<"Would you like to go first or second (1 or 2): "<<endl;
    playerTurn = cin.get();

    //Make sure the player doesn't enter something stupid.
    while(playerTurn != '1' && playerTurn != '2'){
        playerTurn = cin.get();
        cout<<"That is not a valid selection."<<endl<<"Please enter either 1 or 2:"<<endl;
    }
    //Init the board
    cout<<"Okay! Here we go, printing board..."<<endl<<endl;
    Board board;
    board.printBoard();
    //end intro


    //TURN SELECTION
    if(playerTurn == '1'){
        playerSymbol = 'X';
        AISymbol ='O';

    }else{
        playerSymbol = 'O';
        AISymbol = 'X';
        //AI.move(move);
    }//end turn selection


    //PRIMARY GAME LOOP
    //So long as no one has won, and there is still a move to be made, keep playing
    while(!board.checkWin() && move < 9){
        cout<<promptMove<<endl;
        int cell;
        cell = (int)cin.get();
        //Make sure the cell is valid
        while(cell < 1 || cell > 9)
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
    }//end game loop

    //GAME-END ROUTINE
    //Check to see if there is a winner
    if(board.checkWin()){
        char winner = board.getWinner();
        if(winner == playerSymbol){
            cout<<endl<<"THE HUMAN WINS!"<<endl;
        }else if(winner == AISymbol){
            cout<<endl<<"THE AI WINS!"<<endl;
        }else{
            //If checkWin is true, but there is no winner, something is wrong
            cout<<endl<<"Something has gone horribly wrong.."<<endl;
        }
    }else{
        cout<<endl<<"IT'S A DRAW!"<<endl;
    }
    //See if the player wants to go again
    cout<<"Would you like to play again (y/n): "<<endl;
    playAgain = cin.get();
    while(playAgain != 'y' && playAgain != 'n'){
        cout<<endl<<"That is not a valid entry."<<endl<<"Would you like to play again (y/n):"<<endl;
        playAgain = cin.get();
    }
    //If the play wants to try again, destroy the board and call main()
    if(playAgain == 'y'){
        board.~Board();
        main();
    }
    //end game-end routine
    return 0;
}