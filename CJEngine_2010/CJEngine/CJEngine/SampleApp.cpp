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

	Texture * wall_texture;
	Texture * box_texture;
	Texture * ball_texture;

	Vector2<float> ball_speed;

	float box_size;

	int human_score;
	int cpu_score;

	enum STATE {PAUSE, GAME, ENTERPAUSE, FINISHED};
	STATE State;

public:
	void BallPhysics()
	{
		Ball->Rotation += 25;
		Ball->Translation += ball_speed;
		if (Ball->Translation.Y>250||Ball->Translation.Y<-250)
		{
			ball_speed.Y = -ball_speed.Y;
		}
		if (Ball->Translation.X>330)
		{
			if ((Ball->Translation-RBox->Translation).Abs2()<(box_size+20)*(box_size+20)/4)
			{
				//IA touches the ball
				ball_speed.X = -ball_speed.X;
				cpu_score++;
			} else
			{
				//IA misses the ball
				Ball->Translation = Vector2<float>(0,0);
				ball_speed = ball_speed*-1;
				human_score+=5;
				State = ENTERPAUSE;
			}
		} else
		if (Ball->Translation.X<-330)
		{
			if ((Ball->Translation-LBox->Translation).Abs2()<(box_size+20)*(box_size+20)/4)
			{
				//Human touches the ball
				ball_speed.X = -ball_speed.X;
				human_score++;
			} else
			{
				//Human misses the ball
				Ball->Translation = Vector2<float>(0,0);
				ball_speed = ball_speed*-1;
				cpu_score+=5;
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
		
		float dy = RBox->Translation.Y - (Ball->Translation+ball_speed*2).Y;
		if (dy>0)
		{
			if (RBox->Translation.Y>-(250-(box_size)/2))
			{
				RBox->Translation.Y-=15;
			}
		}
		else
		{
			if (RBox->Translation.Y<(250-(box_size)/2))
			{
				RBox->Translation.Y+=15;
			}
		}
	}

	void GameplayFSM()
	{		
		static double t0 = engine->GetElapsedTime();

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
		engine->SetFPSLimit(60);
		engine->RegisterEventListener(*this);
		sgm = engine->GetSceneGraphManager();
		rsm = engine->GetResourceManager();

		box_texture = rsm->AddTexture("./box.png");
		ball_texture = rsm->AddTexture("./ball.png");
		wall_texture = rsm->AddTexture("./wall.png");

		NWall = sgm->AddSpriteNode();
		SWall = sgm->AddSpriteNode();
		Ball = sgm->AddSpriteNode();
		LBox = sgm->AddSpriteNode();
		RBox = sgm->AddSpriteNode();
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
		NWall->AddTexture(*wall_texture);
		SWall->AddTexture(*wall_texture);
		Ball->AddTexture(*ball_texture);
		LBox->AddTexture(*box_texture);
		RBox->AddTexture(*box_texture);

		human_score = 0;
		cpu_score = 0;
			
		char buf[64];

		ball_speed = Vector2<float>(6,7);

		while (engine->Run())
		{
			GameplayFSM();

			engine->BeginRender();
			sprintf_s(buf,64,"Time:%.2lf",engine->GetElapsedTime());
			Time->SetText(buf);
			sprintf_s(buf,64,"Human:%d     IA:%d",human_score,cpu_score);			
			Score->SetText(buf);

			sgm->RenderAllGraph();
			///////////////////////////
			//
			// PLACE CODE HERE
			//
			///////////////////////////
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
				LBox->Translation.Y+=10;
		}
		if ((evt.keystate[VK_DOWN]&0x80)!=0)
		{
			if (LBox->Translation.Y>-(250-(box_size)/2))
				LBox->Translation.Y-=10;
		}
		if ((evt.keystate[VK_SPACE]&0x80)!=0)
		{

		}
	}
};

int main()
{
	App p;
	system("PAUSE");
	return 0;
}