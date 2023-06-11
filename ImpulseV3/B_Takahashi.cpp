#include "Impulse.h"
#include <array>

static const int MARKDATA[4] = { MARK_MISANGA, MARK_SHOES, MARK_WATCH };

GAME_BEGIN( B_Takahashi );

int _true_button = 0;
int _false_button = 0;
int _true_mark = 0;
int _false_mark = 0;
int _count = 5;
int _number = 0;
//int _zero_point_five = 0;
int _question_mark = 0;

void setup( ) {
	creator( "PGPL＆VRマスターコース １年", "髙橋 涼太" );

	_count = 5;
	/*_zero_point_five = 0;*/

	stopwatch( STOPWATCH::START );
	_number = createAsset( ASSET::NUMBER );
	setAsset( _number, CMD::POS_X, ( SCREEN_WIDTH / 2 ) + 160 );
	setAsset( _number, CMD::POS_Y, 230 );
	setAsset( _number, CMD::STATUS, _count );

	int number_frame = createAsset( ASSET::FRAME );
	setAsset( number_frame, CMD::POS_X, ( SCREEN_WIDTH / 2 ) + 160 );
	setAsset( number_frame, CMD::POS_Y, 230 );

	int plate_frame = createAsset( ASSET::PLATE );
	setAsset( plate_frame, CMD::POS_X, ( SCREEN_WIDTH / 2 ) + 160 );
	setAsset( plate_frame, CMD::POS_Y, 150 );
	setAsset( plate_frame, CMD::STATUS, PLATE_REMAINING );

	_true_button = createAsset( ASSET::BUTTON );
	_false_button = createAsset( ASSET::BUTTON );
	_true_mark = createAsset( ASSET::MARK );
	_false_mark = createAsset( ASSET::MARK );

	_question_mark = createAsset( ASSET::MARK );
	setAsset( _question_mark, CMD::POS_X, ( SCREEN_WIDTH / 2 ) - 160 );
	setAsset( _question_mark, CMD::POS_Y, 230 );

	int question_mark_plate = createAsset( ASSET::PLATE );
	setAsset( question_mark_plate, CMD::POS_X, ( SCREEN_WIDTH / 2 ) - 160 );
	setAsset( question_mark_plate, CMD::POS_Y, 150 );

	int question_mark_frame = createAsset( ASSET::FRAME );
	setAsset( question_mark_frame, CMD::POS_X, ( SCREEN_WIDTH / 2 ) - 160 );
	setAsset( question_mark_frame, CMD::POS_Y, 230 );

	resetQuestion( );
}

struct Pos {
	int x;
	int y;
};
struct Pos1 {
	int x;
	int y;
};


int calAbs( int n ) {
	if ( n < 0 ) {
		n *= -1;
	}
	return n;
}

int calAbs1( int n ) {
	if ( n < 0 ) {
		n *= -1;
	}
	return n;
}

void resetQuestion( ) {
	int past_mark = getAsset( _true_mark, CMD::STATUS );
	int true_mark;
	do {
		true_mark = MARKDATA[getRand( ) % 3];
	} while ( true_mark == past_mark );
	setAsset( _question_mark, CMD::STATUS, true_mark );
	setAsset( _true_mark, CMD::STATUS, true_mark );

	int false_mark;
	do {
		false_mark = MARKDATA[getRand( ) % 3];
	} while ( true_mark == false_mark );
	setAsset( _false_mark, CMD::STATUS, false_mark );

	int true_pos_x_old = getAsset( _true_button, CMD::POS_X );
	int true_pos_y_old = getAsset( _true_button, CMD::POS_Y );

	int false_pos_x_old = getAsset( _false_button, CMD::POS_X );
	int false_pos_y_old = getAsset( _false_button, CMD::POS_Y );


	while ( 1 ) 	{
		int true_pos_x = ( getRand( ) % ( SCREEN_WIDTH - 200 ) ) + 100;
		int true_pos_y = ( getRand( ) % ( SCREEN_HEIGHT - 600 ) ) + 400;

		int false_pos_x = ( getRand( ) % ( SCREEN_WIDTH - 200 ) ) + 100;
		int false_pos_y = ( getRand( ) % ( SCREEN_HEIGHT - 600 ) ) + 400;

		setAsset( _true_button, CMD::POS_X, true_pos_x );
		setAsset( _true_button, CMD::POS_Y, true_pos_y );
		setAsset( _true_mark, CMD::POS_X, true_pos_x );
		setAsset( _true_mark, CMD::POS_Y, true_pos_y );

		setAsset( _false_button, CMD::POS_X, false_pos_x );
		setAsset( _false_button, CMD::POS_Y, false_pos_y );
		setAsset( _false_mark, CMD::POS_X, false_pos_x );
		setAsset( _false_mark, CMD::POS_Y, false_pos_y );

		Pos now_pos = { true_pos_x,true_pos_y };
		Pos old_pos = { true_pos_x_old,true_pos_y_old };

		Pos now_pos_one = { false_pos_x,false_pos_y };
		Pos old_pos_one = { false_pos_x_old,false_pos_y_old };

		if ( !( isHitting( now_pos, old_pos ) ) ) {
			if ( !( isHitting( now_pos_one, old_pos_one ) ) ) {
				if ( !( isHitting( now_pos, now_pos_one ) ) ) {
					break;
				}
			}
		}

	}
}

bool isHitting( Pos now_pos, Pos old_pos ) {
	int diff_width = 0;
	int diff_height = 0;

	diff_width = calAbs( now_pos.x - old_pos.x );
	diff_height = calAbs( now_pos.y - old_pos.y );

	if ( diff_width < 130 && diff_height < 130 ) {
		return true;
	}

	return false;
}


void update( ) {
	if ( getAsset( _true_button, CMD::TOUCH ) ) {
		/*	_zero_point_five = 0;
			_zero_point_five++;*/

		resetQuestion( );

		_count--;
		setAsset( _number, CMD::STATUS, _count );

		if ( _count == 0 ) {
			finish( );
		}
	}
}

STRING info( ) {
	return "お題のマークと同じマークを\n押そう！"; // ここに説明文を入力します。
}


int tag( ) {
	return 25;
}

GAME_END;