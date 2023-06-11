#include "Impulse.h"

GAME_BEGIN( D_Isozaki );

int Qt = 0;
int Qt_mark = 0;
int button[ 100 ] = { 0 };
int mark[ 100 ] = { 0 };
//お題のステータスを保存する変数
int Qt_status = 0;
//ボタンのステータスを保存する変数
int button_status = 0;
int Frame = 0;
int Plate = 0;
int random_mark[ 24 ];

STRING info( ) {
	return "お題と同じマークをタッチして消そう！"; // ここに説明文を入力します。
}



const int CONST_MARK[ 4 ] = {
 MARK_DRINK,
 MARK_SHOES,
 MARK_WATCH,
 MARK_MISANGA,
};

void setup( ) {

	creator( "ゲームプログラマー専攻 １年", "磯﨑 佑真" );

	Frame = createAsset( ASSET::FRAME );
	setAsset( Frame, CMD::POS_X, SCREEN_WIDTH / 2 );
	setAsset( Frame, CMD::POS_Y, SCREEN_HEIGHT / 2 - 200 );
	Plate = createAsset( ASSET::PLATE );
	setAsset( Plate, CMD::POS_X, SCREEN_WIDTH / 2 );
	setAsset( Plate, CMD::POS_Y, SCREEN_HEIGHT / 2 - 280 );
	//お題
	for ( int i = 0; i < 24; i++ ) {
		random_mark[ i ] = createAsset( ASSET::MARK );
		setAsset( random_mark[ i ], CMD::POS_X, -500 );
		setAsset( random_mark[ i ], CMD::STATUS, CONST_MARK[ i % 4 ] );

	}
	Qt = createAsset( ASSET::MARK );
	setAsset( Qt, CMD::POS_X, SCREEN_WIDTH / 2 );
	setAsset( Qt, CMD::POS_Y, SCREEN_HEIGHT / 2 - 200 );
	int rand = getRandomMark( );
	int rand_mark = getAsset( random_mark[ rand ], CMD::STATUS );
	setAsset( Qt, CMD::STATUS, rand_mark );
	Qt_mark = getAsset( Qt, CMD::STATUS );
	//マーク付きのボタン

	for ( int i = 0; i < 8; i++ ) {
		for ( int j = 0; j < 3; j++ ) {
			int x = SCREEN_WIDTH / 2 + -( 160 * 8 / 2 ) + i * 160 + 160 / 2;
			int y = j * 160 + SCREEN_HEIGHT / 2;

			button[ i + j * 8 ] = createAsset( ASSET::BUTTON );
			setAsset( button[ i + j * 8 ], CMD::POS_X, x );
			setAsset( button[ i + j * 8 ], CMD::POS_Y, y );
			mark[ i + j * 8 ] = createAsset( ASSET::MARK );
			setAsset( mark[ i + j * 8 ], CMD::POS_X, x );
			setAsset( mark[ i + j * 8 ], CMD::POS_Y, y );
			rand = getRandomMark( );
			rand_mark = getAsset( random_mark[ rand ], CMD::STATUS );
			setAsset( mark[ i + j * 8 ], CMD::STATUS, rand_mark );
			random_mark[ rand ] = -1;
		}
	}

	stopwatch( STOPWATCH::START );
}

void update( ) {
	for ( int i = 0; i < 24; i++ ) {
		int touch = getAsset( button[ i ], CMD::TOUCH );
		Qt_status = getAsset( Qt, CMD::STATUS );
		button_status = getAsset( mark[ i ], CMD::STATUS );
		if ( touch == 1 ) {
			if ( Qt_status == button_status ) {
				setAsset( button[ i ], CMD::VISIBLE, false );
				setAsset( mark[ i ], CMD::VISIBLE, false );
			}
		}
	}
	bool clear = true;
	for ( int i = 0; i < 24; i++ ) {
		int mark_status = getAsset( mark[ i ], CMD::STATUS );
		int mark_visible = getAsset( mark[ i ], CMD::VISIBLE );
		if ( mark_status == Qt_mark &&
			 mark_visible == ( int )true ) {
			clear = false;
		}
	}
	if ( clear ) {
		stopwatch( STOPWATCH::STOP );
		finish( );
	}
}

int getRandomMark( ) {
	int rand = getRand( ) % 24;
	while ( random_mark[ rand ] == -1 ) {
		rand = getRand( ) % 24;
	}
	return rand;
}

int tag( ) {
	return 42;
}

GAME_END;

//お題のマーク　6～12個