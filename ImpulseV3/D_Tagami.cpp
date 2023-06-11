#include "Impulse.h"

GAME_BEGIN( D_Tagami );

//フェーズの間に待ち（１秒くらい）（ボタンの入力も無効）を入れる
//→その際には定数(const)を定義して使用すると後々楽
int cownt = 0;
int tenkey[ 10 ] = {}; // 0~9 // □□□□□□□□□□
int keynumber[ 10 ] = {};     // □□□□□□□□□□
int keypos_x = 0;
int keypos_y = 0;
int targetnum[ 4 ] = {};
int targetpos_x = SCREEN_WIDTH / 2 - 150;
int touch[ 10 ] = {};
int targetframe = 0;
int frame = 0;
int plate = 0;
int waitframe = 0;
bool creaflag = false;

const int WAIT_TIME = 60;

// パフォーマンスモードでゲーム開始前に表示されるゲーム説明を登録します
// １行１４文字で４行まで正常に表示できます
STRING info( ) {
	return "上の画面に次々に表示されるお題の数字\nを素早く入力しよう！"; // ここに説明文を入力します。
}

void setup( ) {

	creator( "ゲームプログラマー専攻 １年", "田上 元洋" );
	waitframe = 0;
	creaflag = false;
	keypos_x = SCREEN_WIDTH / 4 + 200;
	keypos_y = ( int )( SCREEN_HEIGHT / 1.8 );
	stopwatch( STOPWATCH::START );
	frame = createAsset( ASSET::FRAME );
	targetframe = createAsset( ASSET::FRAME );
	setAsset( frame, CMD::POS_X, targetpos_x );
	setAsset( frame, CMD::POS_Y, 300 );
	plate = createAsset( ASSET::PLATE );
	cownt = createAsset( ASSET::NUMBER );
	setAsset( cownt, CMD::POS_X, 100 );
	setAsset( cownt, CMD::POS_Y, 250 );
	setAsset( targetframe, CMD::POS_X, 100 );
	setAsset( targetframe, CMD::POS_Y, 250 );
	setAsset( cownt, CMD::STATUS, 3 );
	setAsset( plate, CMD::POS_X, 100 );
	setAsset( plate, CMD::POS_Y, 175 );
	setAsset( plate, CMD::STATUS, PLATE_REMAINING );
	for ( int j = 0; j < 4; j++ ) {
		targetnum[ j ] = createAsset( ASSET::NUMBER );
		setAsset( targetnum[ j ], CMD::POS_X, targetpos_x );
		setAsset( targetnum[ j ], CMD::POS_Y, 300 );
		setAsset( targetnum[ j ], CMD::STATUS, getRand( ) % 10);
		targetpos_x = targetpos_x + 100;
	}
	for ( int i = 0; i < 10; i++ ) {
		tenkey[ i ] = createAsset( ASSET::BUTTON );
		setAsset( tenkey[ i ], CMD::POS_X, keypos_x );
		setAsset( tenkey[ i ], CMD::POS_Y, keypos_y );
		keynumber[ i ] = createAsset( ASSET::NUMBER );
		setAsset( keynumber[ i ], CMD::POS_X, keypos_x );
		setAsset( keynumber[ i ], CMD::POS_Y, keypos_y );
		setAsset( keynumber[ i ], CMD::STATUS, i );
		keypos_x = keypos_x + 140;
		if ( i == 4 ) {
			keypos_y = keypos_y + 140;
			keypos_x = SCREEN_WIDTH / 4 + 200;
		}
	}
	targetpos_x = SCREEN_WIDTH / 2 - 150;
}

void update( ) {
	
	for ( int i = 0; i < 10; i++ ) {
		touch[ i ] = getAsset( tenkey[ i ], CMD::TOUCH );
		if ( waitframe == 0 ) {
			stopwatch( STOPWATCH::START );
			if ( touch[ i ] == 1
				 && getAsset( targetnum[ 3 ], CMD::STATUS ) == getAsset( keynumber[ i ], CMD::STATUS )
				 && getAsset( targetnum[ 2 ], CMD::VISIBLE ) == false
				 && getAsset( targetnum[ 3 ], CMD::VISIBLE ) == ( int )true ) {
				setAsset( targetnum[ 3 ], CMD::VISIBLE, false );
				setAsset( frame, CMD::POS_X, targetpos_x );
			}
			if ( touch[ i ] == 1
				 && getAsset( targetnum[ 2 ], CMD::STATUS ) == getAsset( keynumber[ i ], CMD::STATUS )
				 && getAsset( targetnum[ 1 ], CMD::VISIBLE ) == false
				 && getAsset( targetnum[ 2 ], CMD::VISIBLE ) == ( int )true ) {
				setAsset( targetnum[ 2 ], CMD::VISIBLE, false );
				targetpos_x = targetpos_x + 100;
				setAsset( frame, CMD::POS_X, targetpos_x );
			}
			if ( touch[ i ] == 1
				 && getAsset( targetnum[ 1 ], CMD::STATUS ) == getAsset( keynumber[ i ], CMD::STATUS )
				 && getAsset( targetnum[ 0 ], CMD::VISIBLE ) == false
				 && getAsset( targetnum[ 1 ], CMD::VISIBLE ) == ( int )true ) {
				setAsset( targetnum[ 1 ], CMD::VISIBLE, false );
				targetpos_x = targetpos_x + 100;
				setAsset( frame, CMD::POS_X, targetpos_x );
			}
			if ( touch[ i ] == 1
				 && getAsset( targetnum[ 0 ], CMD::STATUS ) == getAsset( keynumber[ i ], CMD::STATUS )
				 && getAsset( targetnum[ 0 ], CMD::VISIBLE ) == ( int )true ) {
				setAsset( targetnum[ 0 ], CMD::VISIBLE, false );
				targetpos_x = targetpos_x + 100;
				setAsset( frame, CMD::POS_X, targetpos_x );
			}
		}
	}
	if ( getAsset( targetnum[ 0 ], CMD::VISIBLE ) == false
		 && getAsset( targetnum[ 1 ], CMD::VISIBLE ) == false
		 && getAsset( targetnum[ 2 ], CMD::VISIBLE ) == false
		 && getAsset( targetnum[ 3 ], CMD::VISIBLE ) == false ) {
		waitframe++;
		stopwatch( STOPWATCH::STOP );
		if ( waitframe%WAIT_TIME==0 ) { 
			setAsset( cownt, CMD::STATUS, getAsset( cownt, CMD::STATUS ) - 1 );
		}
		if (  getAsset( cownt, CMD::STATUS ) > 0&&waitframe%WAIT_TIME==0 ) { 
		for ( int i = 0; i < 4; i++ ) {
			setAsset( targetnum[ i ], CMD::VISIBLE, true );
			setAsset( targetnum[ i ], CMD::STATUS,getRand( ) % 10 );
		}
		targetpos_x = SCREEN_WIDTH / 2 - 150;
		setAsset( frame, CMD::POS_X, targetpos_x );
		waitframe = 0;
		}
	}
	if ( getAsset( cownt, CMD::STATUS ) == 0 ) {
		targetpos_x = SCREEN_WIDTH / 2 - 150;
		setAsset( frame, CMD::POS_X, targetpos_x );
		finish( );
		setAsset( frame, CMD::VISIBLE, false );
	}
	
}

int tag( ) {
	return 44;
}

GAME_END;