#include "./SceneGraphManager.h"
#include "./CJEngine.h"

SceneGraphManager::SceneGraphManager(void)
{
	root_node_ = new SceneNode();
}

SceneGraphManager::~SceneGraphManager(void)
{
	delete root_node_;
}

SpriteNode * SceneGraphManager::AddSpriteNode()
{
	SpriteNode * node = new SpriteNode();
	root_node_->AddChild(*node);
	return node;
}

SpriteNode * SceneGraphManager::AddSpriteNode(SceneNode & parent)
{
	SpriteNode * node = new SpriteNode();
	parent.AddChild(*node);
	return node;
}

TextNode * SceneGraphManager::AddTextNode()
{
	TextNode * node = new TextNode(*CJEngine::instance_->GetBuiltInFont());
	root_node_->AddChild(*node);
	return node;
}

TextNode * SceneGraphManager::AddTextNode(SceneNode & parent)
{
	TextNode * node = new TextNode(*CJEngine::instance_->GetBuiltInFont());
	parent.AddChild(*node);
	return node;
}

void SceneGraphManager::RenderAllGraph()
{
	root_node_->Render();
}

void Rm(SceneNode * node, SceneNode * parent)
{
	if (parent!=node)
	{
		for (unsigned int i=0;i<parent->ChildrenCount();i++)
		{
			Rm(node,(*parent)[i]);
		}
	}
	else
	{
		
	}
}

void SceneGraphManager::RemoveNode(SceneNode * node)
{
	root_node_->RemoveChild(*node);
}