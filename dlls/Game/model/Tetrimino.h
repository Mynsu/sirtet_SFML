#pragma once
#pragma hdrstop
#include <Lib/precompiled.h>
#include <array>
#include "Stage.h"
#include "../Constant.h"

namespace model
{
	enum class Rotation
	{
		A,
		B,
		C,
		D,

		NULL_MAX,
	};

	// BLOCKS_A_TETRIMINO x BLOCKS_A_TETRIMINO
	// 4 x 4
	using LocalSpace = uint16_t;
	class Tetrimino
	{
	public:
		// Needs initialization.
		inline Tetrimino( )
			: mIsFallingDown( false )
		{
			mCellShape.setOutlineThickness( 1.f );
			mCellShape.setOutlineColor( sf::Color::Black );
		}
		inline Tetrimino( const Tetrimino& arg )
			: mIsFallingDown( false ),
			mRotationID( arg.mRotationID ), mPosition( arg.mPosition )
		{
			mCellShape.setFillColor( arg.mCellShape.getFillColor( ) );
			mCellShape.setOutlineThickness( 1.f );
			mCellShape.setOutlineColor( sf::Color::Black );
			for ( uint8_t i = 0u; i != static_cast< uint8_t >( Rotation::NULL_MAX ); ++i )
			{
				mPossibleRotations[ i ] = arg.mPossibleRotations[ i ];
			}
		}
		inline void operator=( const Tetrimino& arg )
		{
			mRotationID = arg.mRotationID;
			mPosition = arg.mPosition;
			mCellShape.setFillColor( arg.mCellShape.getFillColor( ) );
			for ( uint8_t i = 0u; i != static_cast< uint8_t >( Rotation::NULL_MAX ); ++i )
			{
				mPossibleRotations[ i ] = arg.mPossibleRotations[ i ];
			}
		}
		~Tetrimino( ) = default;

		static Tetrimino Spawn( );

		inline void draw( sf::RenderWindow& window )
		{
			for ( uint8_t i = 0; i != ::model::tetrimino::BLOCKS_A_TETRIMINO*::model::tetrimino::BLOCKS_A_TETRIMINO; ++i )
			{
				if ( (mPossibleRotations[static_cast<int>(mRotationID)]>>i) & 1u ) //�ñ�: msb 0���� ä������ 1�ϱ�?
				{
					// Coordinate transformation
					const sf::Vector2< int8_t > localPos( i%model::tetrimino::BLOCKS_A_TETRIMINO, i/model::tetrimino::BLOCKS_A_TETRIMINO );
					mCellShape.setPosition( mOrigin_ + sf::Vector2f(mPosition+localPos)*mCellSize_ );
					window.draw( mCellShape );
				}
			}
		}
		inline bool isFallingDown( ) const
		{
			return mIsFallingDown;
		}
		inline sf::Vector2<int8_t> position( ) const
		{
			return mPosition;
		}
		inline sf::Color color( ) const
		{
			return mCellShape.getFillColor( );
		}
		// Current blocks within their own local space.
		inline LocalSpace blocks( ) const
		{
			return mPossibleRotations[ static_cast<int>(mRotationID) ];
		}
		// Returns true when colliding with the floor or another tetrimino.
		inline bool down( const std::array< std::array<::model::Cell,::model::stage::GRID_WIDTH>, ::model::stage::GRID_HEIGHT >& grid, const uint8_t diff = 1u )
		{
			ASSERT_TRUE( diff < ::model::stage::GRID_HEIGHT );
			mPosition.y += diff;
			return hasCollidedWith( grid );
		}
		inline void tryMoveLeft( const std::array< std::array<::model::Cell,::model::stage::GRID_WIDTH>, ::model::stage::GRID_HEIGHT >& grid, const uint8_t diff = 1u )
		{
			ASSERT_TRUE( diff < ::model::stage::GRID_WIDTH );
			Tetrimino afterMove( *this );
			afterMove.mPosition.x -= diff;
			if ( false == afterMove.hasCollidedWith( grid ) )
			{
				*this = afterMove;
			}
		}
		inline void tryMoveRight( const std::array< std::array<::model::Cell,::model::stage::GRID_WIDTH>, ::model::stage::GRID_HEIGHT >& grid, const uint8_t diff = 1u )
		{
			ASSERT_TRUE( diff < ::model::stage::GRID_WIDTH );
			Tetrimino afterMove( *this );
			afterMove.mPosition.x += diff;
			if ( false == afterMove.hasCollidedWith( grid ) )
			{
				*this = afterMove;
			}
		}
		// Rotates counter-clockwise.
		void tryRotate( const std::array< std::array<::model::Cell,::model::stage::GRID_WIDTH>, ::model::stage::GRID_HEIGHT >& grid );
		inline void fallDown( const bool isFallingDown = true )
		{
			mIsFallingDown = isFallingDown;
		}
		inline void setOrigin( const sf::Vector2f& origin )
		{
			mOrigin_ = origin;
		}
		inline void setSize( const float cellSize )
		{
			ASSERT_TRUE( 0 < cellSize );
			mCellShape.setSize( sf::Vector2f( cellSize, cellSize ) );
			mCellSize_ = cellSize;
		}
		inline void setColor( const sf::Color color )
		{
			mCellShape.setFillColor( color );
		}
	private:
		bool hasCollidedWith( const std::array< std::array<Cell,::model::stage::GRID_WIDTH>, ::model::stage::GRID_HEIGHT >& grid ) const;
		bool mIsFallingDown;
		// X and y on global coordinate.
		// Unit: Grid.
		sf::Vector2< int8_t > mPosition;
		Rotation mRotationID;
		float mCellSize_;
		sf::Vector2f mOrigin_;
		sf::RectangleShape mCellShape;
		LocalSpace mPossibleRotations[ static_cast<int>(Rotation::NULL_MAX) ];
		static sf::Vector2<int8_t> Test[ static_cast<int>(Rotation::NULL_MAX) ][ 4 ];
	};
}