namespace linus {
	namespace utils {
		inline void hideConsole() {
			HWND consoleWindow = GetConsoleWindow();
			ShowWindow(consoleWindow, SW_HIDE);
		}
	}
}