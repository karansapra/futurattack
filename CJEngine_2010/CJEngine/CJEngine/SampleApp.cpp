#include <math.h>
#include "./CJEngine.h"

class App : public IEventListener
{
	CJEngine * engine;
	SceneGraphManager * sgm;
	ResourceManager * rsm;

	SpriteNode * NWall;
	SpriteNode * SWall;
	SpriteNode * Ball;
	SpriteNode * LBox;
	SpriteNode * RBox;

	TextNode * Score;
	TextNode * Time;
	EffectNode * Effect;

	//Contains all sprites
	Texture * sprites_texture;
	Texture * horz_texture;

	FX * blur;
	
	Vector2<float> ball_speed;

	float box_size;

	int human_score;
	int cpu_score;

	enum STATE {PAUSE, GAME, ENTERPAUSE, FINISHED};
	STATE State;
	float dt;

public:
	void BallPhysics()
	{
		Ball->Rotation += 25;
		Ball->Translation += ball_speed *dt;
		
		if (Ball->Translation.Y>250)
		{
			Ball->Translation.Y = 250;
			ball_speed.Y = -ball_speed.Y;
		} else if(Ball->Translation.Y<-250)
		{
			Ball->Translation.Y = -250;
			ball_speed.Y = -ball_speed.Y;
		}

		if (Ball->Translation.X>330)
		{
			if ((Ball->Translation-RBox->Translation).Abs2()<(box_size+20)*(box_size+20)/4)
			{
				//IA touches the ball
				Ball->Translation.X=330;
				ball_speed.X = -ball_speed.X;
				cpu_score++;
			} else
			{
				//IA misses the ball
				Ball->Translation = Vector2<float>(0,150.0f*engine->GetRandomNumber());
				ball_speed = ball_speed*-1;
				human_score+=5;
				//Winner->Visible = true;
				State = ENTERPAUSE;
			}
		} else
		if (Ball->Translation.X<-330)
		{
			if ((Ball->Translation-LBox->Translation).Abs2()<(box_size+20)*(box_size+20)/4)
			{
				//Human touches the ball
				Ball->Translation.X=-330;
				ball_speed.X = -ball_speed.X;
				human_score++;
			} else
			{
				//Human misses the ball
				Ball->Translation = Vector2<float>(0,150.0f*engine->GetRandomNumber());
				ball_speed = ball_speed*-1;
				cpu_score+=5;
				//Looser->Visible = true;
				State = ENTERPAUSE;
			}
		}

	}

	void IA()
	{
		static unsigned int i = (unsigned int)((engine->GetRandomNumber()+2.2)*2);
		i--;
		if (i!=0)
			return;
		
		i = (unsigned int)((engine->GetRandomNumber()+2.2)*1.3);

		if ((Ball->Translation-RBox->Translation).Abs2()>150000 || (Ball->Translation-RBox->Translation).Abs2()<2000)
			return;
		
		float dy = RBox->Translation.Y - (Ball->Translation-ball_speed*dt).Y;
		if (dy>0)
		{
			if (RBox->Translation.Y>-(250-(box_size)/2))
			{
				RBox->Translation.Y-=650*dt;
			}
		}
		else
		{
			if (RBox->Translation.Y<(250-(box_size)/2))
			{
				RBox->Translation.Y+=650*dt;
			}
		}
	}

	void Animation()
	{
		double t = engine->GetElapsedTime();
	}

	void GameplayFSM()
	{		
		static double t0 = engine->GetElapsedTime();
		static float t = (float)engine->GetElapsedTime();
		float nt = (float)engine->GetElapsedTime();
		dt = nt-t;
		t = nt;

		Animation();

		switch (State)
		{
		case PAUSE:
			if (t0+1<engine->GetElapsedTime())
				State = GAME;
			break;

		case GAME:
			BallPhysics();
			IA();
			break;

		case ENTERPAUSE:
			t0 = engine->GetElapsedTime();
			if (box_size<40)
				State = FINISHED;
			else
				State = PAUSE;			
			
			break;

		case FINISHED:
			break;

		default:
			break;
		}

	}

	App()
	{
		box_size = 100;
		State = PAUSE;

		engine = CJEngine::Instance();
		engine->Init();
		engine->RegisterEventListener(*this);
		sgm = engine->GetSceneGraphManager();
		rsm = engine->GetResourceManager();

		/*
		Textures
		*/
		sprites_texture = rsm->AddTexture("./sprites.png");
		horz_texture = rsm->AddTexture("./horz.png");

		/*
		FX Shaders
		*/
		blur = rsm->AddEffect("blur.vert","blur.frag");

		Effect = sgm->AddEffectNode();
		Effect->SetEffect(*blur);

		NWall = sgm->AddSpriteNode();
		NWall->TexCoord_TopLeft = Vector2<float>(0.0f,0.97f);
		NWall->TexCoord_BottomRight = Vector2<float>(1.0f,1.0f);

		SWall = sgm->AddSpriteNode();		
		SWall->TexCoord_TopLeft = Vector2<float>(0.0f,0.97f);
		SWall->TexCoord_BottomRight = Vector2<float>(1.0f,1.0f);

		//Ball = sgm->AddSpriteNode((SceneNode&)*Effect);
		Ball = sgm->AddSpriteNode();
		Ball->TexCoord_TopLeft = Vector2<float>(0.0f,0.75f);
		Ball->TexCoord_BottomRight = Vector2<float>(0.25f,1.0f);
		
		
		LBox = sgm->AddSpriteNode();
		LBox->TexCoord_TopLeft = Vector2<float>(0.25f,0.0f);
		LBox->TexCoord_BottomRight = Vector2<float>(0.5f,1.0f);		

		RBox = sgm->AddSpriteNode();
		RBox->TexCoord_BottomRight = Vector2<float>(0.25f,0.0f);
		RBox->TexCoord_TopLeft = Vector2<float>(0.5f,1.0f);		

	
		Score = sgm->AddTextNode();
		Time = sgm->AddTextNode();
		
		NWall->Translation.Y = 270;		
		NWall->Size.X = 700;
		SWall->Translation.Y = -270;
		SWall->Size.X = 700;

		LBox->Translation.X = -350;
		LBox->Size.Y = box_size;
		RBox->Translation.X = 350;
		RBox->Size.Y = box_size;

		Time->Translation.X = -350;
		Time->Translation.Y = 285;

		Score->Translation.X = -200;
		Score->Translation.Y = 285;

		/*
		Textures
		*/
		NWall->AddTexture(*horz_texture);
		SWall->AddTexture(*horz_texture);
		Ball->AddTexture(*sprites_texture);
		LBox->AddTexture(*sprites_texture);
		RBox->AddTexture(*sprites_texture);

		human_score = 0;
		cpu_score = 0;

		char buf[64];

		ball_speed = Vector2<float>(300,350);

		while (engine->Run())
		{
			GameplayFSM();

			engine->BeginRender();
			sprintf_s(buf,64,"FPS:%.2lf",engine->GetFPS());
			Time->SetText(buf);
			
			if (State!=FINISHED)
				sprintf_s(buf,64,"Human:%d     AI:%d",human_score,cpu_score);
			else
				sprintf_s(buf,64,"Human:%d     AI:%d   --PAUSE--",human_score,cpu_score);

			Score->SetText(buf);

			sgm->RenderAllGraph();

			engine->EndRender();
		}		
	}

	~App()
	{
		delete engine;
	}

	void OnEvent(const Event & evt)
	{
		if ((evt.keystate[VK_UP]&0x80)!=0)
		{
			if (LBox->Translation.Y<(250-(box_size)/2))
				LBox->Translation.Y+=500*dt;
		}
		if ((evt.keystate[VK_DOWN]&0x80)!=0)
		{
			if (LBox->Translation.Y>-(250-(box_size)/2))
				LBox->Translation.Y-=500*dt;
		}
		if ((evt.keystate[VK_SPACE]&0x80)!=0)
		{
			if ((evt.keystate[VK_SPACE]&0x01)==1)
				State = FINISHED;
			else
				State = GAME;
		}
	}
};

int main()
{
	App p;
	return 0;
}
