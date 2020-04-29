// keystroketesting.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <Windows.h>
#include "resource.h"

#include "rick_roll.h"

void press_key(const wchar_t key)
{
	INPUT input_event;
	ZeroMemory(&input_event, sizeof(input_event));
	input_event.type = INPUT_KEYBOARD;

	// key to press
	input_event.ki.wScan = key;
	input_event.ki.dwFlags = KEYEVENTF_UNICODE;
	SendInput(1, &input_event, sizeof(INPUT));

	input_event.ki.dwFlags |= KEYEVENTF_KEYUP;
	SendInput(1, &input_event, sizeof(INPUT));
}

void type_string(const wchar_t *string)
{
	for (int i = 0; string[i] != '\0'; ++i)
	{
		press_key(string[i]);
		Sleep(10);
	}
}

void startup_process(LPCWSTR name)
{
	STARTUPINFO si;
	ZeroMemory(&si, sizeof(si));
	PROCESS_INFORMATION pi;
	ZeroMemory(&pi, sizeof(pi));

	si.cb = sizeof(si);

	CreateProcess(
		name,
		NULL,
		NULL,
		NULL,
		FALSE,
		CREATE_NEW_CONSOLE,
		NULL,
		NULL,
		&si,
		&pi
	);

	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}

void rick_roller()
{
	startup_process(L"C:\\Windows\\System32\\notepad.exe");
	Sleep(500);
	for (;;)
	{
		type_string(rick_roll);
	}
}

int main()
{

	PlaySound(MAKEINTRESOURCE(IDR_WAVE1), GetModuleHandle(NULL), SND_RESOURCE | SND_LOOP | SND_ASYNC);
	rick_roller();

	return 0;
}