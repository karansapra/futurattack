#ifndef TORNADO_H
#define TORNADO_H

#include "types.h"
#include "core.h"

class IRenderable
{
public:
	virtual void Render()=0;
	virtual void PreRender();

};

/*
XBox 360 Controller constants
*/
#define XB360_A			0x1
#define XB360_B			0x2
#define XB360_X			0x4
#define XB360_Y			0x8
#define XB360_BACK		0x40
#define XB360_START		0x80
#define XB360_LB		0x10
#define XB360_RB		0x20
#define XB360_LJOYPRESS 0x100
#define XB360_RJOYPRESS 0x200

#define XB360_POV_N			0
#define XB360_POV_NE		4500
#define XB360_POV_E			9000
#define XB360_POV_SE		13500
#define XB360_POV_S			18000
#define XB360_POV_SW		22500
#define XB360_POV_W			27000
#define XB360_POV_NW		31500
#define XB360_POV_NONE		65535

struct JOYSTICK_INFOS
{
	XY analogA;
	XY analogB;
	U32 Buttons;
	U32 ZAxis;
	U32 POVPad;
	bool Plugged;

	JOYSTICK_INFOS()
	{
		Buttons = 0;
		ZAxis = 0;
		POVPad = 0;
		Plugged = false;
	}
};



class TornadoEngine
{
	JOYSTICK_INFOS joy_infos;

	/*
	Default constructor
	*/
	TornadoEngine();

	/*
	Initialization of OpenGL
	*/
	void glinit();

	/*
	Initialization of timing parameters
	*/
	void timing_init();

	/*
	Starting time
	*/
	double startup_time;

	/*
	CPU frequency, used in timing functions
	*/
	double cpu_freq;

	/*
	Current scene rendered
	*/
	IRenderable * scene;

	/*
	OpenGL Rendering function
	*/
	static void render();

	static void refresh();

public:

	/*
	Returns the singleton of the engine
	*/
	static TornadoEngine * GetInstance();

	/*
	Initialize the engine
	*/
	void Init(IRenderable & initial_scene);

	/*
	Starts the engine
	*/
	void Run();

	/*
	Return the time in milliseconds since the start of engine
	*/
	REAL GetTime();

	/*
	Primitive drawing method
	*/
	void DrawSphere(REAL size, Vector3 & center=Vector3());
	void DrawCone(REAL base_size,REAL height);
	void DrawLine(Vector3 & direction, Vector3 & origin=Vector3());
	void DrawCube(REAL size, Vector3 & center=Vector3());
	void DrawVertexArray(VertexArray & varray);
	void DrawMesh(Mesh & mesh);
	void DrawMeshAndAABB(Mesh & mesh);

	void SetWireframeState(bool enabled);

	JOYSTICK_INFOS GetJoystickState();
};

#endif