// Music Room Interface
// --------------------
// musicroom.cpp - Main starting code
// --------------------
// "¨Ï" Nmlgc, 2010-2011

#include "musicroom.h"
#include <math.h>
#include <fx.h>
#include "mainwnd.h"
#include <bgmlib/config.h>
#include <bgmlib/bgmlib.h>
#include <th_tool_shared/utils.h>
#include <locale.h>

#ifdef PROFILING_LIBS
LARGE_INTEGER operator - (const LARGE_INTEGER& a, const LARGE_INTEGER& b)	{LARGE_INTEGER r; r.QuadPart = a.QuadPart - b.QuadPart; return r;}
LARGE_INTEGER operator + (const LARGE_INTEGER& a, const LARGE_INTEGER& b)	{LARGE_INTEGER r; r.QuadPart = a.QuadPart + b.QuadPart; return r;}
#endif

FILE _iob[] = { *stdin, *stdout, *stderr };

extern "C" FILE * __cdecl __iob_func(void)
{
	return _iob;
}

bool ReadConfig(ConfigFile* Cfg);
void SetupPM();

// Globals
// =======

ConfigFile MainCFG;
ConfigParser* LGD;	// Local Game Directory section in [LGDFile]

// GUI
// ---
MainWnd* MWBack;	// Back end GUI class
bool Play;	// Play selected track?
ushort FadeAlgID = 0;	// Fade algorithm
bool SilRem = true;	// Remove opening silence?
bool RemEnabled = true;
bool SilResolve() { return SilRem && RemEnabled; }
int Volume = 100;
// ---

// Game
// ----
GameInfo* ActiveGame = NULL;
// ----

// [update]
// --------
bool WikiUpdate;
FXString WikiURL;
// --------

// Encoders
// --------
List<Encoder*> Encoders;
FXushort EncFmt;
bool ShowConsole; // Show encoding console during the process
// --------

ushort LoopCnt;	// Song loop count (2 = song gets repeated once)
float FadeDur;	// Fade duration
FXString AppPath;
FXString OutPath;	// Output directory

// =======

// String Constants
      FXString PrgName = L"¹ÂÁ÷ ·ë ÀÎÅÍÆäÀÌ½º";
	  FXString WebPage = "http://bit.ly/musicroom_interface";
const FXString PrgVer = "v2.2";
const FXString NoGame = L"(·ÎµåÇÑ °ÔÀÓ ¾øÀ½)";
      FXString CfgFile = "musicroom.cfg";
	  FXString LGDFile = "gamedirs.cfg";
const FXString Example = L"¿¹½Ã: ";
const FXString DumpFile = "extract";
const FXString DecodeFile = DumpFile + ".raw";
      FXString OggDumpFile = "decode.ogg";
	  FXString OggPlayFile = "play.ogg";
const FXString Cmp[LANG_COUNT] = {L"íÂÍØíº", "Composer", L"ÀÛ°î°¡"};

extern const unsigned char ICON_AKYU[];

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "");

	//memset((void *)0x000013FC, 0x00000000, 1);

	FXIcon* AppIcon;

	SetupPM();

	// Setup directories
	// -----------------
	AppPath = CorrectAppPath(argv[0]);
	
	OggDumpFile.prepend(FXSystem::getTempDirectory() + SlashString);
	OggPlayFile.prepend(FXSystem::getTempDirectory() + SlashString);
	CfgFile.prepend(AppPath);
	LGDFile.prepend(AppPath);
	// -----------------

	// Read config files
	// -----------------
	ConfigFile MainCFG(CfgFile);
	ReadConfig(&MainCFG);

	ConfigFile LocalGameDir(LGDFile);
	LocalGameDir.Load();
	LGD = LocalGameDir.CheckSection("gamedirs");
	// -----------------

	FXApp App(PrgName, "Nmlgc");
	App.init(argc, argv);

	PrgName += " " + PrgVer;

	AppIcon = new FXICOIcon(&App, ICON_AKYU);

	MWBack = new MainWnd(&App, AppIcon);
	MW = &MainWndFront::Inst();
	App.create();

	MWBack->show(PLACEMENT_SCREEN);

	if(argc > 1)	MWBack->handle(NULL, FXSEL(SEL_COMMAND, MainWnd::MW_LOAD_GAME), argv[1]);

	FXint Ret = App.run();

	// -------
	// Cleanup
	// -------

	LocalGameDir.Save();
	LocalGameDir.Clear();

	MainCFG.Save();
	MainCFG.Clear();

	// Clear encoders
	ListEntry<Encoder*>* CurEnc = Encoders.First();
	while(CurEnc)
	{
		SAFE_DELETE(CurEnc->Data);
		CurEnc = CurEnc->Next();
	}
	Encoders.Clear();

	MW->Clear();

	BGMLib::Clear();

	SAFE_DELETE(AppIcon);

#ifdef WIN32
#ifdef _DEBUG
	_CrtDumpMemoryLeaks();
#endif
#endif
	return Ret;
}
