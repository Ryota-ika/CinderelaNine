#include "Impulse.h"
#include <array>

GAME_BEGIN( D_Takahashi );

int button[ 4 ] = { 0 };
int flame = 0;
int mark = 0;//お題
int Ansmark[ 4 ] = { 0 };//ボタンのマーク
int count = 0;//ナンバー
int count_status = 0;//ナンバーのステータス
bool flag;
bool can_push_flag;
int time = 0;
int mark_status = 0;
int frame_mark = 0;
int frane_count = 0;
int plate_mark = 0;
int plate_count = 0;

const int CONST_MARK[ 4 ] = {
	MARK_DRINK,
	MARK_MISANGA,
	MARK_SHOES,
	MARK_WATCH,
};

//ASSET::FRAME;
//ASSET::PLATE;
void setup( ) override {
	creator( "ゲームプログラマー専攻 １年", "髙橋 幸南" );
	plate_mark = createAsset( ASSET::PLATE );
	setAsset( plate_mark, CMD::POS_X, SCREEN_WIDTH / 2 );
	setAsset( plate_mark, CMD::POS_Y, SCREEN_HEIGHT / 5 );
	
	plate_count = createAsset( ASSET::PLATE );
	setAsset( plate_count, CMD::POS_X, SCREEN_WIDTH /5 );
	setAsset( plate_count, CMD::POS_Y, SCREEN_HEIGHT / 5 );
	setAsset( plate_count, CMD::STATUS, PLATE_REMAINING );

	frame_mark = createAsset( ASSET::FRAME );
	setAsset( frame_mark, CMD::POS_X, SCREEN_WIDTH / 2 );
	setAsset( frame_mark, CMD::POS_Y, SCREEN_HEIGHT / 3 );

	frane_count = createAsset( ASSET::FRAME );
	setAsset( frane_count, CMD::POS_X, SCREEN_WIDTH / 5 );
	setAsset( frane_count, CMD::POS_Y, SCREEN_HEIGHT / 3 );

	mark = createAsset( ASSET::MARK );
	setAsset( mark, CMD::POS_X, -100 );
	setAsset( mark, CMD::POS_Y, -100 );
	setAsset( mark, CMD::VISIBLE, 0 );

	stopwatch( STOPWATCH::STOP );
	flame = 0;
	flag = false;
	count = 3;
	count_status = createAsset( ASSET::NUMBER );
	setAsset( count_status, CMD::POS_X, SCREEN_WIDTH / 5 );
	setAsset( count_status, CMD::POS_Y, SCREEN_HEIGHT / 3 );
	setAsset( count_status, CMD::STATUS, count );
	std::array<int, 4>buf = getRandomMarkArray( );
	for ( int i = 0; i < 4; i++ ) {
		button[ i ] = createAsset( ASSET::BUTTON );
		setAsset( button[ i ], CMD::POS_X, ( int )( SCREEN_WIDTH / 3.5 ) + 300 * i );
		setAsset( button[ i ], CMD::POS_Y, 700 );
		Ansmark[ i ] = createAsset( ASSET::MARK );
		setAsset( Ansmark[ i ], CMD::STATUS, buf[ i ] );
		setAsset( Ansmark[ i ], CMD::POS_X, ( int )( SCREEN_WIDTH / 3.5 ) + 300 * i );
		setAsset( Ansmark[ i ], CMD::POS_Y, 700 );
	}
	time = ( 60 * 2 ) + getRand( ) % ( ( 60 * 5 ) - ( 60 * 2 ) );


}

void update( ) override {
	if ( time == flame ) {
		flag = true;
		stopwatch( STOPWATCH::START );
	}
	if ( flag ) {
		//std::array<int, 4>buf = getRandomMarkArray( );
		
		setAsset( mark, CMD::VISIBLE, 1 );
		setAsset( mark, CMD::POS_X, SCREEN_WIDTH / 2 );
		setAsset( mark, CMD::POS_Y, SCREEN_HEIGHT / 3 );
		setAsset( mark, CMD::STATUS, RandomMark( ) );
		mark_status = getAsset( mark, CMD::STATUS );


		can_push_flag = true;
		flag = false;
	}
	for ( int i = 0; i < 4; i++ ) {
		int touch = getAsset( button[ i ], CMD::TOUCH );
		int mark_status = getAsset( mark, CMD::STATUS );//マークのステータス保存
		int button_status = getAsset( Ansmark[ i ], CMD::STATUS );//ボタンのステータス保存
		if ( !can_push_flag ) { 
			setAsset( button[ i ], CMD::STATUS, BUTTON_DISABLED );
		}
		if ( can_push_flag ) { 
			setAsset( button[ i ], CMD::STATUS, BUTTON_NORMAL );
		}
		if ( mark_status == button_status ) {
			if ( touch == 1 ) {
				if ( getAsset( mark, CMD::VISIBLE ) != 1 ) {
					continue;
				}
				count--;
				setAsset( count_status, CMD::STATUS, count );
				flame = 0;
				setAsset( mark, CMD::VISIBLE, false );
				stopwatch( STOPWATCH::STOP );
				can_push_flag = false;
				//finish( );
			}
		}
	}
	if ( count <= 0 ) {
		for ( int i = 0; i < 4; i++ ) 		{
			setAsset( button[ i ], CMD::STATUS, BUTTON_DISABLED );
		}
		finish( );
	}
	flame++;
}

int RandomMark( ) {
	int sel_mark;
	while ( true ) {
		sel_mark = CONST_MARK[ getRand( ) % 4 ];
		if ( mark_status != sel_mark ) {
			break;
		}
	}
	return sel_mark;
}

std::array<int, 4>getRandomMarkArray( ) {
	std::array<int, 4>buf = { CONST_MARK[ 0 ],CONST_MARK[ 1 ],CONST_MARK[ 2 ],CONST_MARK[ 3 ] };
	for ( int i = 0; i < 4; i++ ) {
		int r = getRand( ) % 4;
		int temp = buf[ i % 4 ];
		buf[ i % 4 ] = buf[ r ];
		buf[ r ] = temp;
	}
	return buf;
}
//1行１4文字４行まで
STRING info( ) override { 
	return "お題のマークが表示されたら、\n同じマークのボタンを押そう！"; 
}

int tag( ) {
	return 45;
}

GAME_END;