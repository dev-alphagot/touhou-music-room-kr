// Music Room Interface
// --------------------
// enc_custom.cpp - External encoding
// --------------------
// "? Nmlgc, 2011

#include "musicroom.h"
#include <bgmlib/ui.h>
#include <bgmlib/list.h>
#include <bgmlib/config.h>

#include <FXHash.h>
#include <FXStream.h>
#include <FXFont.h>
#include <FXHorizontalFrame.h>
#include <FXVerticalFrame.h>
#include <FXGroupBox.h>
#include <FXLabel.h>
#include <FXTextField.h>
#include <FXStat.h>
#include <FXThread.h>
#include <FXMessageBox.h>

#include <FXIO.h>
#include <FXFile.h>

#include "extract.h"
#include "enc_custom.h"

#ifdef WIN32
#include <wchar.h>
#include <windows.h>
static PROCESS_INFORMATION ProcInf;
#endif

// Settings
// --------
void Encoder_Custom::DlgCreate(FXVerticalFrame* Frame, FXDialogBox* Target, const FXuint& Msg)
{
	FXGroupBox* HelpBox;
		FXLabel* HelpLabel;
	
	FXGroupBox* CLBox;
	FXHorizontalFrame* CLFrame;
		FXVerticalFrame* ExeFrame;
		FXVerticalFrame* OptFrame;
		
	if(!Help.empty())
	{
	HelpBox = new FXGroupBox(Frame, L"도움말", GROUPBOX_NORMAL | FRAME_GROOVE | LAYOUT_FILL_X);
		HelpLabel = new FXLabel(HelpBox, Help, NULL, JUSTIFY_LEFT);
		HelpLabel->setFont(Monospace);
		new FXLabel(HelpBox, L"더 많은 옵션이 궁금하다면, 인코더 실행 파일을 명령 프롬프트에서 실행시켜보세요.");
	}
		
	CLBox = new FXGroupBox(Frame, L"명령줄", GROUPBOX_NORMAL | FRAME_GROOVE | LAYOUT_FILL_X | LAYOUT_BOTTOM);
	CLFrame = new FXHorizontalFrame(CLBox, LAYOUT_FILL);
		ExeFrame = new FXVerticalFrame(CLFrame, LAYOUT_FILL_Y);
		OptFrame = new FXVerticalFrame(CLFrame, LAYOUT_FILL);

		new FXLabel(ExeFrame, L"실행 파일: ");
		new FXLabel(OptFrame, L"옵션: ");

		Cmd[0] = new FXTextField(ExeFrame, 15);	Cmd[0]->setText(CmdLine[0]);
		Cmd[1] = new FXTextField(OptFrame, 30, NULL, 0, TEXTFIELD_NORMAL | LAYOUT_FILL_X);	Cmd[1]->setText(CmdLine[1]);
}

bool Encoder_Custom::DlgApply(FXDialogBox* Parent)
{
	FXString NewEnc = Cmd[0]->getText();
	FXString Str;

	if(NewEnc != CmdLine[0])
	{
		// Check if encoder executable is present
		if(!FXStat::exists(NewEnc))
		{
			FXMessageBox::error((FXWindow*)MW->MW, MBOX_OK, PrgName.text(), "%s!", NewEnc + L"(을)를 찾을 수 없습니다.");
			return false;
		}
	}

	CmdLine[0] = NewEnc;
	CmdLine[1] = Cmd[1]->getText();
	return true;
}
// --------

void Encoder_Custom::FmtReadConfig(ConfigParser* Sect)
{
	Sect->GetValue("help", TYPE_STRING, &Help);
	Sect->LinkValue("encoder", TYPE_STRING, &CmdLine[0]);
	Sect->LinkValue("options", TYPE_STRING, &CmdLine[1]);
}

bool Encoder::Extract_Default(TrackInfo* TI, FXString& EncFN, GameInfo* GI, Extract_Vals& V)
{
	Extractor& Ext = Extractor::Inst();
	FXString Str;
		
	Str.format("%s...", V.DisplayFN + L" 생성 중");
	BGMLib::UI_Stat_Safe(Str);

	V.Init(TI, FMT_BYTE);

	// load/decode source file
	if(!Ext.PrepareInput(TI, GI, V))	return false;

	FXString& DumpFN = Ext.BuildPCM(TI, V);
	V.In.close();
	if(StopReq)	return StopReq = false;

	// Encode
	BGMLib::UI_Stat_Safe(L"인코딩 중...");

	if(!Encode(EncFN, DumpFN, V))
	{
		if(*V.Ret != 0)	*V.Ret = MBOX_CLICKED_CANCEL;
		return false;
	}
	return true;
}

bool Encoder_Custom::Extract(TrackInfo *TI, FX::FXString &EncFN, GameInfo *GI, Extract_Vals &V)
{
	V.TagEngine = true;
	return Extract_Default(TI, EncFN, GI, V);
}

bool Encoder_Custom::Encode(const FXString& DestFN, const FXString& SrcFN, Extract_Vals& V)
{
	FXString Str, Cmd;

	Cmd.format("%s%s", AppPath, CmdLine[0].text());
	Str.format("%s %s \"%s\" \"%s\"", CmdLine[1], CmdLine[1], SrcFN, DestFN);
#ifdef WIN32
	// Yes, we have to use this for Unicode compliance!

	STARTUPINFO SI;
	ZeroMemory(&SI, sizeof(STARTUPINFO));
	SI.cb = sizeof(STARTUPINFO);
	SI.dwFlags = STARTF_USESHOWWINDOW;
	SI.wShowWindow = SW_SHOWNOACTIVATE;
	ZeroMemory(&ProcInf, sizeof(PROCESS_INFORMATION));

	wchar_t* CmdW = new FXnchar[Cmd.length() + 1];
	wchar_t* StrW = new FXnchar[Str.length() + 1];

	utf2ncs(CmdW, Cmd.length() + 1, Cmd.text(), Cmd.length() + 1);
	utf2ncs(StrW, Str.length() + 1, Str.text(), Str.length() + 1);

	DWORD Flags = 0;//CREATE_NEW_PROCESS_GROUP;
	if(!ShowConsole)	Flags |= DETACHED_PROCESS;

	BOOL r = CreateProcessW(CmdW, StrW, NULL, NULL, true, Flags, NULL, NULL, &SI, &ProcInf);

	SAFE_DELETE_ARRAY(CmdW);
	SAFE_DELETE_ARRAY(StrW);

	if(!r)
	{
		Str.format("\n%s\n", CmdLine[0] + L"을(를) 실행할 수 없습니다!\n설치한 폴더에 파일이 존재하는 지 확인하시고,\n인코더 설정을 바꿔주세요.");
		BGMLib::UI_Error_Safe(Str);
		return false;
	}
#else
	system(Str.text());
#endif
	// ------

	Ret = true;
	WaitForSingleObject(ProcInf.hProcess, INFINITE);
	
	ZeroMemory(&ProcInf, sizeof(PROCESS_INFORMATION));

	return Ret;	// may be changed by FmtStop
}

// Yay, how stupid.
static BOOL CALLBACK EnumWndProc(HWND HWnd, LPARAM lParam)
{
	wchar_t Str[MAX_PATH];
	GetWindowText(HWnd, Str, MAX_PATH);

	const FXString& Cmd = *((FXString*)lParam);
	FXString Test = Str;
	if(Test.contains(Cmd))
	{
		SendMessage(HWnd, WM_QUIT, 0, 0);
		SendMessage(HWnd, WM_CLOSE, 0, 0);
		SendMessage(HWnd, WM_DESTROY, 0, 0);
		return false;
	}
	return true;
}

FXString Encoder_Custom::Init(GameInfo* GI)
{
	FXString Ret;
	Ret.format("%s %s\n", L"명령줄: " + CmdLine[0], CmdLine[1]);
	if(GI->Vorbis)
	{
		Ret.append(L"경고: ");
		if(this->Lossless)	Ret.append(L"무손실 코덱에서 ");
		else				Ret.append(L"손실 코덱으로 ");
		Ret.append(L"인코딩을 시도학고 있습니다.\n");
	}
	return Ret;
}

void Encoder_Custom::FmtStop()
{
	if(ProcInf.hProcess != 0)
	{
		Ret = false;
		HWND EncWnd = NULL;
		EnumWindows(EnumWndProc, (LPARAM)&CmdLine[0]);
		if(EncWnd)
		{
			SendMessage(EncWnd, WM_QUIT, 0, 0);
			SendMessage(EncWnd, WM_CLOSE, 0, 0);
			SendMessage(EncWnd, WM_DESTROY, 0, 0);
		}
	}
	else	while(StopReq)	FXThread::sleep(TIMEOUT);
}

Encoder_Custom::~Encoder_Custom()
{
	CmdLine[0].clear();
	CmdLine[1].clear();
	Help.clear();
}
