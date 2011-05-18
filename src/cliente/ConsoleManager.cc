#include <errno.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <sys/select.h>

#include <ConsoleManager.h>
#include <system/System.h>

ConsoleManager::ConsoleManager (ConsoleListener& listener)
	: input_size (4),
	  log_size (8),
	  listener (listener)
{
	//trace (TRACE_MAXIMUM);

	/* XXX: estupido curses, gracias por simular SA_RESTART... */
	int nonblock = 1;
	System::check (ioctl (fileno (stdin), FIONBIO, &nonblock));
	sigemptyset (&mask);

	/* Inicializacion de curses. */
	initscr ();
	cbreak ();
	noecho ();

	/* 0          0,COLS
	 * +----------+
	 * |          |
	 * |----------| log_size (Overlapping window)
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

	logging = NULL;
}

ConsoleManager::~ConsoleManager ()
{
	if (logging)
		delwin (logging);

	delwin (msg);
	delwin (input);
	endwin ();
}

int ConsoleManager::next_char (WINDOW *w)
{
	/* XXX: ... magia con pselect para devolver EINTR :´( */
	int err;
	fd_set fds;
	int ifd = fileno (stdin);

	FD_ZERO (&fds);
	FD_SET (ifd, &fds);

	/* TODO: sigmask...
	 * http://www.linuxprogrammingblog.com/code-examples/using-pselect-to-avoid-a-signal-race
	 * */
	do {
		if (FD_ISSET (ifd, &fds)) {
			err = wgetch (w);
			if (err != ERR || errno != EAGAIN)
				return err;
		}

		FD_ZERO (&fds);
		FD_SET (ifd, &fds);

		err = pselect (ifd +1, &fds, NULL, NULL, NULL, &mask);

		if (err == -1)
			if (errno == EINTR)
				return ERR;
			else throw SystemErrorException ();
	} while (true);
}

enum ConsoleManager::cause ConsoleManager::run ()
{
	enum ConsoleManager::cause status = ERROR;
	bool running = true;
	int c;
	bool escaped = false;

	while (running) {
		c = next_char (input);
		if (c == ERR) {
		        if (errno == EINTR)
				status = ConsoleManager::INTERRUPTED;
			else
				status = ConsoleManager::ERROR;
			break;
		}

		//wprintw (msg, "key: %s (%d)\n", keyname(c), c);
		wnoutrefresh (msg);

		if (escaped) {
			if (c == 'q') {
				status = ConsoleManager::EXIT_REQUESTED;
				break;
			}
			if (c != 27)
				/* c==27 esta cubierto debajo. */
				escaped = false;
		}
		if (c == 27)
			escaped = !escaped;
		else if (isprint (c)) {
			input_buffer.push_back (c);
			waddch (input, c);
		} else if (c == KEY_BACKSPACE) {
			if (input_buffer.size () > 0)
				input_buffer.pop_back ();
			waddch (input, '\b');
			wdelch (input);
		} else if (c == KEY_ENTER || c == '\n') {
			std::string text (input_buffer.begin(), input_buffer.end());

			listener.onInputLine (text);

			input_buffer.clear ();
			werase (input);
		}

		wnoutrefresh (input);
		doupdate ();
	}
	return status;
}

void ConsoleManager::append (const std::string& msg)
{
	waddstr (this->msg, msg.c_str ());
	this->refresh ();
}

void ConsoleManager::refresh ()
{
	wnoutrefresh (msg);
	if (logging)
		wnoutrefresh (logging);
	wnoutrefresh (input);
	doupdate ();
}

WINDOW *ConsoleManager::getLoggingWindow ()
{
	if (!logging) {
		wresize (msg, LINES - input_size - log_size, COLS);
		mvwin (msg, log_size, 0);
		logging = newwin (log_size, COLS, 0, 0);
		scrollok (logging, TRUE);
		scrollok (msg, TRUE);
	}
	return logging;
}
