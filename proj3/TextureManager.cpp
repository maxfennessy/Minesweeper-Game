#include "TextureManager.h"

unordered_map<string, sf::Texture> TextureManager::textures;

void TextureManager::LoadTexture(string fileName)
{
	string path = "images/";
	path += fileName + ".png";

	textures[fileName].loadFromFile(path);
}

void TextureManager::LoadTextureCounter(int count)
{
	string path = "images/digits.png";

	textures["digits" + count].loadFromFile(path, sf::IntRect(count * 21, 0, 21, 32));
}

sf::Texture& TextureManager::GetTexture(string textureName)
{
	if (textures.find(textureName) == textures.end()) // if not found
	{
		LoadTexture(textureName);
	}
	return textures[textureName];
}

sf::Texture& TextureManager::GetTextureCounter(int count)
{
	if (textures.find("digits" + count) == textures.end()) // if not found
	{
		LoadTextureCounter(count);
	}
	return textures["digits" + count];
}

void TextureManager::Clear()
{
	textures.clear(); // clears all stored objects
}