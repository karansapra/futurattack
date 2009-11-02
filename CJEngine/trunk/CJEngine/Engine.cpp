/*
 * Engine.cpp
 *
 *  Created on: 27 oct. 2009
 *      Author: Clement
 */

#include "Engine.h"

namespace CJEngine {

	Engine * Engine::_engine_instance=0;

	Engine::Engine() {
        _time = 0.0f;
        _quit_on_escape = true;
        _igamelogic = 0;
	}

	Engine::~Engine() {

	}

	Engine * Engine::GetInstance()
	{
		if (_engine_instance==0)
			_engine_instance = new Engine();

		return _engine_instance;
	}

	int Engine::GetWidth()
	{
		return _width;
	}

	int Engine::GetHeight()
	{
		return _height;
	}

    bool Engine::Init(int width, int height, const char *title, bool fullscreen)
    {		
    	_width = width;
    	_height = height;
    	_title = (char*)((title));
        _fullscreen = fullscreen;
        _hinstance = GetModuleHandleA(0);

		_audio_device = alcOpenDevice(NULL);
		if (_audio_device==NULL)
			_audio_enabled = false;
		else
		{
			_audio_context = alcCreateContext(_audio_device,NULL);
			alcMakeContextCurrent(_audio_context);
			_audio_enabled = true;			
			_eax_enabled = (bool)alIsExtensionPresent("EAX2.0");			
			int format,size,freq;
			ALboolean loop;

			ALuint buffers[1];
			ALuint sources[1];
			alGenBuffers(1,buffers);
			alGenSources(1,sources);

			OggVorbis_File fichier_ogg;
			vorbis_info * infos;

			if (ov_fopen("C:\\ogg.ogg",&fichier_ogg)==0)
			{				
				char data[44100*4*2];
				int bitstream;
				int total=0;
				while (total<44100*4*2)
					total += ov_read(&fichier_ogg,data+total,44100*4*2-total,0,2,1,&bitstream);

				infos = ov_info(&fichier_ogg,-1);
				printf("Infos\nChannels:%d\nRate:%d\n",infos->channels,infos->rate);
				printf("Decode size:%d\n",total);
				alBufferData(buffers[0],AL_FORMAT_STEREO16,data,44100*4*2,infos->rate);				
				alSourcei(sources[0],AL_BUFFER,buffers[0]);
				alSourcePlay(sources[0]);
			}
		}


        LARGE_INTEGER cpu_freq;
        if(QueryPerformanceFrequency(&cpu_freq) == 0)
            return 0;

        _cpu_frequency = (float)((cpu_freq.QuadPart));
        //Creation of the class to create the window
        WNDCLASS wc;
        ZeroMemory(&wc,sizeof(WNDCLASS));
		wc.hCursor = LoadCursorA(NULL,IDC_ARROW);
        wc.hIcon = LoadIconA(_hinstance,MAKEINTRESOURCE(IDI_ICON1));
        wc.hInstance = _hinstance;
        wc.lpfnWndProc = _wnd_proc_wrapper;
        wc.lpszClassName = "mainframe";
        wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
        if(RegisterClassA(&wc) == 0)
            return false;

        _mainframe = CreateWindow("mainframe",_title,WS_SYSMENU | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
    			100,100,_width,_height,NULL,NULL,_hinstance,NULL);
        if (_mainframe==NULL)
    		return false;
        ShowWindow(_mainframe,SW_SHOW);
        UpdateWindow(_mainframe);
        _GLInit();
        QueryPerformanceCounter(&_t0);
        return true;
    }
    void Engine::Run()
    {
        static MSG msg;
        static LARGE_INTEGER tnow;
        static LARGE_INTEGER delta_time;

        SetTimer(_mainframe,101,20,NULL);

        while (GetMessageA(&msg,NULL,0,0))
        {
			//Calcul du temps
			QueryPerformanceCounter(&tnow);
			delta_time.QuadPart = tnow.QuadPart - _t0.QuadPart;
			_time = ((float)(delta_time.QuadPart)) / _cpu_frequency;
			TranslateMessage(&msg);
			DispatchMessageA(&msg);
        }
    }

    void Engine::_SetDCPixelFormat(HDC hdc)
    {
        int npixelfmt;
        static PIXELFORMATDESCRIPTOR pfd = {sizeof(PIXELFORMATDESCRIPTOR),1,
			PFD_DRAW_TO_WINDOW|PFD_DOUBLEBUFFER|PFD_SUPPORT_OPENGL|PFD_TYPE_RGBA,
			32,0,0,0,0,0,0,0,0,0,0,0,0,0,16,0,0,0,0,0,0,0};
        npixelfmt = ChoosePixelFormat(_hdc, &pfd);
        SetPixelFormat(hdc, npixelfmt, &pfd);
    }

    void Engine::_GLInit()
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

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
    }

    void Engine::_GLRender()
    {
        //FPS Computation on '5' frames
    	static int npasses = 0;
        static float last_time = 0.0f;
        static float delta;
        static UIFramePtrIterator uiframe_iter;

        npasses++;
        if(npasses == 5){
            delta = _time - last_time;
            last_time = _time;
            _fps = 5.0f / delta;
            npasses = 0;
        }

        //OpenGL Rendering
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		//Render pass
        if (_igamelogic!=0)
        	_igamelogic->RenderPass(_time);
		

		
    }

    float Engine::GetSecondsElapsed()
    {
        return _time;
    }

    float Engine::GetFPS()
    {
        return _fps;
    }

    void Engine::SetTitle(char *title)
    {
        SetWindowTextA(_mainframe, title);
    }

    void Engine::ExitOnEscape(bool enabled)
    {
        _quit_on_escape = enabled;
    }

    void Engine::AddEventReceiver(const IEventReceiver & ieventreceiver)
    {
        if(&ieventreceiver != 0)
            _ieventreceivers.push_back((IEventReceiver*)(&ieventreceiver));

    }
    void Engine::RemoveEventReceiver(const IEventReceiver & ieventreceiver)
    {
        if(&ieventreceiver != 0){
            IEventReceiverPtrIterator i;
            for(i = _ieventreceivers.begin();i < _ieventreceivers.end();i++){
                if(*i == &ieventreceiver)
                    break;

            }
            _ieventreceivers.erase(i);
        }
    }

    void Engine::DrawScene(IScene & scene)
    {
    	if (&scene!=0)
    	{
			scene.PreRender();
			scene.Render(_time);
    	}
    }

    void Engine::SetCamera(ICamera & camera)
    {
    	camera.Apply();
    }

    /*
     *
     * UI Methods
     *
     */
	void Engine::AddUIFrame(const UIFrame & frame)
	{
		if (&frame != 0)
		{
			_uiframes.push_back((UIFrame*)&frame);
			AddEventReceiver(frame);
		}
	}

	void Engine::RemoveUIFrame(const UIFrame & frame)
	{
		if (&frame != 0)
		{
			UIFramePtrIterator i;
			for (i=_uiframes.begin();i<_uiframes.end();i++)
			{
				if (*i==&frame)
					break;
			}
			_uiframes.erase(i);
			RemoveEventReceiver(frame);
		}

	}

    /*
     *
     * Game Logic methods
     *
     */
    void Engine::SetCurrentGameLogic(const IGameLogic & logic)
    {
    	if (&logic!=0)
    	{
    		_igamelogic = (IGameLogic*)&logic;
    		AddEventReceiver(*_igamelogic);
    	}
    }

    void Engine::RemoveCurrentGameLogic()
    {
    	RemoveEventReceiver(*_igamelogic);
    	_igamelogic = 0;
    }


    /*
     *
     * Reserved
     *
     */
    LRESULT CALLBACK Engine::WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
    {
    	static IEventReceiverPtrIterator i;
    	static Event evt;

        switch (msg)
    	{
    	case WM_DESTROY:
    		DestroyWindow(_mainframe);
    		PostQuitMessage(0);
    		break;

    	case WM_CREATE:
    		_hdc = GetDC(hwnd);
    		_SetDCPixelFormat(_hdc);
    		_hglrc = wglCreateContext(_hdc);
    		wglMakeCurrent(_hdc,_hglrc);
    		break;

    	case WM_LBUTTONDOWN:
    		evt.mousex = LOWORD(lparam);
    		evt.mousey = HIWORD(lparam);
    		evt.event_type = MOUSE_LEFT_CLICK;

    		for (i=_ieventreceivers.begin();i<_ieventreceivers.end();i++)
    		{
    			if (*i!=0)
    			{
    				(*i)->EventArrived(evt);
    			}
    		}
    		break;

    	case WM_RBUTTONDOWN:
    		evt.mousex = LOWORD(lparam);
    		evt.mousey = HIWORD(lparam);
    		evt.event_type = MOUSE_RIGHT_CLICK;

    		for (i=_ieventreceivers.begin();i<_ieventreceivers.end();i++)
    		{
    			if (*i!=0)
    			{
    				(*i)->EventArrived(evt);
    			}
    		}
    		break;

    	case WM_KEYDOWN:
    		if (VK_ESCAPE==wparam && _quit_on_escape)
    			DestroyWindow(_mainframe);

    		evt.keycode = wparam;
    		evt.event_type = KEYDOWN;

    		for (i=_ieventreceivers.begin();i<_ieventreceivers.end();i++)
    		{
    			if (*i!=0)
    			{
    				(*i)->EventArrived(evt);
    			}
    		}
    		break;

    	case WM_TIMER:
    		InvalidateRect(hwnd,NULL,FALSE);
    		_GLRender();
    		SwapBuffers(_hdc);
    		ValidateRect(hwnd,NULL);
    		break;

    	default:
    		return DefWindowProcA(hwnd,msg,wparam,lparam);
    	}
        return 0L;
    }

	bool Engine::IsKeyPressed(int vk_code)
	{
		if (((GetKeyState(vk_code)>>15)&0x01) == 0x01)
			return true;

		return false;
	}

	LRESULT CALLBACK _wnd_proc_wrapper(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
    {
        static Engine *engine = Engine::GetInstance();
        return engine->WndProc(hwnd, msg, wparam, lparam);
    }


}
