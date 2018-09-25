#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Window.h"

#include "SDL/include/SDL.h"


j1Window::j1Window() : j1Module()
{
	window = NULL;
	screen_surface = NULL;
	name.create("window");
}

// Destructor
j1Window::~j1Window()
{
}

// Called before render is available
bool j1Window::Awake()
{
	LOG("Init SDL window & surface");
	bool ret = true;

	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		LOG("SDL_VIDEO could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	else
	{
		//Create window
		Uint32 flags = SDL_WINDOW_SHOWN;

		width = App->nodeF.child("window").child("resolution").attribute("width").as_int();
		height = App->nodeF.child("window").child("resolution").attribute("height").as_int();
		scale = App->nodeF.child("window").child("resolution").attribute("scale").as_int();

		if(App->nodeF.child("window").child("fullscreen").attribute("value").as_bool())
		{
			flags |= SDL_WINDOW_FULLSCREEN;
		}

		if(App->nodeF.child("window").child("borderless").attribute("value").as_bool())
		{
			flags |= SDL_WINDOW_BORDERLESS;
		}

		if(App->nodeF.child("window").child("resizable").attribute("value").as_bool())
		{
			flags |= SDL_WINDOW_RESIZABLE;
		}

		if(App->nodeF.child("window").child("fullscreen_window").attribute("value").as_bool())
		{
			flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		}

		window = SDL_CreateWindow(App->nodeF.child("app").child_value("title"), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);

		if(window == NULL)
		{
			LOG("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			ret = false;
		}
		else
		{
			//Get window surface
			screen_surface = SDL_GetWindowSurface(window);

			// TODO 4: Read the title of the app from the XML
			// and set directly the window title using SetTitle()
			
			
		/*	SetTitle(App->nodeF.child_value());*/

			

		}
	}

	return ret;
}

// Called before quitting
bool j1Window::CleanUp()
{
	LOG("Destroying SDL window and quitting all SDL systems");

	//Destroy window
	if(window != NULL)
	{
		SDL_DestroyWindow(window);
	}

	//Quit SDL subsystems
	SDL_Quit();
	return true;
}

// Set new window title
void j1Window::SetTitle(const char* new_title)
{
	//title.create(new_title);
	SDL_SetWindowTitle(window, new_title);
}

void j1Window::GetWindowSize(uint& width, uint& height) const
{
	width = this->width;
	height = this->height;
}

uint j1Window::GetScale() const
{
	return scale;
}