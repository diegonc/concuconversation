#include <string>
#include <vector>

#include <curses.h>

#include <Cliente.h>

Cliente::Cliente () : input_size (4)
{
	/* Inicializacion de curses. */
	initscr ();
	cbreak ();
	noecho ();

	/* 0          0,COLS
	 * +----------+
	 * |          |
	 * |          |
	 * |          |
	 * |          |
	 * +----------+ LINES - input_size
	 * |          |
	 * |          |
	 * +----------+
	 *            LINES,COLS
	 */
	msg = newwin (LINES - input_size, COLS, 0, 0);
	scrollok (msg, TRUE);

	input = newwin (input_size, COLS, LINES - input_size, 0);
	keypad (input, TRUE);
}

Cliente::~Cliente ()
{
	delwin (msg);
	delwin (input);
	endwin ();
}


void Cliente::run ()
{
	bool running = true;
	int c;
	bool escaped = false;

	while (running) {
		c = wgetch (input);

		wprintw (msg, "key: %s (%d)\n", keyname (c), c);
		
		if (escaped) {
			if (c == 'q')
				break;
			escaped = false;
		} if (isprint (c)) {
			input_buffer.push_back (c);
			waddch (input, c);
		} else if (c == KEY_BACKSPACE) {
			if (input_buffer.size () > 0)
				input_buffer.pop_back ();
			waddch (input, '\b');
			wdelch (input);
		} else if (c == KEY_ENTER || c == '\n') {
			input_buffer.push_back ('\n');

			std::string text (input_buffer.begin(), input_buffer.end());
			waddstr (msg, text.c_str ());
			input_buffer.clear ();
			werase (input);
		} else if (c == 27)
			escaped = true;

		wnoutrefresh (msg);
		wnoutrefresh (input);
		doupdate ();
	}
}


