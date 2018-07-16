#include <iostream>
#include <conio.h>
#include <stdio.h>
#include<string>
#include <windows.h>

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

struct position	//	structure of position, used for specifying the cursor position
{
	int x,y;
};

void gotoxy(position pos)
{
	CursorPosition.X = pos.x; // Locates column
	CursorPosition.Y = pos.y; // Locates Row
	SetConsoleCursorPosition(console,CursorPosition); // Sets position for next thing to be printed
}

void gotoxy(int x, int y)
{
    CursorPosition.X = x; // Locates column
	CursorPosition.Y = y; // Locates Row
	SetConsoleCursorPosition(console,CursorPosition); // Sets position for next thing to be printed
}

int menu(position str_pos, char menu_items[260][260], int no_items, int gap=0)	//	the actual function(call this...)
{
	int ac_gap=gap+1;	//	actual gap provides the next line

	position m;	//	used in printing the menu
	gotoxy(str_pos);	//	sets cursor to the starting point
	m=str_pos;

	for(int i=0; i<no_items; i++)	//	loop to print the menu items
	{
		cout<<"   ";	//	initial space for the menu handler " ->"(3 spaced)
		cout<<menu_items[i];	//	printing array of strings

		for(int i=0; i<ac_gap; i++)	//	loop to print newline for the appropriate gaps
			cout<<endl;

		m.y+=ac_gap;
		gotoxy(m);
	}

	gotoxy(str_pos);
	cout<<"->";	//	printing the menu handler

	position ctr, ret;	//	the control and return position respectively
						/*	the control position holds the instantaneous cursor position and,
							the return position hold the fixed position where the cursor is moved
							while returning from the function
						*/

	ctr=str_pos;
	int menu_id=0;	/*	this menu id hold the value of the menu item selected. This is returned too
						the first items has a menu id: 0(zero)
					*/

	while(1)	//	seems to be an infinite loop(for infinite scrolling within the menu)
	{
		/*	setting the position of return variable and the cursor is moved	*/
		ret.x=str_pos.x+2;
		ret.y=str_pos.y+((no_items-1)*ac_gap)+2;
		gotoxy(ret);

		system("pause>nul"); //	the >nul bit causes it the print no message

		/* GetAsyncKeyState determines whether a key is up or down at the time the
		function is called, and whether the key was pressed after a previous call to GetAsyncKeyState.  */

		if(GetAsyncKeyState(VK_DOWN)) //	down button pressed
		{
			if(menu_id>=0 && menu_id<(no_items-1))	//	checking legal menu id
			{
				gotoxy(ctr);
				cout<<"  ";	//	printing space on the previous location of the menu handler
				ctr.y+=ac_gap;	//	new location for the menu handler
				gotoxy(ctr);
				cout<<"->";	//	printing the menu handler in the new location
				menu_id++;	//menu id changed
			}

		}

		else if(GetAsyncKeyState(VK_UP)) //	up button pressed
		{
			if(menu_id>0 && menu_id<no_items)	//	checking legal menu id
			{
				gotoxy(ctr);
				cout<<"  ";	//	printing space on the previous location of the menu handler
				ctr.y-=ac_gap;	//	new location for the menu handler
				gotoxy(ctr);
				cout<<"->";	//	printing the menu handler in the new location
				menu_id--;	//menu id changed
			}
		}

		else if(GetAsyncKeyState(VK_RETURN))	//	return(ENTER) button pressed
			return menu_id;
	}
}

/*	NOTE: x and y postion elements are based on the coordinate system
		It looks like as if the whole program is in the 4th quadrant
		(0,0)	x(1)	x(2)	x(3)	.	.	.
		y(1)
		y(2)
		y(3)
		.
		.
		.
	*/


//	SAMPLE MAIN function
/*int main()
{
	position str;
	str.x=0;
	str.y=3;

	char menu_items[260][260]={"Apples","Bananas","Grapes","Guava","Potato","Tomato","Ginger"};
	int no_items=8;
	int menu_id;
	int gap=1;

	char temp[100];
	cout<<"Enter: ";
	//cin>>temp;
    cin.getline(temp, sizeof(temp));

	strcpy(menu_items[7], temp);

	menu_id=menu(str, menu_items, no_items, gap);

	cout<<"You entered menu_id: "<<menu_id;

	return 0;
}*/

