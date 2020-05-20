#include <stdio.h>
#include <ncurses.h>
#include <signal.h>
#include <stdlib.h>
WINDOW * chatmenu;

void titleMenu(WINDOW * menuwin) {	
	wattron(menuwin, A_BOLD);
	wattron(menuwin, COLOR_PAIR(1));
	mvwprintw(menuwin, 0, 0, "      DEAD");
	wattroff(menuwin, COLOR_PAIR(1));
	wattroff(menuwin, A_BOLD);
}

void borderMenu(WINDOW * chatmenu, int yMax, int xMax) {
	refresh();	
	chatmenu = newwin(LINES, COLS, yMax-yMax, xMax-xMax);
	if(!has_colors()) {exit(0);}
	start_color();
	init_pair(1, COLOR_RED, COLOR_BLACK);
	wattron(chatmenu, COLOR_PAIR(1));
	//mvwprintw(chatmenu, 0, 0, "chat");	
	box(chatmenu, '*', '*');
	wattroff(chatmenu, COLOR_PAIR(1));
	wrefresh(chatmenu);
}

static volatile sig_atomic_t signal_ = 0;

static void sig_handler(int sig)
{
  if (SIGWINCH == sig) {
	signal_ = true;
  }
} // sig_handler



int main() {

	initscr(); //stdscr
	noecho();
	cbreak();

	int yMax, xMax;
	getmaxyx(stdscr, yMax, xMax);
	
	WINDOW * menuwin = newwin(5, 15, (yMax/2.5), (xMax/2.15) );
	wrefresh(menuwin);
	keypad(menuwin, true);
	
	borderMenu(chatmenu, yMax, xMax);		
	titleMenu(menuwin);	

	char* options[3] = {"Start Chatting", "Enter Username", "Exit         "};
	
	int choice;
	int highlight = 0;
	

	while(1) {
		

		wtimeout(menuwin, 100); // 0.1 seconds
		
 		choice = wgetch(menuwin);
		if(signal(SIGWINCH, sig_handler) == SIG_ERR) 
			printw("signal error");
	

				
  		if (signal_) {
			endwin();
			refresh();
			clear();
			getmaxyx(stdscr, yMax, xMax);
			menuwin = newwin(5, 15, (yMax/2.5), (xMax/2.15));
			titleMenu(menuwin);
			keypad(menuwin, true);
			borderMenu(chatmenu, yMax, xMax);
			
		}
		
		
	
		for(int i = 0; i < 3; i++) {
			if(i == highlight)
			wattron(menuwin, A_REVERSE);
			mvwprintw(menuwin, i+2, 1, options[i]);
			wattroff(menuwin, A_REVERSE);
		}
	//choice = wgetch(menuwin);

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
		
		if(choice == 10 && highlight == 0) {
			choice = false;
			
		}
		if(choice == 10 && highlight == 1) {
			printw("1");

		}
		if(choice == 10 && highlight == 2) {
			printw("2");

		}
	}



	
	wrefresh(menuwin);
	endwin();
	return 0;

}
