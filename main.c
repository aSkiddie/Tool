#include <stdio.h>
#include <ncurses.h>

int main() {

	initscr(); //stdscr
	noecho();
	cbreak();


	int yMax, xMax;
	getmaxyx(stdscr, yMax, xMax);
	
	WINDOW * menuwin = newwin(5, xMax-64, yMax-32, 5);
//	box(menuwin, 0, 'x');
	//refresh();
	wrefresh(menuwin);
	keypad(menuwin, true);
	
	start_color();
	init_pair(1, COLOR_WHITE, 0);
	attron(COLOR_PAIR(1));
	mvwprintw(menuwin, 0, (xMax-18)/2, "     DEAD");	
	wattroff(menuwin, COLOR_PAIR(1));
	refresh();

	char* options[3] = {"Start Chatting", "Enter Username", "\t   Exit     "};
	
	int choice;
	int highlight = 0;
	

	while(1) {
		for(int i = 0; i < 3; i++) {
			if(i == highlight)
				wattron(menuwin, A_REVERSE);
			mvwprintw(menuwin, i+2, (xMax-18)/2, options[i]);
			wattroff(menuwin, A_REVERSE);
		}
		choice = wgetch(menuwin);

		switch (choice)
		{
			case KEY_UP:
				highlight--;
				if(highlight == -1)
					highlight = 0;
				break;
			case KEY_DOWN:
				highlight++;
				if(highlight == 3)
					highlight = 2;
				break;
			default:
				break;
		}

		if(choice == 10)
			break;
	}



	getch();

	endwin();
	return 0;

}
