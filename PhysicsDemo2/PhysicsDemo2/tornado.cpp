#include "Tornado.h"

#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "GL/glut.h"
#include <stdio.h>

void IRenderable::PreRender()
{
	gluLookAt(10.0,10.0,20.0,0.0,0.0,0.0,0.0,1.0,0.0);
}

void TornadoEngine::render()
{
	const int grid_size = 20;
	const int grid_step = 1;
	static REAL theta=0.0;

	TornadoEngine * engine = GetInstance();
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	engine->scene->PreRender();

	if ((GetKeyState(VK_LEFT)&0x8000)!=0)		
		theta+=1.0;
	
	if ((GetKeyState(VK_RIGHT)&0x8000)!=0)		
		theta-=1.0;			
	
	glRotatef(theta,0.0,1.0,0.0);

	glLineStipple(1,0xF0F0);
	glEnable(GL_LINE_STIPPLE);
	glLineWidth(1.0);
	glBegin(GL_LINES);
	{
		glColor3f(0.5,0.5,0.5);
		for (int x=-grid_size;x<=grid_size;x+=grid_step)
		{
			//Along X axis
			glVertex3f(x,0.0,-grid_size);
			glVertex3f(x,0.0,grid_size);

			//Along Z axis
			glVertex3f(-grid_size,0.0,x);
			glVertex3f(grid_size,0.0,x);
		}
		glVertex3f(0.0,-grid_size,0.0);
		glVertex3f(0.0,grid_size,0.0);
	}
	glEnd();
	glutWireCube(grid_step);
	glDisable(GL_LINE_STIPPLE);


	glLineWidth(2.0);
	glPushMatrix();
	engine->scene->Render();
	glPopMatrix();

	glutSwapBuffers();
}

void TornadoEngine::glinit()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);            
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	
	//glClearDepth(1.0f);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_BLEND);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	gluPerspective(40.0f,16.0f/10.0f,0.1f,1000.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();	
}

TornadoEngine::TornadoEngine()
{
	scene=NULL;
}

TornadoEngine * TornadoEngine::GetInstance()
{
	static TornadoEngine * instance = NULL;
	if (instance==NULL)
		instance = new TornadoEngine();
	return instance;
}

void TornadoEngine::Init(IRenderable & initial_scene)
{
	static bool realized=false;

	if (!realized)
	{
		scene = &initial_scene;
		int i=1;
		char modulename[256];
		GetModuleFileName(NULL,modulename,256);
		char * str[] = {modulename,NULL};
		glutInit(&i,str);
		glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
		glutInitWindowSize(800,500);
		glutCreateWindow("PhysicsDemo2");			
		glinit();
		timing_init();		
		realized = true;
	}
}

void TornadoEngine::timing_init()
{
	LARGE_INTEGER frequency;
	LARGE_INTEGER counter;
	QueryPerformanceFrequency(&frequency);
	cpu_freq = (double)(long long)frequency.QuadPart;
	QueryPerformanceCounter(&counter);
	startup_time = (double)(long long)counter.QuadPart;
	startup_time = startup_time/cpu_freq;
}

void TornadoEngine::refresh()
{
	glutPostRedisplay();
	Sleep(10);
}

void TornadoEngine::Run()
{
	glutDisplayFunc(render);
	glutIdleFunc(refresh);
	glutMainLoop();
}

void TornadoEngine::DrawSphere(REAL size, Vector3 & center)
{
	glPushMatrix();
	glTranslatef(center.x,center.y,center.z);
	glColor3f(0.0,1.0,0.0);
	glutWireSphere(size,12,12);
	glPopMatrix();
}

void TornadoEngine::DrawCube(REAL size, Vector3 & center)
{
	glPushMatrix();
	glTranslatef(center.x,center.y,center.z);
	glColor3f(0.0,1.0,0.0);
	glutWireCube(size);
	glPopMatrix();
}

void TornadoEngine::DrawCone(REAL base_size, REAL height)
{
	glPushMatrix();
	glColor3f(0.0,1.0,0.0);
	glRotatef(90,1,0,0);
	glTranslatef(0,0,-0.25*height);
	glutWireCone(base_size,height,16,3);
	glPopMatrix();
}

void TornadoEngine::DrawLine(Vector3 & direction, Vector3 & origin)
{
	glPushMatrix();
	glBegin(GL_LINES);
	glColor3f(0.0,0.0,1.0);
	glVertex3f(origin.x,origin.y,origin.z);
	glVertex3f(origin.x+direction.x,origin.y+direction.y,origin.z+direction.z);
	glEnd();	
	glPopMatrix();	
}

REAL TornadoEngine::GetTime()
{
	static LARGE_INTEGER counter;
	static double counter_real;
	QueryPerformanceCounter(&counter);
	counter_real = (double)(long long)counter.QuadPart;
	counter_real = counter_real/cpu_freq;
	return (REAL)(counter_real-startup_time);
}

JOYSTICK_INFOS TornadoEngine::GetJoystickState()
{
	static JOYINFOEX joyinfoex;

	joyinfoex.dwSize = sizeof(JOYINFOEX);
	joyinfoex.dwFlags = JOY_RETURNALL;

	if (joyGetPosEx(0,&joyinfoex)==JOYERR_UNPLUGGED)
		return JOYSTICK_INFOS();

	joy_infos.Plugged = true;

	joy_infos.Buttons = joyinfoex.dwButtons;
	
	joy_infos.analogA.x = joyinfoex.dwXpos;
	joy_infos.analogA.y = joyinfoex.dwYpos;

	joy_infos.analogB.x = joyinfoex.dwUpos;
	joy_infos.analogB.y = joyinfoex.dwRpos;
	
	joy_infos.ZAxis = joyinfoex.dwZpos;

	joy_infos.POVPad = joyinfoex.dwPOV;

	return joy_infos;
}
