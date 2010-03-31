#include "./EffectNode.h"


EffectNode::EffectNode(void)
{
}

EffectNode::~EffectNode(void)
{
}

void EffectNode::BeginRealization()
{
	if (fx_)
		fx_->Enable();
}

void EffectNode::EndRealization()
{
	if (fx_)
		fx_->Disable();
}

void EffectNode::SetEffect(const FX & fx)
{
	fx_ = (FX*)&fx;
}