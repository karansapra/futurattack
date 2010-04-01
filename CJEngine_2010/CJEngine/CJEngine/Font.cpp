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
	
	if (hfont==NULL)
		throw Exception("Font::Font : Can't create font");
	
	SelectObject(hdc,hfont);
	gllist = glGenLists(128);

	if (gllist==0)
		throw Exception("Font::Font : Can't create font");

	wglUseFontBitmaps(hdc,0,128,gllist);
	DeleteObject(hfont);
}

Font::~Font(void)
{
	if (gllist!=0)
		glDeleteLists(gllist,128);
}
