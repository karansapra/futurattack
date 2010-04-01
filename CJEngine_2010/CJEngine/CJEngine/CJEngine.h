/*!
 * \file CJEngine.h
 * \brief Contains the CJEngine class definition
 * \author Clément JACOB
 *
 */

#pragma once
#include "./Core.h"
#include "./Vector2.h"
#include "./IEventListener.h"
#include "./SceneGraphManager.h"
#include "./ResourceManager.h"
#include "./Font.h"


/*!
 * \class CJEngine
 * \brief Central class of the Engine
 *
 * CJEngine is the central class of the engine. You can
 * perform anything from this class. To obtain an instance
 * of it, you should call the static method Instance(). Just
 * after obtaining that unique instance, you should call
 * Init() to perform initialization tasks, like window creation...
 *
 */
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
	/*!	
	 * \brief Unique instance of CJEngine
	 * 
	 * The first time it's called, you should configure the engine
	 * returned by the the Init() method
	 *
	 * \return The pointer to the unique instance of CJEngine
	 * 
	 */
	static CJEngine * Instance();

	/*!	
	 * \brief Unique instance of CJEngine
	 * \return The pointer to the unique instance of CJEngine
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
	float GetFPS();

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
