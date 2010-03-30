#include "./SpriteNode.h"
#include "./Core.h"

SpriteNode::SpriteNode(void)
{
	Size = Vector2<float>(20,20);
	texture_ = NULL;
	fx_ = NULL;
	Visible = true;
}

SpriteNode::~SpriteNode(void)
{
}

void SpriteNode::DrawNode()
{
	if (!Visible)
		return;

	if (fx_!=NULL)
		fx_->Enable();

	if (texture_!=NULL)
	{
		glEnable(GL_ALPHA);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
		glDisable(GL_DEPTH_TEST);
		glEnable(GL_TEXTURE_2D);


		glBindTexture(GL_TEXTURE_2D,texture_->gltexture_id_);		
		glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE );
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);
	}
	else
	{
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
	}

	glBegin(GL_QUADS);
	glColor4f(Color.X,Color.Y,Color.Z,1.0f);
	
	glTexCoord2f(0.0f,1.0f);
	glVertex2f(-Size.X/2,-Size.Y/2);
	
	glTexCoord2f(0.0f,0.0f);
	glVertex2f(-Size.X/2,Size.Y/2);
	
	glTexCoord2f(1.0f,0.0f);
	glVertex2f(Size.X/2,Size.Y/2);

	glTexCoord2f(1.0f,1.0f);
	glVertex2f(Size.X/2,-Size.Y/2);

	glEnd();

	if (fx_!=NULL)
		fx_->Disable();

	/*
	glBegin(GL_LINES);
	glColor3d(1.0,0.0,0.0);
	glVertex2d(0,0);
	glVertex2d(20,0);
	glColor3d(0.0,0.0,1.0);
	glVertex2d(0,0);
	glVertex2d(0,20);
	glEnd();	
	*/
}

void SpriteNode::AddTexture(const Texture & texture)
{
	texture_ = (Texture*)&texture;
}

void SpriteNode::AddEffect(const FX & fx)
{
	fx_ = (FX*)&fx;
}