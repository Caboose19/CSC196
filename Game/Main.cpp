#include "core.h"
#include "Game.h"
#include "Audio/AudioSystem.h"
#include <time.h>

	Game game;


	bool Update(float dt) 
	{ 
		bool quit = game.Update(dt);

		return quit;
	}

	void Draw(Core::Graphics& graphics)
	{
		game.Draw(graphics);
	}

	int main()
	{
	
		srand(static_cast<unsigned int>(time(NULL)));

		g_audioSystem.Startup();
		game.Startup();
	
		char name[] = "CSC196";
		Core::Init(name, 800 ,600);
		Core::RegisterUpdateFn(Update);
		Core::RegisterDrawFn(Draw);

		Core::GameLoop();
		Core::Shutdown();

		game.Shutdown();
		g_audioSystem.Shutdown();
	}
