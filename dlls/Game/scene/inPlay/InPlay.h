#pragma once
#pragma hdrstop
#include <Lib/precompiled.h>
#include "../IScene.h"
#include "IScene.h"

namespace scene::inPlay
{
	class InPlay final : public ::scene::IScene
	{
	public:
		InPlay( ) = delete;
		InPlay( sf::RenderWindow& window, const SetScene_t& setScene );
		~InPlay( );

		void loadResources( ) override;
		void update( ) override;
		void draw( ) override;
		::scene::ID currentScene( ) const override;
		///auto newEqualTypeInstance( ) -> std::unique_ptr< ::scene::IScene > override;
	private:
		static bool IsInstantiated;
		sf::RenderWindow& mWindow;
		const SetScene_t& mSetScene;
		std::unique_ptr< ::scene::inPlay::IScene > mCurrentScene;
		sf::RectangleShape mBackgroundRect;
	};
}