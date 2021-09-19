/********************************************************************************
*                                                                               *
*                             Regular Expression Test                           *
*                                                                               *
*********************************************************************************
* Copyright (C) 1999,2009 by Jeroen van der Zijp.   All Rights Reserved.        *
********************************************************************************/
#include "fx.h"


/*


*/

#define NCAP 1    // Must be less that or equal to 10


/*******************************************************************************/


// Start the whole thing
int main(){
  FXRex::Error err;
  FXRex rex;
  FXbool ok;
  FXint i;
  FXint beg[NCAP];
  FXint end[NCAP];
  fxTraceLevel=101;

	const int MatchCount = 4;
	FXString Match[MatchCount];

	Match[0]="\\{\\{MusicRoom(?!/Cmt)";
	Match[1]="\\{\\{M.sicRoom/Cmt.*?\\}\\}";
	Match[2]="\\{\\{lang\\|.*?\\|";
	Match[3]="\n:";

  FXString Source(L"{{MusicRoom/CD\n"
L"|category=#01\n"
L"|title   =[[Lyrics: 童祭　～ Innocent Treasures|童祭　～ Innocent Treasures]]\n"
L"|titleEN =Kid's Festival ~ Innocent Treasures\n"
L"}}{{MusicRoom/Cmt\n"
L":::|ja=\n"
L":夢違え、幻の朝靄の世界の記憶を<br/>\n"
L":現し世は、崩れゆく砂の上に<br/>\n"
L":空夢の、古の幽玄の世界の歴史を<br/>\n"
L":白日は、沈みゆく街に\n"
L"|en=\n"
L":Being awaken, with a memory of morning mist in an illusionary world.<br/>\n"
L":Reality, on a vanishing cloud.<br/>\n"
L":Daydream, a history of an ancient mystic world.<br/>\n"
L":Daylight, into a vanishing town.\n"
L"}}{{MusicRoom/Cmt\n"
L"|ja={{lang|ja|\n"
L"（夜が明ける。幻の朝靄の中で夜が明ける。<br/>\n"
L"私は幻想の世界で子供達と一緒に遊んでいたわ。<br/>\n"
L"子供達はみんな楽しそうだった。みんな笑っていた）}}\n"
L"|en={{lang|en|\n"
L"''(Dawn is about to come. Dawn is about to come in an illusionary morning mist.''<br/>\n"
L"''I had a good time with the kids in an illusionary world.''<br/>\n"
L"''All of the kids looked really happy and smiled.)}}''\n"
L"}}{{MusicRoom/Cmt\n"
L"|ja=\n"
L":幻か、砂上の楼閣なのか<br/>\n"
L":夜明け迄、この夢、胡蝶の夢\n"
L"|en=\n"
L":Is it an illusion, or a castle in the air?<br/>\n"
L":Till daybreak, my heart is in another world.\n"
L"}}{{MusicRoom/Cmt\n"
L"|ja=\n"
L"（――こんなに笑っている子供を最後に見たのは一体いつだろう。<br/>\n"
L"聴いた事もない不思議な唄、不思議な踊り。どうやら今日は祭らしい。<br/>\n"
L"私も、いつかはこんな子供達の笑顔がある国に住みたいと思ったわ）\n"
L"|en=\n"
L"''(...I cannot remember the last time I saw kids with this a big of a smile.''<br/>\n"
L"''Mysterious songs that I've never listened to; Mysterious dances that I've never seen. Maybe a festival is being held today.''<br/>\n"
L"''Someday, I want to live in such a country where I can see the kids smile.)''\n"
L"}}{{MusicRoom/Cmt\n"
L"|ja=\n"
L":夢違え、幻の紅の屋{{nesttest}}敷の異彩を<br/>\n"
L":現し世は、血の気無い石の上に<br/>\n"
L":空夢の、古の美しき都のお伽を<br/>\n"
L":白日は、穢れゆく街に\n"
L"|en=\n"
L":Being awaken, with a memory of an illusionary scarlet mansion in its strange color.<br/>\n"
L":Reality, on a cold-hearted stone.<br/>\n"
L":Daydream, a fairy tale of an ancient beautiful capital.<br/>\n"
L":Daylight, into a filthy town.}}\n"
L"|}");

  for(int c = 0; c < MatchCount; c++)
  {
	  fprintf(stderr, "match #%d\n", c+1);
	  err=rex.parse(Match[c],FXRex::Normal|FXRex::Capture|FXRex::IgnoreCase|FXRex::Newline);
	  fprintf(stderr,"parse(\"%s\") = %s\n\n",Match[c],FXRex::getError(err));

	  int m = 0;

	  // while(rex.match(Source.mid(m, Source.length() - m),beg,end,FXRex::Forward,NCAP))
	  while(rex.match(Source,beg,end,FXRex::Forward,NCAP,m))
	  {
	   fprintf(stderr,"match at %d:%d\n",beg[0],end[0]);
		for(i=1; i<NCAP; i++)
		{
		  fprintf(stderr,"capture at %d:%d\n",beg[i],end[i]);
		  }
		for(i=beg[0]; i<end[0]; i++)
		{
		  fprintf(stderr,"%c",Source[i]);
		  }
		fprintf(stderr,"\n");
		m += end[0];
	  }
  }
  return 1;
  }

