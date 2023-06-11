#include "Impulse.h"

GAME_BEGIN( A_Nagashima );

int hutiodai = 0;
int hutisuuji = 0;
int suuji = 0;
int count = 10;
int odai = 0;
int odaitbl[ 4 ] = { MARK_DRINK,MARK_SHOES,MARK_WATCH,MARK_MISANGA };
int buttontbl[ 4 ] = {};
int marktbl[ 4 ] = {};

STRING info( ) {
	return "お題と同じマークの\nボタンを押そう！";
}

void setup( ) {

	creator( "ゲームプログラマー専攻 ２年", "長嶋 広大" );

	int x = 340;
	count = 5;
	stopwatch( STOPWATCH::START );


	int odaiplate = createAsset( ASSET::PLATE );
	setAsset( odaiplate, CMD::POS_X, ( int )( 640 * 1.5 ) );
	setAsset( odaiplate, CMD::POS_Y, ( int )( 190 * 1.5 ) );

	int nokori = createAsset( ASSET::PLATE );
	setAsset( nokori, CMD::STATUS, PLATE_REMAINING );
	setAsset( nokori, CMD::POS_X, ( int )( 200 * 1.5 ) );
	setAsset( nokori, CMD::POS_Y, ( int )( 190 * 1.5 ) );

	hutiodai = createAsset( ASSET::FRAME );
	setAsset( hutiodai, CMD::POS_X, ( int )( 640 * 1.5 ) );
	setAsset( hutiodai, CMD::POS_Y, ( int )( 250 * 1.5 ) );

	hutisuuji = createAsset( ASSET::FRAME );
	setAsset( hutisuuji, CMD::POS_X, ( int )( 200 * 1.5 ) );
	setAsset( hutisuuji, CMD::POS_Y, ( int )( 250 * 1.5 ) );

	for ( int i = 0; i < 4; i++ ) {
		buttontbl[ i ] = createAsset( ASSET::BUTTON );
		setAsset( buttontbl[ i ], CMD::POS_X, ( int )( x * 1.5 ) );
		setAsset( buttontbl[ i ], CMD::POS_Y, ( int )( 550 * 1.5 ) );
		x = x + 200;
	}
	x = 340;
	for ( int i = 0; i < 4; i++ ) {
		marktbl[ i ] = createAsset( ASSET::MARK );
		setAsset( marktbl[ i ], CMD::STATUS, odaitbl[ i ] );
		setAsset( marktbl[ i ], CMD::POS_X, ( int )( x * 1.5 ) );
		setAsset( marktbl[ i ], CMD::POS_Y, ( int )( 550 * 1.5 ) );
		x = x + 200;
	}


	//左上のナンバー
	suuji = createAsset( ASSET::NUMBER );
	setAsset( suuji, CMD::STATUS, count );
	setAsset( suuji, CMD::POS_X, ( int )( 200 * 1.5 ) );
	setAsset( suuji, CMD::POS_Y, ( int )( 250 * 1.5 ) );

	//お題
	odai = createAsset( ASSET::MARK );
	setAsset( odai, CMD::STATUS, odaitbl[ getRand( ) % 4 ] );
	setAsset( odai, CMD::POS_X, ( int )( 640 * 1.5 ) );
	setAsset( odai, CMD::POS_Y, ( int )( 250 * 1.5 ) );

}

void update( ) {
	int i;
	int seikainum = 0;

	for ( i = 0; i < 4; i++ ) {
		if ( getAsset( odai, CMD::STATUS ) == getAsset( marktbl[ i ], CMD::STATUS ) ) {
			seikainum = i;
		}
	}

	if ( getAsset( buttontbl[ seikainum ], CMD::TOUCH ) ) {
		count--;
		setAsset( odai, CMD::STATUS, odaitbl[ getRand( ) % 4 ] );
		setAsset( suuji, CMD::STATUS, count );
	}


	if ( count == 0 ) {
		stopwatch( STOPWATCH::STOP );
		finish( );
	}
}

int tag( ) {
	return 18;
}

GAME_END;