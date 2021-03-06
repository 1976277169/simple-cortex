// ==========
// render2d.h
// ==========

#ifndef RENDER2D_H
#define RENDER2D_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "utils/utils.h"

class Render2D
{
public:
	Render2D(unsigned int sizeX, unsigned int sizeY)
	{
		_sizeX = sizeX;
		_sizeY = sizeY;

		_numPixels = _sizeX * _sizeY;

		_image.create(_sizeX, _sizeY);

		_rData.resize(_numPixels);
		_gData.resize(_numPixels);
		_bData.resize(_numPixels);

		for (int p = 0; p < _numPixels; p++)
		{
			_rData[p] = 0.0f;
			_gData[p] = 0.0f;
			_bData[p] = 0.0f;
		}
	}

	void setPixelsFromBinaryVector (char color, bool transparancy, std::vector<char> binaryVec)
	{
		for (int p = 0; p < _numPixels; p++)
		{
			if (!(transparancy && binaryVec[p] == 0))
			{
				switch(color)
				{
					case 'r':
						_rData[p] = (float)binaryVec[p];
						break;

					case 'g':
						_gData[p] = (float)binaryVec[p];
						break;

					case 'b':
						_bData[p] = (float)binaryVec[p];
						break;
				}
			}
		}
	}

	void setPixels (std::vector<float> r, std::vector<float> g, std::vector<float> b)
	{
		for (int p = 0; p < _numPixels; p++)
		{
			_rData[p] = r[p];
			_gData[p] = g[p];
			_bData[p] = b[p];
		}
	}

	void setPosition(unsigned int positionX, unsigned int positionY)
	{   
		_sprite.setPosition(positionX, positionY);
	}

	void setScale(float scale)
	{   
		_sprite.setScale(sf::Vector2f(scale, scale));
	}

	sf::Sprite getSprite()
	{   
		for (int y = 0; y < _sizeX; y++)
		{
			for (int x = 0; x < _sizeX; x++)
			{
 				unsigned int i = x + _sizeX * y;

				_color.r = 255.0f * _rData[i];
				_color.g = 255.0f * _gData[i];
				_color.b = 255.0f * _bData[i];

				_image.setPixel(x, y, _color);
			}
		}

		_texture.loadFromImage(_image);
		_sprite.setTexture(_texture);
		_sprite.setOrigin(sf::Vector2f(_texture.getSize().x * 0.5f, _texture.getSize().y * 0.5f));

		return _sprite;
	}

private:
	unsigned int _sizeX;
	unsigned int _sizeY;
	unsigned int _numPixels;

	std::vector<float> _rData;
	std::vector<float> _gData;
	std::vector<float> _bData;

	sf::Color _color;
	sf::Image _image;
	sf::Texture _texture;
	sf::Sprite _sprite;
};

#endif
