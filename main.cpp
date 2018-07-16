#include <iostream>
#include <conio.h>
#include <stdio.h>
#define _WIN32_WINNT 0x05232
#include <windows.h>
#include <process.h>
#include <cwchar>

#include "menu_creator.cpp"

#define size 50

using namespace std;

int blinker[1][3] = {1,1,1};

int glider[3][3] = {{0,1,0},
                    {0,0,1},
                    {1,1,1}};

int small_exploder[4][3] = {{0,1,0},
                            {1,1,1},
                            {1,0,1},
                            {0,1,0}};

int exploder[5][5] = {  {1,0,1,0,1},
                        {1,0,0,0,1},
                        {1,0,0,0,1},
                        {1,0,0,0,1},
                        {1,0,1,0,1}};

int ten_cell_row[1][10] = {1,1,1,1,1,1,1,1,1,1};

int lightweight_spacecraft[4][5] = {{0,1,1,1,1},
                                    {1,0,0,0,1},
                                    {0,0,0,0,1},
                                    {1,0,0,1,0}};

int tumbler[6][7] = {   {0,1,1,0,1,1,0},
                        {0,1,1,0,1,1,0},
                        {0,0,1,0,1,0,0},
                        {1,0,1,0,1,0,1},
                        {1,0,1,0,1,0,1},
                        {1,1,0,0,0,1,1}};

int gosper_glider_gun[11][38] = {   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
                                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
                                    {0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0},
                                    {0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0},
                                    {0,1,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                    {0,1,1,0,0,0,0,0,0,0,0,1,0,0,0,1,0,1,1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
                                    {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
                                    {0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                    {0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};


void MaximizeOutputWindow(void)
{
    HWND consoleWindow = GetConsoleWindow(); // This gets the value Windows uses to identify your output window
    ShowWindow(consoleWindow, SW_MAXIMIZE); // this mimics clicking on its' maximize button
}

void RestoreOutputWindow(void)
{
    HWND consoleWindow = GetConsoleWindow(); // Same as above
    ShowWindow(consoleWindow, SW_RESTORE); // this mimics clicking on its' maximize for a second time, which puts it back to normal
}

bool isValid(int r, int c)
{
    if(r<0||c<0||r==size||c==size)
        return false;
    else
        return true;
}

/*void makeValid(int r, int c)
{
    if(r<0)
        r=size-1;
    if(c<0)
        c=size-1;
    if(r==size)
        r=0;
    if(c==size)
        c=0;
}*/

int findNeighbours(int B[size][size], int r, int c)
{
    int n=0;
    int i=r, j=c;

    if(isValid(--i, --j))
        n+=B[i][j];

    if(isValid(++i, j))
        n+=B[i][j];

    if(isValid(++i, j))
        n+=B[i][j];

    if(isValid(i, ++j))
        n+=B[i][j];

    if(isValid(i, ++j))
        n+=B[i][j];

    if(isValid(--i, j))
        n+=B[i][j];

    if(isValid(--i, j))
        n+=B[i][j];

    if(isValid(i, --j))
        n+=B[i][j];

    return n;
}

void genGap(int B1[size][size])
{
    int n;
    int B2[size][size]={0};

    for(int i=0; i<size; i++)
    {
        for(int j=0; j<size; j++)
        {
            /*if(!isValid(i, j))
                makeValid(i, j);*/

            n=findNeighbours(B1, i, j);

            if(B1[i][j]==1)
            {
                if(n<2)
                    B2[i][j]=0;

                else if(n==2 || n==3)
                    B2[i][j]=1;

                else if(n>3)
                    B2[i][j]=0;
            }

            else if(B1[i][j]==0)
            {
                if(n==3)
                    B2[i][j]=1;
            }
        }
    }

    for(int i=0; i<size; i++)
    {
        for(int j=0; j<size; j++)
            B1[i][j]=B2[i][j];
    }
}

void printB(int B[size][size])
{
    for(int i=0; i<size; i++)
    {
        for(int j=0; j<size; j++)
        {
            if(B[i][j]==0)
                putchar(32);//cout<<" ";

            else if(B[i][j]==1)
                putchar(254);//cout<<(char)254;//cout<<"*";

            putchar(32);//cout<<" ";
        }
        putchar(10);//cout<<endl;
    }
}

void printB_boaders(int B[size][size])
{
    cout<<(char)201;

    for(int i=0; i<size*2; i++)
        cout<<(char)205;

    cout<<(char)187<<endl;

    for(int i=0; i<size; i++)
    {
        cout<<(char)186;
        for(int j=0; j<size; j++)
        {
            if(B[i][j]==0)
                cout<<" ";

            else if(B[i][j]==1)
                cout<<(char)254;
                //cout<<"*";

            cout<<" ";
        }
        cout<<(char)186<<endl;
    }

    cout<<(char)200;

    for(int i=0; i<size*2; i++)
        cout<<(char)205;

    cout<<(char)188;
}

void simulate(int B[size][size])
{
    int gen = 0;

    system("cls");

    while(1)
    {
        gotoxy(0,0);

        printB(B);
        genGap(B);

        //_getch();

        gen++;

        if(GetKeyState(VK_ESCAPE) & 0x8000)
            break;
    }
}

void deploy_blinker(int B[size][size], int x, int y)
{
    for(int i=0, y1=y; i<1; i++, y1++)
    {
        for(int j=0, x1=x; j<3; j++, x1++)
        {
            B[y1][x1]=blinker[i][j];
        }
    }
}


void deploy_glider(int B[size][size], int x, int y)
{
    for(int i=0, y1=y; i<3; i++, y1++)
    {
        for(int j=0, x1=x; j<3; j++, x1++)
        {
            B[y1][x1]=glider[i][j];
        }
    }
}

void deploy_small_exploder(int B[size][size], int x, int y)
{
    for(int i=0, y1=y; i<4; i++, y1++)
    {
        for(int j=0, x1=x; j<3; j++, x1++)
        {
            B[y1][x1]=small_exploder[i][j];
        }
    }
}

void deploy_exploder(int B[size][size], int x, int y)
{
    for(int i=0, y1=y; i<5; i++, y1++)
    {
        for(int j=0, x1=x; j<5; j++, x1++)
        {
            B[y1][x1]=exploder[i][j];
        }
    }
}

void deploy_ten_cell_row(int B[size][size], int x, int y)
{
    for(int i=0, y1=y; i<1; i++, y1++)
    {
        for(int j=0, x1=x; j<10; j++, x1++)
        {
            B[y1][x1]=ten_cell_row[i][j];
        }
    }
}

void deploy_lightweight_spacecraft(int B[size][size], int x, int y)
{
    for(int i=0, y1=y; i<4; i++, y1++)
    {
        for(int j=0, x1=x; j<5; j++, x1++)
        {
            B[y1][x1]=lightweight_spacecraft[i][j];
        }
    }
}

void deploy_tumbler(int B[size][size], int x, int y)
{
    for(int i=0, y1=y; i<6; i++, y1++)
    {
        for(int j=0, x1=x; j<7; j++, x1++)
        {
            B[y1][x1]=tumbler[i][j];
        }
    }
}

void deploy_gosper_glider_gun(int B[size][size], int x, int y)
{
    for(int i=0, y1=y; i<11; i++, y1++)
    {
        for(int j=0, x1=x; j<38; j++, x1++)
        {
            B[y1][x1]=gosper_glider_gun[i][j];
        }
    }
}

/*void getBoard_menu(int B[size][size])
{
    int x, y;

    cout<<"Predefined Patterns Menu";

    position str;
	str.x=0;
	str.y=2;

    char menu_items[260][260] = {"Glider", "Small Exploder", "Exploder", "10 Cell Row",
                                "Light Weight Spacecraft", "Tumbler", "Gosper Glider Gun", "Exit"};
    int no_items=8;
    int menu_id;

    menu_id=menu(str, menu_items, no_items);
    cout<<endl;

    switch(menu_id)
    {
    case 0:
        {
            cout<<"Pattern of a Glider:"<<endl<<endl;
            for(int i=0; i<3; i++)
            {
                cout<<" ";
                for(int j=0; j<3; j++)
                {
                    if(glider[i][j]==0)
                        cout<<" ";

                    else if(glider[i][j]==1)
                        cout<<(char)254;

                    cout<<" ";
                }
                cout<<endl;
            }

            cout<<endl<<endl;

            cout<<"Enter a position to deploy Glider"<<endl;
            cout<<"x = ";
            cin>>x;
            cout<<"y = ";
            cin>>y;

            deploy_glider(B, x, y);

            break;
        }

    case 1:
        {
            cout<<"Pattern of a Small Exploder:"<<endl<<endl;
            for(int i=0; i<4; i++)
            {
                cout<<" ";
                for(int j=0; j<3; j++)
                {
                    if(small_exploder[i][j]==0)
                        cout<<" ";

                    else if(small_exploder[i][j]==1)
                        cout<<(char)254;

                    cout<<" ";
                }
                cout<<endl;
            }

            cout<<endl<<endl;

            cout<<"Enter a position to deploy Small Exploder"<<endl;
            cout<<"x = ";
            cin>>x;
            cout<<"y = ";
            cin>>y;

            deploy_small_exploder(B, x, y);

            break;
        }

    case 2:
        {
            cout<<"Pattern of a Exploder:"<<endl<<endl;
            for(int i=0; i<5; i++)
            {
                cout<<" ";
                for(int j=0; j<5; j++)
                {
                    if(exploder[i][j]==0)
                        cout<<" ";

                    else if(exploder[i][j]==1)
                        cout<<(char)254;

                    cout<<" ";
                }
                cout<<endl;
            }

            cout<<endl<<endl;

            cout<<"Enter a position to deploy Exploder"<<endl;
            cout<<"x = ";
            cin>>x;
            cout<<"y = ";
            cin>>y;

            deploy_exploder(B, x, y);

            break;
        }

    case 3:
        {
            cout<<"Pattern of a 10 Cell Row:"<<endl<<endl;
            for(int i=0; i<1; i++)
            {
                cout<<" ";
                for(int j=0; j<10; j++)
                {
                    if(ten_cell_row[i][j]==0)
                        cout<<" ";

                    else if(ten_cell_row[i][j]==1)
                        cout<<(char)254;

                    cout<<" ";
                }
                cout<<endl;
            }

            cout<<endl<<endl;

            cout<<"Enter a position to deploy 10 Cell Row"<<endl;
            cout<<"x = ";
            cin>>x;
            cout<<"y = ";
            cin>>y;

            deploy_ten_cell_row(B, x, y);

            break;
        }

    case 4:
        {
            cout<<"Pattern of a Lightweight Spacecraft:"<<endl<<endl;
            for(int i=0; i<4; i++)
            {
                cout<<" ";
                for(int j=0; j<5; j++)
                {
                    if(lightweight_spacecraft[i][j]==0)
                        cout<<" ";

                    else if(lightweight_spacecraft[i][j]==1)
                        cout<<(char)254;

                    cout<<" ";
                }
                cout<<endl;
            }

            cout<<endl<<endl;

            cout<<"Enter a position to deploy Lightweight Spacecraft"<<endl;
            cout<<"x = ";
            cin>>x;
            cout<<"y = ";
            cin>>y;

            deploy_lightweight_spacecraft(B, x, y);

            break;
        }

    case 5:
        {
            cout<<"Pattern of a Tumbler:"<<endl<<endl;
            for(int i=0; i<6; i++)
            {
                cout<<" ";
                for(int j=0; j<7; j++)
                {
                    if(tumbler[i][j]==0)
                        cout<<" ";

                    else if(tumbler[i][j]==1)
                        cout<<(char)254;

                    cout<<" ";
                }
                cout<<endl;
            }

            cout<<endl<<endl;

            cout<<"Enter a position to deploy Tumbler"<<endl;
            cout<<"x = ";
            cin>>x;
            cout<<"y = ";
            cin>>y;

            deploy_tumbler(B, x, y);

            break;
        }

    case 6:
        {
            cout<<"Pattern of a Gosper Glider Gun:"<<endl<<endl;
            for(int i=0; i<11; i++)
            {
                cout<<" ";
                for(int j=0; j<38; j++)
                {
                    if(gosper_glider_gun[i][j]==0)
                        cout<<" ";

                    else if(gosper_glider_gun[i][j]==1)
                        cout<<(char)254;

                    cout<<" ";
                }
                cout<<endl;
            }

            cout<<endl<<endl;

            cout<<"Enter a position to deploy Gosper Glider Gun"<<endl;
            cout<<"x = ";
            cin>>x;
            cout<<"y = ";
            cin>>y;

            deploy_gosper_glider_gun(B, x, y);

            break;
        }

    case 7:
        {
            exit(0);
        }
    }

    cout<<endl<<"Please Note: This is an infinitely looped simulator. Press ESC to stop the simulation"<<endl;
    cout<<"Press any key to start simulating...";
    _getch();
}*/

void pattern_menu(int B[size][size], int x, int y)
{
    gotoxy(110,0);  cout<<"Predefined Patterns Menu";

    position str;
	str.x=110;
	str.y=2;

    char menu_items[260][260] = {"Blinker","Glider", "Small Exploder", "Exploder", "10 Cell Row",
                                "Light Weight Spacecraft", "Tumbler", "Gosper Glider Gun", "Exit"};
    int no_items=9;
    int menu_id;

    menu_id=menu(str, menu_items, no_items);

    int y1=12;
    int x1=110;
    gotoxy(x1, y1);

    switch(menu_id)
    {
    case 0:
        {
            cout<<"Pattern of a Blinker:";
            y1+=2;
            gotoxy(x1, y1);

            for(int i=0; i<1; i++)
            {
                cout<<" ";
                for(int j=0; j<3; j++)
                {
                    if(blinker[i][j]==0)
                        cout<<" ";

                    else if(blinker[i][j]==1)
                        cout<<(char)254;

                    cout<<" ";
                }
                y1++;
                gotoxy(x1, y1);
            }

            y1+=2;
            gotoxy(x1, y1);
            cout<<"Press RETURN to deploy and ESC to cancel...";

            system("pause>nul");

            y1+=2;
            gotoxy(x1, y1);

            if(GetAsyncKeyState(VK_RETURN) & 0x8000)
            {
                deploy_blinker(B, x, y);
                cout<<"Deploying Successful";
            }


            if(GetAsyncKeyState(VK_ESCAPE) & 0x8000)
            {
                gotoxy(x1, y1++);
                cout<<"Deploying was canceled";
            }

            y1++;
            gotoxy(x1, y1);
            cout<<"Press any key to continue...";

            break;
        }

    case 1:
        {
            cout<<"Pattern of a Glider:";
            y1+=2;
            gotoxy(x1, y1);

            for(int i=0; i<3; i++)
            {
                cout<<" ";
                for(int j=0; j<3; j++)
                {
                    if(glider[i][j]==0)
                        cout<<" ";

                    else if(glider[i][j]==1)
                        cout<<(char)254;

                    cout<<" ";
                }
                y1++;
                gotoxy(x1, y1);
            }

            y1+=2;
            gotoxy(x1, y1);
            cout<<"Press RETURN to deploy and ESC to cancel...";

            system("pause>nul");

            y1+=2;
            gotoxy(x1, y1);

            if(GetAsyncKeyState(VK_RETURN) & 0x8000)
            {
                deploy_glider(B, x, y);
                cout<<"Deploying Successful";
            }


            if(GetAsyncKeyState(VK_ESCAPE) & 0x8000)
            {
                gotoxy(x1, y1++);
                cout<<"Deploying was canceled";
            }

            y1++;
            gotoxy(x1, y1);
            cout<<"Press any key to continue...";

            break;
        }

    case 2:
        {
            cout<<"Pattern of a Small Exploder:";
            y1+=2;
            gotoxy(x1, y1);

            for(int i=0; i<4; i++)
            {
                cout<<" ";
                for(int j=0; j<3; j++)
                {
                    if(small_exploder[i][j]==0)
                        cout<<" ";

                    else if(small_exploder[i][j]==1)
                        cout<<(char)254;

                    cout<<" ";
                }
                y1++;
                gotoxy(x1, y1);
            }

            y1+=2;
            gotoxy(x1, y1);
            cout<<"Press RETURN to deploy and ESC to cancel...";

            system("pause>nul");

            y1+=2;
            gotoxy(x1, y1);

            if(GetAsyncKeyState(VK_RETURN) & 0x8000)
            {
                deploy_small_exploder(B, x, y);
                cout<<"Deploying Successful";
            }


            if(GetAsyncKeyState(VK_ESCAPE) & 0x8000)
            {
                gotoxy(x1, y1++);
                cout<<"Deploying was canceled";
            }

            y1++;
            gotoxy(x1, y1);
            cout<<"Press any key to continue...";

            break;
        }

    case 3:
        {
            cout<<"Pattern of a Exploder:";
            y1+=2;
            gotoxy(x1, y1);

            for(int i=0; i<5; i++)
            {
                cout<<" ";
                for(int j=0; j<5; j++)
                {
                    if(exploder[i][j]==0)
                        cout<<" ";

                    else if(exploder[i][j]==1)
                        cout<<(char)254;

                    cout<<" ";
                }
                y1++;
                gotoxy(x1, y1);
            }

            y1+=2;
            gotoxy(x1, y1);
            cout<<"Press RETURN to deploy and ESC to cancel...";

            system("pause>nul");

            y1+=2;
            gotoxy(x1, y1);

            if(GetAsyncKeyState(VK_RETURN) & 0x8000)
            {
                deploy_exploder(B, x, y);
                cout<<"Deploying Successful";
            }


            if(GetAsyncKeyState(VK_ESCAPE) & 0x8000)
            {
                gotoxy(x1, y1++);
                cout<<"Deploying was canceled";
            }

            y1++;
            gotoxy(x1, y1);
            cout<<"Press any key to continue...";

            break;
        }

    case 4:
        {
            cout<<"Pattern of a 10 Cell Row:";
            y1+=2;
            gotoxy(x1, y1);

            for(int i=0; i<1; i++)
            {
                cout<<" ";
                for(int j=0; j<10; j++)
                {
                    if(ten_cell_row[i][j]==0)
                        cout<<" ";

                    else if(ten_cell_row[i][j]==1)
                        cout<<(char)254;

                    cout<<" ";
                }
                y1++;
                gotoxy(x1, y1);
            }

            y1+=2;
            gotoxy(x1, y1);
            cout<<"Press RETURN to deploy and ESC to cancel...";

            system("pause>nul");

            y1+=2;
            gotoxy(x1, y1);

            if(GetAsyncKeyState(VK_RETURN) & 0x8000)
            {
                deploy_ten_cell_row(B, x, y);
                cout<<"Deploying Successful";
            }


            if(GetAsyncKeyState(VK_ESCAPE) & 0x8000)
            {
                gotoxy(x1, y1++);
                cout<<"Deploying was canceled";
            }

            y1++;
            gotoxy(x1, y1);
            cout<<"Press any key to continue...";

            break;
        }

    case 5:
        {
            cout<<"Pattern of a Lightweight Spacecraft:";
            y1+=2;
            gotoxy(x1, y1);

            for(int i=0; i<4; i++)
            {
                cout<<" ";
                for(int j=0; j<5; j++)
                {
                    if(lightweight_spacecraft[i][j]==0)
                        cout<<" ";

                    else if(lightweight_spacecraft[i][j]==1)
                        cout<<(char)254;

                    cout<<" ";
                }
                y1++;
                gotoxy(x1, y1);
            }

            y1+=2;
            gotoxy(x1, y1);
            cout<<"Press RETURN to deploy and ESC to cancel...";

            system("pause>nul");

            y1+=2;
            gotoxy(x1, y1);

            if(GetAsyncKeyState(VK_RETURN) & 0x8000)
            {
                deploy_lightweight_spacecraft(B, x, y);
                cout<<"Deploying Successful";
            }


            if(GetAsyncKeyState(VK_ESCAPE) & 0x8000)
            {
                gotoxy(x1, y1++);
                cout<<"Deploying was canceled";
            }

            y1++;
            gotoxy(x1, y1);
            cout<<"Press any key to continue...";

            break;
        }

    case 6:
        {
            cout<<"Pattern of a Tumbler:"<<endl<<endl;
            y1+=2;
            gotoxy(x1, y1);

            for(int i=0; i<6; i++)
            {
                cout<<" ";
                for(int j=0; j<7; j++)
                {
                    if(tumbler[i][j]==0)
                        cout<<" ";

                    else if(tumbler[i][j]==1)
                        cout<<(char)254;

                    cout<<" ";
                }
                y1++;
                gotoxy(x1, y1);
            }

            y1+=2;
            gotoxy(x1, y1);
            cout<<"Press RETURN to deploy and ESC to cancel...";

            system("pause>nul");

            y1+=2;
            gotoxy(x1, y1);

            if(GetAsyncKeyState(VK_RETURN) & 0x8000)
            {
                deploy_tumbler(B, x, y);
                cout<<"Deploying Successful";
            }


            if(GetAsyncKeyState(VK_ESCAPE) & 0x8000)
            {
                gotoxy(x1, y1++);
                cout<<"Deploying was canceled";
            }

            y1++;
            gotoxy(x1, y1);
            cout<<"Press any key to continue...";

            break;
        }

    case 7:
        {
            cout<<"Pattern of a Gosper Glider Gun:"<<endl<<endl;
            y1+=2;
            gotoxy(x1, y1);

            for(int i=0; i<11; i++)
            {
                cout<<" ";
                for(int j=0; j<38; j++)
                {
                    if(gosper_glider_gun[i][j]==0)
                        cout<<" ";

                    else if(gosper_glider_gun[i][j]==1)
                        cout<<(char)254;

                    cout<<" ";
                }
                y1++;
                gotoxy(x1, y1);
            }

            y1+=2;
            gotoxy(x1, y1);
            cout<<"Press RETURN to deploy and ESC to cancel...";

            system("pause>nul");

            y1+=2;
            gotoxy(x1, y1);

            if(GetAsyncKeyState(VK_RETURN) & 0x8000)
            {
                deploy_gosper_glider_gun(B, x, y);
                cout<<"Deploying Successful";
            }


            if(GetAsyncKeyState(VK_ESCAPE) & 0x8000)
            {
                gotoxy(x1, y1++);
                cout<<"Deploying was canceled";
            }

            y1++;
            gotoxy(x1, y1);
            cout<<"Press any key to continue...";

            break;
        }

    case 8:
        {
            gotoxy(x1, y1);
            cout<<"Press any key to continue...";

            break;
        }
    }

    _getch();

}

void art2();
void help()
{
    system("cls");

    art2();
    cout<<endl<<endl;

    cout<<(char)218<<"MAIN MENU"; for(int i=0; i<99 ;i++)cout<<(char)196; cout<<(char)191<<endl;
    cout<<(char)179<<"As soon as you enter \"Start Program\" option, you will be presented with an empty board in the editing mode. "<<(char)179<<endl;
    cout<<(char)179<<"\"Help and Keyboard Shortcuts\" have brought you here.                                                        "<<(char)179<<endl;
    cout<<(char)179<<"\"Exit\" will stop the program and return 0(zero) to the operating system.                                    "<<(char)179<<endl;
    cout<<(char)179<<"In other words, it will successfully terminate the program.                                                 "<<(char)179<<endl;
    cout<<(char)192; for(int i=0; i<108 ;i++)cout<<(char)196; cout<<(char)217;
    cout<<endl<<endl;

    cout<<(char)218<<"EDITING MODE"; for(int i=0; i<102 ;i++)cout<<(char)196; cout<<(char)191<<endl;
    cout<<(char)179<<"In this mode you can insert or delete Lifes and also create patterns in the board.                                "<<(char)179<<endl;
    cout<<(char)179<<"Use your Arrow keys(UP, DOWN, LEFT, RIGHT) to move the pointer over the board.                                    "<<(char)179<<endl;
    cout<<(char)179<<"                                                                                                                  "<<(char)179<<endl;
    cout<<(char)179<<"The following shortcut keys may be useful:                                                                        "<<(char)179<<endl;
    cout<<(char)179<<"INSERT : Insert a Life in the point where the pointer is currently pointing.                                      "<<(char)179<<endl;
    cout<<(char)179<<"DELETE : Delete the Life in the point where the pointer is currently pointing.                                    "<<(char)179<<endl;
    cout<<(char)179<<"D      : Delete all the lifes present in the board.                                                               "<<(char)179<<endl;
    cout<<(char)179<<"M      : Open a Predefined Pattern Menu to insert a pattern in the point where the pointer is currently pointing. "<<(char)179<<endl;
    cout<<(char)179<<"RETURN : Exit Editing mode and automatically start the Simulation Mode with the defined Life(s) on the board.     "<<(char)179<<endl;
    cout<<(char)179<<"HOME   : Remove all data in the board and return to the main menu.                                                "<<(char)179<<endl;
    cout<<(char)179<<"F1     : Open this Help                                                                                           "<<(char)179<<endl;
    cout<<(char)192; for(int i=0; i<114 ;i++)cout<<(char)196; cout<<(char)217;
    cout<<endl<<endl;

    cout<<(char)218<<"PREDEFINED PATTERN MENU"; for(int i=0; i<86 ;i++)cout<<(char)196; cout<<(char)191<<endl;
    cout<<(char)179<<"Whenever Predefined Pattern Menu is triggered, your current location in the board will be highlighted.       "<<(char)179<<endl;
    cout<<(char)179<<"When Predefined Pattern Menu is opened in the Editing Mode, you would find a short menu over the right side. "<<(char)179<<endl;
    cout<<(char)179<<"Use your Arrow keys(UP, DOWN) to move the pointer and naviagate through the scroll over menu.                "<<(char)179<<endl;
    cout<<(char)179<<"Press RETURN to select the corresponding pattern.                                                            "<<(char)179<<endl;
    cout<<(char)179<<"To confirm press RETURN, or to cancel press ESC.                                                             "<<(char)179<<endl;
    cout<<(char)192; for(int i=0; i<109 ;i++)cout<<(char)196; cout<<(char)217;
    cout<<endl<<endl;

    cout<<(char)218<<"SIMULATION MODE"; for(int i=0; i<106 ;i++)cout<<(char)196; cout<<(char)191<<endl;
    cout<<(char)179<<"When Simulation Mode is triggered, the simulation with the defined life(s) would start automatically                     "<<(char)179<<endl;
    cout<<(char)179<<"Press ECS to stop the simulation and return to the Editing Mode with the same state at which the simulation was stopped. "<<(char)179<<endl;
    cout<<(char)179<<"(Press and hold or continuously press ECS key to stop when single press doesn't work)                                    "<<(char)179<<endl;
    cout<<(char)192; for(int i=0; i<121 ;i++)cout<<(char)196; cout<<(char)217;
    cout<<endl<<endl;

    cout<<(char)218<<"CREDITS"; for(int i=0; i<12 ;i++)cout<<(char)196; cout<<(char)191<<endl;
    cout<<(char)179<<"Kinjal Raykarmakar "<<(char)179<<endl;
    cout<<(char)179<<"Code::Blocks       "<<(char)179<<endl;
    cout<<(char)179<<"My PC              "<<(char)179<<endl;
    cout<<(char)192; for(int i=0; i<19 ;i++)cout<<(char)196; cout<<(char)217;

    cout<<endl<<endl<<"Press any key to return...";

    gotoxy(0,0);
    _getch();
}

int getBoard_manual(int B[size][size])
{
    int i=0, j=0, x=1, y=1;

    printB_boaders(B);

    while(1)
    {
        loop:
        gotoxy(x, y);

        system("pause>nul");

        if(GetAsyncKeyState(VK_RETURN) & 0x8000)
            break;

        if(GetAsyncKeyState(VK_RIGHT) & 0x8000)
        {
            j++;
            if(j==size)
            {
                j--;
                goto loop;
            }

            x+=2;
            gotoxy(x,y);
        }

        if(GetAsyncKeyState(VK_LEFT) & 0x8000)
        {
            j--;
            if(j<0)
            {
                j++;
                goto loop;
            }

            x-=2;
            gotoxy(x,y);
        }

        if(GetAsyncKeyState(VK_DOWN) & 0x8000)
        {
            i++;
            if(i==size)
            {
                i--;
                goto loop;
            }

            y++;
            gotoxy(x,y);
        }

        if(GetAsyncKeyState(VK_UP) & 0x8000)
        {
            i--;
            if(i<0)
            {
                i++;
                goto loop;
            }

            y--;
            gotoxy(x,y);
        }

        if(GetAsyncKeyState(VK_INSERT) & 0x8000)
        {
            B[i][j]=1;
            system("cls");
            printB_boaders(B);
        }

        if(GetAsyncKeyState(VK_DELETE) & 0x8000)
        {
            B[i][j]=0;
            system("cls");
            printB_boaders(B);
        }


        if(GetAsyncKeyState(0x44) & 0x8000) //  D
        {
            for(int i=0; i<size; i++)
            {
                for(int j=0; j<size; j++)
                    B[i][j]=0;
            }
            system("cls");
            printB_boaders(B);
        }

        if(GetAsyncKeyState(0x4D) & 0x8000) //  M
        {
            cout<<(char)176;

            pattern_menu(B, j, i);

            //system("pause>nul");
            system("cls");
            printB_boaders(B);

            i=0;
            j=0;
            x=1;
            y=1;
        }

        if(GetAsyncKeyState(VK_F1) & 0x8000)
        {
            help();

            system("cls");
            printB_boaders(B);

            i=0;
            j=0;
            x=1;
            y=1;
        }

        if(GetAsyncKeyState(VK_HOME) & 0x8000)
            return 1;
    }

    return 0;
}

void art1()
{
    cout<<"   ______   ______   .__   __. ____    __    ____  ___   ____    ____  __     _______.      "<<endl;
    cout<<"  /      | /  __  \\  |  \\ |  | \\   \\  /  \\  /   / /   \\  \\   \\  /   / (_ )   /       |      "<<endl;
    cout<<" |  ,----'|  |  |  | |   \\|  |  \\   \\/    \\/   / /  ^  \\  \\   \\/   /   |/   |   (----`      "<<endl;
    cout<<" |  |     |  |  |  | |  . `  |   \\            / /  /_\\  \\  \\_    _/          \\   \\          "<<endl;
    cout<<" |  `----.|  `--'  | |  |\\   |    \\    /\\    / /  _____  \\   |  |        .----)   |         "<<endl;
    cout<<"  \\______| \\______/  |__| \\__|     \\__/  \\__/ /__/     \\__\\  |__|        |_______/          "<<endl;
    cout<<"   _______      ___      .___  ___.  _______                                                "<<endl;
    cout<<"  /  _____|    /   \\     |   \\/   | |   ____|                                               "<<endl;
    cout<<" |  |  __     /  ^  \\    |  \\  /  | |  |__                                                  "<<endl;
    cout<<" |  | |_ |   /  /_\\  \\   |  |\\/|  | |   __|                                                 "<<endl;
    cout<<" |  |__| |  /  _____  \\  |  |  |  | |  |____                                                "<<endl;
    cout<<"  \\______| /__/     \\__\\ |__|  |__| |_______|                                               "<<endl;
    cout<<"   ______    _______        __       __   _______  _______                                  "<<endl;
    cout<<"  /  __  \\  |   ____|      |  |     |  | |   ____||   ____|                                 "<<endl;
    cout<<" |  |  |  | |  |__         |  |     |  | |  |__   |  |__                                    "<<endl;
    cout<<" |  |  |  | |   __|        |  |     |  | |   __|  |   __|                                   "<<endl;
    cout<<" |  `--'  | |  |           |  `----.|  | |  |     |  |____                                  "<<endl;
    cout<<"  \\______/  |__|           |_______||__| |__|     |_______|                                 "<<endl;
}

void art2()
{
    cout<<"      ___           ______      __    __   __    ______  __  ___                           "<<endl;
    cout<<"     /   \\         /  __  \\    |  |  |  | |  |  /      ||  |/  /                           "<<endl;
    cout<<"    /  ^  \\       |  |  |  |   |  |  |  | |  | |  ,----'|  '  /                            "<<endl;
    cout<<"   /  /_\\  \\      |  |  |  |   |  |  |  | |  | |  |     |    <                             "<<endl;
    cout<<"  /  _____  \\     |  `--'  '--.|  `--'  | |  | |  `----.|  .  \\                            "<<endl;
    cout<<" /__/     \\__\\     \\_____\\_____\\\\______/  |__|  \\______||__|\\__\\                           "<<endl;
    cout<<"   ______   ____    ____  _______ .______     ____    ____  __   ___________    __    ____ "<<endl;
    cout<<"  /  __  \\  \\   \\  /   / |   ____||   _  \\    \\   \\  /   / |  | |   ____\\   \\  /  \\  /   / "<<endl;
    cout<<" |  |  |  |  \\   \\/   /  |  |__   |  |_)  |    \\   \\/   /  |  | |  |__   \\   \\/    \\/   /  "<<endl;
    cout<<" |  |  |  |   \\      /   |   __|  |      /      \\      /   |  | |   __|   \\            /   "<<endl;
    cout<<" |  `--'  |    \\    /    |  |____ |  |\\  \\----.  \\    /    |  | |  |____   \\    /\\    /    "<<endl;
    cout<<"  \\______/      \\__/     |_______|| _| `._____|   \\__/     |__| |_______|   \\__/  \\__/     "<<endl;

}

int main()
{
    MaximizeOutputWindow();
    START1:

    system("cls");

    int x, y;
    int ret;

    art1();

    int B[size][size]={0};

    position str;
	str.x=0;
	str.y=20;

    char menu_items[260][260] = {"Start Program", "Help and Keyboard Shortcuts", "Exit"};
    int no_items=3;
    int menu_id;

    while(1)
    {
        system("cls");

        art1();
        menu_id=menu(str, menu_items, no_items);

        switch(menu_id)
        {
        case 0:
            {
                START2:

                system("cls");

                ret=getBoard_manual(B);

                if(ret==0)
                    simulate(B);

                else if(ret==1)
                    goto START1;

                goto START2;
            }

        case 1:
            {

                help();
                break;
            }

        case 2:
            {
                exit(0);
            }
        }
    }

   	return 0;
}
