#pragma once

#include "./SceneNode.h"
#include "./Vector2.h"
#include "./Vector3.h"
#include "./Texture.h"
#include "./FX.h"

class SceneGraphManager;
class SpriteNode : public SceneNode
{
	friend class SceneGraphManager;

	Texture * texture_;
	FX * fx_;

protected:
	SpriteNode(void);
	~SpriteNode(void);

public:	
	
	virtual void DrawNode();

	//Properties
	Vector2<float> Size;	
	void AddTexture(const Texture & texture);
	void AddEffect(const FX & fx);
	bool Visible;
};
