#include "Impulse.h"

GAME_BEGIN( D_Saiga );

int btn[ 12 ] = { };

int num[ 12 ] = { };

int count = 0;

int num_count = 0;

int theme_num = 0;

int theme_now = 0;

int num_now[ 12 ] = { };

int plate[ 2 ] = { };

int frame[ 2 ] = {  };

void setup( ) {

	creator( "ゲームプログラマー専攻 １年", "雜賀 琉日（サイガ ルカ）" );

	plate[ 0 ] = createAsset( ASSET::PLATE );
	setAsset( plate[ 0 ], CMD::POS_X, 960 );
	setAsset( plate[ 0 ], CMD::POS_Y, 490 );

	plate[ 1 ] = createAsset( ASSET::PLATE );
	setAsset( plate[ 1 ], CMD::POS_X, 250 );
	setAsset( plate[ 1 ], CMD::POS_Y, 200 );
	setAsset( plate[ 1 ], CMD::STATUS,PLATE_REMAINING );

	frame [0]=createAsset( ASSET::FRAME);
	setAsset( frame[0], CMD::POS_X, 960 );
	setAsset( frame[0], CMD::POS_Y, 580 );

	frame[ 1 ] = createAsset( ASSET::FRAME );
	setAsset( frame[ 1 ], CMD::POS_X, 250 );
	setAsset( frame[ 1 ], CMD::POS_Y, 280 );


	count = 5;

	//カウントを表示
	num_count = createAsset( ASSET::NUMBER );
	setAsset( num_count, CMD::POS_X, 250 );
	setAsset( num_count, CMD::POS_Y, 280 );
	setAsset( num_count, CMD::STATUS, count );

	//ボタン・ナンバーを配置
	btn[ 0 ] = createAsset( ASSET::BUTTON );
	setAsset( btn[ 0 ], CMD::POS_X, 960 );
	setAsset( btn[ 0 ], CMD::POS_Y, 230 );

	btn[ 1 ] = createAsset( ASSET::BUTTON );
	setAsset( btn[ 1 ], CMD::POS_X, 1150 );
	setAsset( btn[ 1 ], CMD::POS_Y, 300 );

	btn[ 2 ] = createAsset( ASSET::BUTTON );
	setAsset( btn[ 2 ], CMD::POS_X, 1300 );
	setAsset( btn[ 2 ], CMD::POS_Y, 420 );

	btn[ 3 ] = createAsset( ASSET::BUTTON );
	setAsset( btn[ 3 ], CMD::POS_X, 1380 );
	setAsset( btn[ 3 ], CMD::POS_Y, 580 );

	btn[ 4 ] = createAsset( ASSET::BUTTON );
	setAsset( btn[ 4 ], CMD::POS_X, 1300 );
	setAsset( btn[ 4 ], CMD::POS_Y, 750 );

	btn[ 5 ] = createAsset( ASSET::BUTTON );
	setAsset( btn[ 5 ], CMD::POS_X, 1150 );
	setAsset( btn[ 5 ], CMD::POS_Y, 880 );

	btn[ 6 ] = createAsset( ASSET::BUTTON );
	setAsset( btn[ 6 ], CMD::POS_X, 960 );
	setAsset( btn[ 6 ], CMD::POS_Y, 950 );

	btn[ 7 ] = createAsset( ASSET::BUTTON );
	setAsset( btn[ 7 ], CMD::POS_X, 780 );
	setAsset( btn[ 7 ], CMD::POS_Y, 880 );

	btn[ 8 ] = createAsset( ASSET::BUTTON );
	setAsset( btn[ 8 ], CMD::POS_X, 630 );
	setAsset( btn[ 8 ], CMD::POS_Y, 750 );

	btn[ 9 ] = createAsset( ASSET::BUTTON );
	setAsset( btn[ 9 ], CMD::POS_X, 540 );
	setAsset( btn[ 9 ], CMD::POS_Y, 580 );

	btn[ 10 ] = createAsset( ASSET::BUTTON );
	setAsset( btn[ 10 ], CMD::POS_X, 630 );
	setAsset( btn[ 10 ], CMD::POS_Y, 420 );

	btn[ 11 ] = createAsset( ASSET::BUTTON );
	setAsset( btn[ 11 ], CMD::POS_X, 780 );
	setAsset( btn[ 11 ], CMD::POS_Y, 300 );

	num[ 0 ] = createAsset( ASSET::NUMBER );
	setAsset( num[ 0 ], CMD::POS_X, 960 );
	setAsset( num[ 0 ], CMD::POS_Y, 230 );
	setAsset( num[ 0 ], CMD::STATUS, 12 );

	num[ 1 ] = createAsset( ASSET::NUMBER );
	setAsset( num[ 1 ], CMD::POS_X, 1150 );
	setAsset( num[ 1 ], CMD::POS_Y, 300 );
	setAsset( num[ 1 ], CMD::STATUS, 1 );

	num[ 2 ] = createAsset( ASSET::NUMBER );
	setAsset( num[ 2 ], CMD::POS_X, 1300 );
	setAsset( num[ 2 ], CMD::POS_Y, 420 );
	setAsset( num[ 2 ], CMD::STATUS, 2 );

	num[ 3 ] = createAsset( ASSET::NUMBER );
	setAsset( num[ 3 ], CMD::POS_X, 1380 );
	setAsset( num[ 3 ], CMD::POS_Y, 580 );
	setAsset( num[ 3 ], CMD::STATUS, 3 );

	num[ 4 ] = createAsset( ASSET::NUMBER );
	setAsset( num[ 4 ], CMD::POS_X, 1300 );
	setAsset( num[ 4 ], CMD::POS_Y, 750 );
	setAsset( num[ 4 ], CMD::STATUS, 4 );

	num[ 5 ] = createAsset( ASSET::NUMBER );
	setAsset( num[ 5 ], CMD::POS_X, 1150 );
	setAsset( num[ 5 ], CMD::POS_Y, 880 );
	setAsset( num[ 5 ], CMD::STATUS, 5 );

	num[ 6 ] = createAsset( ASSET::NUMBER );
	setAsset( num[ 6 ], CMD::POS_X, 960 );
	setAsset( num[ 6 ], CMD::POS_Y, 950 );
	setAsset( num[ 6 ], CMD::STATUS, 6 );

	num[ 7 ] = createAsset( ASSET::NUMBER );
	setAsset( num[ 7 ], CMD::POS_X, 780 );
	setAsset( num[ 7 ], CMD::POS_Y, 880 );
	setAsset( num[ 7 ], CMD::STATUS, 7 );

	num[ 8 ] = createAsset( ASSET::NUMBER );
	setAsset( num[ 8 ], CMD::POS_X, 630 );
	setAsset( num[ 8 ], CMD::POS_Y, 750 );
	setAsset( num[ 8 ], CMD::STATUS, 8 );

	num[ 9 ] = createAsset( ASSET::NUMBER );
	setAsset( num[ 9 ], CMD::POS_X, 540 );
	setAsset( num[ 9 ], CMD::POS_Y, 580 );
	setAsset( num[ 9 ], CMD::STATUS, 9 );

	num[ 10 ] = createAsset( ASSET::NUMBER );
	setAsset( num[ 10 ], CMD::POS_X, 630 );
	setAsset( num[ 10 ], CMD::POS_Y, 420 );
	setAsset( num[ 10 ], CMD::STATUS, 10 );

	num[ 11 ] = createAsset( ASSET::NUMBER );
	setAsset( num[ 11 ], CMD::POS_X, 780 );
	setAsset( num[ 11 ], CMD::POS_Y, 300 );
	setAsset( num[ 11 ], CMD::STATUS, 11 );

	//お題ナンバーを配置
	theme_num = createAsset( ASSET::NUMBER );
	setAsset( theme_num, CMD::STATUS, 1 + getRand( ) % 12 );
	setAsset( theme_num, CMD::POS_X, 960 );
	setAsset( theme_num, CMD::POS_Y, 580 );

	//ストップウォッチを計測
	stopwatch( STOPWATCH::START );

}

void update( ) {

	theme_now = getAsset( theme_num, CMD::STATUS );

	int touch[ 12 ] = {  };

	int num_now[ 12 ] = {  };

	for ( int i = 0; i < 12; i++ ) {

		touch[ i ] = getAsset( btn[ i ], CMD::TOUCH );

		num_now[ i ] = getAsset( num[ i ], CMD::STATUS );

		if ( touch[ i ] == 1 ) {

			if ( num_now[ i ] == theme_now ) {

				count--;

				setAsset( num_count, CMD::STATUS, count );

				setAsset( theme_num, CMD::STATUS, 1 + getRand( ) % 12 );

			}
		}
	}

	if ( count<=0 ) {

		finish( );

		stopwatch( STOPWATCH::STOP );

	}
}

// パフォーマンスモードでゲーム開始前に表示されるゲーム説明を登録します
// １行１４文字で４行まで正常に表示できます
STRING info( ) {
	return "画面の真ん中に表示された数字と\n同じ数字を押そう！"; // ここに説明文を入力します。
}

int tag( ) {
	return 43;
}

GAME_END;