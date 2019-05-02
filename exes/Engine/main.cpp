﻿#pragma hdrstop
#include <iostream>
#include <unordered_map>
#include <memory>
#include <SFML/Graphics.hpp>
#include <Game/sequence/ISequence.h>
#include <Game/sequence/Opening.h>
#include <Lib/Endian.h>
#include "ServiceLocator.h"

using hash = uint32_t;

int main( int argc, char* argv[ ] )
{
	std::unordered_map< hash, int > variableTable;//int보다 general해야 하는데...
	variableTable.reserve( 10 );

	variableTable.emplace( 3139364470, 800 ); // winWidth
	variableTable.emplace( 1251131622, 600 ); // winHeight
	variableTable.emplace( 3519249062, sf::Style::Close ); // winStyle
/*
=====
Handling arguments
=====
*/
	{
		const std::string argHelp0( "--help" );
		const std::string argHelp1( "--h" );
		const std::string argWinSize( "--WS" );
		const std::string argFullscreen( "--FS" );

		for ( int i = 1; i < argc; ++i )
		{
			const char* cur = argv[ i ];
			if ( 0 == argHelp0.compare( cur ) || 0 == argHelp1.compare( cur ) )
			{
				std::cout << "Here are case-sensitive parameters available:\n";
				std::cout << "\t" << argHelp0.data( ) << ", " << argHelp1.data( ) << ": Show parameters with their own arguments.\n";
				std::cout << "\t" << argWinSize.data( ) << " [width] [height]: Set the window size.\n";
				std::cout << "\t" << argFullscreen.data( ) << ": Run on the fullscreen mode.\n";

				return 0;
			}
			else if ( 0 == argWinSize.compare( cur ) )
			{
				const int subArg0 = std::atoi( argv[ ++i ] );
				// Exception: When NON-number characters has been input,
				if ( 0 == subArg0 )
				{
					std::cerr << "Error: Let me know a number, not character.\n";
					return -1;
				}
				// Exception: When the argument is too low to be a WIDTH value,
				else if ( 400 >= subArg0 )
				{
					std::cerr << "Error: Too narrow width.\n";
					return -1;
				}
				variableTable.find( 3139364470 )->second = subArg0;

				const int subArg1 = std::atoi( argv[ ++i ] );
				// Exception: When NON-number characters has been input,
				if ( 0 == subArg1 )
				{
					std::cerr << "Error: Let me know a number, not character.\n";
					return -1;
				}
				// Exception: When the argument is too low to be a HEIGHT value,
				else if ( 300 >= subArg1 )
				{
					std::cerr << "Error: Too low height.\n";
					return -1;
				}
				variableTable.find( 1251131622 )->second = subArg1;
			}
			else if ( 0 == argFullscreen.compare( cur ) )
			{
				variableTable.find( 3519249062 )->second |= sf::Style::Fullscreen;
			}
			else
			{
				std::cerr << "Error: There is no such parameter.\n";
				return -1;
			}
		}
	}
/*
=====
Initialization
=====
*/
	{
		::util::endian::BindConvertFunc( );
	}

/*
=====
Window
=====
*/
	sf::RenderWindow window( sf::VideoMode( variableTable.find( 3139364470 )->second, // winWidth
											variableTable.find( 1251131622 )->second ), // winHeight
							 "Sirtet: the Classic",
							 variableTable.find( 3519249062 )->second ); // winStyle
	window.setFramerateLimit( 60 );
	auto& console = *ServiceLocator::Console( window.getSize( ) );
	std::unique_ptr< ::sequence::ISequence > game( std::make_unique< ::sequence::Opening >( window ) );

	bool isOpen = true;
	while ( true == isOpen )
	{
		sf::Event event;
		while ( true == window.pollEvent( event ) )
		{
			if ( sf::Event::Closed == event.type )
			{
				isOpen = false;
			}
			else if ( sf::Event::KeyPressed == event.type )
			{
				if ( sf::Keyboard::Escape == event.key.code )
				{
					if ( false == console.isVisible( ) )
					{
						isOpen = false;
					}
				}
			}
		
			// Console
			{
				console.handleEvent( event );
			}
		}

		game->update( );//

		window.clear( );
		game->draw( );//
		if ( true == console.isVisible( ) )
		{
			window.draw( console );
		}
		window.display( );
	}

/*
=====
Resource Free
=====
*/
	window.close( );
}