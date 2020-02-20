#pragma once
#include <list>
#include <SFML/Window.hpp>

namespace scene::inPlay
{
	enum class ID
	{
		EXIT = -3,
		UNDO = -2,
		AS_IS = -1,
		READY,
		PLAYING,
		GAME_OVER,
		ALL_LEVELS_CLEARED,
		ASSERTION,
	};

	class IScene
	{
	public:
		IScene( const IScene& ) = delete;
		void operator=( const IScene& ) = delete;
		virtual ~IScene( ) = default;
		
		virtual void loadResources( ) = 0;
		// Returns 0 when doing nothing, -1 when coming back, 1 when going on.
		virtual ::scene::inPlay::ID update( std::vector<sf::Event>& eventQueue ) = 0;
		virtual void draw( ) = 0;

		// NOTE: Protected constructor prevents users from instantiating the abstract class.
	protected:
		IScene( ) = default;
	};
}