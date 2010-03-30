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
	/*
	Returns the unique instance of the engine (Singleton)
	*/
	static CJEngine * Instance();

	/*
	Initializes the engine, should be called at the top of your code
	*/
	void Init(Vector2<unsigned int> resolution = Vector2<unsigned int>(800,600));

	/*
	Returns the resource manager. Can load plethora of files, like
	music, pictures
	*/
	ResourceManager * GetResourceManager();

	/*
	Returns the graph manager of the engine. Permits
	to add new nodes to render, special nodes, like
	effects nodes
	*/
	SceneGraphManager * GetSceneGraphManager();

	/*
	Returns the default font of the engine, Arial 12
	*/
	Font * GetBuiltInFont();

	/*
	Set the max rendering frequency
	*/
	void SetFPSLimit(float fps);

	/*
	Returns the seconds elapsed since the first run
	of the engine (Run)
	*/
	double GetElapsedTime();

	/*
	Runs one cycle of the engine
	*/
	bool Run();

	/*
	Allow rendering
	*/
	void BeginRender();

	/*
	Terminate rendering
	*/
	void EndRender();

	/*
	Returns a random number in range [-1 ; 1]
	*/
	float GetRandomNumber();

	/*
	Registers a new listener
	*/
	void RegisterEventListener(const IEventListener & event_listener);
	
	/*
	Destroy the engine
	*/
	~CJEngine(void);
};
