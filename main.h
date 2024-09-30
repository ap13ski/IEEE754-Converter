#ifndef MAIN_H
#define MAIN_H
//#############################################################################


#include <windows.h>
#include <commctrl.h>
#include "converter.h"
#include "clipboard.h"
#include "time.h"
#include "file.h"

#include "resources.h"

#pragma comment(lib, "comctl32.lib")

//=============================================================================
HWND ctlGroupBoxValue;
HWND ctlTextBoxValue;
HWND ctlPushButtonConvert;
HWND ctlLabelValue;

HWND ctlGroupBoxSingle;
HWND ctlTextBoxSingleBinarySign;
HWND ctlTextBoxSingleBinaryExp;
HWND ctlTextBoxSingleBinaryMantissa;
HWND ctlTextBoxSingleHex;
HWND ctlTextBoxSingleIEEE754;
HWND ctlCheckBoxExpSingle;
HWND ctlPushButtonCopySingleBinary;
HWND ctlPushButtonCopySingleHex;
HWND ctlPushButtonCopySingleIEEE754;
HWND ctlLabelSingleBinarySign;
HWND ctlLabelSingleBinaryExp;
HWND ctlLabelSingleBinaryMantissa;
HWND ctlLabelSingleHex;
HWND ctlLabelSingleIEEE754;

HWND ctlGroupBoxDouble;
HWND ctlTextBoxDoubleBinarySign;
HWND ctlTextBoxDoubleBinaryExp;
HWND ctlTextBoxDoubleBinaryMantissa;
HWND ctlTextBoxDoubleHex;
HWND ctlTextBoxDoubleIEEE754;
HWND ctlCheckBoxExpDouble;
HWND ctlPushButtonCopyDoubleBinary;
HWND ctlPushButtonCopyDoubleHex;
HWND ctlPushButtonCopyDoubleIEEE754;
HWND ctlLabelDoubleBinarySign;
HWND ctlLabelDoubleBinaryExp;
HWND ctlLabelDoubleBinaryMantissa;
HWND ctlLabelDoubleHex;
HWND ctlLabelDoubleIEEE754;

HWND ctlGroupBoxResults;
HWND ctlPushButtonCopyResults;
HWND ctlPushButtonSaveResults;

HWND ctlGroupBoxInfo;
HWND ctlPushButtonHelp;
HWND ctlPushButtonAbout;

HWND ctlGroupBoxHistory;
HWND ctlComboBoxHistory;

NS_IEEE754::Converter converter;
NS_CLIPBOARD::Clipboard clipboard;
NS_TIME::DateTime datetime;
NS_FILE::File file;

HFONT hFontNormal;
HFONT hFontBold;

bool isSingleScientificExp;
bool isDoubleScientificExp;

//=============================================================================
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void CreateControls(const HWND& hwnd);
void Calculate();
void UpdateResults();

void UpdateTextboxSingleIEEE754();
void UpdateTextboxDoubleIEEE754();
bool GetCheckboxState(const HWND& hwnd, int buttonID);
std::string GetEditText(const HWND& hEdit);

bool ClipboardCopy(const std::string& str);
void ClipboardCopySingleBinaryTotal();
void ClipboardCopySingleHex();
void ClipboardCopySingleIEEE754();
void ClipboardCopyDoubleBinaryTotal();
void ClipboardCopyDoubleHex();
void ClipboardCopyDoubleIEEE754();
void ClipboardCopyResults();
void FileSaveResults();
void ShowInfo();
void ShowHelp();
void ComboBoxHistoryEntryAdd(const char* entry);
void ComboBoxHistoryEntryRemove(int index);
void ComboBoxHistoryEntrySelect();

void CreateFontCustom(HFONT& hFont, int fnWeight);
void UpdateFont(HWND& hControl, HFONT& hFont);
void UpdateFonts();
void InitState();

//=============================================================================


//#############################################################################
#endif