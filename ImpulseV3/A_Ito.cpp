#include "Impulse.h"

GAME_BEGIN( A_Ito );

#define BUTTON_MAX (9)

int button[ BUTTON_MAX ] = {};

int num[ BUTTON_MAX ] = {};

int count = 0;

int tenpu[ BUTTON_MAX ] = {};

void setup( ) {

	int i = 0;
	for ( i = 0; i < BUTTON_MAX; i++ ) {
		tenpu[ i ] = i + 1;

	}
	count = 1;

	stopwatch( STOPWATCH::START );

	creator( "ゲームプログラマー専攻 ２年", "伊藤 陸斗" );

	for ( i = 0; i < BUTTON_MAX; i++ ) {

		button[ i ] = createAsset( ASSET::BUTTON );
		setAsset( button[ i ], CMD::POS_X, ( SCREEN_WIDTH / 2 - 170 ) + 170 * ( i % 3 ) );
		setAsset( button[ i ], CMD::POS_Y, ( SCREEN_HEIGHT / 2 - 170 ) + 170 * ( i / 3 ) );

		num[ i ] = createAsset( ASSET::NUMBER );
		setAsset( num[ i ], CMD::POS_X, ( SCREEN_WIDTH / 2 - 170 ) + 170 * ( i % 3 ) );
		setAsset( num[ i ], CMD::POS_Y, ( SCREEN_HEIGHT / 2 - 170 ) + 170 * ( i / 3 ) );
		setAsset( num[ i ], CMD::STATUS, getNumber( ) );
	}
}

void update( ) {
	for ( int i = 0; i < BUTTON_MAX; i++ ) {
		if ( getAsset( button[ i ], CMD::TOUCH ) ) {
			if ( getAsset( num[ i ], CMD::STATUS ) == count ) {
				setAsset( button[ i ], CMD::VISIBLE, 0 );
				setAsset( num[ i ], CMD::VISIBLE, 0 );
				count++;
			}

		}
	}

	if ( count == BUTTON_MAX + 1 ) {
		stopwatch( STOPWATCH::STOP );
		finish( );
	}
}

STRING info( ) {
	return "表示されたボタンを\n１から順番に押していこう！";
}

int getNumber( ) {
	int e = -1;
	while ( 1 ) {
		int r = getRand( ) % BUTTON_MAX;
		if ( tenpu[ r ] != -1 ) {
			e = tenpu[ r ];
			tenpu[ r ] = -1;
			break;
		}
	}
	return e;
}

int tag( ) {
	return 15;
}

GAME_END;