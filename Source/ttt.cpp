#include "additionalfunctions.h"
#include "ttt.h"

TTT::TTT()
{
    player1_name = "";
    player2_name = "";

    player1_wins = 0;
    player2_wins = 0;

    order = true;
    multiplayer = false;

    lines[0].x = screenW * 5/12;
    lines[0].y = screenH * 4/12;
    lines[0].w = 5;
    lines[0].h = screenH * 7/12 + 5;

    lines[1] = lines[0];
    lines[1].x = screenW * 7/12 + 5;

    lines[2].x = screenW * 3/12;
    lines[2].y = (lines[1].h / 3) + lines[0].y;
    lines[2].w = screenW * 6/12 + 10;
    lines[2].h = 5;

    lines[3] = lines[2];
    lines[3].y = 2 * (lines[1].h / 3) + lines[0].y;

    choices[0].x = lines[2].x + 5;
    choices[0].y = lines[0].y + 5;
    choices[0].w = screenW * 2/12 - 10;
    choices[0].h = lines[2].y - lines[0].y - 10;

    choices[1] = choices[0];
    choices[1].x = lines[0].x + lines[0].w + 5;

    choices[2] = choices[0];
    choices[2].x = lines[1].x + lines[1].w + 5;

    choices[3] = choices[0];
    choices[3].y = lines[2].y + lines[2].h + 5;
    choices[3].h = (lines[3].y - 5) - (lines[2].y + lines[2].h + 5);

    choices[4] = choices[3];
    choices[4].x = choices[1].x;

    choices[5] = choices[3];
    choices[5].x = choices[2].x;

    choices[6] = choices[0];
    choices[6].y = lines[3].y + lines[3].h + 5;
    choices[6].h = (lines[0].y + lines[0].h - 5) - (choices[6].y);

    choices[7] = choices[6];
    choices[7].x = choices[1].x;

    choices[8] = choices[6];
    choices[8].x = choices[2].x;
}

int TTT::menu()
{
    bool player2;

    if (m_amount_players(player2) == -1)
    {
        return -1;
    }

    if (m_player_names(player2) == -1)
    {
        return -1;
    }

    if (m_order() == -1)
    {
        return -1;
    }

    multiplayer = player2;

    return 0;
}

int TTT::m_amount_players(bool &player2)
{
    change_fsize(250);

    int mouseX, mouseY;

    string Tic = "Tic Tac Toe";
    string play1 = "1 Player";
    string play2 = "2 Players";
    string confirm_text = "Confirm";
    string instruct = "Select either 1 Player or 2 Players and click CONFIRM";

    SDL_Event a;

    bool confirm;

    player2 = false;

    confirm = false;

    change_fsize(250);
    SDL_Rect t = {screenW * 1/4, screenH * 1/20, screenW * 2/4, screenH * 2/10};

    highlight(Tic, false, t);

    SDL_Rect p1 = {screenW * 1/10, screenH * 1/2, screenW * 2/10, screenH * 1/10};

    SDL_Rect p2 = {screenW * 7/10, screenH * 1/2, screenW * 2/10, screenH * 1/10};

    SDL_Rect confirm_pos = {screenW * 4/10, screenH * 8/10, screenW * 2/10, screenH * 1/10};
    highlight(confirm_text, false, confirm_pos);

    SDL_Rect instruct_pos = {screenW * 2/10, screenH * 1/3, screenW * 6/10, screenH * 1/20};
    highlight(instruct, false, instruct_pos);

    SDL_UpdateWindowSurface(mWindow);

    Uint32 start, total;

    while(!confirm)
    {
        if (SDL_PollEvent(&a) != 0)
        {
            if (a.type == SDL_QUIT)
            {
                return -1;
            }
        }

        if (a.type == SDL_MOUSEMOTION)
        {
            SDL_GetMouseState(&mouseX, &mouseY);
        }

        start = SDL_GetTicks();

        if (rect_detection(p1, a, mouseX, mouseY))
        {
            player2 = false;
        }

        if (rect_detection(p2, a, mouseX, mouseY))
        {
            player2 = true;
        }

        if (rect_detection(confirm_pos, a, mouseX, mouseY))
        {
            confirm = true;
        }

        //Highlight or Remove Highlight Player 1
        if (!player2)
        {
            highlight(play1, true, p1);
            highlight(play2, false, p2);
        }

        else
        {
            highlight(play1, false, p1);
            highlight(play2, true, p2);
        }

        total = SDL_GetTicks();
        fps_cap(start, total);

        SDL_RenderPresent(wRenderer);
    }

    SDL_FillRect(wSurface, NULL, black);
    SDL_UpdateWindowSurface(mWindow);

    return 0;
}

int TTT::m_player_names(bool player2)
{
    change_fsize(250);

    SDL_Event a;

    int mouseX, mouseY;

    bool button_release = false;

    string Tic = "Tic Tac Toe";
    SDL_Rect t = {screenW * 1/4, screenH * 1/20, screenW * 2/4, screenH * 2/10};
    highlight(Tic, false, t);
    bool confirm = false;

    string player_n = "Player Name: ";
    string player2_n = "Player 2 Name: ";
    string instruct_p1 = "Enter the player name(s)";
    string instruct_p2 = "Press Enter to set name(s) and click CONFIRM to continue";
    string confirm_text = "Confirm";

    SDL_Rect instruct_pos_p1 = {screenW * 3/10, screenH * 3/10, screenW * 4/10, screenH * 1/20};
    highlight(instruct_p1, false, instruct_pos_p1);

    SDL_Rect instruct_pos_p2 = {screenW * 1/10, screenH * 7/20, screenW * 8/10, screenH * 1/20};
    highlight(instruct_p2, false, instruct_pos_p2);

    SDL_Rect p1 = {screenW * 1/10, screenH * 1/2, screenW * 2/10, screenH * 1/10};

    SDL_Rect p2 = {screenW * 1/10, screenH * 1/2 + (screenH * 3/20), screenW * 2/10, screenH * 1/10};

    SDL_Rect player1_input = {p1.x + screenW * 5/20, screenH * 1/2, screenW * 2/4, screenH * 1/10};
    SDL_SetTextInputRect(&player1_input);
    SDL_FillRect(wSurface, &player1_input, white);

    SDL_Rect player2_input = {p2.x + screenW * 5/20, p2.y, screenW * 2/4 , screenH * 1/10};
    SDL_SetTextInputRect(&player2_input);

    SDL_Rect confirm_pos = {screenW * 4/10, screenH * 8/10, screenW * 2/10, screenH * 1/10};
    highlight(confirm_text, false, confirm_pos);

    if (!player2)
    {
        player2_name = "Computer";
    }

    else
    {
        SDL_FillRect(wSurface, &player2_input, white);
    }

    while (!confirm)
    {
        if (SDL_PollEvent(&a) != 0)
        {
            if (a.type == SDL_QUIT)
            {
                return -1;
            }
        }

        if (a.type == SDL_MOUSEMOTION)
        {
            SDL_GetMouseState(&mouseX, &mouseY);
        }

        Uint32 start = SDL_GetTicks();

        highlight(player_n, false, p1);

        if (player2)
        {
            highlight(player2_n, false, p2);
        }

        if ((rect_detection(player1_input, a, mouseX, mouseY)) && (button_release))
        {
            button_release = false;
            player1_name = input_text(player1_input, 10, player1_name);
        }

        if (player2)
        {
            if ((rect_detection(player2_input, a, mouseX, mouseY)) && (button_release))
            {
                button_release = false;
                player2_name = input_text(player2_input, 10, player2_name);
            }
        }

        if (a.type == SDL_MOUSEBUTTONUP)
        {
            button_release = true;
        }

        if (rect_detection(confirm_pos, a, mouseX, mouseY))
        {
            if ((player1_name.length() != 0) && (player2_name.length() != 0))
            {
                confirm = true;
            }

            if (player1_name == player2_name)
            {
                confirm = false;
            }
        }

        Uint32 total = SDL_GetTicks();
        fps_cap(start, total);

        if ((player1_name == "Quit") || (player2_name == "Quit"))
        {
            return -1;
        }

        SDL_RenderPresent(wRenderer);
    }

    SDL_FillRect(wSurface, NULL, black);
    SDL_UpdateWindowSurface(mWindow);

    return 0;
}

int TTT::m_order()
{
    change_fsize(250);

    int mouseX, mouseY;

    bool select = true;

    SDL_Event a;

    string Tic = "Tic Tac Toe";
    SDL_Rect t = {screenW * 1/4, screenH * 1/20, screenW * 2/4, screenH * 2/10};
    highlight(Tic, false, t);

    string instruct = "Select the person who plays first and press CONFIRM to continue";
    SDL_Rect instruct_pos = {screenW * 1/10, screenH * 7/20, screenW * 8/10, screenH * 1/20};
    highlight(instruct, false, instruct_pos);

    string confirm_text = "Confirm";
    SDL_Rect confirm_pos = {screenW * 4/10, screenH * 8/10, screenW * 2/10, screenH * 1/10};
    highlight(confirm_text, false, confirm_pos);

    SDL_Rect p1n = {screenW * 1/10, screenH * 1/2, screenW * 2/10, screenH * 1/10};

    SDL_Rect p2n = {screenW * 7/10, screenH * 1/2, screenW * 2/10, screenH * 1/10};

    bool quit = false;
    bool confirm = false;

    while(!quit)
    {
        if (SDL_PollEvent(&a) == 1)
        {
            if (a.type == SDL_QUIT)
            {
                return -1;
            }
        }

        if (SDL_MOUSEBUTTONUP)
        {
            quit = true;
        }
    }

    while (!confirm)
    {
        if (SDL_PollEvent(&a) == 1)
        {
            if (a.type == SDL_QUIT)
            {
                return -1;
            }
        }

        Uint32 start = SDL_GetTicks();

        if (a.type == SDL_MOUSEMOTION)
        {
            SDL_GetMouseState(&mouseX, &mouseY);
        }

        if (rect_detection(p1n, a, mouseX, mouseY))
        {
            select = true;
        }

        if (rect_detection(p2n, a, mouseX, mouseY))
        {
            select = false;
        }

        if (rect_detection(confirm_pos, a, mouseX, mouseY))
        {
            confirm = true;
        }

        if (select)
        {
            highlight(player1_name, true, p1n);
            highlight(player2_name, false, p2n);

            order = true;
        }

        else
        {
            highlight(player1_name, false, p1n);
            highlight(player2_name, true, p2n);

            order = false;
        }

        Uint32 total = SDL_GetTicks();
        fps_cap(start, total);

        SDL_RenderPresent(wRenderer);
    }

    SDL_FillRect(wSurface, NULL, black);
    SDL_UpdateWindowSurface(mWindow);

    return 0;
}

int TTT::game_loop()
{
    int win_type;

    SDL_Event a;

    draw_heading();

    draw_board();

    update_wins();

    while (1)
    {
        if (SDL_PollEvent(&a) == 1)
        {
            if (a.type == SDL_QUIT)
            {
                return -1;
            }
        }

        if (order)
        {
            if (!multiplayer)
            {
                if (get_player_choice(1) < 0)
                {
                    return -1;
                }

                win_type = check_win();

                if (win_type != 0)
                {
                    determine_winner(win_type);
                    return 0;
                }

                get_computer_choice();

                win_type = check_win();

                if (win_type != 0)
                {
                    determine_winner(win_type);
                    return 0;
                }
            }

            else
            {
                if (get_player_choice(1) < 0)
                {
                    return -1;
                }

                win_type = check_win();

                if (win_type != 0)
                {
                    determine_winner(win_type);
                    return 0;
                }

                if (get_player_choice(2) < 0)
                {
                    return -1;
                }

                win_type = check_win();

                if (win_type != 0)
                {
                    determine_winner(win_type);
                    return 0;
                }
            }
        }

        else
        {
            if (!multiplayer)
            {
                get_computer_choice();

                win_type = check_win();

                if (win_type != 0)
                {
                    determine_winner(win_type);
                    return 0;
                }

                if (get_player_choice(1) < 0)
                {
                    return -1;
                }

                win_type = check_win();

                if (win_type != 0)
                {
                    determine_winner(win_type);
                    return 0;
                }
            }

            else
            {
                if (get_player_choice(2) < 0)
                {
                    return -1;
                }

                win_type = check_win();

                if (win_type != 0)
                {
                    determine_winner(win_type);
                    return 0;
                }

                if (get_player_choice(1) < 0)
                {
                    return -1;
                }

                win_type = check_win();

                if (win_type != 0)
                {
                    determine_winner(win_type);
                    return 0;
                }
            }
        }
    }

    SDL_FillRect(wSurface, NULL, black);

    return 0;
}

void TTT::draw_heading()
{
    change_fsize(250);

    string Tic = "Tic Tac Toe";

    SDL_Rect title_pos = {screenW * 4/10, screenH * 1/20, screenW * 2/10, screenH * 1/10};
    highlight(Tic, false, title_pos);

    string instruct = "Click on the area to take the space";

    SDL_Rect instruct_pos = {screenW * 2/10, title_pos.y + title_pos.h, screenW * 6/10, screenH * 1/20};
    highlight(instruct, false, instruct_pos);

    SDL_Rect p1_pos = {screenW * 1/20, screenH * 1/4, screenW * 3/20, screenH * 1/10};
    highlight(player1_name, false, p1_pos);

    SDL_Rect p2_pos = {screenW * 16/20, screenH * 1/4, screenW * 3/20, screenH * 1/10};
    highlight(player2_name, false, p2_pos);

    SDL_RenderPresent(wRenderer);
}

void TTT::draw_board()
{
    SDL_FillRects(wSurface, lines, 4, white);

    for (int i = 0; i < 9; i++)
    {
        board[i] = ' ';
    }

    SDL_RenderPresent(wRenderer);
}

int TTT::get_player_choice(int order_number)
{
    change_fsize(250);

    string name;

    SDL_Event a;

    bool pick = false;

    int mouseX, mouseY;

    if (order_number == 1)
    {
        name = player1_name;
    }

    else if (order_number == 2)
    {
        name = player2_name;
    }

    name += ", It is your turn";

    SDL_Rect name_pos = {lines[2].x + (lines[0].x - lines[2].x)/2, screenH * 4/20, lines[1].x - lines[2].x, screenH * 1/10};
    highlight(name, false, name_pos);

    SDL_RenderPresent(wRenderer);

    while (!pick)
    {
        if (SDL_PollEvent(&a) == 1)
        {
            if (a.type == SDL_QUIT)
            {
                return -1;
            }
        }

        Uint32 start = SDL_GetTicks();

        if (a.type == SDL_MOUSEMOTION)
        {
            SDL_GetMouseState(&mouseX, &mouseY);
        }

        if (rect_detection(choices[0], a, mouseX, mouseY))
        {
            pick = selected(0, order_number);
        }

        if (rect_detection(choices[1], a, mouseX, mouseY))
        {
            pick = selected(1, order_number);
        }

        if (rect_detection(choices[2], a, mouseX, mouseY))
        {
            pick = selected(2, order_number);
        }

        if (rect_detection(choices[3], a, mouseX, mouseY))
        {
            pick = selected(3, order_number);
        }

        if (rect_detection(choices[4], a, mouseX, mouseY))
        {
            pick = selected(4, order_number);
        }

        if (rect_detection(choices[5], a, mouseX, mouseY))
        {
            pick = selected(5, order_number);
        }

        if (rect_detection(choices[6], a, mouseX, mouseY))
        {
            pick = selected(6, order_number);
        }

        if (rect_detection(choices[7], a, mouseX, mouseY))
        {
            pick = selected(7, order_number);
        }

        if (rect_detection(choices[8], a, mouseX, mouseY))
        {
            pick = selected(8, order_number);
        }

        Uint32 total = SDL_GetTicks();

        fps_cap(start, total);
    }

    update_spaces();

    SDL_FillRect(wSurface, &name_pos, black);

    SDL_RenderPresent(wRenderer);

    return 0;
}

bool TTT::selected(int choice, int order_number)
{
    if (board[choice] == ' ')
    {
        if ((order) && (order_number == 1))
        {
            board[choice] = 'X';
        }

        else if ((order) && (order_number == 2))
        {
            board[choice] = 'O';
        }

        else if ((!order) && (order_number == 1))
        {
            board[choice] = 'O';
        }

        else if ((!order) && (order_number == 2))
        {
            board[choice] = 'X';
        }

        return true;
    }

    return false;
}

void TTT::update_spaces()
{
    change_fsize(120);

    int w, h;

    string X = "X";
    string O = "O";

    for (int i = 0; i < 9; i++)
    {
        if (board[i] == 'X')
        {
            TTF_SizeText(font, X.c_str(), &w, &h);
            SDL_Rect pos = {choices[i].x + choices[i].w/2 - w/2, choices[i].y, w, choices[i].h};
            highlight(X, false, pos);
        }

        else if (board[i] == 'O')
        {
            TTF_SizeText(font, O.c_str(), &w, &h);
            SDL_Rect pos = {choices[i].x + choices[i].w/2 - w/2, choices[i].y, w, choices[i].h};
            highlight(O, false, pos);
        }
    }

    SDL_RenderPresent(wRenderer);
}

int TTT::check_win()
{
    bool full = true;
    int line = 0;

    if ((board[0] == board[1]) && (board[1] == board[2]) && (board[0] != ' '))
    {
        line = 1;
    }

    if ((board[3] == board[4]) && (board[4] == board[5]) && (board[3] != ' '))
    {
        line = 2;
    }

    if ((board[6] == board[7]) && (board[7] == board[8]) && (board[6] != ' '))
    {
        line = 3;
    }

    if ((board[0] == board[3]) && (board[3] == board[6]) && (board[0] != ' '))
    {
        line = 4;
    }

    if ((board[1] == board[4]) && (board[4] == board[7]) && (board[1] != ' '))
    {
        line = 5;
    }

    if ((board[2] == board[5]) && (board[5] == board[8]) && (board[2] != ' '))
    {
        line = 6;
    }

    if ((board[0] == board[4]) && (board[4] == board[8]) && (board[0] != ' '))
    {
        line = 7;
    }

    if ((board[2] == board[4]) && (board[4] == board[6]) && (board[2] != ' '))
    {
        line = 8;
    }

    if (line == 0)
    {
        for (int i = 0; i < 9; i++)
        {
            if (board[i] == ' ')
            {
                full = false;
            }
        }

        if (full)
        {
            line = -1;
        }
    }

    return line;
}

int TTT::computer_logic()
{
    char pieces[2];

    if (order)
    {
        pieces[0] = 'O';
        pieces[1] = 'X';
    }

    else
    {
        pieces[0] = 'X';
        pieces[1] = 'O';
    }

    for (int i = 0; i < 2; i++)
    {
        if (board[0] == ' ')
        {
            if ((board[1] == board[2]) && (board[1] == pieces[i]))
            {
                return 0;
            }

            else if ((board[3] == board[6]) && (board[3] == pieces[i]))
            {
                return 0;
            }

            else if ((board[4] == board[8]) && (board[4] == pieces[i]))
            {
                return 0;
            }
        }

        if (board[1] == ' ')
        {
            if ((board[0] == board[2]) && (board[0] == pieces[i]))
            {
                return 1;
            }

            else if ((board[4] == board[7]) && (board[4] == pieces[i]))
            {
                return 1;
            }
        }

        if (board[2] == ' ')
        {
            if ((board[0] == board[1]) && (board[0] == pieces[i]))
            {
                return 2;
            }

            else if ((board[4] == board[6]) && (board[4] == pieces[i]))
            {
                return 2;
            }

            else if ((board[5] == board[8]) && (board[5] == pieces[i]))
            {
                return 2;
            }
        }

        if (board[3] == ' ')
        {
            if ((board[4] == board[5]) && (board[4] == pieces[i]))
            {
                return 3;
            }

            else if ((board[0] == board[6]) && (board[0] == pieces[i]))
            {
                return 3;
            }
        }

        if (board[4] == ' ')
        {
            if ((board[3] == board[5]) && (board[3] == pieces[i]))
            {
                return 4;
            }

            else if ((board[1] == board[7]) && (board[1] == pieces[i]))
            {
                return 4;
            }

            else if ((board[0] == board[8]) && (board[0] == pieces[i]))
            {
                return 4;
            }

            else if ((board[2] == board[6]) && (board[2] == pieces[i]))
            {
                return 4;
            }
        }

        if (board[5] == ' ')
        {
            if ((board[3] == board[4]) && (board[3] == pieces[i]))
            {
                return 5;
            }

            else if ((board[2] == board[8]) && (board[2] == pieces[i]))
            {
                return 5;
            }
        }

        if (board[6] == ' ')
        {
            if ((board[0] == board[3]) && (board[0] == pieces[i]))
            {
                return 6;
            }

            else if ((board[2] == board[4]) && (board[2] == pieces[i]))
            {
                return 6;
            }

            else if ((board[7] == board[8]) && (board[7] == pieces[i]))
            {
                return 6;
            }
        }

        if (board[7] == ' ')
        {
            if ((board[1] == board[4]) && (board[1] == pieces[i]))
            {
                return 7;
            }

            else if ((board[6] == board[8]) && (board[6] == pieces[i]))
            {
                return 7;
            }
        }

        if (board[8] == ' ')
        {
            if ((board[2] == board[5]) && (board[2] == pieces[i]))
            {
                return 8;
            }

            else if ((board[0] == board[4]) && (board[0] == pieces[i]))
            {
                return 8;
            }

            else if ((board[6] == board[7]) && (board[6] == pieces[i]))
            {
                return 8;
            }
        }
    }

    return -1;
}

void TTT::get_computer_choice()
{
    int play = -1;

    bool emp = true;

    for (int i = 0; i < 9; i++)
    {
        if (board[i] != ' ')
        {
            emp = false;
        }
    }

    srand(time(NULL));

    if (emp)
    {
        play = (rand() % 5) * 2;
    }

    else
    {
        play = computer_logic();
    }

    if (play == -1)
    {
        do
        {
            play = rand() % 9;
        }while(board[play] != ' ');
    }

    if (order)
    {
        board[play] = 'O';
    }

    else
    {
        board[play] = 'X';
    }

    update_spaces();
}

void TTT::determine_winner(int win)
{
    change_fsize(250);

    string name;

    int play_num = 0;

    int w, h;

    if (player1_name.length() > player2_name.length())
    {
        name = player1_name;
    }

    else
    {
        name = player2_name;
    }

    name += " It is your turn";

    TTF_SizeText(font, name.c_str(), &w, &h);
    SDL_Rect clear_space = {lines[2].x + (lines[0].x - lines[2].x)/2, screenH * 4/20, lines[1].x - lines[2].x, screenH * 1/10};
    SDL_FillRect(wSurface, &clear_space, black);

    SDL_RenderPresent(wRenderer);

    change_fsize(120);
    string X = "X";
    string O = "O";

    for (int i = 0; i < 9; i++)
    {
        if (board[i] == 'X')
        {
            TTF_SizeText(font, X.c_str(), &w, &h);
            SDL_Rect pos = {choices[i].x + choices[i].w/2 - w/2, choices[i].y, w, choices[i].h};

            if ((win == 1) && ((i == 0) || (i == 1) || (i == 2)))
            {
                play_num = 1;
                highlight(X, true, pos);
            }

            else if ((win == 2) && ((i == 3) || (i == 4) || (i == 5)))
            {
                play_num = 1;
                highlight(X, true, pos);
            }

            else if ((win == 3) && ((i == 6) || (i == 7) || (i == 8)))
            {
                play_num = 1;
                highlight(X, true, pos);
            }

            else if ((win == 4) && ((i == 0) || (i == 3) || (i == 6)))
            {
                play_num = 1;
                highlight(X, true, pos);
            }

            else if ((win == 5) && ((i == 1) || (i == 4) || (i == 7)))
            {
                play_num = 1;
                highlight(X, true, pos);
            }

            else if ((win == 6) && ((i == 2) || (i == 5) || (i == 8)))
            {
                play_num = 1;
                highlight(X, true, pos);
            }

            else if ((win == 7) && ((i == 0) || (i == 4) || (i == 8)))
            {
                play_num = 1;
                highlight(X, true, pos);
            }

            else if ((win == 8) && ((i == 2) || (i == 4) || (i == 6)))
            {
                play_num = 1;
                highlight(X, true, pos);
            }
        }

        else if (board[i] == 'O')
        {
            TTF_SizeText(font, O.c_str(),&w, &h);
            SDL_Rect pos = {choices[i].x + choices[i].w/2 - w/2, choices[i].y, w, choices[i].h};

            if ((win == 1) && ((i == 0) || (i == 1) || (i == 2)))
            {
                play_num = 2;
                highlight(O, true, pos);
            }

            else if ((win == 2) && ((i == 3) || (i == 4) || (i == 5)))
            {
                play_num = 2;
                highlight(O, true, pos);
            }

            else if ((win == 3) && ((i == 6) || (i == 7) || (i == 8)))
            {
                play_num = 2;
                highlight(O, true, pos);
            }

            else if ((win == 4) && ((i == 0) || (i == 3) || (i == 6)))
            {
                play_num = 2;
                highlight(O, true, pos);
            }

            else if ((win == 5) && ((i == 1) || (i == 4) || (i == 7)))
            {
                play_num = 2;
                highlight(O, true, pos);
            }

            else if ((win == 6) && ((i == 2) || (i == 5) || (i == 8)))
            {
                play_num = 2;
                highlight(O, true, pos);
            }

            else if ((win == 7) && ((i == 0) || (i == 4) || (i == 8)))
            {
                play_num = 2;
                highlight(O, true, pos);
            }

            else if ((win == 8) && ((i == 2) || (i == 4) || (i == 6)))
            {
                play_num = 2;
                highlight(O, true, pos);
            }
        }
    }

    change_fsize(250);

    if (win == -1)
    {
        string draw = "It is a Draw";
        SDL_Rect draw_pos = {lines[2].x + (lines[0].x - lines[2].x)/2, screenH * 4/20, lines[1].x - lines[2].x, screenH * 1/10};
        highlight(draw, false, draw_pos);
    }

    else if (((play_num == 1) && (order)) || ((!order) && (play_num == 2)))
    {
        name = player1_name + " is the Winner";

        SDL_Rect draw_pos = {lines[2].x + (lines[0].x - lines[2].x)/2, screenH * 4/20, lines[1].x - lines[2].x, screenH * 1/10};
        highlight(name, false, draw_pos);

        player1_wins++;
    }

    else
    {
        name = player2_name + " is the Winner";

        SDL_Rect draw_pos = {lines[2].x + (lines[0].x - lines[2].x)/2, screenH * 4/20, lines[1].x - lines[2].x, screenH * 1/10};
        highlight(name, false, draw_pos);

        player2_wins++;
    }

    SDL_RenderPresent(wRenderer);

    SDL_Event e;

    bool cont = false;

    while (!cont)
    {
        if (SDL_PollEvent(&e) == 1)
        {
            if (e.type == SDL_QUIT)
            {
                cont = true;
            }
        }

        if ((e.type == SDL_MOUSEBUTTONDOWN) || (e.type == SDL_KEYDOWN))
        {
            cont = true;
        }
    }
}

int TTT::play_again()
{
    change_fsize(250);

    bool select = false;
    bool confirm = false;

    SDL_Event a;

    int mouseX, mouseY;

    SDL_FillRect(wSurface, NULL, black);

    string again_text = "Would you like to play again ?";
    string Y = "Yes";
    string N = "No";
    string confirm_text = "Confirm";

    SDL_Rect again_pos = {screenW * 2/10, screenH * 3/12, screenW * 6/10, screenH * 1/10};
    highlight(again_text, false, again_pos);

    SDL_Rect y_pos = {screenW * 2/10, screenH * 1/2, screenW * 1/10, screenH * 1/10};

    SDL_Rect n_pos = {screenW * 7/10, screenH * 1/2, screenW * 1/10, screenH * 1/10};

    SDL_Rect confirm_pos = {screenW * 4/10, screenH * 8/10, screenW * 2/10, screenH * 1/10};
    highlight(confirm_text, false, confirm_pos);

    while (!confirm)
    {
        if (SDL_PollEvent(&a) == 1)
        {
            if (a.type == SDL_QUIT)
            {
                return -1;
            }
        }

        Uint32 start = SDL_GetTicks();

        if (a.type == SDL_MOUSEMOTION)
        {
            SDL_GetMouseState(&mouseX, &mouseY);
        }

        if (rect_detection(y_pos, a, mouseX, mouseY))
        {
            select = false;
        }

        if (rect_detection(n_pos, a, mouseX, mouseY))
        {
            select = true;
        }

        if (rect_detection(confirm_pos, a, mouseX, mouseY))
        {
            confirm = true;
        }

        if (!select)
        {
            highlight(Y, true, y_pos);
            highlight(N, false, n_pos);
        }

        else
        {
            highlight(N, true, n_pos);
            highlight(Y, false, y_pos);
        }

        Uint32 total = SDL_GetTicks();

        fps_cap(start, total);

        SDL_RenderPresent(wRenderer);
    }

    SDL_FillRect(wSurface, NULL, black);

    if (!select)
    {
        return 0;
    }

    return -1;
}

void TTT::update_wins()
{
    change_fsize(250);

    char e[3];
    char f[3];

    snprintf(e, 3, "%d", player1_wins);
    snprintf(f, 3, "%d", player2_wins);

    string p1_wins = "Wins: ";
    p1_wins.append(e);

    string p2_wins = "Wins: ";
    p2_wins.append(f);

    SDL_Rect p1_wins_pos = {screenW * 3/40, screenH * 7/20, screenW * 1/10, screenH * 1/10};

    SDL_Rect p2_wins_pos = {screenW * 33/40, screenH * 7/20, screenW * 1/10, screenH * 1/10};

    if (player1_wins >= 0)
    {
        highlight(p1_wins.c_str(), false, p1_wins_pos);
    }

    if (player2_wins >= 0)
    {
        highlight(p2_wins.c_str(), false, p2_wins_pos);
    }

    SDL_RenderPresent(wRenderer);
}



