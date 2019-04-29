#include "Object.h"
#include <iostream>

Object::Object()
{
}

Object::Object(SDL_Renderer * des, std::string path)
{
	this->des = des;
	Rect = { 0, 0, 0, 0 };
	loadIMG(path);
}

Object::~Object()
{
	SDL_DestroyTexture(pObject);
	pObject = NULL;
}

void Object::loadIMG(std::string path)
{
	SDL_Surface* loadedSurface = NULL;
	loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface != NULL)
	{
		Rect.w = loadedSurface->w;
		Rect.h = loadedSurface->h;
		pObject = SDL_CreateTextureFromSurface(des, loadedSurface);
		if (pObject == NULL)
		{
			std::cout << "Could not create texture form surface, IMG_path: " << path << '\n' << SDL_GetError() << '\n';
		}
	}
	else std::cout << "Could not load image: " << path << '\n' << SDL_GetError() << '\n';
	SDL_FreeSurface(loadedSurface);
}

void Object::Render(SDL_Rect* clips)
{
	SDL_RenderCopy(des, pObject, clips, &Rect);
}
