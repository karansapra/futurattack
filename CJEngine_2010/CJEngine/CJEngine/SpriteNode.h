#pragma once

#include "./SceneNode.h"
#include "./Vector2.h"
#include "./Vector3.h"
#include "./Texture.h"

class SceneGraphManager;
class SpriteNode : public SceneNode
{
	friend class SceneGraphManager;

	Texture * texture_;

protected:
	SpriteNode(void);
	~SpriteNode(void);

public:	
	
	virtual void DrawNode();

	//Properties
	Vector2<float> Size;	
	void AddTexture(const Texture & texture);
};
