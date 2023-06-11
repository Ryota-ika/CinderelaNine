#include "Impulse.h"

GAME_BEGIN( A_Abe );
#define BUTTON_MAX (4) 

int button[ BUTTON_MAX ] = {};

int pushcount = 0;
int countnumber = 0;


int touch[ BUTTON_MAX ] = {};

int button_status[ BUTTON_MAX ] = {};

int counter = 0;
int remain = 0;

int _frame = 0;


void setup( ) {

	creator("ゲームプログラマー専攻 ２年", "阿部 一真" );

	int i = 0;

	countnumber = 3;
	pushcount = 0;
	counter = 0;

	for ( i = 0; i < BUTTON_MAX; i++ ) {
		button[ i ] = -1;

	}

	initbutton( );
	initPushcount( );

	_frame = createAsset( ASSET::FRAME );
	setAsset( _frame, CMD::POS_X, getAsset( pushcount, CMD::POS_X ) );
	setAsset( _frame, CMD::POS_Y, getAsset( pushcount, CMD::POS_Y ) );

	stopwatch( STOPWATCH::START );
}

STRING info( ) { 
	return "出てくるボタンを全て消そう！";
}

void initbutton( ) {
	for ( int i = 0; i < BUTTON_MAX; i++ ) {
		button[ i ] = create_button( );

	}
}

struct Vec { //構造体
	int x;
	int y;
};

int create_button( ) {
	int obj = createAsset( ASSET::BUTTON );
	struct Vec pos = getObjectCreatepos( ); //posの中に下のVecを入れる

	//座標を取得する
	setAsset( obj, CMD::POS_X, pos.x );
	setAsset( obj, CMD::POS_Y, pos.y );

	//consoleWrite( "pos.x = %d, pos.y = %d", pos.x, pos.y ); //Debug用
	return obj;



}

Vec getObjectCreatepos( ) {
	const int AREA_BEGIN = 70;

	const int AREA_X = SCREEN_WIDTH - AREA_BEGIN * 2; //画面の両端をAREA_Xのは範囲から除く
	const int AREA_Y = SCREEN_HEIGHT - 210 - AREA_BEGIN * 2; //Xと同様、100はストップウォッチ分下げる必要があるため

	//int bx = 0;
	//int by = 0;

	struct Vec rVec { //rVecの初期化
		0, 0
	};

	while ( true ) {
		rVec.x = AREA_BEGIN + getRand( ) % AREA_X;
		rVec.y = AREA_BEGIN + 210 + getRand( ) % AREA_Y;

		if ( !isHitting( rVec ) ) { //isHittingの101行目が満たされていない時、breakさせる
			break;
		}
	}

	return rVec;
}

int calAbs( int n ) { //ーにいったらー掛けて＋にする(絶対値)
	if ( n < 0 ) {
		n *= -1;
	}
	return n;
}

bool isHitting( Vec vec ) {
	int i = 0;
	int diff_width = 0;
	int diff_height = 0;

	for ( i = 0; i < BUTTON_MAX; i++ ) {

		if ( button[ i ] != -1 ) {
			diff_width = calAbs( vec.x - getAsset( button[ i ], CMD::POS_X ) ); //ボタン間のX座標の距離
			diff_height = calAbs( vec.y - getAsset( button[ i ], CMD::POS_Y ) ); //同様、Y座標

			if ( diff_width < 140 && diff_height < 140 ) { //それぞれの距離が128未満だった場合、72行目の処理に戻る
				return true;
			}
		}
	}
	return false; //そうでない場合、breakの処理

}


void initPushcount( ) {
	pushcount = createAsset( ASSET::NUMBER );
	setAsset( pushcount, CMD::POS_X, SCREEN_WIDTH - 180 );
	setAsset( pushcount, CMD::POS_Y, 140 );
	setAsset( pushcount, CMD::STATUS, countnumber );

	remain = createAsset( ASSET::PLATE );

	setAsset( remain, CMD::STATUS, PLATE_REMAINING );
	setAsset( remain, CMD::POS_X, SCREEN_WIDTH - 180 );
	setAsset( remain, CMD::POS_Y, 55 );
}





void update( ) {

	struct Vec pos = getObjectCreatepos( ); //45行目と同様

	for ( int i = 0; i < BUTTON_MAX; i++ ) {
		touch[ i ] = getAsset( button[ i ], CMD::TOUCH );

		button_status[ i ] = getAsset( button[ i ], CMD::STATUS );

		if ( touch[ i ] == 1 ) {

			setAsset( button[ i ], CMD::STATUS, BUTTON_DISABLED );
			counter++;

		}
	}

	if ( counter == BUTTON_MAX ) { //全部押したときの繰り返しの処理

		for ( int i = 0; i < BUTTON_MAX; i++ ) {
			pos = getObjectCreatepos( ); //	座標を再取得する、しないとボタンの座標が被る
			setAsset( button[ i ], CMD::POS_X, pos.x );
			setAsset( button[ i ], CMD::POS_Y, pos.y );
			setAsset( button[ i ], CMD::STATUS, BUTTON_NORMAL );

		}

		counter = 0;

		countnumber--;
		setAsset( pushcount, CMD::STATUS, countnumber );

	}

	initFinish( );
}






void initFinish( ) {
	if ( countnumber == 0 ) {
		stopwatch( STOPWATCH::STOP );
		for ( int i = 0; i < BUTTON_MAX; i++ ) {

			destroyAsset( button[ i ] );

		}
		finish( );
	}
	return;
}

int tag( ) {
	return 11;
}

GAME_END;