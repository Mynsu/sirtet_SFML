#include "../pch.h"
#include "NextTetriminoPanel.h"
#include "../model/Tetrimino.h"

void ui::NextTetriminoPanel::setTetrimino( const::model::Tetrimino& next )
{
	const sf::Color nextTetColor( next.color() );
	for ( uint8_t i = 0; ::model::tetrimino::BLOCKS_A_TETRIMINO != i; ++i )
	{
		mBlocks[i].setFillColor( nextTetColor );
	}
	const ::model::tetrimino::Type type = next.type( );
	const ::model::tetrimino::LocalSpace nextTetBlocks = next.blocks( );
	const sf::Vector2f margin( mCellSize_, mCellSize_ );
	uint8_t k = 0;
	for ( uint8_t i = 0u; i != ::model::tetrimino::BLOCKS_A_TETRIMINO*::model::tetrimino::BLOCKS_A_TETRIMINO; ++i )
	{
		if ( nextTetBlocks & (0x1u<<(::model::tetrimino::BLOCKS_A_TETRIMINO*::model::tetrimino::BLOCKS_A_TETRIMINO-i-1u)) )
		{
			sf::Vector2f localPos( sf::Vector2<uint8_t>(i%model::tetrimino::BLOCKS_A_TETRIMINO,i/model::tetrimino::BLOCKS_A_TETRIMINO) );
			switch( type )
			{
				case ::model::tetrimino::Type::I:
					mBlocks[k].setPosition( mPosition_ + margin - sf::Vector2f(0.f, mCellSize_*0.5f)
										   + localPos*mCellSize_ );
					break;
				case ::model::tetrimino::Type::O:
					mBlocks[k].setPosition( mPosition_ + margin
										   + localPos*mCellSize_ );
					break;
				default:
					mBlocks[k].setPosition( mPosition_ + margin*1.5f + sf::Vector2f(0.f, mCellSize_*0.5f)
										   + localPos*mCellSize_ );
					break;
			}
			if ( ::model::tetrimino::BLOCKS_A_TETRIMINO == ++k )
			{
				break;
			}
		}
	}
}

void ui::NextTetriminoPanel::draw( )
{
	mWindow_.draw( mPanel );
	for ( uint8_t i = 0; ::model::tetrimino::BLOCKS_A_TETRIMINO != i; ++i )
	{
		mWindow_.draw( mBlocks[i] );
	}
}