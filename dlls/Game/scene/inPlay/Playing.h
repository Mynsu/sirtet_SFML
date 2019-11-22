#pragma once
#include "IScene.h"
#include "../../model/Tetrimino.h"
#include "../../model/Stage.h"
#include "../../vfx/Combo.h"

namespace scene::inPlay
{
	class Playing final : public ::scene::inPlay::IScene
	{
	public:
		Playing( ) = delete;
		Playing( sf::RenderWindow& window, sf::Drawable& shapeOrSprite, const std::unique_ptr<::scene::inPlay::IScene>& overlappedScene );
		~Playing( ) = default;

		void loadResources( ) override;
		::scene::inPlay::ID update( std::list< sf::Event >& eventQueue ) override;
		void draw( ) override;
	private:
		void reloadTetrimino( );
		uint8_t mRowCleared;
		uint32_t mFrameCount_fallDown, mFrameCount_clearingInterval_, mFrameCount_clearingVfx_, mFrameCount_gameOver;
		float mTempo;
		float mCellSize_;
		sf::RenderWindow& mWindow_;
		sf::RectangleShape& mBackgroundRect_;
		const std::unique_ptr<::scene::inPlay::IScene>& mOverlappedScene_;
		sf::Vector2f mMargin_;
		sf::Vector2f mNextTetriminoPanelPosition_;
		sf::RectangleShape mNextTetriminoPanel;
		sf::RectangleShape mNextTetriminoBlock_;
		::vfx::Combo mVfxCombo;
		::model::Tetrimino mCurrentTetrimino;
		std::queue< ::model::Tetrimino > mNextTetriminos;
		::model::Stage mPlayerStage;
	};
}