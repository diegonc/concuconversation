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

std::string Cliente::readstring()
{
	bool escaped = false;
	int c;
	std::vector<char> chars;

	while ((c = wgetch (input)) != ERR) {
		if (escaped) {
			if (c == 'q')
				throw "aborted";
			escaped = false;
		} if (isprint(c)) {
			chars.push_back(c);
			waddch (input, c);
		} else if (c == KEY_BACKSPACE) {
			wprintw (msg, "KBS ");
			if (chars.size() > 0)
				chars.pop_back ();
			waddch (input, '\b');
			wdelch (input);
		} else if (c == KEY_ENTER || c == '\n') {
			break;
		} else if (c == 27)
			escaped = true;

		wprintw (msg, "key: %s (%d)\n", keyname (c), c);
		wrefresh (msg);
		wrefresh (input);
	}

	werase (input);
	wnoutrefresh (input);

	return std::string (chars.begin(), chars.end());
}

void Cliente::run ()
{
	bool running = true;
	int c;

	wattron (msg, A_REVERSE);
	while (running) {
		std::string text = readstring ();

		waddstr (msg, text.c_str ());
		waddch (msg, '\n');
		wrefresh (msg);
	}
	
}


