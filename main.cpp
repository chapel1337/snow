#include <SDL.h>
#include <random>
#include <deque>
#include <windows.h>

/*
* written by chapel1337
* started on 12/19/2022, finished on 12/20/2022
* my first actual sdl2 project, very happy
* there's not much to say about this, it's just a basic snow falling program
* the mouse moving the snow away took way too long to attempt, ending up being a failure
* i'll probably make a christmas tree decorator after this because christmas is in 5 days
* we haven't been hit with a snow storm yet unfortunately
* will add snow piling feature tomorrow
*/

#ifdef DEBUG
	#include <iostream>
	using std::cout;
#endif

using std::deque;

SDL_Window* window{ SDL_CreateWindow("snow", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 500, SDL_WINDOW_SHOWN) }; // && SDL_WINDOW_FULLSCREEN) };
SDL_Surface* surface{ SDL_GetWindowSurface(window) };
SDL_Renderer* renderer{ SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC) };

// SDL_Surface* kot{ SDL_LoadBMP("dog.bmp") };
// SDL_Rect mouseCollision{ 0, 0, 25, 25 };

// SDL_Rect snowPile{ 250, 250, 10, 20 };

SDL_Event event{};

int speed{ 1 };

bool random{};
bool pileSnow{ true };

deque<deque<SDL_Rect>> snowFlakes
{
	{},
	{},
	{},
	{},
	{},
	{},
	{},
	{},
	{},
	{},
	{},
	{},
	{},
	{},
	{},
	{},
	{},
	{},
	{},
};

std::mt19937 mt{ std::random_device{}() };
int getRandom(const int  minimum, const int maximum)
{
	std::uniform_int_distribution<> random{ minimum, maximum };

	return random(mt);
}

void fall()
{
	while (true)
	{
		// SDL_GetMouseState(&mouseCollision.x, &mouseCollision.y);
		SDL_PollEvent(&event);

		// cout << mouseX << ", " << mouseY << '\n';

		if (event.type == SDL_QUIT)
		{
			SDL_DestroyWindow(window);
			SDL_Quit();

			exit(1);
		}
		else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE)
		{
			SDL_DestroyWindow(window);
			SDL_Quit();

			#ifdef DEBUG
				exit(1);
			#endif
		}
		else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_UP)
		{
			++speed;

			#ifdef DEBUG
				cout << speed << '\n';
			#endif
		}
		else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_DOWN && speed != 1)
		{
			--speed;

			#ifdef DEBUG
				cout << speed << '\n';
			#endif
		}
		/*
		else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_s)
		{
			if (pileSnow)
			{
				pileSnow = false;
			}
			else
			{
				pileSnow = true;
			}
		*/
		/*
		else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_LEFT)
		{
			SDL_SetWindowSize(window, SDL_GetWindowSurface(window)->w, SDL_GetWindowSurface(window)->h + 25);
		}
		else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_RIGHT)
		{
			SDL_SetWindowSize(window, SDL_GetWindowSurface(window)->w + 25, SDL_GetWindowSurface(window)->h);
		}
		*/
		else if (event.type == SDL_MOUSEWHEEL)
		{
			if (event.wheel.y > 0)
			{
				speed += event.wheel.y;
			}
			else if (event.wheel.y < 0 && speed != 1)
			{
				speed += event.wheel.y;
			}

			#ifdef DEBUG
				cout << speed << '\n';
			#endif
		}
		else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_h)
		{
			MessageBoxA(NULL, "\n to increase or decrease the speed of the the snow, use the scrollwheel\n if a mouse is not present, use the up and down arrows instead \n to toggle random colors, press r \n to exit, press esc \n to open the help menu, press h \n\n written by chapel1337 \n started on 12/19/2022, finished on 12/20/2022", "help", MB_ICONQUESTION);
		}
		else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_r)
		{
			if (random)
			{
				random = false;
			}
			else
			{
				random = true;
			}
		}

		if (!random)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}

		for (int i{}; i < snowFlakes.size(); ++i)
		{
			for (int o{}; o < snowFlakes[i].size(); ++o)
			{
				if (snowFlakes[i][o].y >= 500 || snowFlakes[i][o].x >= 500)
				{
					// snowPile.h += 5;
					snowFlakes[i][o].y = getRandom(1, 15);
				}
				else if (snowFlakes[i][o].y <= 0 || snowFlakes[i][o].x <= 0)
				{
					snowFlakes[i][o].y = 480;
				}

				/*
				for (int p{ mouseX }; p <= mouseX + 10; ++p)
				{
					if (snowFlakes[i][o].x == p)
					{
						// cout << i << '-' << o << " | " << snowFlakes[i][o].y << " | mouse x : " << p << '\n';

						snowFlakes[i][o].x += 1;

						break;
					}
				}

				for (int p{ mouseX }; p >= mouseX - 10; --p)
				{
					if (snowFlakes[i][o].x == p)
					{
						/// cout << i << '-' << o << " | " << snowFlakes[i][o].y << " | mouse -x : " << p << '\n';

						snowFlakes[i][o].x -= 1;

						break;
					}
				}

				for (int p{ mouseY }; p <= mouseY + 10; ++p)
				{
					if (snowFlakes[i][o].y == p)
					{
						snowFlakes[i][o].y -= 1;

						break;
					}
				}

				for (int p{ mouseY }; p <= mouseY - 10; ++p)
				{
					if (snowFlakes[i][o].y == p)
					{
						snowFlakes[i][o].y -= 1;

						break;
					}
				}
				*/

				/*
				
				for (int p{ mouseCollision.y }; p <= mouseCollision.h; ++p)
				{
					for (int a{ mouseCollision.x }; a <= mouseCollision.w; ++a)
					{
						if (snowFlakes[i][o].y == p && snowFlakes[i][o].x == a)
						{
							cout << "yes: " << mouseCollision.x << ", " << mouseCollision.y << '\n';

							snowFlakes[i][o].y -= 25;
							snowFlakes[i][o].x += 25;
						}
						else
						{
							// cout << "no: " << mouseCollision.x << ", " << mouseCollision.y << '\n';
						}
					}
				}
				*/

				/*
				if (snowFlakes[i][o].x == mouseCollision.x)
				{
					snowFlakes[i][o].x += getRandom(1, 5);
					snowFlakes[i][o].y -= getRandom(1, 5);
				}*/

				snowFlakes[i][o].y += speed;
				snowFlakes[i][o].x += getRandom(-1, 1);

				if (random)
				{
					SDL_SetRenderDrawColor(renderer, getRandom(1, 255), getRandom(1, 255), getRandom(1, 255), 255);
				}

				/*
				if (pileSnow)
				{
					SDL_RenderFillRect(renderer, &snowPile);
				}
				*/

				SDL_RenderFillRect(renderer, &snowFlakes[i][o]);
			}
		}

		// SDL_RenderFillRect(renderer, &mouseCollision);

		SDL_RenderPresent(renderer);

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		SDL_Delay(10);
	}
}

int main(int argc, char* args[])
{
	for (int i{}; i < snowFlakes.size(); ++i)
	{
		for (int o{}; o <= 20; ++o)
		{
			SDL_Rect snowFlake{ (o + 1) * 25, getRandom(5, 35) * (i + 1), 10, 10 };

			#ifdef DEBUG
				std::cout << i << ' ' << snowFlake.x << '\n';
			#endif

			snowFlakes[i].push_back(snowFlake);
		}
	}

	fall();

	return 0;
}