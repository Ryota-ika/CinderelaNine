#include "Impulse.h"
#include <array>
#include <vector>

GAME_BEGIN( A_Hiraoka );

#define OBJ_NUM ( 8 )
#define OBJ_BEGIN_POS_X ( 400 )  //285
#define OBJ_BEGIN_POS_Y ( 500 )  //400
#define ITEM_NUM ( 3 )

int obj_button[ OBJ_NUM ] = {};
int obj_mark[ OBJ_NUM ] = {};

int item_mark[ ITEM_NUM ] = {};
int item_frame[ ITEM_NUM ] = {};

int item_del_num[ ITEM_NUM ] = {};

int i = 0;

const int MARK[ 4 ] = { MARK_DRINK,MARK_MISANGA,MARK_WATCH,MARK_SHOES };
//const int MARK[ 5 ];

int pick_mark[ OBJ_NUM ] = { };
int pick_item_mark[ ITEM_NUM ] = { };



void setup( ) {

	stopwatch( STOPWATCH::START );

	creator( "ゲームプログラマー専攻 ２年", "平岡 龍鳳" );

	for ( int i = 0; i < OBJ_NUM; i++ ) {
		pick_mark[ i ] = MARK[ i % 4 ];
	}
	for ( int i = 0; i < ITEM_NUM; i++ ) {
		pick_item_mark[ i ] = MARK[ i % 4 ];
		item_del_num[ i ] = 0;
	}


	//お題のマーク
	initTem( );
	//回答ボタン
	initObj( );

}

void initTem( void ) {
	const int SPASE = 500;
	const int TOP_POS_X = SCREEN_WIDTH / 2 - SPASE;

	//250
	//200

	for ( i = 0; i < ITEM_NUM; i++ ) {
		item_mark[ i ] = createAsset( ASSET::MARK );
		setAsset( item_mark[ i ], CMD::POS_X, TOP_POS_X + SPASE * i );
	}
	for ( i = 0; i < ITEM_NUM; i++ ) {
		setAsset( item_mark[ i ], CMD::POS_Y, 300 );
	}
	for ( i = 0; i < ITEM_NUM; i++ ) {
		item_frame[ i ] = createAsset( ASSET::FRAME );
		setAsset( item_frame[ i ], CMD::POS_X, TOP_POS_X + SPASE * i );
		setAsset( item_frame[ i ], CMD::POS_Y, 300 );
	}
	for ( i = 0; i < 3; i++ ) {
		setAsset( item_mark[ i ], CMD::STATUS, GetRandomTEM( ) );
	}
}

void initObj( void ) {
	const int SPASE = 360;
	const int TOP_POS_X = SCREEN_WIDTH / 2 - SPASE / 2 - SPASE;

	int pos_x = 0;
	int pos_y = 0;

	for ( i = 0; i < OBJ_NUM; i++ ) {
		obj_button[ i ] = createAsset( ASSET::BUTTON );
		obj_mark[ i ] = createAsset( ASSET::MARK );
		if ( i <= 3 ) {
			pos_x = TOP_POS_X + ( i * SPASE );
			pos_y = OBJ_BEGIN_POS_Y;
		} else {
			pos_x = TOP_POS_X + ( ( i - 4 ) * SPASE );
			pos_y = OBJ_BEGIN_POS_Y + 200;
		}

		setAsset( obj_mark[ i ], CMD::POS_X, pos_x );
		setAsset( obj_mark[ i ], CMD::POS_Y, pos_y );

		setAsset( obj_button[ i ], CMD::POS_X, pos_x );
		setAsset( obj_button[ i ], CMD::POS_Y, pos_y );

		setAsset( obj_mark[ i ], CMD::STATUS, getRandom( ) );
	}


	//for ( i = 0; i < 5; i++ ) {
	//	button[ i ] = createAsset( ASSET::BUTTON );
	//	setAsset( button[ i ], CMD::POS_X, 285 + ( i * 175 ) );
	//	setAsset( button[ i ], CMD::POS_Y, 350 );

	//	B_mark[ i ] = createAsset( ASSET::MARK );
	//	setAsset( B_mark[ i ], CMD::POS_X, 285 + ( i * 175 ) );
	//	setAsset( B_mark[ i ], CMD::POS_Y, 350 );
	//}
	//for ( i = 0; i < 5; i++ ) {
	//	button2[ i ] = createAsset( ASSET::BUTTON );
	//	setAsset( button2[ i ], CMD::POS_X, 285 + ( i * 175 ) );
	//	setAsset( button2[ i ], CMD::POS_Y, 550 );
	//	B_mark2[ i ] = createAsset( ASSET::MARK );
	//	setAsset( B_mark2[ i ], CMD::POS_X, 285 + ( i * 175 ) );
	//	setAsset( B_mark2[ i ], CMD::POS_Y, 550 );
	//}
	//for ( i = 0; i < 5; i++ ) {
	//	setAsset( B_mark[ i ], CMD::STATUS, asset_mark[ random( ) % 4 ] );
	//}
	//for ( i = 0; i < 5; i++ ) {
	//	setAsset( B_mark2[ i ], CMD::STATUS, asset_mark[ random( ) % 4 ] );
	//}
}

int GetRandomTEM( ) {
	int result = 0;

	while ( true ) {
		int r = getRand( ) % ITEM_NUM;
		if ( pick_item_mark[ r ] == -1 ) {
			continue;
		}
		result = pick_item_mark[ r ];
		pick_item_mark[ r ] = -1;
		break;
	}
	return result;
}
//マークのランダム取得被りの調整込み
int getRandom( ) {
	int result = 0;

	while ( 1 ) {
		int r = getRand( ) % OBJ_NUM;
		if ( pick_mark[ r ] == -1 ) {
			continue;
		}

		result = pick_mark[ r ];
		pick_mark[ r ] = -1;
		break;
	}

	return result;
}

int Answer = 0;
void update( ) {
	int touch;
	//回答の認識
	for ( i = 0; i < OBJ_NUM; i++ ) {
		touch = getAsset( obj_button[ i ], CMD::TOUCH );
		if ( touch == 1 ) {
			for ( int j = 0; j < ITEM_NUM; j++ ) {
				if ( getAsset( obj_mark[ i ], CMD::STATUS ) == getAsset( item_mark[ j ], CMD::STATUS ) ) {
					setAsset( obj_mark[ i ], CMD::VISIBLE, 0 );
					setAsset( obj_button[ i ], CMD::VISIBLE, 0 );

					item_del_num[ j ] += 1;
					if ( item_del_num[ j ] == 2 ) {
						setAsset( item_mark[ j ], CMD::VISIBLE, 0 );
					}
				}
			}
		}
	}
	//結果の確認
	bool fin_result = true;
	for ( i = 0; i < ITEM_NUM; i++ ) {
		if ( item_del_num[ i ] != 2 ) {
			fin_result = false;
		}

	}
	if ( fin_result == true ) {
		finish( );
	}
}

// パフォーマンスモードでゲーム開始前に表示されるゲーム説明を登録します
// １行１４文字で４行まで正常に表示できます
STRING info( ) {
	return "３つのお題と同じマークのついた\nボタンを全て消そう！"; // ここに説明文を入力します。
}

int tag( ) {
	return 14;
}

GAME_END;