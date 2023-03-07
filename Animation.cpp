#include "Animation.h"

Animation::Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime)
{
	this->imageCount = imageCount;
	this->switchTime = switchTime;

	this->totalTime = 0.f;
	this->currentImage.x = 0;

	this->uvRect.width = texture->getSize().x / static_cast<float>(imageCount.x);
	this->uvRect.height = texture->getSize().y / static_cast<float>(imageCount.y);


}

Animation::~Animation()
{
}

void Animation::update(int row, float deltaTime)
{
	this->currentImage.y = row;
	this->totalTime += deltaTime;

	if (this->totalTime >= this->switchTime)
	{
		this->totalTime -= this->switchTime;
		this->currentImage.x++;

		if (this->currentImage.x >= this->imageCount.x)
		{
			this->currentImage.x = 0;
		}
	}

	uvRect.left = currentImage.x * uvRect.width;
	uvRect.top = currentImage.y * uvRect.height;
}

