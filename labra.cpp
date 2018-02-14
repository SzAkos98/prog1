#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <unistd.h>
#include <sys/ioctl.h>


int 
main (void)
{

	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	int xj = 0, xk = 0, yj = 0, yk=0;
	int mx = w.ws_col*2 , my = w.ws_row*2;

	WINDOW *win;
	win = initser ();
	noecho ();
	cbreak ();
	nodelay (win , true);

	for (;;)
	{
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
		mx = w.ws_col*2;
		my = w.ws_row*2;
		xj = (xj - 1) % mx;
		xk = (xk + 1) % mx;
		yj = (yj - 1) % mx;
		yk = (yk + 1) % mx;
		clear ();

		for (int i=0; i<w.ws_col;i++)
			{
			mvprintw(0, i, "-");
			}
		for (int i=0; i<w.ws_row; i++)
			{
			mvprintw(w.ws_row-1, i, "-");
			}
		mvprintw(abs ((yj + (my - yk)) /2),abs ((xj + (mx-xk)) /2), "O");
		
		refresh();
		usleep(150000);
	}
	return 0;
}
