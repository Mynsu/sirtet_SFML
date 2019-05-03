#pragma once
#pragma hdrstop
#include "../Common.h"
#include "ISequence.h"

namespace sequence
{
	class GAME_API Opening final : public ISequence
	{
	public:
		Opening( ) = delete;
		Opening( sf::RenderWindow& window );
		~Opening( ) = default;

		void update( ) override;
		void draw( ) override;
	private:
		sf::RenderWindow& mWindow;
		sf::Texture mTexture;
		sf::Sprite mSprite;
	};
}
