#pragma once

#include <vector>
#include <algorithm>
#include "./Vector2.h"
#include "./Vector3.h"

class SceneNode;
typedef std::vector<SceneNode*> SceneNodePtrList;
typedef SceneNodePtrList::iterator SceneNodePtrListIterator;

class SceneGraphManager;
class SceneNode
{
	friend class SceneGraphManager;

protected:
	SceneNodePtrList childen_;
	SceneNode(void);

public:	
	virtual ~SceneNode(void);

	void AddChild(const SceneNode & node);
	void RemoveChild(const SceneNode & node);
	unsigned int ChildrenCount();
	SceneNode * operator[](int i);	
	
	void Render();
	virtual void DrawNode();

	//Properties
	bool PropagateScaling;
	Vector2<float> Translation;
	Vector2<float> Scale;
	float Rotation;
	Vector3<float> Color;
};
