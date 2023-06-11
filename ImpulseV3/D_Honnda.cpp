#include "Impulse.h"
#include <array>
#include <vector>

GAME_BEGIN( D_Honnda );

const int MARK_STATUS[ 4 ] = { MARK_DRINK,MARK_SHOES,MARK_WATCH,MARK_MISANGA };

int _asset_num = 0;
int _asset_mark_thema = 0;
int _asset_button[ 4 ] = {};
int _asset_mark[ 4 ] = {};

int _num = 3;
int _vec_x[ 4 ] = { +9, +7, +8, -8 };
int _vec_y[ 4 ] = { -1, +3, -3, +5 };

void setup( ) {
	creator( "ゲームプログラマー専攻 １年", "本田 渉" ); // ゲームの製作者プレートを表示します
	stopwatch( STOPWATCH::START );

	_num = 3;

	{ //3カウント
		int frame = createAsset( ASSET::FRAME );
		setAsset( frame, CMD::STATUS, PLATE_REMAINING );
		setAsset( frame, CMD::POS_X, 1350 );
		setAsset( frame, CMD::POS_Y, 100 );

		_asset_num = createAsset( ASSET::NUMBER );
		setAsset( _asset_num, CMD::POS_X, 1350 );
		setAsset( _asset_num, CMD::POS_Y, 100 );
		setAsset( _asset_num, CMD::STATUS, _num );

		int plate = createAsset( ASSET::PLATE );
		setAsset( plate, CMD::STATUS, PLATE_REMAINING );
		setAsset( plate, CMD::POS_X, 1350 );
		setAsset( plate, CMD::POS_Y, 50 );
	}

	{ //お題
		int frame = createAsset( ASSET::FRAME );
		setAsset( frame, CMD::STATUS, PLATE_REMAINING );
		setAsset( frame, CMD::POS_X, 1600 );
		setAsset( frame, CMD::POS_Y, 100 );

		_asset_mark_thema = createAsset( ASSET::MARK );
		setAsset( _asset_mark_thema, CMD::POS_X, 1600 );
		setAsset( _asset_mark_thema, CMD::POS_Y, 100 );
		setAsset( _asset_mark_thema, CMD::STATUS, MARK_STATUS[ getRand( ) % 4 ] );

		int plate = createAsset( ASSET::PLATE );
		setAsset( plate, CMD::STATUS, PLATE_THEME );
		setAsset( plate, CMD::POS_X, 1600 );
		setAsset( plate, CMD::POS_Y, 50 );
	}

	for ( int i = 0; i < 4; i++ ) {
		_asset_button[ i ] = createAsset( ASSET::BUTTON );
		setAsset( _asset_button[ i ], CMD::POS_X, getRand( ) % 1900 );
		setAsset( _asset_button[ i ], CMD::POS_Y, getRand( ) % 1080 );
		_asset_mark[ i ] = createAsset( ASSET::MARK );
		setAsset( _asset_mark[ i ], CMD::STATUS, MARK_STATUS[ i ] );
	}
}

void update( ) {
	// move button
	for ( int i = 0; i < 4; i++ ) {
		int x = getAsset( _asset_button[ i ], CMD::POS_X );
		int y = getAsset( _asset_button[ i ], CMD::POS_Y );
		x += _vec_x[ i ];
		y += _vec_y[ i ];

		if ( x < 64 ) { // 左
			x = 64;
			_vec_x[ i ] *= -1;
		}

		if ( x > 1800 ) { // 右
			x = 1800;
			_vec_x[ i ] *= -1;
		}

		if ( y > 980 ) { // 下
			y = 980;
			_vec_y[ i ] *= -1;
		}

		if ( y < 230 ) { // 上
			y = 230;
			_vec_y[ i ] *= -1;
		}

		setAsset( _asset_button[ i ], CMD::POS_X, x );
		setAsset( _asset_button[ i ], CMD::POS_Y, y );

		int touch = getAsset( _asset_button[ i ], CMD::TOUCH );
		if ( touch == 1 ) {
			int mark = getAsset( _asset_mark_thema, CMD::STATUS );
			if ( MARK_STATUS[ i ] == mark ) {
				_num--;
				setAsset( _asset_num, CMD::STATUS, _num );

				int new_mark;
				do {
					new_mark = MARK_STATUS[ getRand( ) % 4 ];
				} while ( new_mark == mark );
				setAsset( _asset_mark_thema, CMD::STATUS, new_mark );
			}

			if ( _num == 0 ) {
				finish( );
			}
		}
	}

	// update mark
	for ( int i = 0; i < 4; i++ ) {
		int x = getAsset( _asset_button[ i ], CMD::POS_X );
		int y = getAsset( _asset_button[ i ], CMD::POS_Y );
		setAsset( _asset_mark[ i ], CMD::POS_X, x );
		setAsset( _asset_mark[ i ], CMD::POS_Y, y );
	}
}

// パフォーマンスモードでゲーム開始前に表示されるゲーム説明を登録します
// １行１４文字で４行まで正常に表示できます
STRING info( ) {
	return "お題と同じマークを付けた\nボタンを"
		   "押そう！"; // ここに説明文を入力します。
}

int tag( ) {
	return 41;
}

GAME_END;