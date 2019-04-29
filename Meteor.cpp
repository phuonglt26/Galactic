#include "Meteor.h"
#include "spacecraft.h"
#include "Bullet.h"

 bool inside(SDL_Rect box1, SDL_Rect box2) { //meteor va cham voi bullet

	 SDL_Point box2_TopLeft = { box2.x, box2.y };
	 SDL_Point box2_TopRight = { box2.x + box2.h, box2.y };
	 if (SDL_PointInRect(&box2_TopLeft, &box1)) return 1;
	 if (SDL_PointInRect(&box2_TopRight, &box1)) return 1;
	 return 0;
}

Meteor::Meteor(SDL_Renderer * des, std::string path, const int & speed)
{
	this->des = des;
	loadIMG(path);
	float ratio_scale = rand() % 10 - 2;
	ratio_scale = ratio_scale / 10. + 1;
	Rect = { 0, 0, (int)(ratio_scale*50), (int)(ratio_scale*50) };
	this->speed = speed;
}

Meteor::~Meteor()
{
}
void checkinside()
{
	Meteor * meteo = NULL;
	Spacecraft* spacecraft = NULL;
	if (inside(meteo->getRect(), spacecraft->getRect()))
	{
		delete meteo;
	}
}

void Meteor::Update(std::vector<Bullet*>* Ammo, Score& score)
{
	for (int i = 0; i < Ammo->size(); i++)
	{
		Bullet* pBullet = Ammo->at(i);
		
		if (inside(Rect, pBullet->getRect())) {

			score.addScore_val(100);
			Ammo->erase(Ammo->begin() +i--);
			pBullet->setRect(-100, -100); // lam vien dan bien mat (ra ngoai man hinh)
			Object Explosion(des, "explosion.png");
			Explosion.setRect(Rect);
			Explosion.Render();
			SDL_RenderPresent(des);
			SDL_Delay(50);
			Rect.y = -100; // lam vien da bay ra ngoai man hinh
			
		}
	}

	Rect.y += speed;

	
}
