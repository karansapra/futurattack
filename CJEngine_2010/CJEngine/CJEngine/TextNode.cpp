#include "./TextNode.h"
#include "./Core.h"
#include "./CJEngine.h"

TextNode::TextNode(const Font & font)
{
	font_ = (Font*)&font;
	strcpy_s(text_,512,"Default text");
}

TextNode::~TextNode(void)
{

}

void TextNode::BeginRealization()
{
	glColor3f(Color.X,Color.Y,Color.Z);
	glRasterPos2i(0,0);	
	glListBase(font_->gllist);
	glCallLists(strlen(text_),GL_UNSIGNED_BYTE,text_);
}

void TextNode::SetText(const char * text)
{
	strcpy_s(text_,512,text);
}