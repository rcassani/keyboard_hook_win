// keyboard_hook.cpp
// 
// Installs a Low Level Keyboard Hook (WH_KEYBOARD_LL), to detetec KEYDOWN events
// For each event, the related key is discribes with is Virtual-Key Code and Key Name
//
//
// Virtual-Key Codes:
// https://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx
// 
// Raymundo Cassani
// 2016


#include <iostream>
#include <Windows.h>
#pragma comment(lib, "user32.lib")

// HHOOK variable
HHOOK hHook{ NULL };

/* Event Handler (callback funtion), it is called in response to a change in the state of a key
 *  https://msdn.microsoft.com/en-us/library/ms644985(v=vs.85).aspx
 */
LRESULT CALLBACK CatchLowLevelKeyboardProc(const int nCode, const WPARAM wParam, const LPARAM lParam)
{
	// lParam is cast as KBDLLHOOKSTRUCT
	KBDLLHOOKSTRUCT keyInfo = *((KBDLLHOOKSTRUCT*)lParam);

	// wParam is the The identifier of the keyboard message. 
	// This parameter can be one of the following messages: WM_KEYDOWN, WM_KEYUP, WM_SYSKEYDOWN, or WM_SYSKEYUP. 
	switch (wParam)
	{
	case WM_KEYDOWN:		
		wchar_t buffer[32] = {};
		UINT key = (keyInfo.scanCode << 16);
		GetKeyNameText((LONG)key, buffer, sizeof(buffer));
		wprintf(L"KEYDOWN event, Virtual-Key Code = %#.2X. Key Name = %s \r\n", keyInfo.vkCode, buffer);
		break;
	}
	// Passes the hook information to the next hook procedure. So other hooks can work
	return CallNextHookEx(hHook, nCode, wParam, lParam);
}

int main(void)
{
	printf("Installing the Low Level Keyboard Hook (WH_KEYBOARD_LL) \r\n");
	hHook = SetWindowsHookEx(WH_KEYBOARD_LL, CatchLowLevelKeyboardProc, NULL, 0);
	if (hHook != NULL) 
	{
		printf("WH_KEYBOARD_LL installed successfully\r\n");
	}
	else
	{
		printf("Error installing WH_KEYBOARD_LL\r\n");
	}

	while (GetMessage(NULL, NULL, 0, 0));
	return 0;
}