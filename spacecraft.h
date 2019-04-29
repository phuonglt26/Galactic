#ifndef SPACECRAFT_H
#define SPACECRAFT_H

#include "Object.h"
#include "Bullet.h"
#include <vector>
#include "Meteor.h"

class Spacecraft : public Object
{
public:
	Spacecraft(SDL_Renderer* des, std::string path, std::vector<Bullet*>* Ammo);
	~Spacecraft();

	void addBullet();
	void Update(const int&x, const int& y, const std::vector<Meteor*>& RockRain);


	bool isDie() const { return isDie_; }
private:
	bool isDie_;
	std::vector<Bullet*>* Ammo;
};

#endif // !SPACECRAFT_H
