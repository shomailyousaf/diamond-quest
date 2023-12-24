#include <iostream>
#include <time.h>
#include <fstream>
#include <windows.h>
#include <conio.h>
#include <cmath>
using namespace std;
char boardA[23][140];
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);  //function used to handle console related properties
int boosting = 0;
void boosting_r();
void show_boost();
void store();
//______________________loading game frame from .txt file__________________________________________
char header[12][160];
void show_header()
{
    for (int i = 0; i < 12; i++)
    {

        for (int j = 0; j < 160; j++)      // display of main header page 
        {

            cout << header[i][j];
        }
        cout << endl;
    }
}
void ronin_header()
{
    string s;
    fstream f;
    f.open("header.txt", ios::in);//reads the contents of "header.txt" 
    for (int i = 0; i < 12; i++)
    {
        getline(f, s);
        for (int j = 0; j < 160; j++)   //The inner loop assigns each character of the read line to the corresponding position in the header array.
        {
            header[i][j] = s[j];
        }
    }
    f.close();
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);  //changes the text color in the console to green

    show_header();
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);  //changes the text color to light aqua
}
//--------------------end show header----------------------------------------------------------------------------

void load()
{
    fstream file;
    file.open("Frame.txt", ios::in);
    string line;
    for (int i = 0; i < 23; i++)
    {
        getline(file, line);
        for (int j = 0; j < 140; j++)  {    //Reads the content of "Frame.txt" and loads it into the `boardA` array

            boardA[i][j] = line[j];
        }
    }
    file.close();
}
void board_show()
{

    for (int i = 0; i < 23; i++)
    {

        for (int j = 0; j < 140; j++)       //Displays the current state of the game frame (`boardA`) on the console.
        {

            cout << boardA[i][j];
        }
        cout << endl;
    }
}
//----------------------end new game------------------------------------------------------------
//-------------------------------continue game-----------------------------------------------
void loadCont()
{
    fstream file;
    file.open("Frame_cont.txt", ios::in);
    string line;
    for (int i = 0; i < 23; i++)
    {
        getline(file, line);
        for (int j = 0; j < 140; j++)      //Reads the content of "Frame_cont.txt" and loads it into the `boardA` array for continuing the game.
        {

            boardA[i][j] = line[j];
        }
    }
    file.close();
}
void board_showCont()
{

    for (int i = 0; i < 23; i++)
    {

        for (int j = 0; j < 140; j++)   //Displays the current state of the game frame for a continued game
        { 

            cout << boardA[i][j];
        }
        cout << endl;
    }
}
//_________________________end load and show frame from .txt file____________________________________
//************************decleration of goto funcion to avoid flickring of game frame*************
void gotoxy(int x, int y) // Function Definition
{
    COORD coordinates;
    coordinates.X = x;
    coordinates.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);     //Moves the console cursor to the specified coordinates (x, y).

}

bool gameRunning = true;     //controls the main loop of the game whether the game is running or not
char gun = '|';

//*********************************************Ronin movement*******************************************************
void moveRonin_down();
void moveRonin_left();
void moveRonin_up();
void moveRonin_right();
void moveRonin_freefall();   //these functions define different movements for Ronin
void moveRoninWith_slap();
char Ronin = 1;
int RoninX = 9;
int RoninY = 58;
// ________________________________Plate movement______________________________________________________________
void slapSelf_move();
bool slapSelf_up();
bool slapSelf_down();
int turn = 0;
int slapX = 5;          // represents currrent position of plate
int slapY = 16;

bool gameRunning_slap_up = true;
//__________________________________________________________________________________
bool gameRunning_slap1 = true;    // Handles Ronin's movement when interacting with obstacles
bool slap1Self_move();
int turn_2 = 0;
int slap1X = 15;
int slap1Y = 73;
int slap2X = 10;
bool slap1Self_move_Up();
bool slap1Self_move_down();
//______________________________________________________________________________________-
int turn_3 = 0;
bool slap2Self_move_Up();
void slap2Self_move();
bool slap2Self_move_down();
// slap 1 movement end____________________________________________________________________
//functions handle detecting, counting, and displaying lives.
int lives = 3;
bool lives_detect();
void lives_count();
void lives_show();
bool l_detect = true;
//-------------------------------------------------------------------------------------------
int pintchX = 4;  //represent the position and character 
int pintchY = 35;
char pintch = 177;
//--------------pintch end--------------------------------------------------------------------

int gunX = 2;
int gunY = 46;
bool gun_fire();
char bullet = 31;
bool gameRunning_fire = true;
//--------------------gun fire end------------------------------------------------------------
void resetRonin();
//--------------------------jump boosterr------------------------------------------------------
char gravity_ch = 178;
bool gravity_off = false;

int jbY = 125;
int jbX = 21;
//-------------------------------------------------------------------------------------------------------
char dimond = 4;
int fX = 6;   //Store the position of the dimond on the game screen
int fY = 131;
int dimond_count = 6;
void remaining_dimond();
char pre_item = ' ';  //Stores the character of the previous item
void gravity();

int change_d = 0;
bool machine_gun();
bool machine_down();
bool machine_up();
int machineX_1 = 19;
int machineX_2 = 20;
int machineY_start = 4;
int machineY_end = 10;

bool machine_fire();
char machine_bullet = 16;
int m_bullet_x = 19;
int m_bullet_y = 10;
int m2_bullet_x = 16;
int m2_bullet_y = 10;
bool Runningfire1 = true;
bool Runningfire2 = true;
bool machine_fire2();
void gravity_jump();
char gravity_on = '@';
char ghostX = 9;
char ghostY = 110;
char previousItemR = ' ';
int ghostDirection();
bool ghostMovementRand();
bool Running_random = true;
int distance(int p_x, int p_y, int g_x, int g_y);
int small_idx();
bool ghost_chase();
bool Running_chasing = true;
int ghostX_2 = ghostX + 1;
int ghostY_2 = ghostY;
char boost = 3;
char previousItem_chase = ' ';
bool fire_down();

int main()
{

    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = false; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);

//--------------------------------------------------------------------------------------------------
reverse:
    system("cls");
    int option;
    ronin_header();
    cout << "\n";
    cout << "\t\t1.Play New Game\n";
    cout << "\t\t2.Continue Load Game\n";
    cout << "\t\t3.Exit\n\n";
    cout << "Press any option...";
    cin >> option;
    if (option == 1)
    {
        load();

        boardA[9][58] = Ronin; // placing Ronin in board
        //--------------reseting ronin position for game-------------
        RoninX = 9;
        RoninY = 58;
        //-----------------pintch position setting------------------------------

        //-----------------------------------------------------------------
        boardA[1][125] = boost; //placement of boost character
        boardA[6][137] = boost;
        boardA[jbX][jbY] = gravity_ch;
        //placement of gravity character at various positions in board
        boardA[fX][fY] = dimond;
        boardA[20][65] = dimond;
        boardA[21][10] = dimond;
        boardA[4][3] = dimond;     
        boardA[4][37] = dimond;
        boardA[17][132] = dimond;
        boardA[8][97] = dimond;
        boardA[1][115] = gravity_on;
        boardA[ghostX_2][ghostY_2] = '-';
        //-------------
        boardA[pintchX][pintchY] = pintch;

        boardA[21][101] = pintch;  //pintch character

        boardA[18][40] = pintch;

        gotoxy(46, 1);

        cout << gun;   // prints gun at console
        boardA[ghostX][ghostY] = 'R';

        system("cls");
        board_show();
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);   //changes the color of text
        gotoxy(pintchY, pintchX);
        cout << pintch;
        gotoxy(101, 21);
        cout << pintch;
        gotoxy(40, 18);
        cout << pintch;

        gotoxy(ghostY, ghostX);
        cout << "R";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    }
    else if (option == 2)
    {
    // If option 2 is selected, perform the following actions

        store();  // Save the current game state
        loadCont();
        system("cls");// Clear the console screen
        board_showCont();
    }
    // Game loop runs while lives are greater than 0
    while (lives > 0)
    {

        Sleep(100);// Pause for a short duration (100 milliseconds)
        l_detect = lives_detect();
        remaining_dimond();
// Check for game over conditions: no lives, or certain game elements are not running
        if (l_detect == false || gameRunning_fire == false || Runningfire1 == false || Runningfire2 == false || Running_random == false || Running_chasing == false)
        {
            Beep(600, 500);  // Emit a beep sound indicating a loss of life
            if (boosting == 0)
                lives_count();// If not boosting, decrement the number of lives
            else
            {
                boosting--; // If boosting, decrement the boost counter
            }
            resetRonin();
        }
        show_boost();// Display the boost status on the screen
        lives_show();

        if (gameRunning_slap_up)
        {
            slapSelf_move();  // Move the player character in response to a slap action
        }
        if (gameRunning_slap1)
        {
            slap1Self_move();// Move the player character in response to another slap action
        }
        slap2Self_move();
        if (GetAsyncKeyState(VK_LEFT))
        {
            moveRonin_left();    // Move the player character to the left
        }
        if (GetAsyncKeyState(VK_RIGHT))
        {
            moveRonin_right();
        }
        if (GetAsyncKeyState(VK_UP))
        {
            moveRonin_up();
        }
        // Check for gravity-related actions when gravity is off
        if (gravity_off == true)
        {
            if (GetAsyncKeyState(VK_UP))
            {
                gravity_jump();// Perform a jump action when the up arrow key is pressed
            }
        }
        if (boardA[RoninX][RoninY + 1] == gravity_on || boardA[RoninX][RoninY - 1] == gravity_on)
        {
            gravity_off = false;  // Turn off gravity if the player is near a gravity-affected area
        }
        if (GetAsyncKeyState(VK_ESCAPE))
        {
            system("cls");
            goto reverse;
        }
        if (lives == 0)
        {
            gotoxy(6, 30);
            cout << "Game Over";
            getch();  // Wait for a key press
            goto reverse;
        }
        if (dimond == 0)
        {
            gotoxy(6, 30);
            cout << "You Win";
            getch();//Wait for a key press
            break;
        }
        // Move the player character in free fall
        moveRonin_freefall();
        moveRoninWith_slap();
        // Check and update the status of various game elements
        gameRunning_fire = gun_fire();
        gravity();// Apply gravity to the player character
        machine_gun();
        Runningfire1 = machine_fire();
        Runningfire2 = machine_fire2();

        Running_random = ghostMovementRand();
        Running_chasing = ghost_chase();
    }
}
//---------------------------main end----------------------------------------------------------------------------------------------------------------------

void moveRonin_left()
{
// Check if the cell two spaces to the left of Ronin is empty, indicating freefall
    if (boardA[RoninX + 2][RoninY] == ' ')
    {
        moveRonin_freefall();
    }
    // Check if there is a diamond to the left of Ronin
    if (boardA[RoninX][RoninY - 1] == dimond)
    {
        boardA[RoninX][RoninY - 1] = ' ';
        gotoxy(RoninY - 1, RoninX);
        cout << " ";
        dimond_count--;
    }

    if (boardA[RoninX][RoninY - 1] == gravity_ch)
    {
        gravity_off = true;
    }
    if (boardA[RoninX][RoninY - 1] == boost)
    {
        boosting_r();  // Activate the boost function if Ronin moves onto a boost item
    }
    if (boardA[RoninX][RoninY - 1] == '.')
    {
       // Move Ronin to the left, updating the water movement
        boardA[RoninX][RoninY] = pre_item;
        gotoxy(RoninY, RoninX);
        cout << pre_item;
        RoninY = RoninY - 1;
        pre_item = boardA[RoninX][RoninY];
        gotoxy(RoninY, RoninX);
        cout << Ronin;
    }
     // Check if the cell to the left of Ronin is empty
    if (boardA[RoninX][RoninY - 1] == ' ')
    {
        boardA[RoninX][RoninY] = ' ';
        gotoxy(RoninY, RoninX);
        cout << " ";
        RoninY = RoninY - 1;
        boardA[RoninX][RoninY] = Ronin;
        gotoxy(RoninY, RoninX);
        cout << Ronin;
    }
}
//-----------------------------ronin Right move-----------------------------------------------------------------
void moveRonin_right()
{
	// Check if the cell one space to the right of Ronin is empty, indicating freefall
    if (boardA[RoninX + 1][RoninY] == ' ')
    {
        moveRonin_freefall();
    }
    // Check if there is a diamond to the right of Ronin
    if (boardA[RoninX][RoninY + 1] == dimond)
    {
        boardA[RoninX][RoninY + 1] = ' ';
        gotoxy(RoninY + 1, RoninX);
        cout << " ";
        dimond_count--;
    }
    // Check if there is a gravity changer to the right of Ronin
    if (boardA[RoninX][RoninY + 1] == gravity_ch)
    {
        gravity_off = true;
    }
    if (boardA[RoninX][RoninY + 1] == boost)
    {
        boosting_r();// Activate the boost function if Ronin moves onto a boost item
    }
    if (boardA[RoninX][RoninY + 1] == '.')
    {
     // Move Ronin to the right, updating the water movement
        boardA[RoninX][RoninY] = pre_item;
        gotoxy(RoninY, RoninX);
        cout << pre_item;
        RoninY = RoninY + 1;
        pre_item = boardA[RoninX][RoninY];
        gotoxy(RoninY, RoninX);
        cout << Ronin;
    }
    // Check if the cell to the right of Ronin is empty
    if (boardA[RoninX][RoninY + 1] == ' ')
    {
    	// Move Ronin to the right and update the game board
        boardA[RoninX][RoninY] = ' ';
        gotoxy(RoninY, RoninX);
        cout << " ";
        RoninY = RoninY + 1;
        boardA[RoninX][RoninY] = Ronin;
        gotoxy(RoninY, RoninX);
        cout << Ronin;
    }
}
//--------------------------------Ronin down-----------------------------------------------------------------------
void moveRonin_down()
{
// Check if the cell one space below Ronin contains a slap trigger ('*')
    if (boardA[RoninX + 1][RoninY] == '*')
    {
        moveRoninWith_slap();
    }
    // Check if the cell one space below Ronin contains a boost item
    if (boardA[RoninX + 1][RoninY] == boost)
    {
        boosting_r();// Activate the boost function if Ronin moves onto a boost item

    }

    if (boardA[RoninX + 2][RoninY] == ' ' && boardA[RoninX + 1][RoninY] == ' ')
    {
    	// Move Ronin downward by two cells and update the game board
        boardA[RoninX][RoninY] = ' ';
        gotoxy(RoninY, RoninX);
        cout << " ";
        RoninX = RoninX + 2;
        boardA[RoninX][RoninY] = Ronin;
        gotoxy(RoninY, RoninX);
        cout << Ronin;
    }
}
// ronin jumping---------------------------------------------------------
void moveRonin_up()
{
    // for jumping________________________________________________________________
    // SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    if (boardA[RoninX - 2][RoninY] == boosting)
    {
        boosting_r();// Activate the boost function if Ronin moves onto a boosting item
    }
    // Check if the cell two spaces above Ronin contains water ('.')
    if (boardA[RoninX - 2][RoninY] == '.')
    {
      // Move Ronin upwards, updating the water movement
        boardA[RoninX][RoninY] = pre_item;
        gotoxy(RoninY, RoninX);
        cout << pre_item;
        RoninX = RoninX - 2;
        pre_item = boardA[RoninX][RoninY];
        gotoxy(RoninY, RoninX);
        cout << Ronin;
    }
// Check if the cell two spaces above Ronin is empty and does not contain specific obstacles
    if (boardA[RoninX - 2][RoninY] == ' ' && boardA[RoninX - 1][RoninY] != '%' && boardA[RoninX - 1][RoninY] != '|')
    {
    	// Move Ronin upwards by two cells and update the game board
        boardA[RoninX][RoninY] = ' ';
        gotoxy(RoninY, RoninX);
        cout << " ";
        RoninX = RoninX - 2;
        boardA[RoninX][RoninY] = Ronin;
        gotoxy(RoninY, RoninX);
        cout << Ronin;
        Sleep(400);// Pause for a short duration (400 milliseconds)
        if (GetAsyncKeyState(VK_LEFT))
        { // for projectile motion______________________________________________________________-
            if (boardA[RoninX + 1][RoninY] == '*')
            {
                moveRoninWith_slap();
            }
            // Move Ronin to the left by three cells
            if (boardA[RoninX][RoninY - 3] == ' ')
            {
                boardA[RoninX][RoninY] = ' ';
                gotoxy(RoninY, RoninX);
                cout << " ";
                RoninY = RoninY - 3;
                boardA[RoninX][RoninY] = Ronin;
                gotoxy(RoninY, RoninX);
                cout << Ronin;
            }
        }
        if (GetAsyncKeyState(VK_RIGHT))
        {
        	// Check if the right arrow key is pressed for projectile motion
            if (boardA[RoninX + 1][RoninY] == '*')
            {
                moveRoninWith_slap();
            }
            if (boardA[RoninX][RoninY + 3] == ' ') // Move Ronin to the right by three cells
            {
                boardA[RoninX][RoninY] = ' ';
                gotoxy(RoninY, RoninX);
                cout << " ";
                RoninY = RoninY + 3;
                boardA[RoninX][RoninY] = Ronin;
                gotoxy(RoninY, RoninX);
                cout << Ronin;
            }
        }

        moveRonin_down();
        // end jumping_____________________________________________________________________________
    }
}
///-----------------------------------------------------------------------------------------------------------------------------------------
void moveRonin_freefall()
{
// Check if gravity is currently off
    if (gravity_off == false)
    {
        // moveRonin_down();
        if (boardA[RoninX + 1][RoninY] == '*')
        {
            moveRoninWith_slap();
        }
        // Check if the cell directly below Ronin contains water ('.'
        if (boardA[RoninX + 1][RoninY] == '.')
        {
            // water movement
            boardA[RoninX][RoninY] = pre_item;
            gotoxy(RoninY, RoninX);
            cout << pre_item;
            RoninX = RoninX + 1;
            pre_item = boardA[RoninX][RoninY];
            gotoxy(RoninY, RoninX);
            cout << Ronin;
        }
        // Check if the cell directly below Ronin contains a diamond
        if (boardA[RoninX + 1][RoninY] == dimond)
        {
        	// Remove the diamond, update count, and clear the previous position
            boardA[RoninX + 1][RoninY] = ' ';
            gotoxy(RoninY, RoninX + 1);
            cout << " ";
            dimond_count--;
        }
        // Check if the cell directly below Ronin is either empty or contains water ('.')
        else if ((boardA[RoninX + 1][RoninY] == ' ' && boardA[RoninX + 1][RoninY] != '*') || (boardA[RoninX + 1][RoninY] == '.'))
        {
            boardA[RoninX][RoninY] = ' ';
            gotoxy(RoninY, RoninX);
            cout << " ";
            RoninX = RoninX + 1;
            gotoxy(RoninY, RoninX);
            boardA[RoninX][RoninY] = Ronin;
            cout << Ronin;
            if (GetAsyncKeyState(VK_LEFT))
            {
            // Check if the cell to the left of Ronin is empty
                if (boardA[RoninX + 1][RoninY] == '*')
                {
                    moveRoninWith_slap();
                }
                if (boardA[RoninX][RoninY - 1] == ' ')
                {
                	 // Move Ronin to the left by one cell
                    boardA[RoninX][RoninY] = ' ';
                    gotoxy(RoninY, RoninX);
                    cout << " ";
                    RoninY = RoninY - 1;
                    boardA[RoninX][RoninY] = Ronin;
                    gotoxy(RoninY, RoninX);
                    cout << Ronin;
                }
            }
            // Check if the right arrow key is pressed for horizontal movement
            if (GetAsyncKeyState(VK_RIGHT))
            {
                if (boardA[RoninX + 1][RoninY] == '*')
                {
                	// Check if the cell to the right of Ronin is empty
                    moveRoninWith_slap();
                }
                if (boardA[RoninX][RoninY + 1] == ' ')
                {
                	// Move Ronin to the right by one cell
                    boardA[RoninX][RoninY] = ' ';
                    gotoxy(RoninY, RoninX);
                    cout << " ";
                    RoninY = RoninY + 1;
                    boardA[RoninX][RoninY] = Ronin;
                    gotoxy(RoninY, RoninX);
                    cout << Ronin;
                }
            }
        }
    }
}

// Function for simulating a jump when gravity is off

void gravity_jump()
{
    if (GetAsyncKeyState(VK_UP))
    {
    	// Check if the cell two spaces below Ronin is empty

        if (boardA[RoninX + 2][RoninY] == ' ')
        {
// Move Ronin upward by two cells and update the game board
            boardA[RoninX][RoninY] = ' ';
            gotoxy(RoninY, RoninX);
            cout << " ";
            RoninX = RoninX + 2;
            boardA[RoninX][RoninY] = Ronin;
            gotoxy(RoninY, RoninX);
            cout << Ronin;
        }
    }
}
// Function for incrementing the boosting counter
void boosting_r()
{
    boosting++;
}
void show_boost()
{

    gotoxy(65, 24);
    cout << "Booster:" << boosting;// Display the boosting count at a specific location on the screen
}

void gravity()
{
// Check if the up arrow key is pressed
    if (gravity_off == true)
    {
        if ((boardA[RoninX - 1][RoninY] == ' ' && boardA[RoninX - 1][RoninY] != '*' && boardA[RoninX - 1][RoninY] != '%') || (boardA[RoninX - 1][RoninY] == '.'))
        {
        	// Check if the cell two spaces below Ronin is empty
            boardA[RoninX][RoninY] = ' ';
            // Move Ronin upward by two cells and update the game board
            gotoxy(RoninY, RoninX);
            cout << " ";
            RoninX = RoninX - 1;
            gotoxy(RoninY, RoninX);
            boardA[RoninX][RoninY] = Ronin;
            cout << Ronin;

            if (GetAsyncKeyState(VK_LEFT))
            {

                if (boardA[RoninX][RoninY - 3] == ' ')
                {
                    boardA[RoninX][RoninY] = ' ';
                    gotoxy(RoninY, RoninX);
                    cout << " ";
                    RoninY = RoninY - 1;
                    boardA[RoninX][RoninY] = Ronin;
                    gotoxy(RoninY, RoninX);
                    cout << Ronin;
                }
            }
            if (GetAsyncKeyState(VK_RIGHT))
            {

                if (boardA[RoninX][RoninY + 3] == ' ')
                {
                    boardA[RoninX][RoninY] = ' ';
                    gotoxy(RoninY, RoninX);
                    cout << " ";
                    RoninY = RoninY + 3;
                    boardA[RoninX][RoninY] = Ronin;
                    gotoxy(RoninY, RoninX);
                    cout << Ronin;
                }
            }
        }
    }
}
void moveRoninWith_slap()
{

    if (boardA[RoninX + 1][RoninY] == '*')
     // If the condition is true (the value at the position to the right is '*'):

     //   ?? Clear the current position on the board
    {

        boardA[RoninX][RoninY] = ' ';
        // 2. Move the cursor to the current position and output a space to clear it on the screen
        gotoxy(RoninY, RoninX);
        cout << " ";
       // Update the Ronin's position one row up
        RoninX = RoninX - 1;
        //set the new position on the board to the ronin chrachter
        boardA[RoninX][RoninY] = Ronin;
        //move the cursor to the new position and output the ronin charachter
        gotoxy(RoninY, RoninX);
        cout << Ronin;
    }
}
void slapSelf_move()
{
    if (turn == 0)
    {
        slapSelf_down();
    }
    if (turn == 1)
    {
        slapSelf_up();
    }
}
bool slapSelf_down()
{
	//check if moving down would reach yhe bottom of the board
    if (slapX + 1 == 15)
    {
        turn = 1;
        //change the turn
    }
    else
    {
    	//clear the current row on board
        for (int i = 16; i < 23; i++)
        {

            boardA[slapX][i] = ' ';
            gotoxy(i, slapX);
            cout << " ";
        }
        //move down by increenting the index row
        slapX = slapX + 1;
        //update the new row on the board with"*"
        for (int i = 16; i < 23; i++)
        {

            boardA[slapX][i] = '*';
            gotoxy(i, slapX);
            cout << "*";
        }
    }
    return true;
}

bool slapSelf_up()
{
	//checking if the board is finished horizontally
    if (slapX - 5 == 0)
    
    {
        turn = 0; //change the turn
    }

    else
    {
        for (int j = 16; j < 23; j++) //change the current row on board
        {

            boardA[slapX][j] = ' ';
            gotoxy(j, slapX);
            cout << " ";
        }

        // move up by decrementing the row index(slapX)
        slapX = slapX - 1;
        //update the new row on the board with"*"
        for (int i = 16; i < 23; i++)
        {

            boardA[slapX][i] = '*';
            gotoxy(i, slapX);
            cout << "*";
        }
    }
    return true;
}
//__________________end 1__________________________________________________________________________________
bool slap1Self_move()
{
    bool result; 
    if (turn_2 == 0)
    {
        result = slap1Self_move_Up();
    }
    if (turn_2 == 1)
    {
        result = slap1Self_move_down();
    }
    return result;
}
bool slap1Self_move_down()
{
	//checking if moving down wouls reach the bottom of the board
    if (slap1X == 15)
    {
        turn_2 = 0; // change the turn
    }
    else
    {
    	//clear the current row on the board
        for (int i = 73; i < 80; i++)
        {
            boardA[slap1X][i] = ' ';
            gotoxy(i, slap1X);
            cout << " ";
        }
        slap1X = slap1X + 1; //move down by incrementing the row index(slap1X)
        for (int i = 73; i < 80; i++)
        {
            boardA[slap1X][i] = '*';  //update  the new row on the board with "*" 
            gotoxy(i, slap1X);
            cout << "*";
        }
    }
    return true; //return true to indicate the movement was successful
}
bool slap1Self_move_Up()
{
    if (slap1X - 10 == 0) //check if moving up wouls reach the top of board
    {
        turn_2 = 1; //change the turn
    }

    else
    {
        for (int i = 73; i < 80; i++)
        {
            boardA[slap1X][i] = ' '; //for clearing the row on the board
            gotoxy(i, slap1X);
            cout << " ";
        }
        slap1X = slap1X - 1; //moving up by decrementing the row index
        for (int i = 73; i < 80; i++)
        {  //update the new row on the board with star
            boardA[slap1X][i] = '*';
            gotoxy(i, slap1X);
            cout << "*";
        }
    }
    return true; //to indicate movment was successful
}

//-----------------------------------------------------------------------------
void slap2Self_move()
{

    if (turn_3 == 0)
    {
        slap2Self_move_Up();
    }
    if (turn_3 == 1)
    {
        slap2Self_move_down();
    }
}
bool slap2Self_move_down()
{
    if (slap2X == 16)
    {
        turn_3 = 0;
    }
    else
    {
        for (int i = 117; i < 125; i++)
        {
            boardA[slap2X][i] = ' '; //to erase the charachter from current position
            gotoxy(i, slap2X);
            cout << " ";
        }
        slap2X = slap2X + 1; //move the object by incrementing its position
        for (int i = 117; i < 125; i++) //draw the charachter to its new postion
        {
            boardA[slap2X][i] = '*';
            gotoxy(i, slap2X);
            cout << "*";
        }
    }
    return true;
}
bool slap2Self_move_Up()
{
    if (slap2X - 4 == 0) //checking if it is the  top of the board  
    {
        turn_3 = 1;
    }

    else
    {
        for (int i = 117; i < 125; i++)
        {
            boardA[slap2X][i] = ' ';  //clear the row
            gotoxy(i, slap2X);
            cout << " ";
        }
        slap2X = slap2X - 1; // move the charachter up by one row
        for (int i = 117; i < 125; i++)
        {
            boardA[slap2X][i] = '*'; //update the board
            gotoxy(i, slap2X);
            cout << "*";
        }
    }
    return true;
}

//------------------end slap movements-----------------------------------------------------------
void lives_count()
{
    lives--;
}
void lives_show()
{   //display the reamining lives on console
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    gotoxy(30, 24); //move the cursor to the specified position
    cout << "Lives Remaining:" << lives; //display the remaining lives
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3); //set the console text colour black
}
bool lives_detect()
{    // check if there is a collision in any of the adjecent poition to the ronin
    if (boardA[RoninX + 1][RoninY] == pintch || boardA[RoninX][RoninY + 1] == pintch || boardA[RoninX][RoninY - 1] == pintch || boardA[RoninX - 1][RoninY] == pintch)
    {
        return false; //if collision detected
    }
    return true;
}
void resetRonin() //reset the charachter on the game board
{
     //clear the current position of chaarchter on the board
    boardA[RoninX][RoninY] = ' ';
    gotoxy(RoninY, RoninX);
    cout << " ";
    //set new position
    RoninX = 9;
    RoninY = 58;
    //update the board with new postion
    boardA[RoninX][RoninY] = Ronin;
    gotoxy(RoninY, RoninX);
    cout << Ronin;
}
bool gun_fire()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    if (true)  //always remain true
    {
        if (boardA[gunX + 1][gunY] == Ronin) //check if there is charachter in the next cell
        {

            cin.get();
            return false;  //if bullet hit the charachter 
        }
        if (boardA[gunX + 1][gunY] == ' ') //check if the next cell is empty or not
        {
            boardA[gunX][gunY] = ' '; //clear the current position
            gotoxy(gunY, gunX);
            cout << " ";
           //move the bullet down one row
            gunX = gunX + 1;
            boardA[gunX][gunY] = bullet; //display the bullet in new position
            gotoxy(gunY, gunX);
            cout << bullet;
        }
        if (boardA[gunX + 1][gunY] == '%') //check if there is no space for the bullet to move
        {
            boardA[gunX][gunY] = ' ';

            gotoxy(gunY, gunX);
            cout << " ";
            //reset the gun position to the specified location
            gunX = 2;
            gunY = 46;
            boardA[gunX][gunY] = bullet; //display the bullet in new postion
            gotoxy(gunY, gunX);
            cout << bullet;
        }
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
    return true; //indicating that firing process is completed
}
void remaining_dimond()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4); //for text colour
    gotoxy(5, 24);  //diplay remaining diamond count at specific position
    cout << "Remaining dimond:" << dimond_count;
    gotoxy(5, 25);
    cout << "Collected Dimond:" << 6 - dimond_count;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
}
bool machine_gun()
{

    bool ans = false;
    if (change_d == 0)
    {
        ans = machine_up(); //calls the function in anwer
    }
    if (change_d == 1)
    {
        ans = machine_down();
    }
    return ans;
}
bool machine_up()
{
    if (machineX_1 == 16)  //check if machine has reached the top row
    {
        change_d = 1;
    }

    for (int i = 4; i < 10; i++)
    { //clears the previous positions of machineX-1
        boardA[machineX_1][i] = ' ';
        gotoxy(i, machineX_1);
        cout << " ";
        if (boardA[machineX_1 - 1][i] == Ronin) //check if there is charachter above the machine
        {
            return false;
        }
    }
    for (int i = 4; i < 10; i++)
    { //clear the previous positions of machine X_2
        boardA[machineX_2][i] = ' ';
        gotoxy(i, machineX_2);
        cout << " ";
    } //move both machines up by 1
    machineX_1 = machineX_1 - 1;
    machineX_2 = machineX_2 - 1;
    for (int i = 4; i < 10; i++)
    {
        if (boardA[machineX_1 - 1][i] == Ronin) //heck if there is charachter above machineX_1
        {
            return false;
        }
        boardA[machineX_1][i] = '|'; //draw the new positions of machineX_2 with "/"
        gotoxy(i, machineX_1);
        cout << "|";
    }
    for (int i = 4; i < 10; i++)
    {
        if (boardA[machineX_1 - 1][i] == Ronin) //check if there is charachter above machine 
        {
            return false;
        }
        boardA[machineX_2][i] = '/';
        gotoxy(i, machineX_2);
        cout << "/";
    }
    return true;
}
//-----------------------------machine gun moving up and down---------------------------------------------------------------------------
bool machine_down()
{
    // machine gun going down
    if (machineX_2 == 20) //check if machine has reached the specific position
    {
        change_d = 0;
    }

    for (int i = 4; i < 10; i++)
    {
        if (boardA[machineX_1 + 1][i] == Ronin) //check if there is charachter at the position below the machineX_1
        {
            return false;
        }
        boardA[machineX_1][i] = ' ';
        gotoxy(i, machineX_1);
        cout << " ";
    }
    for (int i = 4; i < 10; i++)
    {
        if (boardA[machineX_1 + 1][i] == Ronin) //check if there is charachter at the position below the machineX_2
        {
            return false;
        }
        boardA[machineX_2][i] = ' ';
        gotoxy(i, machineX_2);
        cout << " ";
    } //move both machine down by one
    machineX_1 = machineX_1 + 1;
    machineX_2 = machineX_2 + 1;
    for (int i = 4; i < 10; i++)
    {
        if (boardA[machineX_1 + 1][i] == Ronin) //check if there is charachter at the position below the machineX_2
        {
            return false;
        }
        boardA[machineX_1][i] = '|';
        gotoxy(i, machineX_1);
        cout << "|";
    }
    for (int i = 4; i < 10; i++)
    {
        if (boardA[machineX_1 + 1][i] == Ronin)
        {
            return false;
        }
        boardA[machineX_2][i] = '/'; //draw new position of machine 2 with "/"
        gotoxy(i, machineX_2);
        cout << "/";
    }
    return true;
}
//---------------------------------------------------------------------------------------------------------------------
//-------------------------machine firing-----------------------------------------------------------------
bool machine_fire()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    //check if thre is charachter in the path of bullet
    if (boardA[m_bullet_x][m_bullet_y + 3] == Ronin || boardA[m_bullet_x][m_bullet_y + 2] == Ronin || boardA[m_bullet_x][m_bullet_y + 1] == Ronin)
    {
        return false; //return false if it hits the charachter
    }
    if (boardA[m_bullet_x][m_bullet_y + 3] == ' ')   //??check if the space ahaed the bullet is empty
    {
        boardA[m_bullet_x][m_bullet_y] = ' '; //clear the previous position of the bullet
        gotoxy(m_bullet_y, m_bullet_x);
        cout << " ";

        m_bullet_y = m_bullet_y + 3; //move the bullet position to the right
        boardA[m_bullet_x][m_bullet_y] = machine_bullet; //draw the bullet to its new position
        gotoxy(m_bullet_y, m_bullet_x);
        cout << machine_bullet;
    }
    //check if the bullet hit certain objects
    if (boardA[m_bullet_x][m_bullet_y + 3] == '%' || boardA[m_bullet_x][m_bullet_y + 3] == dimond || boardA[m_bullet_x][m_bullet_y + 1] == '%' || boardA[m_bullet_x][m_bullet_y + 1] == dimond || boardA[m_bullet_x][m_bullet_y + 3] == '%' || boardA[m_bullet_x][m_bullet_y + 2] == dimond || boardA[m_bullet_x][m_bullet_y + 2] == pintch || boardA[m_bullet_x][m_bullet_y + 3] == pintch || boardA[m_bullet_x][m_bullet_y + 1] == pintch)
    {
        boardA[m_bullet_x][m_bullet_y] = ' '; //clear the previous path of the bullet

        gotoxy(m_bullet_y, m_bullet_x);
        cout << " ";
        m_bullet_x = machineX_1; //reset the bullet to the initial postion
        m_bullet_y = 10;
    }

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    return true;
}
bool machine_fire2()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
 //check if there is charahter in the path of bullet
    if (boardA[m_bullet_x][m2_bullet_y + 3] == Ronin || boardA[m_bullet_x][m2_bullet_y + 2] == Ronin || boardA[m_bullet_x][m2_bullet_y + 1] == Ronin)
    {
        return false;
    }
    if (boardA[m2_bullet_x][m2_bullet_y + 3] == ' ') //check if there is space ahead of the bullet
    {
        boardA[m2_bullet_x][m2_bullet_y] = ' '; //clear the previous bullet postion
        gotoxy(m2_bullet_y, m2_bullet_x);
        cout << " ";

        m2_bullet_y = m2_bullet_y + 3;  //move the bullet position to the right
        boardA[m2_bullet_x][m2_bullet_y] = machine_bullet; //draw the bullet to its new position
        gotoxy(m2_bullet_y, m2_bullet_x);
        cout << machine_bullet;
    }
    //check if the bullet hit something other than empty space
    if (boardA[m2_bullet_x][m2_bullet_y + 3] != ' ' || boardA[m2_bullet_x][m2_bullet_y + 2] != ' ' || boardA[m2_bullet_x][m2_bullet_y + 1] != ' ')
    {
        boardA[m2_bullet_x][m2_bullet_y] = ' '; //clear the previous position of bullet

        gotoxy(m2_bullet_y, m2_bullet_x);
        cout << " ";
        m2_bullet_x = machineX_1;
        m2_bullet_y = 10; //reset the bullet to the inital position
    }

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    return true;
}
//--------------------------------------------------------------------------------------------------------------------------------
///----------------------------Random generator----------------------------------------------------------------
int ghostDirection()
{
    srand(time(0));
    int result = 1 + (rand() % 4);
    return result;
}

bool ghostMovementRand()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    int value = ghostDirection();

    if (value == 1) //genrate a random direcrion for ghost
    {
        // move left in random movement
        if (boardA[ghostX][ghostY - 1] != '*' && boardA[ghostX][ghostY - 1] != '%')
        {
            if (boardA[ghostX][ghostY - 1] == ' ' || boardA[ghostX][ghostY - 1] == '.' || boardA[ghostX][ghostY - 1] == Ronin)
            {
                boardA[ghostX][ghostY] = previousItemR;
                gotoxy(ghostY, ghostX);
                cout << previousItemR;
                ghostY = ghostY - 1; //move the ghost to the left
                previousItemR = boardA[ghostX][ghostY];
                if (previousItemR == Ronin) //check if ghost collide with charachter
                { 
                    previousItemR = ' ';
                    resetRonin();

                    return false;
                }
                boardA[ghostX][ghostY] = 'R'; //draw ghost at new position
                gotoxy(ghostY, ghostX);
                cout << "R";
            }
        }
        return true;
    }
    if (value == 2)
    {
        // move right in random movement
        if (boardA[ghostX][ghostY + 1] != '*' && boardA[ghostX][ghostY + 1] != '*')
        {
            if (boardA[ghostX][ghostY + 1] == ' ' || boardA[ghostX][ghostY + 1] == '.' || boardA[ghostX][ghostY + 1] == Ronin)
            {
                boardA[ghostX][ghostY] = previousItemR; //clear the previous position of ghost
                gotoxy(ghostY, ghostX);
                cout << previousItemR;
                ghostY = ghostY + 1; //move ghost to right
                previousItemR = boardA[ghostX][ghostY];
                if (previousItemR == Ronin) //check if ghost collided with charachter
                {
                    previousItemR = ' ';
                    resetRonin();
                    return false;
                }
                boardA[ghostX][ghostY] = 'R';  //draw ghost at new position
                gotoxy(ghostY, ghostX);
                cout << "R";
            }
        }
        return true;
    }
    if (value == 3)
    {
        // move up in random movements
        if (boardA[ghostX - 1][ghostY] != '*' || boardA[ghostX - 1][ghostY] != '%')
        {
            if (boardA[ghostX - 1][ghostY] == ' ' || boardA[ghostX - 1][ghostY] == '.' || boardA[ghostX - 1][ghostY] == Ronin)
            {

                boardA[ghostX][ghostY] = previousItemR; //clear the previous position of ghost
                gotoxy(ghostY, ghostX);
                cout << previousItemR; 
                ghostX = ghostX - 1; //move ghost up
                previousItemR = boardA[ghostX][ghostY];
                if (previousItemR == Ronin)
                {
                    previousItemR = ' ';

                    return false;
                }
                boardA[ghostX][ghostY] = 'R'; //draw ghost at new position
                gotoxy(ghostY, ghostX);
                cout << "R";
            }
        }
        return true;
    }
    if (value == 4)
    {
        // move down in random movement
        if (boardA[ghostX + 1][ghostY] != '*' && boardA[ghostX + 1][ghostY] != '%')
        {
            if ((boardA[ghostX + 1][ghostY] == ' ' || boardA[ghostX + 1][ghostY] == ' ' || boardA[ghostX + 1][ghostY] == '.') && boardA[ghostX + 1][ghostY] != '*')
            {
                boardA[ghostX][ghostY] = previousItemR; //clear the previous position of ghost
                gotoxy(ghostY, ghostX);
                cout << previousItemR;
                ghostX = ghostX + 1;//move ghost down
                previousItemR = boardA[ghostX][ghostY];
                if (previousItemR == Ronin)  //check if ghost collided with charachter
                {
                    previousItemR = ' ';

                    return false;
                }
                boardA[ghostX][ghostY] = 'R'; //draw ghost at new position
                gotoxy(ghostY, ghostX);
                cout << "R";
            }
        }
        return true;
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
}
//-----------------------------------------------------------------------------------------------------
//***********************************************************************************************************************************************
bool ghost_chase()

{

    bool ans = fire_down();

    return ans;
}

bool fire_down()
{
    if (boardA[ghostX_2 + 1][ghostY_2] == Ronin) //check if the cell below conatin charachter
    {

        return false;
    }
    if (boardA[ghostX_2 + 1][ghostY_2] == ' ') //check if the cell below conatin empty
    {
        boardA[ghostX_2][ghostY_2] = ' '; //clear current position of ghost
        gotoxy(ghostY_2, ghostX_2);
        cout << " ";

        ghostX_2 = ghostX_2 + 1; //move ghost down
        boardA[ghostX_2][ghostY_2] = bullet; //place the bullet in the new position of the ghost
        gotoxy(ghostY_2, ghostX_2);
        cout << bullet;
    }
    else if (boardA[ghostX_2 + 1][ghostY_2] != ' ')
    {
        boardA[ghostX_2][ghostY_2] = ' '; //clear current position of ghost

        gotoxy(ghostY_2, ghostX_2);
        cout << " ";
        ghostX_2 = ghostX + 1;
        ghostY_2 = ghostY;
        boardA[ghostX_2][ghostY_2] = bullet; //place the bullet in the new position of the ghost
        gotoxy(ghostY_2, ghostX_2);
        cout << bullet;
    }
    return true;
}

void store()
{
    fstream file;
    string row;
    file.open("Frame_cont.tX_1t", ios::out);

    for (int i = 0; i < 23; i++)
    {

        for (int j = 0; j < 140; j++)
        {

            row = row + boardA[i][j];
        }
        file << row << endl;
        row = " ";
    }
}
