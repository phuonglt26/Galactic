#ifndef OBJECT_H
#define OBJECT_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>

class Object {
public:
	Object();
	Object(SDL_Renderer* des, std::string path);
	~Object();

	void loadIMG(std::string path);
	virtual void Render(SDL_Rect* clips = NULL);

	void setRect(const int& x, const int& y) { Rect.x = x; Rect.y = y; }
	void setRect(const SDL_Rect &Rect) { this->Rect = Rect; }
	SDL_Rect getRect() const { return Rect; }

protected:
	SDL_Texture* pObject;
	SDL_Renderer* des;
	SDL_Rect Rect;
};



#endif // !OBJECT_H
