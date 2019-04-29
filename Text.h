#ifndef TEXT_H
#define TEXT_H
#include "Object.h"
#include <SDL_TTF.h>

class Text :public Object
{
public:
	Text();
	Text(SDL_Renderer* des, std::string path);
	~Text();

	void setText(const std::string &text)  { str_val = text; }
	void setColor(const Uint8 &Red, const Uint8 &Green, const Uint8 &Blue);
	bool loadTextureText();
protected:
	std::string str_val;
	SDL_Color textColor;
	TTF_Font* pFont;
};

class Score :public Text
{
public:
	Score(SDL_Renderer* des, std::string path);
	~Score();

	void addScore_val(const long long &val) { Score_val += val; }
	long long getScore_val() const { return Score_val; }

	void Render();
	void UpdateScore();
private:
	long long Score_val;
};

std::string Convert_toString(long long  value);
#endif // !TEXT_H

