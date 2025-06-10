#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
using std::unordered_map;
using std::string;

class TextureManager
{
	static unordered_map<string, sf::Texture> textures;
	static void LoadTexture(string textureName);
	static void LoadTextureCounter(int count);
public:
	static sf::Texture& GetTexture(string textureName);
	static sf::Texture& GetTextureCounter(int count);
	static void Clear();
};

