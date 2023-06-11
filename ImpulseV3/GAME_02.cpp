#include "Impulse.h"
#include <array>
#include <vector>

GAME_BEGIN( GAME_02 );

struct OBJECT {
	int button = 0;
	int mark = 0;
};

static const int PROBLEM_NUM = 4;
const std::array< int, PROBLEM_NUM > getRandom_ARRAY = { MARK_DRINK, MARK_SHOES, MARK_WATCH, MARK_MISANGA };

std::vector< int > _theme = { };
std::array< int, 3 > _arrow = {};
int _frame = 0;
std::array< OBJECT, PROBLEM_NUM > _object = { };
int _wait_count = 0;
int _clear_count = 0;
int _plate = 0;
int _number = 0;
int _frame_number = 0;

int tag( ) {
	return 2;
}

void setup( ) {
	_wait_count = 0;
	_clear_count = 0;

	_frame = createAsset( ASSET::FRAME );
	setAsset( _frame, CMD::POS_X, ( SCREEN_WIDTH / 2 - 280 ) + 140 * 0 + 140 / 2 );
	setAsset( _frame, CMD::POS_Y, SCREEN_HEIGHT / 2 + -100 );

	this->createTheme( );
	this->createObject( );

	_plate = createAsset( ASSET::PLATE );
	setAsset( _plate, CMD::STATUS, PLATE_REMAINING );
	setAsset( _plate, CMD::POS_X, SCREEN_WIDTH - getAsset( _plate, CMD::WIDTH ) / 2 - 100 );
	setAsset( _plate, CMD::POS_Y, getAsset( _plate, CMD::HEIGHT ) / 4 );

	_frame_number = createAsset( ASSET::FRAME );
	setAsset( _frame_number, CMD::POS_X, getAsset( _plate, CMD::POS_X ) );
	setAsset( _frame_number, CMD::POS_Y, getAsset( _plate, CMD::POS_Y ) + 85 );

	_number = createAsset( ASSET::NUMBER );
	setAsset( _number, CMD::STATUS, 3 );
	setAsset( _number, CMD::POS_X, getAsset( _plate, CMD::POS_X ) );
	setAsset( _number, CMD::POS_Y, getAsset( _plate, CMD::POS_Y ) + 85 );

	stopwatch( STOPWATCH::START );
	creator( "ゲームプログラマー専攻 ３年", "岡田 征海" );
}

void update( ) {
	for ( int i = 0; i < PROBLEM_NUM; i++ ) {
		if ( getAsset( _object[ i ].button, CMD::TOUCH ) == 1 ) {
			if ( getAsset( _object[ i ].mark, CMD::STATUS ) == getAsset( _theme[ 0 ], CMD::STATUS ) ) {
				setAsset( _object[ i ].button, CMD::VISIBLE, 0 );
				setAsset( _object[ i ].mark, CMD::VISIBLE, 0 );
				setAsset( _theme[ 0 ], CMD::VISIBLE, 0 );

				_theme.erase( _theme.begin( ) );

				if ( _theme.size( ) > 0 ) {
					setAsset( _frame, CMD::POS_X, getAsset( _theme[ 0 ], CMD::POS_X ) );
				}
			}
		}
	}

	if ( _theme.size( ) == 0 ) {
		stopwatch( STOPWATCH::STOP );
		_wait_count++;

		if ( _wait_count > 80 ) {
			stopwatch( STOPWATCH::START );

			_wait_count = 0;
			_clear_count++;
			setAsset( _number, CMD::STATUS, 3 - _clear_count );

			if ( _clear_count != 3 ) {
				this->createTheme( );
				this->createObject( );
			} else {
				setAsset( _frame, CMD::VISIBLE, 0 );
			}
		}
	}

	if ( _clear_count >= 3 ) {
		finish( );
	}
}

STRING info( ) {
	return "選択されているマークと同じマーク\nの付いたボタンを押していこう！";
}

void createTheme( ) {
	_theme.clear( );
	_arrow.fill( 0 );

	std::vector< int >v = { getRandom_ARRAY[ 0 ], getRandom_ARRAY[ 1 ], getRandom_ARRAY[ 2 ], getRandom_ARRAY[ 3 ] };
	for ( int i = 0; i < PROBLEM_NUM; i++ ) {
		_theme.push_back( createAsset( ASSET::MARK ) );

		const int r = getRand( ) % v.size( );
		setAsset( _theme[ i ], CMD::STATUS, v[ r ] );
		v.erase( v.begin( ) + r );

		setAsset( _theme[ i ], CMD::POS_X, ( SCREEN_WIDTH / 2 - 560 ) + 280 * i + 280 / 2 );
		setAsset( _theme[ i ], CMD::POS_Y, SCREEN_HEIGHT / 2 + -100 );
	}

	for ( int i = 0; i < 3; i++ ) {
		_arrow[ i ] = createAsset( ASSET::MARK );
		setAsset( _arrow[ i ], CMD::STATUS, MARK_RIGHT );
		setAsset( _arrow[ i ], CMD::POS_X, ( SCREEN_WIDTH / 2 - 420 ) + 280 * i + 280 / 2 );
		setAsset( _arrow[ i ], CMD::POS_Y, SCREEN_HEIGHT / 2 + -100 );
	}

	setAsset( _frame, CMD::POS_X, getAsset( _theme[ 0 ], CMD::POS_X ) );
}

void createObject( ) {
	_object.fill( OBJECT( ) );

	std::vector< int >v = { getRandom_ARRAY[ 0 ], getRandom_ARRAY[ 1 ], getRandom_ARRAY[ 2 ], getRandom_ARRAY[ 3 ] };
	for ( int i = 0; i < PROBLEM_NUM; i++ ) {
		_object[ i ].button = createAsset( ASSET::BUTTON );
		_object[ i ].mark = createAsset( ASSET::MARK );

		const int r = getRand( ) % v.size( );
		setAsset( _object[ i ].mark, CMD::STATUS, v[ r ] );
		v.erase( v.begin( ) + r );

		const int ox = ( SCREEN_WIDTH / 2 - 280 ) + 140 * i + 140 / 2;
		const int oy = SCREEN_HEIGHT / 2 + 100;

		setAsset( _object[ i ].mark, CMD::POS_X, ox );
		setAsset( _object[ i ].mark, CMD::POS_Y, oy );

		setAsset( _object[ i ].button, CMD::POS_X, ox );
		setAsset( _object[ i ].button, CMD::POS_Y, oy );
	}
}

GAME_END;