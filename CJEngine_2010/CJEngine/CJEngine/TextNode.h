#pragma once

#include "./SceneNode.h"
#include "./Font.h"

class SceneGraphManager;
class TextNode : public SceneNode
{
	friend class SceneGraphManager;

	char text_[512];
	Font * font_;

protected:
	TextNode(const Font & font);
	~TextNode(void);

public:
	virtual void DrawNode();

	void SetText(const char * text);
};
