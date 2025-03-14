#include "main.h"

//=============================================================================
#define IDC_GROUPBOX_VALUE					1001
#define IDC_TEXTBOX_VALUE					1002
#define IDC_PUSHBUTTON_CONVERT				1003
#define IDC_LABEL_VALUE						1004

#define IDC_GROUPBOX_SINGLE					1005
#define IDC_TEXTBOX_SINGLE_BINARY_SIGN		1006
#define IDC_TEXTBOX_SINGLE_BINARY_EXP		1007
#define IDC_TEXTBOX_SINGLE_BINARY_MANTISSA	1008
#define IDC_TEXTBOX_SINGLE_HEX				1009
#define IDC_TEXTBOX_SINGLE_IEEE754			1010
#define IDC_CHECKBOX_EXP_SINGLE				1011
#define IDC_PUSHBUTTON_COPY_SINGLE_BINARY	1012
#define IDC_PUSHBUTTON_COPY_SINGLE_HEX		1013
#define IDC_PUSHBUTTON_COPY_SINGLE_IEEE754	1014
#define IDC_LABEL_SINGLE_BINARY_SIGN		1015
#define IDC_LABEL_SINGLE_BINARY_EXP			1016
#define IDC_LABEL_SINGLE_BINARY_MANTISSA	1017
#define IDC_LABEL_SINGLE_HEX				1018
#define IDC_LABEL_SINGLE_IEEE754			1019

#define IDC_GROUPBOX_DOUBLE					1020
#define IDC_TEXTBOX_DOUBLE_BINARY_SIGN		1021
#define IDC_TEXTBOX_DOUBLE_BINARY_EXP		1022
#define IDC_TEXTBOX_DOUBLE_BINARY_MANTISSA	1023
#define IDC_TEXTBOX_DOUBLE_HEX				1024
#define IDC_TEXTBOX_DOUBLE_IEEE754			1025
#define IDC_CHECKBOX_EXP_DOUBLE				1026
#define IDC_PUSHBUTTON_COPY_DOUBLE_BINARY	1027
#define IDC_PUSHBUTTON_COPY_DOUBLE_HEX		1028
#define IDC_PUSHBUTTON_COPY_DOUBLE_IEEE754	1029
#define IDC_LABEL_DOUBLE_BINARY_SIGN		1030
#define IDC_LABEL_DOUBLE_BINARY_EXP			1031
#define IDC_LABEL_DOUBLE_BINARY_MANTISSA	1032
#define IDC_LABEL_DOUBLE_HEX				1033
#define IDC_LABEL_DOUBLE_IEEE754			1034

#define IDC_GROUPBOX_RESULTS				1035
#define IDC_PUSHBUTTON_COPY_RESULTS			1036
#define IDC_PUSHBUTTON_SAVE_RESULTS			1037

#define IDC_GROUPBOX_INFO					1038
#define IDC_PUSHBUTTON_HELP					1039
#define IDC_PUSHBUTTON_ABOUT				1040

#define IDC_GROUPBOX_HISTORY				1041
#define IDC_COMBOBOX_HISTORY				1042

//=============================================================================

const char* FONT_NORMAL = "Tahoma";

std::string STR_RESULTS_COPY_OK = LoadStrFromResource(hInst, IDS_STR_RESULTS_COPY_OK);
std::string STR_RESULTS_COPY_FAIL = LoadStrFromResource(hInst, IDS_STR_RESULTS_COPY_FAIL);
std::string STR_RESULTS_SAVE_OK = LoadStrFromResource(hInst, IDS_STR_RESULTS_SAVE_OK);
std::string STR_RESULTS_SAVE_FAIL = LoadStrFromResource(hInst, IDS_STR_RESULTS_SAVE_FAIL);
std::string STR_APP_HELP = LoadStrFromResource(hInst, IDS_STR_APP_HELP);
std::string STR_APP_ABOUT = LoadStrFromResource(hInst, IDS_STR_APP_ABOUT);
std::string STR_APP_HELP_TEXT = LoadStrFromResource(hInst, IDS_STR_APP_HELP_TEXT);
std::string STR_APP_ABOUT_TEXT = LoadStrFromResource(hInst, IDS_STR_APP_ABOUT_TEXT);

std::string STR_GROUPBOX_RESULTS = LoadStrFromResource(hInst, IDS_STR_GROUPBOX_RESULTS);

std::string CONVERTER_RESULTS_STATUS_OK = LoadStrFromResource(hInst, IDS_STR_CONVERTER_RESULTS_STATUS_OK);
std::string CONVERTER_RESULTS_STATUS_FAIL = LoadStrFromResource(hInst, IDS_STR_CONVERTER_RESULTS_STATUS_FAIL);

//=============================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{	
	hInst = hInstance;
	HWND hwnd;
	MSG msg;
	
	std::string STR_APP_NAME = LoadStrFromResource(hInst, IDS_STR_APP_NAME);
	std::string STR_ERROR_REG_CLASS = LoadStrFromResource(hInst, IDS_STR_ERROR_REG_CLASS);

	WNDCLASSEX wndmain;
	wndmain.cbSize = sizeof(WNDCLASSEX);
	wndmain.style = 0;
	wndmain.lpfnWndProc = WndProc;
    wndmain.cbClsExtra = 0;
    wndmain.cbWndExtra = 0;
    wndmain.hInstance = hInstance;
    wndmain.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APP_ICON));
    wndmain.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndmain.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
    wndmain.lpszMenuName = NULL;
    wndmain.lpszClassName = STR_APP_NAME.c_str();
	wndmain.hIconSm = NULL;

    if (!RegisterClassEx(&wndmain))
	{
		MessageBox(NULL, STR_ERROR_REG_CLASS.c_str(), STR_APP_NAME.c_str(), MB_ICONERROR);
		return 0;
    }

	hwnd = CreateWindowEx(0, wndmain.lpszClassName, STR_APP_NAME.c_str(), WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 856, 756, 0, NULL, hInstance, NULL);	

	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		// TAB and SHIFT+TAB handler
		//==========================
		if (msg.message == WM_KEYDOWN || msg.message == WM_SYSKEYDOWN)
		{
			if (msg.wParam == VK_TAB)
			{
				BOOL isDirBackward = GetAsyncKeyState(VK_SHIFT) & 0x8000;
				
				HWND itemNext = GetNextDlgTabItem(hwnd, GetFocus(), isDirBackward);
				if (IsWindow(itemNext))
				{
					SetFocus(itemNext);
					continue;
				}
			}			
		}
		//==========================
		
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int) msg.wParam;
}

//=============================================================================
std::string LoadStrFromResource(HINSTANCE hInstance, int strID)
{
	char buffer[BUFFER_STR];
	LoadString(hInstance, strID, buffer, sizeof(buffer) / sizeof(char));
	
	std::string result = buffer;	
	return result;
}

//=============================================================================
void CreateControls(const HWND& hwnd)
{	
	INITCOMMONCONTROLSEX initCtls;
	InitCommonControlsEx(&initCtls);
	
	const char* TEXT_CLASS_BUTTON = "BUTTON";
	const char* TEXT_CLASS_LABEL = "STATIC";
	const char* TEXT_CLASS_EDIT = "EDIT";
	const char* TEXT_CLASS_COMBOBOX = "COMBOBOX";
	
	std::string STR_EMPTY = LoadStrFromResource(hInst, IDS_STR_EMPTY);

	std::string STR_GROUPBOX_VALUE = LoadStrFromResource(hInst, IDS_STR_GROUPBOX_VALUE);
	std::string STR_LABEL_VALUE = LoadStrFromResource(hInst, IDS_STR_LABEL_VALUE);
	std::string STR_PUSHBUTTON_CONVERT = LoadStrFromResource(hInst, IDS_STR_PUSHBUTTON_CONVERT);

	std::string STR_GROUPBOX_SINGLE = LoadStrFromResource(hInst, IDS_STR_GROUPBOX_SINGLE);
	std::string STR_LABEL_SINGLE_BINARY_SIGN = LoadStrFromResource(hInst, IDS_STR_LABEL_SINGLE_BINARY_SIGN);
	std::string STR_LABEL_SINGLE_BINARY_EXP = LoadStrFromResource(hInst, IDS_STR_LABEL_SINGLE_BINARY_EXP);
	std::string STR_LABEL_SINGLE_BINARY_MANTISSA = LoadStrFromResource(hInst, IDS_STR_LABEL_SINGLE_BINARY_MANTISSA);
	std::string STR_PUSHBUTTON_COPY_SINGLE_BINARY = LoadStrFromResource(hInst, IDS_STR_PUSHBUTTON_COPY_SINGLE_BINARY);
	std::string STR_LABEL_SINGLE_HEX = LoadStrFromResource(hInst, IDS_STR_LABEL_SINGLE_HEX);
	std::string STR_PUSHBUTTON_COPY_SINGLE_HEX = LoadStrFromResource(hInst, IDS_STR_PUSHBUTTON_COPY_SINGLE_HEX);
	std::string STR_LABEL_SINGLE_IEEE754 = LoadStrFromResource(hInst, IDS_STR_LABEL_SINGLE_IEEE754);
	std::string STR_PUSHBUTTON_COPY_SINGLE_IEEE754 = LoadStrFromResource(hInst, IDS_STR_PUSHBUTTON_COPY_SINGLE_IEEE754);
	std::string STR_CHECKBOX_EXP_SINGLE = LoadStrFromResource(hInst, IDS_STR_CHECKBOX_EXP_SINGLE);

	std::string STR_GROUPBOX_DOUBLE = LoadStrFromResource(hInst, IDS_STR_GROUPBOX_DOUBLE);
	std::string STR_LABEL_DOUBLE_BINARY_SIGN = LoadStrFromResource(hInst, IDS_STR_LABEL_DOUBLE_BINARY_SIGN);
	std::string STR_LABEL_DOUBLE_BINARY_EXP = LoadStrFromResource(hInst, IDS_STR_LABEL_DOUBLE_BINARY_EXP);
	std::string STR_LABEL_DOUBLE_BINARY_MANTISSA = LoadStrFromResource(hInst, IDS_STR_LABEL_DOUBLE_BINARY_MANTISSA);
	std::string STR_PUSHBUTTON_COPY_DOUBLE_BINARY = LoadStrFromResource(hInst, IDS_STR_PUSHBUTTON_COPY_DOUBLE_BINARY);
	std::string STR_LABEL_DOUBLE_HEX = LoadStrFromResource(hInst, IDS_STR_LABEL_DOUBLE_HEX);
	std::string STR_PUSHBUTTON_COPY_DOUBLE_HEX = LoadStrFromResource(hInst, IDS_STR_PUSHBUTTON_COPY_DOUBLE_HEX);
	std::string STR_LABEL_DOUBLE_IEEE754 = LoadStrFromResource(hInst, IDS_STR_LABEL_DOUBLE_IEEE754);
	std::string STR_PUSHBUTTON_COPY_DOUBLE_IEEE754 = LoadStrFromResource(hInst, IDS_STR_PUSHBUTTON_COPY_DOUBLE_IEEE754);
	std::string STR_CHECKBOX_EXP_DOUBLE = LoadStrFromResource(hInst, IDS_STR_CHECKBOX_EXP_DOUBLE);

	std::string STR_GROUPBOX_INFO = LoadStrFromResource(hInst, IDS_STR_GROUPBOX_INFO);
	std::string STR_PUSHBUTTON_HELP = LoadStrFromResource(hInst, IDS_STR_PUSHBUTTON_HELP);
	std::string STR_PUSHBUTTON_ABOUT = LoadStrFromResource(hInst, IDS_STR_PUSHBUTTON_ABOUT);

	std::string STR_GROUPBOX_RESULTS = LoadStrFromResource(hInst, IDS_STR_GROUPBOX_RESULTS);
	std::string STR_PUSHBUTTON_COPY_RESULTS = LoadStrFromResource(hInst, IDS_STR_PUSHBUTTON_COPY_RESULTS);
	std::string STR_PUSHBUTTON_SAVE_RESULTS = LoadStrFromResource(hInst, IDS_STR_PUSHBUTTON_SAVE_RESULTS);

	std::string STR_GROUPBOX_HISTORY = LoadStrFromResource(hInst, IDS_STR_GROUPBOX_HISTORY);
	std::string STR_COMBOBOX_HISTORY = LoadStrFromResource(hInst, IDS_STR_COMBOBOX_HISTORY);

	// GROUPBOX_VALUE
	ctlGroupBoxValue = CreateWindowEx(0, TEXT_CLASS_BUTTON, STR_GROUPBOX_VALUE.c_str(), WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 10, 10, 830, 95, hwnd, (HMENU)IDC_GROUPBOX_VALUE, NULL, NULL);	
	ctlLabelValue = CreateWindowEx(0, TEXT_CLASS_LABEL, STR_LABEL_VALUE.c_str(), WS_CHILD | WS_VISIBLE, 20, 40, 340, 30, hwnd, (HMENU)IDC_LABEL_VALUE,	0, NULL);	
	ctlTextBoxValue = CreateWindowEx(WS_EX_CLIENTEDGE | WS_EX_LEFT, TEXT_CLASS_EDIT, STR_EMPTY.c_str(), WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, 20, 65, 680, 30, hwnd, (HMENU)IDC_TEXTBOX_VALUE, NULL, NULL);
	ctlPushButtonConvert = CreateWindowEx(0, TEXT_CLASS_BUTTON, STR_PUSHBUTTON_CONVERT.c_str(), WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_DEFPUSHBUTTON, 710, 65, 120, 30, hwnd, (HMENU)IDC_PUSHBUTTON_CONVERT, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);

	// GROUPBOX_SINGLE	
	ctlGroupBoxSingle = CreateWindowEx(0, TEXT_CLASS_BUTTON, STR_GROUPBOX_SINGLE.c_str(), WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 10, 115, 830, 250, hwnd, (HMENU)IDC_GROUPBOX_SINGLE, NULL, NULL);	
	ctlLabelSingleBinarySign = CreateWindowEx(0, TEXT_CLASS_LABEL, STR_LABEL_SINGLE_BINARY_SIGN.c_str(), WS_CHILD | WS_VISIBLE, 20, 145, 100, 30, hwnd, (HMENU)IDC_LABEL_SINGLE_BINARY_SIGN,	0, NULL);
	ctlLabelSingleBinaryExp = CreateWindowEx(0, TEXT_CLASS_LABEL, STR_LABEL_SINGLE_BINARY_EXP.c_str(), WS_CHILD | WS_VISIBLE, 75, 145, 100, 30, hwnd, (HMENU)IDC_LABEL_SINGLE_BINARY_EXP,	0, NULL);
	ctlLabelSingleBinaryMantissa = CreateWindowEx(0, TEXT_CLASS_LABEL, STR_LABEL_SINGLE_BINARY_MANTISSA.c_str(), WS_CHILD | WS_VISIBLE, 200, 145, 100, 30, hwnd, (HMENU)IDC_LABEL_SINGLE_BINARY_MANTISSA,	0, NULL);
	ctlTextBoxSingleBinarySign = CreateWindowEx(WS_EX_CLIENTEDGE | WS_EX_LEFT, TEXT_CLASS_EDIT, STR_EMPTY.c_str(), WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, 20, 170, 55, 30, hwnd, (HMENU)IDC_TEXTBOX_SINGLE_BINARY_SIGN, NULL, NULL);
	ctlTextBoxSingleBinaryExp = CreateWindowEx(WS_EX_CLIENTEDGE | WS_EX_LEFT, TEXT_CLASS_EDIT, STR_EMPTY.c_str(), WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, 75, 170, 125, 30, hwnd, (HMENU)IDC_TEXTBOX_SINGLE_BINARY_EXP, NULL, NULL);	
	ctlTextBoxSingleBinaryMantissa = CreateWindowEx(WS_EX_CLIENTEDGE | WS_EX_LEFT, TEXT_CLASS_EDIT, STR_EMPTY.c_str(), WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, 200, 170, 500, 30, hwnd, (HMENU)IDC_TEXTBOX_SINGLE_BINARY_MANTISSA, NULL, NULL);
	ctlPushButtonCopySingleBinary = CreateWindowEx(0, TEXT_CLASS_BUTTON, STR_PUSHBUTTON_COPY_SINGLE_BINARY.c_str(), WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_DEFPUSHBUTTON, 710, 170, 120, 30, hwnd, (HMENU)IDC_PUSHBUTTON_COPY_SINGLE_BINARY, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
	// HEX
	ctlLabelSingleHex = CreateWindowEx(0, TEXT_CLASS_LABEL, STR_LABEL_SINGLE_HEX.c_str(), WS_CHILD | WS_VISIBLE, 20, 210, 350, 30, hwnd, (HMENU)IDC_LABEL_SINGLE_HEX,	0, NULL);
	ctlTextBoxSingleHex = CreateWindowEx(WS_EX_CLIENTEDGE | WS_EX_LEFT, TEXT_CLASS_EDIT, STR_EMPTY.c_str(), WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, 20, 235, 680, 30, hwnd, (HMENU)IDC_TEXTBOX_SINGLE_HEX, NULL, NULL);
	ctlPushButtonCopySingleHex = CreateWindowEx(0, TEXT_CLASS_BUTTON, STR_PUSHBUTTON_COPY_SINGLE_HEX.c_str(), WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_DEFPUSHBUTTON, 710, 235, 120, 30, hwnd, (HMENU)IDC_PUSHBUTTON_COPY_SINGLE_HEX, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
	// IEEE754
	ctlLabelSingleIEEE754 = CreateWindowEx(0, TEXT_CLASS_LABEL, STR_LABEL_SINGLE_IEEE754.c_str(), WS_CHILD | WS_VISIBLE, 20, 275, 350, 30, hwnd, (HMENU)IDC_LABEL_SINGLE_IEEE754,	0, NULL);
	ctlTextBoxSingleIEEE754 = CreateWindowEx(WS_EX_CLIENTEDGE | WS_EX_LEFT, TEXT_CLASS_EDIT, STR_EMPTY.c_str(), WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, 20, 300, 680, 30, hwnd, (HMENU)IDC_TEXTBOX_SINGLE_IEEE754, NULL, NULL);
	ctlPushButtonCopySingleIEEE754 = CreateWindowEx(0, TEXT_CLASS_BUTTON, STR_PUSHBUTTON_COPY_SINGLE_IEEE754.c_str(), WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_DEFPUSHBUTTON, 710, 300, 120, 30, hwnd, (HMENU)IDC_PUSHBUTTON_COPY_SINGLE_IEEE754, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
	ctlCheckBoxExpSingle = CreateWindowEx(0, TEXT_CLASS_BUTTON, STR_CHECKBOX_EXP_SINGLE.c_str(), WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_AUTOCHECKBOX, 20, 330, 200, 30, hwnd, (HMENU)IDC_CHECKBOX_EXP_SINGLE, NULL, NULL);

	// GROUPBOX_DOUBLE
	ctlGroupBoxDouble = CreateWindowEx(0, TEXT_CLASS_BUTTON, STR_GROUPBOX_DOUBLE.c_str(), WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 10, 375, 830, 250, hwnd, (HMENU)IDC_GROUPBOX_DOUBLE, NULL, NULL);	
	ctlLabelDoubleBinarySign = CreateWindowEx(0, TEXT_CLASS_LABEL, STR_LABEL_DOUBLE_BINARY_SIGN.c_str(), WS_CHILD | WS_VISIBLE, 20, 405, 100, 30, hwnd, (HMENU)IDC_LABEL_DOUBLE_BINARY_SIGN,	0, NULL);
	ctlLabelDoubleBinaryExp = CreateWindowEx(0, TEXT_CLASS_LABEL, STR_LABEL_DOUBLE_BINARY_EXP.c_str(), WS_CHILD | WS_VISIBLE, 75, 405, 100, 30, hwnd, (HMENU)IDC_LABEL_DOUBLE_BINARY_EXP,	0, NULL);
	ctlLabelDoubleBinaryMantissa = CreateWindowEx(0, TEXT_CLASS_LABEL, STR_LABEL_DOUBLE_BINARY_MANTISSA.c_str(), WS_CHILD | WS_VISIBLE, 200, 405, 100, 30, hwnd, (HMENU)IDC_LABEL_DOUBLE_BINARY_MANTISSA,	0, NULL);
	ctlTextBoxDoubleBinarySign = CreateWindowEx(WS_EX_CLIENTEDGE | WS_EX_LEFT, TEXT_CLASS_EDIT, STR_EMPTY.c_str(), WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, 20, 430, 55, 30, hwnd, (HMENU)IDC_TEXTBOX_DOUBLE_BINARY_SIGN, NULL, NULL);
	ctlTextBoxDoubleBinaryExp = CreateWindowEx(WS_EX_CLIENTEDGE | WS_EX_LEFT, TEXT_CLASS_EDIT, STR_EMPTY.c_str(), WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, 75, 430, 125, 30, hwnd, (HMENU)IDC_TEXTBOX_DOUBLE_BINARY_EXP, NULL, NULL);	
	ctlTextBoxDoubleBinaryMantissa = CreateWindowEx(WS_EX_CLIENTEDGE | WS_EX_LEFT, TEXT_CLASS_EDIT, STR_EMPTY.c_str(), WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, 200, 430, 500, 30, hwnd, (HMENU)IDC_TEXTBOX_DOUBLE_BINARY_MANTISSA, NULL, NULL);
	ctlPushButtonCopyDoubleBinary = CreateWindowEx(0, TEXT_CLASS_BUTTON, STR_PUSHBUTTON_COPY_DOUBLE_BINARY.c_str(), WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_DEFPUSHBUTTON, 710, 430, 120, 30, hwnd, (HMENU)IDC_PUSHBUTTON_COPY_DOUBLE_BINARY, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
	// HEX
	ctlLabelDoubleHex = CreateWindowEx(0, TEXT_CLASS_LABEL, STR_LABEL_DOUBLE_HEX.c_str(), WS_CHILD | WS_VISIBLE, 20, 470, 350, 30, hwnd, (HMENU)IDC_LABEL_DOUBLE_HEX,	0, NULL);
	ctlTextBoxDoubleHex = CreateWindowEx(WS_EX_CLIENTEDGE | WS_EX_LEFT, TEXT_CLASS_EDIT, STR_EMPTY.c_str(), WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, 20, 495, 680, 30, hwnd, (HMENU)IDC_TEXTBOX_DOUBLE_HEX, NULL, NULL);
	ctlPushButtonCopyDoubleHex = CreateWindowEx(0, TEXT_CLASS_BUTTON, STR_PUSHBUTTON_COPY_DOUBLE_HEX.c_str(), WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_DEFPUSHBUTTON, 710, 495, 120, 30, hwnd, (HMENU)IDC_PUSHBUTTON_COPY_DOUBLE_HEX, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
	// IEEE754
	ctlLabelDoubleIEEE754 = CreateWindowEx(0, TEXT_CLASS_LABEL, STR_LABEL_DOUBLE_IEEE754.c_str(), WS_CHILD | WS_VISIBLE, 20, 535, 350, 30, hwnd, (HMENU)IDC_LABEL_DOUBLE_IEEE754,	0, NULL);
	ctlTextBoxDoubleIEEE754 = CreateWindowEx(WS_EX_CLIENTEDGE | WS_EX_LEFT, TEXT_CLASS_EDIT, STR_EMPTY.c_str(), WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, 20, 560, 680, 30, hwnd, (HMENU)IDC_TEXTBOX_DOUBLE_IEEE754, NULL, NULL);
	ctlPushButtonCopyDoubleIEEE754 = CreateWindowEx(0, TEXT_CLASS_BUTTON, STR_PUSHBUTTON_COPY_DOUBLE_IEEE754.c_str(), WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_DEFPUSHBUTTON, 710, 560, 120, 30, hwnd, (HMENU)IDC_PUSHBUTTON_COPY_DOUBLE_IEEE754, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
	ctlCheckBoxExpDouble = CreateWindowEx(0, TEXT_CLASS_BUTTON, STR_CHECKBOX_EXP_DOUBLE.c_str(), WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_AUTOCHECKBOX, 20, 590, 200, 30, hwnd, (HMENU)IDC_CHECKBOX_EXP_DOUBLE, NULL, NULL);

	// GROUPBOX_INFO
	ctlGroupBoxInfo = CreateWindowEx(0, TEXT_CLASS_BUTTON, STR_GROUPBOX_INFO.c_str(), WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 10, 635, 270, 70, hwnd, (HMENU)IDC_GROUPBOX_INFO, NULL, NULL);
	ctlPushButtonHelp = CreateWindowEx(0, TEXT_CLASS_BUTTON, STR_PUSHBUTTON_HELP.c_str(), WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_DEFPUSHBUTTON, 20, 665, 120, 30, hwnd, (HMENU)IDC_PUSHBUTTON_HELP, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
	ctlPushButtonAbout = CreateWindowEx(0, TEXT_CLASS_BUTTON, STR_PUSHBUTTON_ABOUT.c_str(), WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_DEFPUSHBUTTON, 150, 665, 120, 30, hwnd, (HMENU)IDC_PUSHBUTTON_ABOUT, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);	

	// GROUPBOX_HISTORY
	ctlGroupBoxHistory = CreateWindowEx(0, TEXT_CLASS_BUTTON, STR_GROUPBOX_HISTORY.c_str(), WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 290, 635, 270, 70, hwnd, (HMENU)IDC_GROUPBOX_HISTORY, NULL, NULL);
	ctlComboBoxHistory = CreateWindowEx(0, TEXT_CLASS_COMBOBOX,	STR_COMBOBOX_HISTORY.c_str(), WS_CHILD | WS_VISIBLE | WS_TABSTOP | CBS_DROPDOWNLIST | WS_VSCROLL, 300, 665, 250, 600, hwnd, (HMENU)IDC_COMBOBOX_HISTORY, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);	
	SendMessage(ctlComboBoxHistory, CB_SETITEMDATA, 0, 0);
	
	// GROUPBOX_RESULTS
	ctlGroupBoxResults = CreateWindowEx(0, TEXT_CLASS_BUTTON, STR_GROUPBOX_RESULTS.c_str(), WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 570, 635, 270, 70, hwnd, (HMENU)IDC_GROUPBOX_RESULTS, NULL, NULL);
	ctlPushButtonCopyResults = CreateWindowEx(0, TEXT_CLASS_BUTTON, STR_PUSHBUTTON_COPY_RESULTS.c_str(), WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_DEFPUSHBUTTON, 580, 665, 120, 30, hwnd, (HMENU)IDC_PUSHBUTTON_COPY_RESULTS, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);	
	ctlPushButtonSaveResults = CreateWindowEx(0, TEXT_CLASS_BUTTON, STR_PUSHBUTTON_SAVE_RESULTS.c_str(), WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_DEFPUSHBUTTON, 710, 665, 120, 30, hwnd, (HMENU)IDC_PUSHBUTTON_SAVE_RESULTS, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);	
	
	CreateFontCustom(hFontNormal, FW_NORMAL);
	CreateFontCustom(hFontBold, FW_BOLD);
	
	UpdateFonts();	
	
	SetFocus(ctlTextBoxValue);	
}

//===================================================
void InitState()
{
	isSingleScientificExp = false;
	isDoubleScientificExp = false;
}

//===================================================
void UpdateFonts()
{	
	UpdateFont(ctlGroupBoxValue, hFontBold);
	UpdateFont(ctlTextBoxValue, hFontNormal);
	UpdateFont(ctlPushButtonConvert, hFontBold);
	UpdateFont(ctlLabelValue, hFontNormal);

	UpdateFont(ctlGroupBoxSingle, hFontBold);
	UpdateFont(ctlTextBoxSingleBinarySign, hFontNormal);
	UpdateFont(ctlTextBoxSingleBinaryExp, hFontNormal);
	UpdateFont(ctlTextBoxSingleBinaryMantissa, hFontNormal);
	UpdateFont(ctlTextBoxSingleHex, hFontNormal);
	UpdateFont(ctlTextBoxSingleIEEE754, hFontNormal);
	UpdateFont(ctlCheckBoxExpSingle, hFontNormal);
	UpdateFont(ctlPushButtonCopySingleBinary, hFontNormal);
	UpdateFont(ctlPushButtonCopySingleHex, hFontNormal);
	UpdateFont(ctlPushButtonCopySingleIEEE754, hFontNormal);
	UpdateFont(ctlLabelSingleBinarySign, hFontNormal);
	UpdateFont(ctlLabelSingleBinaryExp, hFontNormal);
	UpdateFont(ctlLabelSingleBinaryMantissa, hFontNormal);
	UpdateFont(ctlLabelSingleHex, hFontNormal);
	UpdateFont(ctlLabelSingleIEEE754, hFontNormal);

	UpdateFont(ctlGroupBoxDouble, hFontBold);
	UpdateFont(ctlTextBoxDoubleBinarySign, hFontNormal);
	UpdateFont(ctlTextBoxDoubleBinaryExp, hFontNormal);
	UpdateFont(ctlTextBoxDoubleBinaryMantissa, hFontNormal);
	UpdateFont(ctlTextBoxDoubleHex, hFontNormal);
	UpdateFont(ctlTextBoxDoubleIEEE754, hFontNormal);
	UpdateFont(ctlCheckBoxExpDouble, hFontNormal);
	UpdateFont(ctlPushButtonCopyDoubleBinary, hFontNormal);
	UpdateFont(ctlPushButtonCopyDoubleHex, hFontNormal);
	UpdateFont(ctlPushButtonCopyDoubleIEEE754, hFontNormal);
	UpdateFont(ctlLabelDoubleBinarySign, hFontNormal);
	UpdateFont(ctlLabelDoubleBinaryExp, hFontNormal);
	UpdateFont(ctlLabelDoubleBinaryMantissa, hFontNormal);
	UpdateFont(ctlLabelDoubleHex, hFontNormal);
	UpdateFont(ctlLabelDoubleIEEE754, hFontNormal);

	UpdateFont(ctlGroupBoxResults, hFontBold);
	UpdateFont(ctlPushButtonCopyResults, hFontNormal);
	UpdateFont(ctlPushButtonSaveResults, hFontNormal);
	
	UpdateFont(ctlGroupBoxInfo, hFontBold);
	UpdateFont(ctlPushButtonHelp, hFontNormal);
	UpdateFont(ctlPushButtonAbout, hFontNormal);

	UpdateFont(ctlGroupBoxHistory, hFontBold);
	UpdateFont(ctlComboBoxHistory, hFontNormal);	
}

//===================================================
void UpdateFont(HWND& hControl, HFONT& hFont)
{
	SendMessage(hControl, WM_SETFONT, (WPARAM)hFont, TRUE);	
}

//===================================================
void CreateFontCustom(HFONT& hFontCustom, int fnWeight)
{
	hFontCustom = CreateFont
	(
		0, 							// int nHeight               // height of font
		0, 							// int nWidth                // average character width
		0, 							// int nEscapement           // angle of escapement
		0, 							// int nOrientation          // base-line orientation angle
		fnWeight, 					// int fnWeight              // font weight
		FALSE, 						// DWORD fdwItalic           // italic attribute option
		FALSE, 						// DWORD fdwUnderline        // underline attribute option
		FALSE, 						// DWORD fdwStrikeOut        // strikeout attribute option
		DEFAULT_CHARSET, 			// DWORD fdwCharSet          // character set identifier
		OUT_DEFAULT_PRECIS, 		// DWORD fdwOutputPrecision  // output precision
		CLIP_DEFAULT_PRECIS, 		// DWORD fdwClipPrecision    // clipping precision
		DEFAULT_QUALITY, 			// DWORD fdwQuality          // output quality
		DEFAULT_PITCH | FF_SWISS, 	// DWORD fdwPitchAndFamily   // pitch and family
		FONT_NORMAL			 		// LPCTSTR lpszFace          // typeface name
	);
}

//===================================================
std::string GetEditText(const HWND& hEdit)
{
    int length = GetWindowTextLength(hEdit);
    if (length <= 0) { return ""; }

    std::string text(length, '\0');
    GetWindowText(hEdit, &text[0], length + 1);

    return text;
}

//===================================================
void Calculate()
{
	converter.CalculateResults(GetEditText(ctlTextBoxValue));
}

//===================================================
void UpdateResults()
{
	SetWindowText(ctlTextBoxValue, converter.results.value.c_str());
	
	SetWindowText(ctlTextBoxSingleBinarySign, converter.results.valueSingleBinarySign.c_str());
	SetWindowText(ctlTextBoxSingleBinaryExp, converter.results.valueSingleBinaryExponent.c_str());
	SetWindowText(ctlTextBoxSingleBinaryMantissa, converter.results.valueSingleBinaryMantissa.c_str());
	SetWindowText(ctlTextBoxSingleHex, converter.results.valueSingleHex.c_str());
	UpdateTextboxSingleIEEE754();
	
	SetWindowText(ctlTextBoxDoubleBinarySign, converter.results.valueDoubleBinarySign.c_str());
	SetWindowText(ctlTextBoxDoubleBinaryExp, converter.results.valueDoubleBinaryExponent.c_str());
	SetWindowText(ctlTextBoxDoubleBinaryMantissa, converter.results.valueDoubleBinaryMantissa.c_str());
	SetWindowText(ctlTextBoxDoubleHex, converter.results.valueDoubleHex.c_str());
	UpdateTextboxDoubleIEEE754();	
	
	if (converter.results.status == true)
		{ SetWindowText(ctlGroupBoxValue, CONVERTER_RESULTS_STATUS_OK.c_str()); }
	else
		{ SetWindowText(ctlGroupBoxValue, CONVERTER_RESULTS_STATUS_FAIL.c_str()); }		

	SetWindowText(ctlGroupBoxResults, STR_GROUPBOX_RESULTS.c_str());
	
	ComboBoxHistoryEntryAdd(converter.results.value.c_str());
}

//===================================================
void UpdateTextboxSingleIEEE754()
{
	if (isSingleScientificExp == true)
	{
		SetWindowText(ctlTextBoxSingleIEEE754, converter.results.valueSingleScientificTrimmed.c_str());
	}
	else
	{
		SetWindowText(ctlTextBoxSingleIEEE754, converter.results.valueSingleExactTrimmed.c_str());	
	}
}

//===================================================
void UpdateTextboxDoubleIEEE754()
{
	if (isDoubleScientificExp == true)
	{
		SetWindowText(ctlTextBoxDoubleIEEE754, converter.results.valueDoubleScientificTrimmed.c_str());
	}
	else
	{
		SetWindowText(ctlTextBoxDoubleIEEE754, converter.results.valueDoubleExactTrimmed.c_str());	
	}
}

//===================================================
bool GetCheckboxState(const HWND& hwnd, int buttonID)
{
	return (IsDlgButtonChecked(hwnd, buttonID) == BST_CHECKED);
}

//===================================================
bool ClipboardCopy(const std::string& str)
{
	if (clipboard.SetData(str))
		{ return true; }
	else
		{ return false; }
}

//===================================================
void ClipboardCopySingleBinaryTotal()
{
	ClipboardCopy(GetEditText(ctlTextBoxSingleBinarySign) + GetEditText(ctlTextBoxSingleBinaryExp) + GetEditText(ctlTextBoxSingleBinaryMantissa));	
}

//===================================================
void ClipboardCopySingleHex()
{
	ClipboardCopy(GetEditText(ctlTextBoxSingleHex));	
}

//===================================================
void ClipboardCopySingleIEEE754()
{
	ClipboardCopy(GetEditText(ctlTextBoxSingleIEEE754));	
}

//===================================================
void ClipboardCopyDoubleBinaryTotal()
{
	ClipboardCopy(GetEditText(ctlTextBoxDoubleBinarySign) + GetEditText(ctlTextBoxDoubleBinaryExp) + GetEditText(ctlTextBoxDoubleBinaryMantissa));	
}

//===================================================
void ClipboardCopyDoubleHex()
{
	ClipboardCopy(GetEditText(ctlTextBoxDoubleHex));	
}

//===================================================
void ClipboardCopyDoubleIEEE754()
{
	ClipboardCopy(GetEditText(ctlTextBoxDoubleIEEE754));	
}

//===================================================
void ClipboardCopyResults()
{
	std::string format = "%Y-%m-%d %H:%M:%S";
	
	if (ClipboardCopy(converter.GetStringResults(datetime.GetCurrentDateTime(format))))
		{ SetWindowText(ctlGroupBoxResults, STR_RESULTS_COPY_OK.c_str()); }
	else
		{ SetWindowText(ctlGroupBoxResults, STR_RESULTS_COPY_FAIL.c_str()); }
}

//===================================================
void FileSaveResults()
{
	std::string format;
	std::string date;
	std::string filename;
	
	format = "%Y-%m-%d_%H-%M-%S";
	date = datetime.GetCurrentDateTime(format);
	filename += date + "__" + converter.results.value + ".txt";
	
	format = "%Y-%m-%d %H:%M:%S";
	date = datetime.GetCurrentDateTime(format);
	std::string results = converter.GetStringResults(date);
	std::replace(results.begin(), results.end(), '\r', ' ');	
	
	if (file.SaveToFile(filename, results))
		{ SetWindowText(ctlGroupBoxResults, STR_RESULTS_SAVE_OK.c_str()); }
	else
		{ SetWindowText(ctlGroupBoxResults, STR_RESULTS_SAVE_FAIL.c_str()); }
}

//===================================================
void ShowInfo()
{
	MessageBox(NULL, STR_APP_ABOUT_TEXT.c_str(), STR_APP_ABOUT.c_str(), MB_OK | MB_ICONINFORMATION);	
}

//===================================================
void ShowHelp()
{
	MessageBox(NULL, STR_APP_HELP_TEXT.c_str(), STR_APP_HELP.c_str(), MB_OK | MB_ICONQUESTION);	
}

//===================================================
void ComboBoxHistoryEntryAdd(const char* entry)
{
    SendMessage(ctlComboBoxHistory, CB_ADDSTRING, 0, (LPARAM)entry);
}

void ComboBoxHistoryEntryRemove(int index)
{
    SendMessage(ctlComboBoxHistory, CB_DELETESTRING, index, 0);
}

void ComboBoxHistoryEntrySelect()
{
	int index = SendMessage(ctlComboBoxHistory, CB_GETCURSEL, 0, 0);
	if (index == CB_ERR)
		{ return; }	
	
	char buffer[BUFFER_STR];
    SendMessage(ctlComboBoxHistory, CB_GETLBTEXT, index, (LPARAM)buffer);
	
	ComboBoxHistoryEntryRemove(index);
	SetWindowText(ctlTextBoxValue, buffer);
	
	Calculate();
	UpdateResults();	
}

//=============================================================================
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
		case WM_CREATE:
			CreateControls(hwnd);
			InitState();
			SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) & ~WS_MAXIMIZEBOX);
			break;
			
		case WM_COMMAND:		
			if (HIWORD(wParam) == BN_CLICKED)
			{
				switch (LOWORD(wParam))
				{					
					case IDC_PUSHBUTTON_CONVERT:
						Calculate();
						UpdateResults();
						break;
						
					case IDC_PUSHBUTTON_COPY_SINGLE_BINARY:
						ClipboardCopySingleBinaryTotal();
						break;
						
					case IDC_PUSHBUTTON_COPY_SINGLE_HEX:
						ClipboardCopySingleHex();
						break;
						
					case IDC_PUSHBUTTON_COPY_SINGLE_IEEE754:
						ClipboardCopySingleIEEE754();
						break;
						
					case IDC_PUSHBUTTON_COPY_DOUBLE_BINARY:
						ClipboardCopyDoubleBinaryTotal();
						break;
						
					case IDC_PUSHBUTTON_COPY_DOUBLE_HEX:
						ClipboardCopyDoubleHex();
						break;
						
					case IDC_PUSHBUTTON_COPY_DOUBLE_IEEE754:
						ClipboardCopyDoubleIEEE754();
						break;						
						
					case IDC_CHECKBOX_EXP_SINGLE:
						isSingleScientificExp = GetCheckboxState(hwnd, IDC_CHECKBOX_EXP_SINGLE);
						UpdateTextboxSingleIEEE754();						
						break;
						
					case IDC_CHECKBOX_EXP_DOUBLE:
						isDoubleScientificExp = GetCheckboxState(hwnd, IDC_CHECKBOX_EXP_DOUBLE);
						UpdateTextboxDoubleIEEE754();						
						break;
						
					case IDC_PUSHBUTTON_HELP:
						ShowHelp();
						break;	
						
					case IDC_PUSHBUTTON_ABOUT:
						ShowInfo();
						break;	
						
					case IDC_PUSHBUTTON_COPY_RESULTS:
						ClipboardCopyResults();
						break;
						
					case IDC_PUSHBUTTON_SAVE_RESULTS:
						FileSaveResults();
						break;						
				}
			}
			
			if (HIWORD(wParam) == CBN_SELCHANGE)
			{
				ComboBoxHistoryEntrySelect();	
			}
			break;
			
		case WM_DESTROY:
			PostQuitMessage(0);
			break; 
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}
//=============================================================================