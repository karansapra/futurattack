#pragma once

#include "./SceneNode.h"
#include "./FX.h"

class SceneGraphManager;
class EffectNode : SceneNode
{
	friend class SceneGraphManager;

	FX * fx_;

protected:
	EffectNode(void);
	~EffectNode(void);

public:
	void BeginRealization();
	void EndRealization();
	void SetEffect(const FX & fx);
};
