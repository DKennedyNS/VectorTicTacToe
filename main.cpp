#include <iostream>
#include <vector>
#include <set> //No idea why I needed to include this since I'm using namespace std...

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
                case 49:
                    row = 0; col = 0;
                    break;
                case 50:
                    row = 0; col = 1;
                    break;
                case 51:
                    row = 0; col = 2;
                    break;
                case 52:
                    row = 1; col = 0;
                    break;
                case 53:
                    row = 1; col = 1;
                    break;
                case 54:
                    row = 1; col = 2;
                    break;
                case 55:
                    row = 2; col = 0;
                    break;
                case 56:
                    row = 2; col = 1;
                    break;
                case 57:
                    row = 2; col = 2;
                    break;
            }//end switch
            if(board[row][col] == 'X' || board[row][col] == 'O'){
                //Cell already filled
                return false;
            }else{
                updateBoard(row,col, symbol);
                return true;
            }
        }//end parse input

    bool checkWin(){
        //Check all possible win conditions
        if(board[0][0]==board[1][1] && board[1][1]==board[2][2]){
            winner = board[0][0];
            return true;
        }else if(board[0][2]==board[1][1] && board[1][1]==board[2][0]){
            winner = board[0][2];
            return true;
        }else if(board[0][0]==board[0][1] && board[0][1]==board[0][2]){
            winner = board[0][0];
            return true;
        }else if(board[1][0]==board[1][1] && board[1][1]==board[1][2]){
            winner = board[1][0];
            return true;
        }else if(board[2][0]==board[2][1] && board[2][1]==board[2][2]){
            winner = board[2][0];
            return true;
        }else if(board[0][0]==board[1][0] && board[1][0]==board[2][0]){
            winner = board[0][0];
            return true;
        }else if(board[0][1]==board[1][1] && board[1][1]==board[2][1]){
            winner = board[0][1];
            return true;
        }else if(board[0][2]==board[1][2] && board[1][2]==board[2][2]){
            winner = board[0][2];
            return true;
        }else{
            return false;}

    }//end check win

    char getWinner(){
        return winner;
        }
    char getSymbol(int row, int col){
        return board[row][col];
    }

    bool isTaken(int cell){
        //parseInput, but with no board update
        int row;
        int col;
        switch(cell)
        {
            case 49:
                row = 0; col = 0;
                break;
            case 50:
                row = 0; col = 1;
                break;
            case 51:
                row = 0; col = 2;
                break;
            case 52:
                row = 1; col = 0;
                break;
            case 53:
                row = 1; col = 1;
                break;
            case 54:
                row = 1; col = 2;
                break;
            case 55:
                row = 2; col = 0;
                break;
            case 56:
                row = 2; col = 1;
                break;
            case 57:
                row = 2; col = 2;
                break;
        }//end switch
        if(board[row][col] == 'X' || board[row][col] == 'O'){
            //Cell already filled
            return true;
        }else{
            //cell not filled
            return false;
        }
    }//end isTaken

    private:
        char winner;
        void updateBoard(int row, int col, char player){
            //Update the value at a specific index
            board.at(row).at(col) = player;
            printBoard();
        }


};//end board class

class AI{
    set<int> movesMade;

public:
    AI() = default;

    int move(Board board, int turn, char AISymbol, char playerSymbol)
    {
        int position = 0;
        bool block = false;
        int diagonal1[3] = {49, 53, 57};
        int diagonal2[3] = {51, 53, 55};

        //Use a for loop to see if any row or col has two human moves in it, if so, set block true.
        //Then iterate through the offending row/col to find the open cell. Set position to the open cell.

        //Rows
        for(int i=0; i<3; i++){
            int count = 0;
            for(int j=0; j<3; j++){
                if(board.getSymbol(i,j) == playerSymbol){
                    count++;
                }
            }
            if(count >= 2){
                block = true;
                for(int k=0; k<3; k++){
                    if(board.getSymbol(i, k) != playerSymbol){
                        position = board.getSymbol(i, k);
                    }
                }
            }
        }

        //Columns
        for(int i=0; i<3; i++){
            int count = 0;
            for(int j=0; j<3; j++){
                if(board.getSymbol(j, i) == playerSymbol){
                    count++;
                }
            }
            if(count >= 2){
                block = true;
                for(int k=0; k<3; k++){
                    if(board.getSymbol(k, i) != playerSymbol){
                        position = board.getSymbol(k, i);
                    }
                }
            }
        }

        //Iterate through the diagonals and check if they are taken, then check if they are taken by me. If not, count++
        for(int i=0; i<3; i++){
            int count = 0;
            if(board.isTaken(diagonal1[i]) && movesMade.find(diagonal1[i]) == movesMade.end()){
                count++;
            }
            if(count>=2){
                for(int j=0; j<3; j++){
                    if(!board.isTaken(diagonal1[j]) && movesMade.find(diagonal1[j]) ==movesMade.end())
                        position = diagonal1[j];
                }
            }
        }

        for(int i=0; i<3; i++){
            int count = 0;
            if(board.isTaken(diagonal2[i]) && movesMade.find(diagonal2[i]) == movesMade.end()){
                count++;
            }
            if(count>=2){
                for(int j=0; j<3; j++){
                    if(!board.isTaken(diagonal2[j]) && movesMade.find(diagonal2[j]) ==movesMade.end())
                        position = diagonal2[j];
                }
            }
        }




        switch (turn)
        {
            case 0:
                //On first turn, always choose bottom right
                position = 57;
                movesMade.insert(57);
                break;
            case 1:
                //This case will only fire if the player goes first
                //On second turn, prefer the bottom right, but if that's taken, go bottom left.
                if (board.getSymbol(2, 2) != playerSymbol)
                {
                    position = 57;
                    movesMade.insert(57);
                } else
                {
                    //Safe to assume if I get here the player chose bottom right
                    position = 55;
                    movesMade.insert(55);
                }
                break;
            case 2:
                //This case will only fire if AI has gone first
                //Try to get top left, otherwise go top right
                if (board.getSymbol(0, 0) != playerSymbol)
                {
                    position = 49;
                    movesMade.insert(49);
                } else
                {
                    position = 51;
                    movesMade.insert(51);
                }
                break;
            case 3:
                //This case will only fire if the human went first
                //If AI got the bottom right, get the top left if possible
                //If not, get the top left if possible. Otherwise, go bottom left.
                if (block)
                {
                    movesMade.insert(position);
                } else if (movesMade.find(57) != movesMade.end() && board.getSymbol(2, 0) != playerSymbol)
                {
                    position = 55;
                    movesMade.insert(55);
                } else if (board.getSymbol(0, 0) != playerSymbol)
                {
                    position = 49;
                    movesMade.insert(49);
                } else
                {
                    position = 51;
                    movesMade.insert(51);
                }
                break;
            case 4:
                //This case will only fire if the AI went first
                //See if a win is possible, if so, win.
                //If not, try to go bottom left
                if (block)
                {
                    movesMade.insert(position);
                } else if (movesMade.find(49) != movesMade.end() && movesMade.find(57) != movesMade.end() &&
                           board.getSymbol(1, 1) != playerSymbol)
                {
                    position = 53;
                    movesMade.insert(53); //end of game
                } else if (movesMade.find(57) != movesMade.end() && movesMade.find(51) != movesMade.end() &&
                           board.getSymbol(1, 2) != playerSymbol)
                {
                    position = 54;
                    movesMade.insert(54);//end of game
                } else if (board.getSymbol(2, 0) != playerSymbol && movesMade.find(55) == movesMade.end())
                {
                    position = 55;
                    movesMade.insert(55);
                }
                break;
            case 5:
                //This case will ony fire if the player went first
                //Exhaustively check for a possible win, then just pick a spot
                if (block)
                {
                    movesMade.insert(position);
                } else if (movesMade.find(57) != movesMade.end() && movesMade.find(55) != movesMade.end() &&
                           board.getSymbol(2, 1) != playerSymbol)
                {
                    position = 56;
                    movesMade.insert(56);
                } else if (movesMade.find(49) != movesMade.end() && movesMade.find(51) != movesMade.end() &&
                           board.getSymbol(0, 1) != playerSymbol)
                {
                    position = 50;
                    movesMade.insert(50);
                } else if (movesMade.find(57) != movesMade.end() && movesMade.find(51) != movesMade.end() &&
                           board.getSymbol(1, 2) != playerSymbol)
                {
                    position = 54;
                    movesMade.insert(54);
                } else if (movesMade.find(49) != movesMade.end() && movesMade.find(55) != movesMade.end() &&
                           board.getSymbol(2, 0) != playerSymbol)
                {
                    position = 55;
                    movesMade.insert(55);
                } else if (board.getSymbol(1, 1) != playerSymbol && movesMade.find(53) == movesMade.end())
                {
                    position = 53;
                    movesMade.insert(53);
                } else
                {
                    //Try every possible spot on the board to see if it's free.
                    for (int i = 49; i < 50; i++)
                    {
                        if (!board.isTaken(i))
                        {
                            position = i;
                            break;
                        }
                    }
                }
                break;
            case 6:
                //This case will ony fire if the AI went first
                //This case is exactly like case 5, only for the AI
                //Exhaustively check for a possible win, then just pick a spot
                if (block)
                {
                    movesMade.insert(position);
                } else if (movesMade.find(57) != movesMade.end() && movesMade.find(55) != movesMade.end() &&
                           board.getSymbol(2, 1) != playerSymbol)
                {
                    board.parseInput(56, AISymbol);
                    movesMade.insert(56);
                } else if (movesMade.find(49) != movesMade.end() && movesMade.find(51) != movesMade.end() &&
                           board.getSymbol(0, 1) != playerSymbol)
                {
                    board.parseInput(50, AISymbol);
                    movesMade.insert(50);
                } else if (movesMade.find(57) != movesMade.end() && movesMade.find(51) != movesMade.end() &&
                           board.getSymbol(1, 2) != playerSymbol)
                {
                    board.parseInput(54, AISymbol);
                    movesMade.insert(54);
                } else if (movesMade.find(49) != movesMade.end() && movesMade.find(55) != movesMade.end() &&
                           board.getSymbol(2, 0) != playerSymbol)
                {
                    board.parseInput(55, AISymbol);
                    movesMade.insert(55);
                } else if (board.getSymbol(1, 1) != playerSymbol && movesMade.find(53) == movesMade.end())
                {
                    board.parseInput(53, AISymbol);
                    movesMade.insert(53);
                } else
                {
                    //Try every possible spot on the board to see if it's free.
                    //This will be the move for all future cases
                    for (int i = 49; i < 50; i++)
                    {
                        if (!board.isTaken(i))
                        {
                            position = i;
                            break;
                        }
                    }
                }
            case 7:
                if (block){
                    movesMade.insert(position);
                }else{
                    for (int i = 49; i < 50; i++)
                    {
                        if (!board.isTaken(i))
                        {
                            position = i;
                            break;
                        }
                    }
                }
            case 8:
                if (block){
                    movesMade.insert(position);
                }else{
                    for (int i = 49; i < 50; i++)
                    {
                        if (!board.isTaken(i))
                        {
                            position = i;
                            break;
                        }
                    }
                }
            case 9:
                if (block){
                    movesMade.insert(position);
                }else{
                    for (int i = 49; i < 50; i++)
                    {
                        if (!board.isTaken(i))
                        {
                            position = i;
                            break;
                        }
                    }
                }
        }//end switch
        return position;
    }//end AI move
};//end AI class

int main()
{
    //VARIABLE DECLARATION
    string promptMove = "Please select a number from the board.";
    char playerSymbol; //holds which symbol the human uses
    char AISymbol; //holds which symbol the AI uses
    int turn = 0; //tracks which turn it is for AI decision making
    char playAgain = '0'; //takes input to see if the player wants to try again
    char playerTurn = '0'; //takes input to see if the player wants to go first
    int cell = 0; //holds which cell the player chooses for their move
    char input; //temporary input holder to enable int cast

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
    AI ai;
    //end intro


    //TURN SELECTION
    if(playerTurn == '1'){
        playerSymbol = 'X';
        AISymbol ='O';

    }else{
        playerSymbol = 'O';
        AISymbol = 'X';
        board.parseInput(ai.move(board, turn, AISymbol, playerSymbol), AISymbol);
    }//end turn selection


    //PRIMARY GAME LOOP
    //So long as no one has won, and there is still a move to be made, keep playing
    while(!board.checkWin() || turn < 9){
        //Make sure the cell is valid by turning the char into its ASCII code
        while(cell < 49 || cell > 57)
        {
            cout<<endl<<promptMove<<endl;
            cin >> input;
            cell = (int)input;
            if(cell <49 || cell > 57){
                cout<<"That is not a valid cell."<<endl;
            }
        }
        //Ask the board if the cell is filled
        while(!board.parseInput(cell, playerSymbol)){
            cout<<"That is not a valid cell."<<endl<<promptMove<<endl;
            cell=(int)getchar();
            cin >> input;
            cell = (int)input;
        }
        if(board.checkWin()){
            break;
        }
        cell = 0;
        turn++;
        board.parseInput(ai.move(board, turn, AISymbol, playerSymbol), AISymbol);
        turn++;
        board.printBoard();
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
    cin >> playAgain;
    while(playAgain != 'y' && playAgain != 'n'){
        cout<<endl<<"That is not a valid entry."<<endl<<"Would you like to play again (y/n):"<<endl;
        cin >> playAgain;
    }
    //If the player wants to try again, destroy the board and call main()
    if(playAgain == 'y'){
        board.~Board();
        main();
    }
    //end game-end routine
    return 0;
}