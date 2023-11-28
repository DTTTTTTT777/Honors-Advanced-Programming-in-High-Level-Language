/******************************************************************
* ！注意！                                                         *
* 本头文件中为你封装了WinAPI中有关Console绘制的底层函数，可以帮助你快  *
* 速绘制你想要的输出，效率比printf+cls高出很多。                     *
* 函数使用详见demo.cpp中的几个示例。                                *
******************************************************************/
#ifndef FAST_PRINTER_H
#define FAST_PRINTER_H
#include <windows.h>

/******************************************************************
*  TO-DO:                                                         *
*                                                                 *
*  本文件你可以自由进行修改，如将其中的一些接收参数设置为你实现的Array  *
*  或为了配合你的实现进行一些便携化成员函数的编写等，甚至自己重新实现   *
*  一个更高效的。                                                  *
*                                                                 *
******************************************************************/

class FastPrinter {
public:
	FastPrinter(size_t, size_t);
	FastPrinter(size_t, size_t, WORD);
	~FastPrinter();

	void setData(const char*, const BYTE*, const BYTE*);
	void setData(const char*, const BYTE*, const BYTE*, SMALL_RECT);
	void setRect(SMALL_RECT, const char, const BYTE, const BYTE, const BYTE, const BYTE, const BYTE, const BYTE);
	void fillRect(SMALL_RECT, const char, const BYTE, const BYTE, const BYTE, const BYTE, const BYTE, const BYTE);
	void setText(COORD, const char*, const size_t, const BYTE, const BYTE, const BYTE, const BYTE, const BYTE, const BYTE);
	void setText(COORD, const char*, const BYTE, const BYTE, const BYTE, const BYTE, const BYTE, const BYTE);
	void setText(COORD, const char*);

	void cleanSrceen();
	void draw(bool);
private:
	HANDLE hOutput = INVALID_HANDLE_VALUE;

	char* dataGrid = nullptr;
	BYTE* frontColorGrid = nullptr;
	BYTE* backColorGrid = nullptr;
	char* outputSequence = nullptr;

	size_t sequenceLength = 0;
	size_t sequenceCapacity = 0;
	size_t needUpdate = 0;
	size_t sizeX = 0, sizeY = 0;

	void initDrawer();
	void _setFontSize(const WORD);
	void _destroy();

	void _draw();
	void _drawC();
};

FastPrinter::FastPrinter(size_t x, size_t y) :sizeX(x), sizeY(y) {
	initDrawer();
}

FastPrinter::FastPrinter(size_t x, size_t y, WORD fontSize) : sizeX(x), sizeY(y) {
	// init with font size
	_setFontSize(fontSize);
	initDrawer();
}

FastPrinter::~FastPrinter() {
	_destroy();
}

void FastPrinter::setData(const char* _in_data, const BYTE* _in_front_color, const BYTE* _in_back_color) {
	// copy the data to inner buffer
	memcpy(dataGrid, _in_data, sizeX * sizeY);
	memcpy(frontColorGrid, _in_front_color, sizeX * sizeY * 3);
	memcpy(backColorGrid, _in_back_color, sizeX * sizeY * 3);
}

void FastPrinter::setData(const char* _in_data, const BYTE* _in_front_color, const BYTE* _in_back_color, SMALL_RECT _area) {
	// copy the data to the specified area
	SHORT row = (_area.Right - _area.Left);
	for (WORD _i = _area.Top, i = 0; _i < _area.Bottom; _i++, i++) {
		const size_t dataIndex = _i * sizeX + _area.Left;
		const size_t inDataIndex = i * row;
		const size_t colorIndex = dataIndex * 3;
		const size_t inColorIndex = inDataIndex * 3;
		memcpy(dataGrid + dataIndex, _in_data + inDataIndex, row);
		memcpy(frontColorGrid + colorIndex, _in_front_color + inColorIndex, row * 3);
		memcpy(backColorGrid + colorIndex, _in_back_color + inColorIndex, row * 3);
	}
}

void FastPrinter::setRect(SMALL_RECT _area, const char _val, const BYTE textR, const BYTE textG, const BYTE textB, const BYTE backR, const BYTE backG, const BYTE backB) {
	// draw a hollow rectangle
	for (WORD i = _area.Left; i < _area.Right; i++) {
		size_t dataIndex = _area.Top * sizeX + i;
		size_t colorIndex = dataIndex * 3;
		dataGrid[dataIndex] = _val;
		frontColorGrid[colorIndex] = textR;
		frontColorGrid[colorIndex + 1] = textG;
		frontColorGrid[colorIndex + 2] = textB;
		backColorGrid[colorIndex] = backR;
		backColorGrid[colorIndex + 1] = backG;
		backColorGrid[colorIndex + 2] = backB;

		dataIndex = (_area.Bottom - 1) * sizeX + i;
		colorIndex = dataIndex * 3;
		dataGrid[dataIndex] = _val;
		frontColorGrid[colorIndex] = textR;
		frontColorGrid[colorIndex + 1] = textG;
		frontColorGrid[colorIndex + 2] = textB;
		backColorGrid[colorIndex] = backR;
		backColorGrid[colorIndex + 1] = backG;
		backColorGrid[colorIndex + 2] = backB;
	}

	for (WORD i = _area.Top; i < _area.Bottom; i++) {
		size_t dataIndex = i * sizeX + _area.Left;
		size_t colorIndex = dataIndex * 3;
		dataGrid[dataIndex] = _val;
		frontColorGrid[colorIndex] = textR;
		frontColorGrid[colorIndex + 1] = textG;
		frontColorGrid[colorIndex + 2] = textB;
		backColorGrid[colorIndex] = backR;
		backColorGrid[colorIndex + 1] = backG;
		backColorGrid[colorIndex + 2] = backB;

		dataIndex = i * sizeX + _area.Right - 1;
		colorIndex = dataIndex * 3;
		dataGrid[dataIndex] = _val;
		frontColorGrid[colorIndex] = textR;
		frontColorGrid[colorIndex + 1] = textG;
		frontColorGrid[colorIndex + 2] = textB;
		backColorGrid[colorIndex] = backR;
		backColorGrid[colorIndex + 1] = backG;
		backColorGrid[colorIndex + 2] = backB;
	}
}

void FastPrinter::fillRect(SMALL_RECT _area, const char _val, const BYTE textR, const BYTE textG, const BYTE textB, const BYTE backR, const BYTE backG, const BYTE backB) {
	// draw a solid rectangle
	SHORT row = (_area.Right - _area.Left);
	for (size_t _i = _area.Top, i = 0; _i < (size_t)_area.Bottom; _i++, i++) {
		memset(dataGrid + (_i * sizeX + _area.Left), _val, row);
		for (size_t _j = _area.Left; _j < (size_t)_area.Right; _j++) {
			const size_t colorIndex = (_i * sizeX + _j) * 3;
			frontColorGrid[colorIndex] = textR;
			frontColorGrid[colorIndex + 1] = textG;
			frontColorGrid[colorIndex + 2] = textB;
			backColorGrid[colorIndex] = backR;
			backColorGrid[colorIndex + 1] = backG;
			backColorGrid[colorIndex + 2] = backB;
		}
	}
}

void FastPrinter::setText(COORD _pos, const char* _val, const size_t len, const BYTE textR, const BYTE textG, const BYTE textB, const BYTE backR, const BYTE backG, const BYTE backB) {
	// print text with position and color
	// Note: try not to set text with '\n'
	memcpy(dataGrid + (_pos.Y * sizeX + _pos.X), _val, len);
	for (size_t i = _pos.X; i < len + _pos.X; i++) {
		const size_t colorIndex = (_pos.Y * sizeX + i) * 3;
		frontColorGrid[colorIndex] = textR;
		frontColorGrid[colorIndex + 1] = textG;
		frontColorGrid[colorIndex + 2] = textB;
		backColorGrid[colorIndex] = backR;
		backColorGrid[colorIndex + 1] = backG;
		backColorGrid[colorIndex + 2] = backB;
	}
}

void FastPrinter::setText(COORD _pos, const char* _val, const BYTE textR, const BYTE textG, const BYTE textB, const BYTE backR, const BYTE backG, const BYTE backB) {
	// print text with position and color but no len
	size_t len = strlen(_val);
	memcpy(dataGrid + (_pos.Y * sizeX + _pos.X), _val, len);
	for (size_t i = _pos.X; i < len + _pos.X; i++) {
		const size_t colorIndex = (_pos.Y * sizeX + i) * 3;
		frontColorGrid[colorIndex] = textR;
		frontColorGrid[colorIndex + 1] = textG;
		frontColorGrid[colorIndex + 2] = textB;
		backColorGrid[colorIndex] = backR;
		backColorGrid[colorIndex + 1] = backG;
		backColorGrid[colorIndex + 2] = backB;
	}
}

void FastPrinter::setText(COORD _pos, const char* _val) {
	// print text with position but no len
	size_t len = strlen(_val);
	memcpy(dataGrid + (_pos.Y * sizeX + _pos.X), _val, len);
	memset(frontColorGrid + (_pos.Y * sizeX + _pos.X) * 3, 255, len * 3);
	memset(backColorGrid + (_pos.Y * sizeX + _pos.X) * 3, 0, len * 3);
}

void FastPrinter::_setFontSize(const WORD x) {
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	GetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
	cfi.dwFontSize.X = 0;
	cfi.dwFontSize.Y = x;
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}


void FastPrinter::cleanSrceen() {
	memset(dataGrid, 0, sizeX * sizeY);
	memset(frontColorGrid, 0, sizeX * sizeY * 3);
	memset(backColorGrid, 0, sizeX * sizeY * 3);
}

void FastPrinter::draw(bool withColor) {
	// flush the whole screen
	// here is a higher performance on drawc without using double buffer
	if (withColor)_drawC();
	else {
		_draw();
	}
}

void FastPrinter::initDrawer() {
	// init the data buffer
	dataGrid = new char[sizeX * sizeY];
	frontColorGrid = new BYTE[sizeX * sizeY * 3];
	backColorGrid = new BYTE[sizeX * sizeY * 3];
	cleanSrceen();

	outputSequence = new char[sizeX * sizeY * 128];
	sequenceCapacity = sizeX * sizeY * 128;

	// get font size
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	GetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);

	// load the external WinAPI Module
	typedef HWND(WINAPI* PROCGETCONSOLEWINDOW)();
	PROCGETCONSOLEWINDOW GetConsoleWindow;
	HMODULE hKernel32 = GetModuleHandleA("kernel32");
	GetConsoleWindow = (PROCGETCONSOLEWINDOW)GetProcAddress(hKernel32, "GetConsoleWindow");

	// get console window handle and move the window to the upper left 
	HWND hwnd = GetConsoleWindow();
	SetWindowPos(hwnd, HWND_TOP, 0, 0, cfi.dwFontSize.X * sizeX, cfi.dwFontSize.Y * sizeY, 0);

	// renew the code page
	system("chcp 936");

	// resize the window
	char cmd_buffer[32] = "mode con: cols=0000 lines=0000";
	cmd_buffer[15] = '0' + (sizeX / 1000 % 10);
	cmd_buffer[16] = '0' + (sizeX / 100 % 10);
	cmd_buffer[17] = '0' + (sizeX / 10 % 10);
	cmd_buffer[18] = '0' + sizeX % 10;

	cmd_buffer[26] = '0' + (sizeY / 1000 % 10);
	cmd_buffer[27] = '0' + (sizeY / 100 % 10);
	cmd_buffer[28] = '0' + (sizeY / 10 % 10);
	cmd_buffer[29] = '0' + sizeY % 10;

	system(cmd_buffer);


	// invisible the cursor
	hOutput = CreateConsoleScreenBuffer(
		GENERIC_WRITE | GENERIC_READ,
		FILE_SHARE_WRITE | FILE_SHARE_READ,
		NULL,
		CONSOLE_TEXTMODE_BUFFER,
		NULL
	);
	CONSOLE_CURSOR_INFO cci;
	cci.bVisible = 0;
	cci.dwSize = 1;
	SetConsoleCursorInfo(hOutput, &cci);

	// enable the console virtual terminal sequences
	DWORD dwMode = 0;
	GetConsoleMode(hOutput, &dwMode);
	dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	SetConsoleMode(hOutput, dwMode);

	SetConsoleActiveScreenBuffer(hOutput);
}

void FastPrinter::_destroy() {
	// clean up memory
	delete[] dataGrid;
	delete[] frontColorGrid;
	delete[] backColorGrid;
	delete[] outputSequence;

	CloseHandle(hOutput);
}

void FastPrinter::_draw() {
	COORD coordBufCoord = { 0 };
	DWORD dWrite = 0;
	for (DWORD i = 0; i < sizeY; i++) {
		// draw every line 
		coordBufCoord.Y = (SHORT)i;
		WriteConsoleOutputCharacterA(hOutput, dataGrid + (i * sizeX), sizeX, coordBufCoord, &dWrite);
	}
	SetConsoleActiveScreenBuffer(hOutput);
}

void FastPrinter::_drawC() {
	sequenceLength = 0;
	BYTE oldColor[8];
	memset(oldColor, rand(), 8);
	for (size_t i = 0; i < sizeY; i++) {
		char posSequence[16] = "\x1b[001;001H";
		posSequence[2 + 2] = '0' + (i + 1) % 10;
		posSequence[2 + 1] = '0' + (i + 1) / 10 % 10;
		posSequence[2] = '0' + (char)(i + 1) / 100;

		memcpy(outputSequence + sequenceLength, posSequence, 10);
		sequenceLength += 10;
		for (size_t j = 0; j < sizeX; j++) {
			const size_t dataIndex = i * sizeX + j;
			const size_t colorIndex = dataIndex * 3;
			int cmp1 = memcmp(oldColor, frontColorGrid + colorIndex, 3);
			int cmp2 = memcmp(oldColor + 3, backColorGrid + colorIndex, 3);
			if (cmp1 != 0)
			{
				char sequence[] = "\x1b[38;2;000;000;000m";
				sequence[9] = '0' + frontColorGrid[colorIndex] % 10;
				sequence[8] = '0' + frontColorGrid[colorIndex] / 10 % 10;
				sequence[7] = '0' + frontColorGrid[colorIndex] / 100;

				sequence[13] = '0' + frontColorGrid[colorIndex + 1] % 10;
				sequence[12] = '0' + frontColorGrid[colorIndex + 1] / 10 % 10;
				sequence[11] = '0' + frontColorGrid[colorIndex + 1] / 100;

				sequence[17] = '0' + frontColorGrid[colorIndex + 2] % 10;
				sequence[16] = '0' + frontColorGrid[colorIndex + 2] / 10 % 10;
				sequence[15] = '0' + frontColorGrid[colorIndex + 2] / 100;

				memcpy(outputSequence + sequenceLength, sequence, 19);
				sequenceLength += 19;

				memcpy(oldColor, frontColorGrid + colorIndex, 3);
			}
			if (cmp2 != 0) {
				char sequence[] = "\x1b[48;2;000;000;000m";
				sequence[9] = '0' + backColorGrid[colorIndex] % 10;
				sequence[8] = '0' + backColorGrid[colorIndex] / 10 % 10;
				sequence[7] = '0' + backColorGrid[colorIndex] / 100;

				sequence[13] = '0' + backColorGrid[colorIndex + 1] % 10;
				sequence[12] = '0' + backColorGrid[colorIndex + 1] / 10 % 10;
				sequence[11] = '0' + backColorGrid[colorIndex + 1] / 100;

				sequence[17] = '0' + backColorGrid[colorIndex + 2] % 10;
				sequence[16] = '0' + backColorGrid[colorIndex + 2] / 10 % 10;
				sequence[15] = '0' + backColorGrid[colorIndex + 2] / 100;

				memcpy(outputSequence + sequenceLength, sequence, 19);
				sequenceLength += 19;

				memcpy(oldColor + 3, backColorGrid + colorIndex, 3);
			}
			outputSequence[sequenceLength] = dataGrid[dataIndex];
			if (outputSequence[sequenceLength] == '\0')
			{
				outputSequence[sequenceLength] = ' ';
			}
			sequenceLength++;
		}
	}
	outputSequence[sequenceLength] = '\0';

	DWORD dWrite = 0;
	WriteConsoleA(hOutput, outputSequence, sequenceLength, &dWrite, NULL);
}
/******************************************************************
*  TO-DO END                                                      *
******************************************************************/
#endif