#ifndef ttt
#define ttt

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>

using namespace std;

class TTT
{
public:

    TTT();

    int menu();                                                  //Runs the follow menus
    int m_amount_players(bool &player2);                   //Gets the amount of players
    int m_player_names(bool player2);                                     //Gets the player names
    int m_order();

    int game_loop();                                                   //Gets the order

    void draw_heading();                      //Draws title, wins and the whose turn it is

    void draw_board();                        //Draws the TicTacToe Board

    int get_player_choice(int order_number);                 //Gets the player choice (From both or one player)

    void get_computer_choice();               //Gets the computers choice

    int computer_logic();

    bool selected(int choice, int order_number);

    void update_spaces();

    void determine_winner(int win);

    int play_again();

    void update_wins();

    int check_win();                          //Checks board if there is a win

private:
    char board[9];         //char array to help with checking win
    int player1_wins;    //Wins of the first player
    int player2_wins;     //Wins of the second player
    string player1_name;
    string player2_name;
    bool order;
    bool multiplayer;
    SDL_Rect lines[4];
    SDL_Rect choices[9];   //Rects that display the choices
};

#endif // ttt
