#include "./CJEngine.h"

CJEngine * CJEngine::instance_ = 0;

CJEngine * CJEngine::Instance()
{
	if (instance_==NULL)
		instance_ = new CJEngine();
	return instance_;
}

void CJEngine::Init(Vector2<unsigned int> resolution)
{
	resolution_.X = resolution.X;
	resolution_.Y = resolution.Y;

	WNDCLASS wc;
	ZeroMemory(&wc,sizeof(WNDCLASS));
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpszClassName = "CJENGINE";
	wc.lpfnWndProc = WndProc;
	RegisterClass(&wc);

	window_handle_ = 
		CreateWindow("CJENGINE","CJ Engine OpenGL",WS_SYSMENU|WS_CLIPCHILDREN|WS_CLIPSIBLINGS,
		100,100,resolution.X,resolution.Y,NULL,NULL,GetModuleHandle(NULL),NULL);

	HDC hdc;
	int npixelfmt;

	hdc = GetDC(window_handle_);
	static PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL|PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		32,
		0,0,0,0,0,0,
		0,0,
		0,0,0,0,0,
		16,
		0,
		0,
		0,
		0,
		0,0,0
	};
	glClearColor(0.0,0.0,0.0,1.0);		//To cancel white screen
	npixelfmt = ChoosePixelFormat(hdc,&pfd);
	SetPixelFormat(hdc,npixelfmt,&pfd);
	HGLRC hglrc = wglCreateContext(hdc);
	wglMakeCurrent(hdc,hglrc);

	/*
	GL EXTENSIONS
	*/
	glCreateShader = (PFNGLCREATESHADERPROC)wglGetProcAddress("glCreateShader");
	glDeleteShader = (PFNGLDELETESHADERPROC)wglGetProcAddress("glDeleteShader");
	glShaderSource = (PFNGLSHADERSOURCEPROC)wglGetProcAddress("glShaderSource");
	glCompileShader = (PFNGLCOMPILESHADERPROC)wglGetProcAddress("glCompileShader");
	glCreateProgram = (PFNGLCREATEPROGRAMPROC)wglGetProcAddress("glCreateProgram");
	glAttachShader = (PFNGLATTACHSHADERPROC)wglGetProcAddress("glAttachShader");
	glLinkProgram = (PFNGLLINKPROGRAMPROC)wglGetProcAddress("glLinkProgram");
	glValidateProgram = (PFNGLVALIDATEPROGRAMPROC)wglGetProcAddress("glValidateProgram");
	glUseProgram = (PFNGLUSEPROGRAMPROC)wglGetProcAddress("glUseProgram");
	glGetShaderiv = (PFNGLGETSHADERIVPROC)wglGetProcAddress("glGetShaderiv");

	/*
	OpenGL Default Values
	*/
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();	
	gluOrtho2D(-resolution_.X/2,resolution_.X/2,-resolution_.Y/2,resolution_.Y/2);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	builtin_font_ = resource_mgr_->AddFont("Arial",14);

	ShowWindow(window_handle_,SW_SHOW);
	UpdateWindow(window_handle_);
}

LRESULT CALLBACK CJEngine::WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	static HDC hdc;

	switch (msg)
	{
	case WM_CREATE:
		hdc = GetDC(hwnd);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hwnd,msg,wparam,lparam);
	}

	return 0L;
}

CJEngine::CJEngine()
{
	resolution_.X = 800;
	resolution_.Y = 600;
	FPS_ = 50;

	event_listener_ = NULL;
	scene_graph_mgr_ = new SceneGraphManager();
	resource_mgr_ = new ResourceManager();
}

CJEngine::~CJEngine(void)
{
	delete scene_graph_mgr_;
	delete resource_mgr_;
}

ResourceManager * CJEngine::GetResourceManager()
{
	return resource_mgr_;
}

SceneGraphManager * CJEngine::GetSceneGraphManager()
{
	return scene_graph_mgr_;
}

Font * CJEngine::GetBuiltInFont()
{
	return builtin_font_;
}

void CJEngine::BeginRender()
{
	InvalidateRect(window_handle_,NULL,FALSE);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void CJEngine::EndRender()
{
	static HDC hdc = GetDC(window_handle_);

	SwapBuffers(hdc);
	ValidateRect(window_handle_,NULL);	
}

float CJEngine::GetFPS()
{
	return FPS_;
}

bool CJEngine::Run()
{
	static bool first_run = true;
	static LARGE_INTEGER frequency;
	static LARGE_INTEGER ctr;

	static __int64 t0;
	static __int64 t1 = 0;

	static Event evt;
	static MSG msg;

	if (first_run)
	{
		QueryPerformanceFrequency(&frequency);
		freq_ = frequency.QuadPart;
		QueryPerformanceCounter(&ctr);
		tstart_ = ctr.QuadPart;
		t0 = tstart_;
		first_run = false;
	}

	QueryPerformanceCounter(&ctr);
	t1 = ctr.QuadPart;

	float dt = (float)(t1-t0);

	if (dt!=0)
		FPS_ = freq_/dt;

	tnow_ = t1;
	t0 = t1;


	if (instance_->event_listener_)
	{
		GetKeyboardState(evt.keystate);
		instance_->event_listener_->OnEvent(evt);
	}		

	if (PeekMessage(&msg,NULL,0,0,PM_REMOVE)!=0)
	{
		if (msg.message==WM_QUIT)
			return false;
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return true;
}

double CJEngine::GetElapsedTime()
{
	__int64 t = (tnow_-tstart_);
	return (double)t/freq_;
}

void CJEngine::RegisterEventListener(const IEventListener & event_listener)
{
	event_listener_ = (IEventListener*)&event_listener;
}

float CJEngine::GetRandomNumber()
{
	static unsigned int x = (unsigned int)tstart_;
	static unsigned int y = 362436069;
	static unsigned int z = 521288629;
	static unsigned int w = 88675123; 
	unsigned int t;

	t = x ^ (x << 11);
	x = y; y = z; z = w;
	w = w ^ (w >> 19) ^ t ^ (t >> 8); 
	float fresult = (float)w/(float)((unsigned int)0xFFFFFFFF);
	return (fresult-0.5f)*2.0f;
}