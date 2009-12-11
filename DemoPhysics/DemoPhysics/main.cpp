#include <stdio.h>
#include <hge.h>
#include <hgevector.h>
#include <hgesprite.h>
#include <vector>

#include "PhysicsEngine.h"
#include "PhysicsObjects.h"

#pragma comment(lib,"hge.lib")
#pragma comment(lib,"hgehelp.lib")

HGE * hge=0;

struct Green
{
	Green(hgeVector A, hgeVector B)
	{
		quad.v[0].tx = 0.0; quad.v[0].ty = 0.0;
		quad.v[1].tx = 0.0; quad.v[1].ty = 1.0;
		quad.v[2].tx = 1.0; quad.v[2].ty = 1.0;
		quad.v[3].tx = 1.0; quad.v[3].ty = 0.0;		
		for (int i=0;i<4;i++)
		{
			quad.v[i].z = 0.5f;
			quad.v[i].col = 0xFFFFFFFF;
		}

		quad.tex = hge->Texture_Load("green.png");
		quad.blend=BLEND_ALPHAADD;
		
		quad.v[0].x = A.x; quad.v[0].y = A.y;
		quad.v[1].x = A.x; quad.v[1].y = B.y;
		quad.v[2].x = B.x; quad.v[2].y = B.y;
		quad.v[3].x = B.x; quad.v[3].y = A.y;
	}

	void Render()
	{
		hge->Gfx_RenderQuad(&quad);
	}

private:
	hgeQuad quad;
};

PhysicsEngine * physics;
GolfBall * ball;
Wall * wall1;
Wall * wall2;
Wall * wall3;
Green * g;
Whole *whole;
hgeSprite * fleche;

Wall * tours[4];

enum STATE {DEBUT,PREPARATION,LANCER,INGAME,END};
STATE etat_jeu=DEBUT;
float alpha = 0.0f;
float power = 3000.0f;


void CollisionCallback(int id1, int id2)
{
	if (id1==100 && id2==101)
	{
		printf("FINI\n");
		etat_jeu = END;
	}
}


bool RenderFunc()
{
	hge->Gfx_BeginScene();
	hge->Gfx_Clear(0);
	
	g->Render();
	
	wall3->Render();
	whole->Render();
	ball->Render();

	if (etat_jeu==PREPARATION)
		fleche->RenderEx(ball->Center_1.x,ball->Center_1.y,alpha,power/25000.0f,1.0f);

	hge->Gfx_EndScene();
	return false;
}

void InGame()
{
	if (!ball->isMoving)
		etat_jeu=PREPARATION;

	physics->Compute(1.0f/100.0f);
}

void Prepa()
{
	if (hge->Input_GetKeyState(HGEK_SPACE))
		etat_jeu=LANCER;
	if (hge->Input_GetKeyState(HGEK_UP))
		alpha-=0.02f;
	if (hge->Input_GetKeyState(HGEK_DOWN))
		alpha+=0.02f;
	if (hge->Input_GetKeyState(HGEK_LEFT) && power>2000.0f)
		power-=100.0f;
	if (hge->Input_GetKeyState(HGEK_RIGHT) && power<25000.0f)
		power+=100.0f;
}

bool FrameFunc()
{
	static int wait_time=0;

	switch (etat_jeu)
	{
	case DEBUT:
		printf("New party\n");
		ball->Center.x = 200;
		ball->Center.y = 300;
		ball->Center_1 = ball->Center;
		etat_jeu=PREPARATION;
		break;
	case LANCER:
		ball->CurrentForce.x = power*cos(alpha);
		ball->CurrentForce.y = power*sin(alpha);
		alpha = 0;
		power = 3000.0f;
		physics->Compute(1.0f/100.0f);
		ball->CurrentForce.x = 0.0f;
		ball->CurrentForce.y = 0.0f;
		etat_jeu = INGAME;
		break;
	case PREPARATION:
		Prepa();
		break;
	case INGAME:
		InGame();		
		break;
	case END:
		wait_time++;
		if (wait_time==200)
		{
			etat_jeu=DEBUT;
			wait_time=0;
		}
		break;
	default:
		etat_jeu=DEBUT;
		break;
	}


	return false;
}

void main()
{
	hge = hgeCreate(HGE_VERSION);
	hge->System_SetState(HGE_LOGFILE,"log.txt");
	hge->System_SetState(HGE_FRAMEFUNC,FrameFunc);
	hge->System_SetState(HGE_RENDERFUNC,RenderFunc);
	hge->System_SetState(HGE_SHOWSPLASH,true);
	hge->System_SetState(HGE_WINDOWED,true);
	hge->System_SetState(HGE_USESOUND,false);
	hge->System_SetState(HGE_SCREENBPP, 32);
	hge->System_SetState(HGE_FPS,100);

	hge->System_Initiate();

	hgeVector A,B;
	A.x = 100;
	A.y = 100;
	B.x = 700;
	B.y = 500;


	physics = new PhysicsEngine();

	g = new Green(A,B);	
	ball = new GolfBall(200,300,10);
	wall3 = new Wall(300,250,370,300);
	whole = new Whole(650,300,12.0f);

	ball->Id=100;
	whole->Id=101;
	ball->CollideCB = CollisionCallback;
	

	float posAx_murs[] = {100,100,700,700};
	float posBx_murs[] = {100,700,700,100};
	float posBy_murs[] = {500,500,100,100};
	float posAy_murs[] = {100,500,500,100};

	for (int i=0;i<4;i++)
	{
		tours[i] = new Wall(posAx_murs[i],posAy_murs[i],
			posBx_murs[i],posBy_murs[i]);
		physics->AddBody(*tours[i]);
	}
	physics->AddBody(*ball);
	physics->AddBody(*wall3);
	physics->AddBody(*whole);

	HTEXTURE fleche_tex = hge->Texture_Load("fleche.png");
	fleche = new hgeSprite(fleche_tex,0,0,200,24);
	fleche->SetBlendMode(BLEND_ALPHABLEND);
	fleche->SetHotSpot(0,12);
	fleche->SetColor(0xFFFFFFFF);
	fleche->SetZ(0.2f);

	hge->System_Start();
	hge->System_Shutdown();
	hge->Release();
}
