#include "Impulse.h"

#include <vector>
#include <array>

GAME_BEGIN( A_Fukatsu );

//int mark[ 4 ] = {};
std::array< int, 4 >mark = {};
int kaito[ 4 ] = {}; //CN_MARK_DRINK, CN_MARK_SHOES, CN_MARK_WATCH, CN_MARK_MISANGA
int button[ 4 ] = {};
int fure = 0;
int seikai = 0;
int kaitoutebl[ 4 ] = { MARK_DRINK, MARK_SHOES, MARK_WATCH, MARK_MISANGA };
int pureto = 0;

int _clear = 0;
std::vector<int>_theme;

int _number_count = 0;
int _flame_count = 0;
int _plate_count = 0;


STRING info( ) {
	return "上のお題に沿って左から右の順で\n下のボタンを早押ししよう！"; // ここに説明文を入力します。
}

void setup( ) {
	boot( );

	_clear = 3;

	const int CX = SCREEN_WIDTH - 280;
	const int CY = 120;

	_number_count = createAsset( ASSET::NUMBER );
	setAsset( _number_count, CMD::POS_X, CX );
	setAsset( _number_count, CMD::POS_Y, CY );
	setAsset( _number_count, CMD::STATUS, _clear );

	_flame_count = createAsset( ASSET::FRAME );
	setAsset( _flame_count, CMD::POS_X, CX );
	setAsset( _flame_count, CMD::POS_Y, CY );

	_plate_count = createAsset( ASSET::PLATE );
	setAsset( _plate_count, CMD::POS_X, CX );
	setAsset( _plate_count, CMD::POS_Y, CY - 80 );
	setAsset( _plate_count, CMD::STATUS, PLATE_REMAINING );

	creator( "ゲームプログラマー専攻 ２年", "深津 翔多" );

}

void update( ) {
	int i;
	int touch;

	for ( i = 0; i < 4; i++ ) {
		touch = getAsset( button[ i ], CMD::TOUCH );
		if ( touch == 1 ) {

			int sa = getAsset( mark.at( seikai ), CMD::STATUS );
			int sb = getAsset( kaito[ i ], CMD::STATUS );
			if ( sa == sb ) {
				seikai++;
				if ( seikai != 4 ) {
					setAsset( fure, CMD::POS_X, getAsset( mark.at( seikai ), CMD::POS_X ) );
					setAsset( pureto, CMD::POS_X, getAsset( mark.at( seikai ), CMD::POS_X ) );
				}
			}
		}
	}
	if ( seikai == 4 ) {
		_clear--;
		setAsset( _number_count, CMD::STATUS, _clear );
		boot( );
	}

	if ( _clear == 0 ) {
		stopwatch( STOPWATCH::STOP );
		finish( );
	}

}

void boot( ) {
	if ( _clear != 3 ) {
		for ( int i = 0; i < 4; i++ ) {
			destroyAsset( button[ i ] );
			destroyAsset( mark[ i ] );
			destroyAsset( kaito[ i ] );
		}

		destroyAsset( fure );
		destroyAsset( pureto );
	}

	_theme.clear( );

	std::vector<int>a = { MARK_DRINK, MARK_SHOES, MARK_WATCH, MARK_MISANGA };
	for ( int i = 0; i < 3; i++ ) {
		int r = getRand( ) % a.size( );
		_theme.push_back( a[ r ] );

		a.erase( a.begin( ) + r );
	}
	_theme.push_back( kaitoutebl[ getRand( ) % 4 ] );

	int i;
	seikai = 0;

	for ( i = 0; i < 4; i++ ) {
		button[ i ] = createAsset( ASSET::BUTTON );
		mark[ i ] = createAsset( ASSET::MARK );
		kaito[ i ] = createAsset( ASSET::MARK );

		setAsset( button[ i ], CMD::POS_X, ( int )( ( 200 + 300 * i ) * 1.5 ) );
		setAsset( button[ i ], CMD::POS_Y, ( int )( ( 500 ) * 1.5 ) );
		setAsset( kaito[ i ], CMD::POS_X, ( int )( ( 200 + 300 * i ) * 1.5 ) );
		setAsset( kaito[ i ], CMD::POS_Y, ( int )( ( 500 ) * 1.5 ) );
		setAsset( kaito[ i ], CMD::STATUS, kaitoutebl[ i ] );

		setAsset( mark[ i ], CMD::POS_X, ( int )( ( 200 + 300 * i ) * 1.5 ) );
		setAsset( mark[ i ], CMD::POS_Y, ( int )( ( 300 ) * 1.5 ) );
		//setAsset( mark[ i ], CMD::STATUS, kaitoutebl[ getRand( ) % 4 ] );
		setAsset( mark[ i ], CMD::STATUS, _theme[ i ] );
	}
	fure = createAsset( ASSET::FRAME );
	setAsset( fure, CMD::POS_X, getAsset( mark[ seikai ], CMD::POS_X ) );
	setAsset( fure, CMD::POS_Y, ( int )( ( 300 ) * 1.5 ) );

	stopwatch( STOPWATCH::START );
	pureto = createAsset( ASSET::PLATE );
	setAsset( pureto, CMD::STATUS, PLATE_THEME );
	setAsset( pureto, CMD::POS_X, getAsset( mark[ seikai ], CMD::POS_X ) );
	setAsset( pureto, CMD::POS_Y, ( int )( ( 300 - 88 ) * 1.5 ) );
}

int tag( ) {
	return 12;
}

GAME_END;