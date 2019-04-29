#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>

#include "spacecraft.h"
#include "Meteor.h"


SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

SDL_Event Events;

const int RENDERER_DRAW_COLOR_R = 0xFF; //255	
const int RENDERER_DRAW_COLOR_G = 0xFF; //255
const int RENDERER_DRAW_COLOR_B = 0xFF; //255
const int RENDERER_DRAW_COLOR_A = 0xFF; //255



const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

const int METEOR_FREQ = 20; // tần xuất ra thêm đá

int mouse_x = 0;
int mouse_y = 0;

bool Init()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << '\n';
		return 0;
	}
	gWindow = SDL_CreateWindow("ASTEROID", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (gWindow == NULL)
	{
		std::cout << "Window could not be create! SDL_Error: " << SDL_GetError() << '\n';
		return 0;
	}

	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
	if (gRenderer == NULL)
	{
		std::cout << "Renderer could not be create! SDL_Error: " << SDL_GetError() << '\n';
		return 0;
	}

	SDL_SetRenderDrawColor(gRenderer, RENDERER_DRAW_COLOR_R, RENDERER_DRAW_COLOR_G, RENDERER_DRAW_COLOR_B, RENDERER_DRAW_COLOR_A);

	//Initialize PNG load
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << '\n';
		return 0;
	}
	//Init Font + Load Font
	if (TTF_Init() == -1)
	{
		printf("\nCan not init TTF.");
	}
	return 1;
}

void Close()
{
	SDL_Quit();
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	SDL_DestroyRenderer(gRenderer);
	gRenderer = NULL;
}

void NewGame() {
	Object background(gRenderer, "background.png");
	std::vector<Bullet*> Ammo;
	std::vector<Meteor*> RocksRain;
	Object Explosion(gRenderer, "explosion.png");
	Spacecraft spacecraft(gRenderer, "spacecraft.png", &Ammo);

	Score score(gRenderer, "Font.ttf");

	int delay = METEOR_FREQ;
	bool isQuit = 0;
	while (!isQuit)
	{
		while (SDL_PollEvent(&Events))
		{
			if (Events.type == SDL_QUIT)
			{
				isQuit = 1;
			}
			else if (Events.type == SDL_MOUSEMOTION)
			{
				mouse_x = Events.motion.x;
				mouse_y = Events.motion.y;
			}
			if (Events.type == SDL_MOUSEBUTTONDOWN)
			{
				if (!spacecraft.isDie()) {
					spacecraft.addBullet();
				}
			}
		}
		if (spacecraft.isDie()) {
			//gameover
			Explosion.setRect(spacecraft.getRect().x, spacecraft.getRect().y);
			Explosion.Render();
			SDL_RenderPresent(gRenderer);
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,
				"Message",
				"Game Over !!!!\nPress OK to continue.",
				NULL);
			break;
		}
		//update
		spacecraft.Update(mouse_x, mouse_y, RocksRain);
		for (int i = 0; i < Ammo.size(); i++)
		{
			Ammo[i]->update();
		}
		for (int i = 0; i < RocksRain.size(); i++)
		{
			RocksRain[i]->Update(&Ammo, score);
			if (RocksRain[i]->getRect().y > SCREEN_HEIGHT) {

				Meteor* pMeteor = RocksRain[i];
				RocksRain.erase(RocksRain.begin() + i--);
				delete pMeteor;
				pMeteor = NULL;
			}
		}
		//tao thien thach
		if (delay > 0) delay--;
		else {
			int n = rand() % 5 + 1; // chỉnh mỗi lần tạo đá ra mấy viên
			while (n--)
			{
				delay = METEOR_FREQ;
				Meteor* newMeteor = new Meteor(gRenderer, "meteor.png", rand() % 15 + 1); //  chỉnh tốc dộ của đá bay
				newMeteor->setRect(rand() % SCREEN_WIDTH, -100);
				RocksRain.push_back(newMeteor);
			}
		}
		score.UpdateScore();
		//Render
		SDL_RenderClear(gRenderer);

		background.Render();
		for (int i = 0; i < Ammo.size(); i++)
			Ammo[i]->Render();
		for (int i = 0; i < RocksRain.size(); i++)
			RocksRain[i]->Render();
		spacecraft.Render();
		score.Render();

		SDL_RenderPresent(gRenderer);
		SDL_Delay(30);
	}
	//delocated
	for (int i = 0; i < Ammo.size(); i++)
	{
		delete Ammo[i];
		Ammo[i] == NULL;
	}
	for (int i = 0; i < RocksRain.size(); i++)
	{
		delete RocksRain[i];
		RocksRain[i] = NULL;
	}


}

int main(int arg, char** argc)
{
	if (Init() == 0) return -1;
	bool isQuit = 0;
	Object Background(gRenderer, "background.png");
	Object newGameButton(gRenderer, "newgame.png");
	Object ExitButton(gRenderer, "exit.png");

	while (!isQuit) {
		while (SDL_PollEvent(&Events)) {
			if (Events.type == SDL_QUIT)
			{
				isQuit = 1;
			}
			if (Events.type == SDL_MOUSEBUTTONDOWN) {
				int x = Events.button.x;
				int y = Events.button.y;
				SDL_Point Point = { x, y };
				if (SDL_PointInRect(&Point, &newGameButton.getRect())) {
					NewGame();
				}
				if (SDL_PointInRect(&Point, &ExitButton.getRect())) {
					isQuit = 1;
				}
			}
		}

		newGameButton.setRect(200, 400);
		ExitButton.setRect(500, 400);

		SDL_RenderClear(gRenderer);

		Background.Render();
		newGameButton.Render();
		ExitButton.Render();

		SDL_RenderPresent(gRenderer);
		SDL_Delay(10);
	}

	Close();
	return 0;
}