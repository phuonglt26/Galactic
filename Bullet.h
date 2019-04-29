#ifndef BULLET_H
#define BULLET_H
#include "Object.h"

class Bullet : public Object
{
public:
	Bullet(SDL_Renderer* des, std::string path);
	~Bullet();

	void update();

private:

};


#endif // !BULLET_H
