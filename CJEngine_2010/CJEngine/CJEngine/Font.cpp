#include "./Font.h"
#include "./Core.h"
#include "./CJEngine.h"

Font::Font(const char * fontname, int size)
{
	HDC hdc = GetDC(CJEngine::instance_->window_handle_);

	HFONT hfont;
	LOGFONT logfont;
	ZeroMemory(&logfont,sizeof(LOGFONT));
	logfont.lfHeight = -size;
	logfont.lfCharSet = ANSI_CHARSET;
	strcpy_s(logfont.lfFaceName,32,fontname);
	hfont = CreateFontIndirect(&logfont);
	SelectObject(hdc,hfont);
	gllist = glGenLists(128);
	wglUseFontBitmaps(hdc,0,128,gllist);
	DeleteObject(hfont);
}

Font::~Font(void)
{
}
