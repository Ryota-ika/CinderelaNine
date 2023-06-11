#include "Impulse.h"

GAME_BEGIN( A_Henmi );

int X = 0;
int button = 0;
int f = 0;
int number = 0;
int count = 5;
int z = 0;
int button_y = 0;
int fream = 0;
STRING info( ) { 
	return "ボタンを押そう！";
}

void setup( ) {
	creator( "ゲームプログラマー専攻 ２年", "辺見 駿弥" );

	f = 0;
	count = 5;
	button = createAsset( ASSET::BUTTON );
	number = createAsset( ASSET::NUMBER );
	z = createAsset( ASSET::PLATE );
	fream = createAsset( ASSET::FRAME );
	setAsset( fream, CMD::POS_X,(int) ( 1230 * 1.5 - 200) );
	setAsset( fream, CMD::POS_Y, (int)(55 * 1.5 ));
	setAsset( button, CMD::POS_X, getRand( ) % SCREEN_WIDTH );
	setAsset( button, CMD::POS_Y, getRand( ) % SCREEN_HEIGHT );
	setAsset( number, CMD::POS_X, (int)(1230 * 1.5 - 200) );
	setAsset( number, CMD::POS_Y, (int)(55 *1.5) );
	setAsset( number, CMD::STATUS, count );
	setAsset( z, CMD::POS_X, (int)(1140 * 1.5 -200 ));
	setAsset( z, CMD::POS_Y, (int)( 55  * 1.5));
	setAsset( z, CMD::STATUS, PLATE_REMAINING );
	stopwatch( STOPWATCH::START );
}

void update( ) {
	f++;
	int touch = getAsset( button, CMD::TOUCH );

	if (touch) {
		count--;
		setAsset( number, CMD::STATUS, count );
		setAsset( button, CMD::POS_X, 150 + ( getRand( ) % ( SCREEN_WIDTH - 300 ) ) );
		setAsset( button, CMD::POS_Y, 300 + ( getRand( ) % ( SCREEN_HEIGHT - 450 ) ) );
	}
	if (count == 0) {
		destroyAsset( button );
		stopwatch( STOPWATCH::STOP );
		finish( );
	}
}

int tag( ) {
	return 13;
}

GAME_END;