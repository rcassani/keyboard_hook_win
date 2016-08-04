// keyboard_hook.cpp
// 
// Installs a Low Level Keyboard Hook WH_KEYBOARD_LL
// The values shown are UINT8 Virtual-Key Codes
// https://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx
// Raymundo Cassani
// 2016


#include <iostream>
#include <Windows.h>
#pragma comment(lib, "user32.lib")

// HHOOK variable
HHOOK hHook{ NULL };

// Event Handler (callback funtion), it is called in response to a change in the state of a key
// https://msdn.microsoft.com/en-us/library/ms644985(v=vs.85).aspx

LRESULT CALLBACK CatchLowLevelKeyboardProc(const int nCode, const WPARAM wParam, const LPARAM lParam)
{
	// lParam is cast as KBDLLHOOKSTRUCT
	KBDLLHOOKSTRUCT keyInfo = *((KBDLLHOOKSTRUCT*)lParam);

	// wParam is the The identifier of the keyboard message. 
	// This parameter can be one of the following messages: WM_KEYDOWN, WM_KEYUP, WM_SYSKEYDOWN, or WM_SYSKEYUP. 
	switch (wParam)
	{
	case WM_KEYDOWN:
		printf("KeyDown event, Key = %d = %c \r\n ", keyInfo.vkCode, keyInfo.vkCode);
		break;
	}
	// Passes the hook information to the next hook procedure. So other hooks can work
	return CallNextHookEx(hHook, nCode, wParam, lParam);
}

int main(void)
{
	printf("Installing the hook\r\n");
	hHook = SetWindowsHookEx(WH_KEYBOARD_LL, CatchLowLevelKeyboardProc, NULL, 0);
	if (hHook != NULL) 
	{
		printf("Hook installed successfully\r\n");
	}
	else
	{
		printf("Error installing hook\r\n");
	}

	while (GetMessage(NULL, NULL, 0, 0));
	return 0;
}