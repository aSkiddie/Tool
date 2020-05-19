#include <stdio.h>
#include <ncurses.h>
#include <signal.h>

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

	printw("Coumns: %d, Lines: %d\n", COLS, LINES);
	int yMax, xMax;
	getmaxyx(stdscr, yMax, xMax);
	printw("%d xMax, %d yMax", xMax, yMax);	
	WINDOW * menuwin = newwin(5, 15, (yMax/2.5), (xMax/2.15) );
//	box(menuwin, 0, 'x');
	//refresh();
	wrefresh(menuwin);
	keypad(menuwin, true);
	
	start_color();
	init_pair(1, COLOR_WHITE, 0);
	attron(COLOR_PAIR(1));
	mvwprintw(menuwin, 0, 0, "      DEAD");	
	wattroff(menuwin, COLOR_PAIR(1));
	refresh();

	char* options[3] = {"Start Chatting", "Enter Username", "Exit        "};
	
	int choice;
	int highlight = 0;
	

	while(1) {
		wtimeout(menuwin, 100); // 0.1 seconds
		
 		choice = wgetch(menuwin);
		if(signal(SIGWINCH, sig_handler) == SIG_ERR) 
			printw("signal error");
	

				
  		if (signal_) {
    		/* do redrawing */
			endwin();
			refresh();
			clear();
			getmaxyx(stdscr, yMax, xMax);
			menuwin = newwin(5, 15, (yMax/2.5), (xMax/2.15));
			mvwprintw(menuwin, 0, 0, "     DEAD");
			keypad(menuwin, true);
	
			
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
		
		if(choice == 10)
			break;
	}



	wrefresh(menuwin);
	endwin();
	return 0;

}
