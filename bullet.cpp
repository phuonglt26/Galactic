#include "Bullet.h"



Bullet::Bullet(SDL_Renderer* des, std::string path)
{
	this->des = des;
	Rect = { 0, 0, 0, 0 };
	loadIMG(path);
}



Bullet::~Bullet()
{
	SDL_DestroyTexture(pObject);
}

void Bullet::update()
{
	Rect.y -= 20;
}
                                                                                                                                                                                                                                          