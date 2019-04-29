#include "Text.h"
#include <sstream>

Text::Text()
{
	textColor.r = 0;
	textColor.g = 255;
	textColor.b = 255;
}

Text::Text(SDL_Renderer * des, std::string path)
{
	textColor.r = 0;
	textColor.g = 255;
	textColor.b = 255;
	this->des = des;
	pFont = TTF_OpenFont("Font.ttf", 20);
}
Text::~Text()
{
	;
}

void Text::setColor(const Uint8 & Red, const Uint8 & Green, const Uint8 & Blue)
{
	SDL_Color color = { Red, Green, Blue };
	textColor = color;
}

bool Text::loadTextureText()
{
	if (pFont != NULL)
	{
		SDL_Surface* textSurface = TTF_RenderText_Solid(pFont, str_val.c_str(), textColor);
		if (textSurface != NULL)
		{
			pObject = SDL_CreateTextureFromSurface(des, textSurface);
			if (pObject != NULL)
			{
				Rect.w = textSurface->w;
				Rect.h = textSurface->h;
			}
			SDL_FreeSurface(textSurface);
		}
	}
 	return pObject == NULL;
}


Score::Score(SDL_Renderer * des, std::string path)
{
	Score_val = 0;
	this->des = des;
	pFont = TTF_OpenFont("font.ttf", 25);
	Rect.x = 0;
	Rect.y = 0;
}

Score::~Score()
{
}

void Score::UpdateScore()
{
	setText(Convert_toString(Score_val));
	loadTextureText();
}

void Score::Render()
{
	
	SDL_RenderCopy(des, pObject, NULL, &Rect);
	SDL_DestroyTexture(pObject);

}
std::string Convert_toString(long long  value)
{
	std::string result;
	std::ostringstream convert;
	convert << value;
	result = convert.str();
	return result;
}
