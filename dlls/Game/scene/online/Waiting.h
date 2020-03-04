#pragma once
#include "IScene.h"

namespace scene::online
{
	class Online;

	class Waiting final : public ::scene::online::IScene
	{
	public:
		Waiting( const sf::RenderWindow& window, Online& net );
		~Waiting( );
		
		void loadResources( const sf::RenderWindow& window ) override;
		::scene::online::ID update( std::vector<sf::Event>& eventQueue,
								   ::scene::online::Online& net,
								   const sf::RenderWindow& window ) override;
		void draw( sf::RenderWindow& window ) override;
	private:
		enum class State
		{
			TICKETING,
			SUBMITTING_TICKET,
		};
		enum class SoundIndex
		{
			SELECTION,
			NULL_MAX,
		};
		static bool IsInstantiated;
		uint16_t mOrder;
		::scene::online::Waiting::State mState;
		std::string mSoundPaths[(int)SoundIndex::NULL_MAX];
		sf::Font mFont;
		sf::Text mTextLabels[3];
	};
}