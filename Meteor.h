#ifndef METEOR_H
#define METEOR_H
#include "Object.h"
#include <vector>
#include "Text.h"
#include "Bullet.h"
 
class Meteor : public Object
{
public:
	Meteor(SDL_Renderer* des, std::string path, const int& speed);
	~Meteor();

	void setSpeed(const int& speed) { this->speed = speed; }
	
	void Update(std::vector<Bullet*>* Ammo, Score& score);

private:
	int speed;
};



#endif // !METEOR_H
