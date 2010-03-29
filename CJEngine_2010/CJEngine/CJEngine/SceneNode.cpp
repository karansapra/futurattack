#include "./SceneNode.h"
#include "./Core.h"

SceneNode::SceneNode(void)
{
	PropagateScaling = false;
	Rotation = 0.0f;
	Scale = Vector2<float>(1.0f,1.0f);
	Color = Vector3<float>(1,1,1);
}

SceneNode::~SceneNode(void)
{
	printf("Delete SceneNode\n");

	for (unsigned int i=0;i<ChildrenCount();i++)
		delete (*this)[i];
}

void SceneNode::AddChild(const SceneNode &node)
{
	childen_.push_back((SceneNode*)&node);
}

void SceneNode::RemoveChild(const SceneNode & node)
{
	childen_.erase(std::remove(childen_.begin(),childen_.end(),&node),childen_.end());
}

unsigned int SceneNode::ChildrenCount()
{
	return childen_.size();
}

SceneNode * SceneNode::operator[](int i)
{
	return childen_[i];
}

void SceneNode::DrawNode()
{
}

void SceneNode::Render()
{
	glPushMatrix();

	glTranslatef(Translation.X,Translation.Y,0.0f);
	glRotatef(Rotation,0.0f,0.0f,1.0f);
	if (!PropagateScaling)
	{
		glPushMatrix();
		glScalef(Scale.X,Scale.Y,1.0f);
		DrawNode();
		glPopMatrix();	
	}
	else
	{
		glScalef(Scale.X,Scale.Y,1.0f);
		DrawNode();
	}

	

	for (unsigned int i=0;i<ChildrenCount();i++)
		(*this)[i]->Render();

	glPopMatrix();
}