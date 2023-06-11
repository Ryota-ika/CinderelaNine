#include "Impulse.h"

GAME_BEGIN( B_Horiguchi );
int button[ 4 ] = { 0 };
int count = 3;
int zero_point_two = 0;
int number = 0;
int random_mark[ 4 ] = { MARK_DRINK,MARK_SHOES,MARK_WATCH,MARK_MISANGA };
int mark[ 4 ] = { 0 };
int question_mark = 0;
int rand_time = 0;
int time = 0;
int stoping = 0;

void setup( ) {
	rand_time = ( getRand( ) % 240 );

	count = 3;

	int number_frame = createAsset( ASSET::FRAME );
	setAsset( number_frame, CMD::POS_X, SCREEN_WIDTH / 2 + 160 );
	setAsset( number_frame, CMD::POS_Y, 230 );

	int number_plate = createAsset( ASSET::PLATE );
	setAsset( number_plate, CMD::POS_X, SCREEN_WIDTH / 2 + 160 );
	setAsset( number_plate, CMD::POS_Y, 150 );
	setAsset( number_plate, CMD::STATUS, PLATE_REMAINING );

	number = createAsset( ASSET::NUMBER );
	setAsset( number, CMD::STATUS, count );
	setAsset( number, CMD::POS_X, SCREEN_WIDTH/2+160 );
	setAsset( number, CMD::POS_Y, 230 );

	button[ 0 ] = createAsset( ASSET::BUTTON );
	setAsset( button[ 0 ], CMD::POS_X, SCREEN_WIDTH / 2 - 300 );
	setAsset( button[ 0 ], CMD::POS_Y, SCREEN_HEIGHT - 100 );
	setAsset( button[ 0 ], CMD::STATUS, BUTTON_DISABLED );

	button[ 1 ] = createAsset( ASSET::BUTTON );
	setAsset( button[ 1 ], CMD::POS_X, SCREEN_WIDTH / 2 - 100 );
	setAsset( button[ 1 ], CMD::POS_Y, SCREEN_HEIGHT - 100 );
	setAsset( button[ 1 ], CMD::STATUS, BUTTON_DISABLED );

	button[ 2 ] = createAsset( ASSET::BUTTON );
	setAsset( button[ 2 ], CMD::POS_X, SCREEN_WIDTH / 2 + 100 );
	setAsset( button[ 2 ], CMD::POS_Y, SCREEN_HEIGHT - 100 );
	setAsset( button[ 2 ], CMD::STATUS, BUTTON_DISABLED );

	button[ 3 ] = createAsset( ASSET::BUTTON );
	setAsset( button[ 3 ], CMD::POS_X, SCREEN_WIDTH / 2 + 300 );
	setAsset( button[ 3 ], CMD::POS_Y, SCREEN_HEIGHT - 100 );
	setAsset( button[ 3 ], CMD::STATUS, BUTTON_DISABLED );

	mark[ 0 ] = createAsset( ASSET::MARK );
	setAsset( mark[ 0 ], CMD::POS_X, SCREEN_WIDTH / 2 - 300 );
	setAsset( mark[ 0 ], CMD::POS_Y, SCREEN_HEIGHT - 250 );
	setAsset( mark[ 0 ], CMD::STATUS, MARK_DRINK );

	mark[ 1 ] = createAsset( ASSET::MARK );
	setAsset( mark[ 1 ], CMD::POS_X, SCREEN_WIDTH / 2 - 100 );
	setAsset( mark[ 1 ], CMD::POS_Y, SCREEN_HEIGHT - 250 );
	setAsset( mark[ 1 ], CMD::STATUS, MARK_MISANGA );

	mark[ 2 ] = createAsset( ASSET::MARK );
	setAsset( mark[ 2 ], CMD::POS_X, SCREEN_WIDTH / 2 + 100 );
	setAsset( mark[ 2 ], CMD::POS_Y, SCREEN_HEIGHT - 250 );
	setAsset( mark[ 2 ], CMD::STATUS, MARK_WATCH );

	mark[ 3 ] = createAsset( ASSET::MARK );
	setAsset( mark[ 3 ], CMD::POS_X, SCREEN_WIDTH / 2 + 300 );
	setAsset( mark[ 3 ], CMD::POS_Y, SCREEN_HEIGHT - 250 );
	setAsset( mark[ 3 ], CMD::STATUS, MARK_SHOES );

	int question_frame = createAsset( ASSET::FRAME );
	setAsset( question_frame, CMD::POS_X, SCREEN_WIDTH / 2 - 160 );
	setAsset( question_frame, CMD::POS_Y, 230 );

	int question_plate = createAsset( ASSET::PLATE );
	setAsset( question_plate, CMD::POS_X, SCREEN_WIDTH / 2 - 160 );
	setAsset( question_plate, CMD::POS_Y, 150 );

	question_mark = createAsset( ASSET::MARK );
	setAsset( question_mark, CMD::POS_X,  SCREEN_WIDTH / 2-160 );
	setAsset( question_mark, CMD::POS_Y, 230 );
	setAsset( question_mark, CMD::STATUS, random_mark[ getRand( ) % 4 ] );

	creator( "PGPL＆VRマスターコース １年", "堀口 凌" );
}

void update( ) {
	if ( stoping == 0 ) {
		stopwatch( STOPWATCH::STOP );
		for ( int i = 0; i < 4; i++ ) {
			setAsset( button[ i ], CMD::STATUS, BUTTON_DISABLED );
		}

		if ( zero_point_two == 12 ) {
			for ( int i = 0; i < 100; i++ ) {
				int random1 = getRand( ) % 4;
				int random2 = getRand( ) % 4;
				int s0 = getAsset( mark[ random1 ], CMD::STATUS );
				int s1 = getAsset( mark[ random2 ], CMD::STATUS );
				setAsset( mark[ random1 ], CMD::STATUS, s1 );
				setAsset( mark[ random2 ], CMD::STATUS, s0 );
			}
			setAsset( question_mark, CMD::STATUS, random_mark[ getRand( ) % 4 ] );
		}
		int two_second = 120;
		if ( time == rand_time + two_second ) {
			stoping = 1;
			stopwatch( STOPWATCH::START );
			for ( int i = 0; i < 4; i++ ) {
				setAsset( button[ i ], CMD::STATUS, BUTTON_NORMAL );
			}
		}
	}
	for ( int i = 0; i < 4; i++ ) {
		if ( getAsset( button[ i ], CMD::TOUCH ) ) {
			int mark_button = getAsset( mark[ i ], CMD::STATUS );
			setAsset( mark[ i ], CMD::STATUS, mark_button );
			if ( getAsset( question_mark, CMD::STATUS ) == getAsset( mark[ i ], CMD::STATUS ) ) {
				count--;
				setAsset( number, CMD::STATUS, count );
				stoping = 0;
				time = 0;
				playSe( SE::HIT );
			} else {
				playSe( SE::MISS );
			}
		}
	}

	if ( zero_point_two == 12 ) {
		zero_point_two = 0;
	}
	else {
		zero_point_two++;
	}
	if ( count == 0 ) {
		finish( );
	}
	time++;
}

STRING info( ) {
	return "マークが止まったらお題と\n同じマークのボタンを押そう！"; // ここに説明文を入力します。
}

int tag( ) {
	return 21;
}

GAME_END;