#pragma once
#include "./Core.h"
#include "./Vector2.h"
#include "./IEventListener.h"
#include "./SceneGraphManager.h"
#include "./ResourceManager.h"
#include "./Font.h"
#include "./Handle.h"

class CJEngine
{
	friend class Font;
	friend class SceneGraphManager;

	//Windows message pump
	static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

	//Constructor
	CJEngine();

	HWND window_handle_;			//Windows' window handle
	static CJEngine * instance_;	//Engine instance
	Vector2<double> resolution_;
	float FPS_;
	IEventListener * event_listener_;
	Font * builtin_font_;
	
	__int64 tstart_, tnow_, freq_;

	ResourceManager * resource_mgr_;
	SceneGraphManager * scene_graph_mgr_;

public:	
	static CJEngine * Instance();
	void Init(Vector2<unsigned int> resolution = Vector2<unsigned int>(800,600));
	ResourceManager * GetResourceManager();
	SceneGraphManager * GetSceneGraphManager();
	Font * GetBuiltInFont();
	void SetFPSLimit(float fps);
	double GetElapsedTime();
	bool Run();
	void BeginRender();
	void EndRender();
	float GetRandomNumber();
	void RegisterEventListener(const IEventListener & event_listener);
	
	~CJEngine(void);	//Destructor
};
