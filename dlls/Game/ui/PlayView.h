#pragma once
#include "../model/Tetrimino.h"
#include "../ui/NextTetriminoPanel.h"
#include "../vfx/Combo.h"

namespace scene::online
{
	class Online;
}

namespace ui
{
	class PlayView
	{
	public:
		PlayView( const bool isPlayable );
		PlayView( const PlayView& another ) = delete;
		PlayView( PlayView&& ) = delete;
		void operator=( const PlayView& ) = delete;
		virtual ~PlayView( ) = default;
		
		static void LoadResources( );
		bool loadCountdownSprite( std::string& filePath );
		void setCountdownSpriteDimension( const sf::Vector2f origin,
										 const float cellSize,
										 const sf::Vector2i clipSize );
		// Initializes member variables and goes to ON_START state.
		void getReady( );
		void update( std::vector<sf::Event>& eventQueue, ::scene::online::Online& net );
		void setNewCurrentTetrimino( const ::model::tetrimino::Type newCurrentType );
		// Applies the stage received from the server.
		// Different from ::model::Stage::deserialize(...).
		void updateStage( const ::model::stage::Grid& grid );
		// Plays line clear visual and sound effects.
		void playLineClearEffects( const uint8_t numOfLinesCleared );
		// Goes to WAITING_OR_OVER state and makes the next-tetrimino-panel clean.
		void gameOver( );
		void draw( sf::RenderWindow& window );
		::model::Tetrimino& currentTetrimino( );
		::model::Stage& stage( );
		::vfx::Combo& vfxCombo( );
		::ui::NextTetriminoPanel& nextTetriminoPanel( );
	private:
		enum class AlarmIndex
		{
			COUNT_DOWN,
			TETRIMINO_DOWN,
			LAND_ON_SERVER,
			NONE_MAX,
		};
		// This function doesn't reset the alarm.
		bool alarmAfter( const uint16_t milliseconds, const AlarmIndex index )
		{
			bool elapsed = false;
			if ( std::chrono::milliseconds(milliseconds) < Clock::now()-mAlarms[(int)index] )
			{
				elapsed = true;
			}
			return elapsed;
		}
		void resetAlarm( const AlarmIndex index )
		{
			mAlarms[(int)index] = Clock::now();
		}
		bool mHasTetriminoLandedOnClient, mHasTetriminoLandedOnServer,
			mIsForThisPlayer, mHasCurrentTetrimino;
		uint8_t mCountDownSec, mNumOfLinesCleared;
		uint16_t mFrameCountInputDelay, mFrameCountVfxDuration, mFPS_,
				mTempoMs;
		enum class State
		{
			ON_START,
			PLAYING,
			WAITING_OR_OVER,
		};
		enum class SoundIndex
		{
			TETRIMINO_LOCK,
			LINE_CLEAR,
			NONE_MAX,
		};
		static std::string SoundPaths[(int)SoundIndex::NONE_MAX];
		State mState_;
		sf::Vector2i countdownSpriteSize_;
		// NOTE: Stack-based sf::Texture instance made a malfunction here.
		std::unique_ptr<sf::Texture> mTexture_countdown;
		Clock::time_point mAlarms[(int)AlarmIndex::NONE_MAX];
		std::queue<::model::Tetrimino> mNextTetriminos;
		sf::Sprite mSprite_countdown;
		::model::Tetrimino mCurrentTetrimino;
		::vfx::Combo mVfxCombo;
		::model::stage::Grid mBufferForStage;
		::model::Stage mStage;
		::ui::NextTetriminoPanel mNextTetriminoPanel;
	};
}