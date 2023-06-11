#include "Impulse.h"
#include <array>

GAME_BEGIN( B_Sasamoto );

std::array< int, 5 >marble = { 0 };
std::array< int, 5 >mark = { 0 };
std::array< int, 4 >random_mark { MARK_DRINK, MARK_MISANGA, MARK_SHOES, MARK_WATCH };

int number = 0;
int count = 3;
int frame = 0;
int plate = 0;

void setup( ) {
	stopwatch( STOPWATCH::START );

	number = 0;
	count = 3;

	marbleNum( );

	creator( "PGPL＆VRマスターコース １年", "笹本 航" );
}

void update( ) {

	for ( int i = 0; i < 4; i++ ) {
		int range = 50;
		int marble_pos_x1 = getAsset( marble[ i ], CMD::POS_X );
		int marble_pos_x2 = getAsset( marble[ 4 ], CMD::POS_X );
		int marble_pos_y1 = getAsset( marble[ i ], CMD::POS_Y );
		int marble_pos_y2 = getAsset( marble[ 4 ], CMD::POS_Y );
		int diff_pos_x = marble_pos_x1 - marble_pos_x2;
		int diff_pos_y = marble_pos_y1 - marble_pos_y2;

		if ( diff_pos_x < 0 ) {
			diff_pos_x *= -1;
		}
		if ( diff_pos_y < 0 ) {
			diff_pos_y *= -1;
		}

		if ( diff_pos_x < range && diff_pos_y < range ) {
			if ( getAsset( mark[ i ], CMD::STATUS ) == getAsset( mark[ 4 ], CMD::STATUS ) ) {
				setAsset( marble[ i ], CMD::STATUS, MARBLE_BREAK );
				setAsset( marble[ 4 ], CMD::STATUS, MARBLE_BREAK );
				count--;
				setAsset( number, CMD::STATUS, count );
				marbleDelete( );
				marbleNum( );
			}
		}
		marbleTogetherMark( );
	}

	if ( count == 0 ) {
		finish( );
	}
}

void marbleTogetherMark( ) {
	int marble_mouse_x = getAsset( marble[ 0 ], CMD::POS_X );
	int marble_mouse_y = getAsset( marble[ 0 ], CMD::POS_Y );

	int marble1_mouse_x = getAsset( marble[ 1 ], CMD::POS_X );
	int marble1_mouse_y = getAsset( marble[ 1 ], CMD::POS_Y );

	int marble2_mouse_x = getAsset( marble[ 2 ], CMD::POS_X );
	int marble2_mouse_y = getAsset( marble[ 2 ], CMD::POS_Y );

	int marble3_mouse_x = getAsset( marble[ 3 ], CMD::POS_X );
	int marble3_mouse_y = getAsset( marble[ 3 ], CMD::POS_Y );

	int marble4_mouse_x = getAsset( marble[ 4 ], CMD::POS_X );
	int marble4_mouse_y = getAsset( marble[ 4 ], CMD::POS_Y );

	setAsset( mark[ 0 ], CMD::POS_X, marble_mouse_x );
	setAsset( mark[ 0 ], CMD::POS_Y, marble_mouse_y );

	setAsset( mark[ 1 ], CMD::POS_X, marble1_mouse_x );
	setAsset( mark[ 1 ], CMD::POS_Y, marble1_mouse_y );

	setAsset( mark[ 2 ], CMD::POS_X, marble2_mouse_x );
	setAsset( mark[ 2 ], CMD::POS_Y, marble2_mouse_y );

	setAsset( mark[ 3 ], CMD::POS_X, marble3_mouse_x );
	setAsset( mark[ 3 ], CMD::POS_Y, marble3_mouse_y );

	setAsset( mark[ 4 ], CMD::POS_X, marble4_mouse_x );
	setAsset( mark[ 4 ], CMD::POS_Y, marble4_mouse_y );
}

void putMarble( ) {
	int pos_x[ 8 ] = { 150, 550, 950, 1350, 1700 };
	int random_y = 0;

	for ( int i = 0; i < 5; i++ ) {
		random_y = ( getRand( ) % ( SCREEN_HEIGHT - 300 ) ) + 220;

		setAsset( marble[ i ], CMD::POS_X, pos_x[ i ] );
		setAsset( marble[ i ], CMD::POS_Y, random_y );
	}
}

int muchMarble( int pos_x ) {
	int much = 0;
	int circle = 120;

	for ( int i = 0; i < 8; i++ ) {
		int marble_x = getAsset( marble[ i ], CMD::POS_X );
		int deff_x = marble_x - pos_x;

		if ( deff_x < 0 ) {
			deff_x *= -1;
		}
		if ( deff_x < circle ) {
			much = 1;
		}
	}
	return much;
}

void marbleNum( ) {
	marble[ 0 ] = createAsset( ASSET::MARBLE );
	marble[ 1 ] = createAsset( ASSET::MARBLE );
	marble[ 2 ] = createAsset( ASSET::MARBLE );
	marble[ 3 ] = createAsset( ASSET::MARBLE );
	marble[ 4 ] = createAsset( ASSET::MARBLE );

	int marble_x = getAsset( marble[ 0 ], CMD::POS_X );
	int marble_y = getAsset( marble[ 0 ], CMD::POS_Y );

	int marble1_x = getAsset( marble[ 1 ], CMD::POS_X );
	int marble1_y = getAsset( marble[ 1 ], CMD::POS_Y );

	int marble2_x = getAsset( marble[ 2 ], CMD::POS_X );
	int marble2_y = getAsset( marble[ 2 ], CMD::POS_Y );

	int marble3_x = getAsset( marble[ 3 ], CMD::POS_X );
	int marble3_y = getAsset( marble[ 3 ], CMD::POS_Y );

	int marble4_x = getAsset( marble[ 4 ], CMD::POS_X );
	int marble4_y = getAsset( marble[ 4 ], CMD::POS_Y );

	mark[ 0 ] = createAsset( ASSET::MARK );
	setAsset( mark[ 0 ], CMD::POS_X, marble_x );
	setAsset( mark[ 0 ], CMD::POS_Y, marble_y );
	setAsset( mark[ 0 ], CMD::STATUS, MARK_WATCH );

	mark[ 1 ] = createAsset( ASSET::MARK );
	setAsset( mark[ 1 ], CMD::POS_X, marble1_x );
	setAsset( mark[ 1 ], CMD::POS_Y, marble1_y );
	setAsset( mark[ 1 ], CMD::STATUS, MARK_MISANGA );

	mark[ 2 ] = createAsset( ASSET::MARK );
	setAsset( mark[ 2 ], CMD::POS_X, marble2_x );
	setAsset( mark[ 2 ], CMD::POS_Y, marble2_y );
	setAsset( mark[ 2 ], CMD::STATUS, MARK_SHOES );

	mark[ 3 ] = createAsset( ASSET::MARK );
	setAsset( mark[ 3 ], CMD::POS_X, marble3_x );
	setAsset( mark[ 3 ], CMD::POS_Y, marble3_y );
	setAsset( mark[ 3 ], CMD::STATUS, MARK_DRINK );

	mark[ 4 ] = createAsset( ASSET::MARK );
	setAsset( mark[ 4 ], CMD::POS_X, marble4_x );
	setAsset( mark[ 4 ], CMD::POS_Y, marble4_y );
	setAsset( mark[ 4 ], CMD::STATUS, random_mark[ getRand( ) % 4 ] );

	number = createAsset( ASSET::NUMBER );
	setAsset( number, CMD::POS_X, SCREEN_WIDTH - 200 );
	setAsset( number, CMD::POS_Y, 150 );
	setAsset( number, CMD::STATUS, count );

	frame = createAsset( ASSET::FRAME );
	setAsset( frame, CMD::POS_X, SCREEN_WIDTH - 200 );
	setAsset( frame, CMD::POS_Y, 150 );

	plate = createAsset( ASSET::PLATE );
	setAsset( plate, CMD::POS_X, SCREEN_WIDTH - 200 );
	setAsset( plate, CMD::POS_Y, 70 );
	setAsset( plate, CMD::STATUS, PLATE_REMAINING );

	putMarble( );
}

void marbleDelete( ) {
	setAsset( marble[ 0 ], CMD::VISIBLE, 0 );
	setAsset( marble[ 1 ], CMD::VISIBLE, 0 );
	setAsset( marble[ 2 ], CMD::VISIBLE, 0 );
	setAsset( marble[ 3 ], CMD::VISIBLE, 0 );
	setAsset( marble[ 4 ], CMD::VISIBLE, 0 );

	setAsset( mark[ 0 ], CMD::VISIBLE, 0 );
	setAsset( mark[ 1 ], CMD::VISIBLE, 0 );
	setAsset( mark[ 3 ], CMD::VISIBLE, 0 );
	setAsset( mark[ 2 ], CMD::VISIBLE, 0 );
	setAsset( mark[ 4 ], CMD::VISIBLE, 0 );

	setAsset( number, CMD::VISIBLE, 0 );
}

STRING info( ) {
	return "同じマーブルを探して、\nぶつけて壊そう！";
}

int tag( ) {
	return 23;
}

GAME_END;