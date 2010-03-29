#pragma once

#include "./SceneNode.h"
#include "./SpriteNode.h"
#include "./TextNode.h"

class SceneGraphManager
{
	SceneNode * root_node_;

public:
	SceneGraphManager(void);
	~SceneGraphManager(void);

	SpriteNode * AddSpriteNode();
	SpriteNode * AddSpriteNode(SceneNode & parent);

	TextNode * AddTextNode();
	TextNode * AddTextNode(SceneNode & parent);

	void RemoveNode(SceneNode * node);

	void RenderAllGraph();
};

