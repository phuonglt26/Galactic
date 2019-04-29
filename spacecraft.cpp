#include "spacecraft.h"
#include "Meteor.h"


bool isColision(SDL_Rect SpaceCraft_rect, SDL_Rect Meteor_rect) { //SpaceCraft_rect va cham voi Meteor_rect

	int offset = 20;
	int x = SpaceCraft_rect.x;
	int y = SpaceCraft_rect.y;
	int w = SpaceCraft_rect.w;
	int h = SpaceCraft_rect.h;
	SDL_Point SpaceCraft_TopLeft = { x + offset, y };
	SDL_Point SpaceCraft_TopRight = { x + w - offset, y };
	SDL_Point SpaceCraft_BotLeft = { x + offset, y + h - offset };
	SDL_Point SpaceCraft_BotRight = { x + w - offset, y + h - offset };

	if (SDL_PointInRect(&SpaceCraft_TopLeft, &Meteor_rect)) return 1;
	if (SDL_PointInRect(&SpaceCraft_TopRight, &Meteor_rect)) return 1;
	if (SDL_PointInRect(&SpaceCraft_BotLeft, &Meteor_rect)) return 1;
	if (SDL_PointInRect(&SpaceCraft_BotRight, &Meteor_rect)) return 1;
	return 0;
}

Spacecraft::Spacecraft(SDL_Renderer* des, std::string path, std::vector<Bullet*>* Ammo) {
	isDie_ = 0;
	this->des = des;
	Rect = { 0, 0, 0, 0 };
	loadIMG(path);
	this->Ammo = Ammo;
}

Spacecraft::~Spacecraft()
{
	SDL_DestroyTexture(pObject);
	pObject = NULL;
}

void Spacecraft::addBullet()
{
	Bullet* newBullet = new Bullet(des, "bullet.png");
	newBullet->setRect(Rect.x + 30, Rect.y);
	Ammo->push_back(newBullet);

}

void Spacecraft::Update(const int& mouse_x, const int& mouse_y, const std::vector<Meteor*>& RockRain)
{
//Update
	//xoa vien dan o ngoai man hinh
	for (int i = 0; i < Ammo->size(); i++)
	{
		int x = Ammo->at(i)->getRect().x;
		int y = Ammo->at(i)->getRect().y;
		if (y < 0) {
			Bullet* pbullet = Ammo->at(i);
			Ammo->erase(Ammo->begin() + i--);
			delete pbullet;
			pbullet = NULL;
		}
	}
	//may bay va cham voi da
	for (int i = 0; i < RockRain.size(); i++)
	{
		if (isColision(Rect, RockRain[i]->getRect())) isDie_ = 1;
	}
	//update vi tri
	setRect(mouse_x - 35, mouse_y - 30);



}

