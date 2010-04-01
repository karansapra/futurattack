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

protected:
	SpriteNode(void);
	~SpriteNode(void);

public:	
	
	virtual void BeginRealization();

	//Properties
	Vector2<float> Size;	
	Vector2<float> TexCoord_TopLeft;
	Vector2<float> TexCoord_BottomRight;
	void AddTexture(const Texture & texture);
	bool Visible;
};
