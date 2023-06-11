#include "Impulse.h"

GAME_BEGIN( C_Cho );

int button[ 9 ] = { 0 };
int number_Answer[ 9 ] = { 0 };
int Answer_Status[ 9 ] = { 0 };
int touch = 0;
int number_Question1 = 0;
int Question1_Status = 0;
int Question1_Clear = 0;
int Question2_Status = 0;
int Question2_Clear = 0;
int Question3_Status = 0;
int Question3_Clear = 0;
int number_Question2 = 0;
int number_Question3 = 0;
int count = 0;
int odai = 0;
int nokori = 0;
int clear = 0;
int time = 0;
int X = 0;
int Y = 0;
int i = 0;
int Question1_Frame = 0;
int Question2_Frame = 0;
int Question3_Frame = 0;
int Count_Frame = 0;
int _getPosX[ 9 ] = { 0 };
int mark_right1 = 0;
int mark_right2 = 0;
int a = 0;
int b = 0;
bool ischeck = false;

const int SHUFFULL = 200;//shuffle回数

void setQuestionNum( ) {
	odai = createAsset( ASSET::PLATE );
	setAsset( odai, CMD::STATUS, PLATE_THEME );
	setAsset( odai, CMD::POS_X, 330 );
	setAsset( odai, CMD::POS_Y, 160 );
	number_Question1 = createAsset( ASSET::NUMBER );
	number_Question2 = createAsset( ASSET::NUMBER );
	number_Question3 = createAsset( ASSET::NUMBER );
	Question1_Frame = createAsset( ASSET::FRAME );
	Question2_Frame = createAsset( ASSET::FRAME );
	Question3_Frame = createAsset( ASSET::FRAME );
	mark_right1 = createAsset( ASSET::MARK );
	setAsset( mark_right1, CMD::POS_X, 200 );
	setAsset( mark_right1, CMD::POS_Y, 250 );
	setAsset( mark_right1, CMD::STATUS, MARK_RIGHT );
	mark_right2 = createAsset( ASSET::MARK );
	setAsset( mark_right2, CMD::POS_X, 460 );
	setAsset( mark_right2, CMD::POS_Y, 250 );
	setAsset( mark_right2, CMD::STATUS, MARK_RIGHT );
	setAsset( number_Question1, CMD::POS_X, 70 );
	setAsset( number_Question1, CMD::POS_Y, 250 );
	setAsset( Question1_Frame, CMD::POS_X, 70 );
	setAsset( Question1_Frame, CMD::POS_Y, 250 );
	setAsset( number_Question2, CMD::POS_X, 330 );
	setAsset( number_Question2, CMD::POS_Y, 250 );
	setAsset( Question2_Frame, CMD::POS_X, 330 );
	setAsset( Question2_Frame, CMD::POS_Y, 250 );
	setAsset( number_Question3, CMD::POS_X, 590 );
	setAsset( number_Question3, CMD::POS_Y, 250 );
	setAsset( Question3_Frame, CMD::POS_X, 590 );
	setAsset( Question3_Frame, CMD::POS_Y, 250 );
	setAsset( number_Question1, CMD::STATUS, getRand( ) % 9 + 1 );
	Question1_Status = getAsset( number_Question1, CMD::STATUS );
	setAsset( number_Question2, CMD::STATUS, getRand( ) % 9 + 1 );
	Question2_Status = getAsset( number_Question2, CMD::STATUS );
	setAsset( number_Question3, CMD::STATUS, getRand( ) % 9 + 1 );
	Question3_Status = getAsset( number_Question3, CMD::STATUS );
}

void countDown( ) {
	nokori = createAsset( ASSET::PLATE );
	setAsset( nokori, CMD::STATUS, PLATE_REMAINING );
	setAsset( nokori, CMD::POS_X, 1840 );
	setAsset( nokori, CMD::POS_Y, 160 );
	stopwatch( STOPWATCH::START );
	count = createAsset( ASSET::NUMBER );
	Count_Frame = createAsset( ASSET::FRAME );
	setAsset( count, CMD::POS_X, 1840 );
	setAsset( count, CMD::POS_Y, 250 );
	setAsset( Count_Frame, CMD::POS_X, 1840 );
	setAsset( Count_Frame, CMD::POS_Y, 250 );
}

void setRandomNum( ) {
	for ( int i = 0; i < 9; i++ ) {
		X = ( 1920 / 9 ) *  i  + 100;
		Y = getRand( ) % 500 + 400;

		setAsset( button[ i ], CMD::POS_X, X );
		setAsset( button[ i ], CMD::POS_Y, Y );
		setAsset( number_Answer[ i ], CMD::STATUS, i + 1 );
		Answer_Status[ i ] = getAsset( number_Answer[ i ], CMD::STATUS );
		setAsset( number_Answer[ i ], CMD::POS_X, X );
		setAsset( number_Answer[ i ], CMD::POS_Y, Y );
		_getPosX[ i ] = getAsset( button[ i ], CMD::POS_X );
	}
	swapButton( SHUFFULL );
}

void swapButton( int count ) {
	for ( int i = 0; i < count; i++ ){
		int rand1 = getRand( ) % 9;
		int rand2 = getRand( ) % 9;
		int pos_x1 = getAsset( button[ rand1 ], CMD::POS_X );
		int pos_x2 = getAsset( button[ rand2 ], CMD::POS_X );
		int pos_y1 = getAsset( button[ rand1 ], CMD::POS_X );
		int pos_y2 = getAsset( button[ rand2 ], CMD::POS_X );
		setAsset( button[ rand1 ], CMD::POS_X, pos_x2 );
		setAsset( number_Answer[ rand1 ], CMD::POS_X, pos_x2 );
		setAsset( button[ rand2 ], CMD::POS_X, pos_x1 );
		setAsset( number_Answer[ rand2 ], CMD::POS_X, pos_x1 );
	}
}

void setup( ) {
	creator( "PGPL＆VRマスターコース １年", "チョウジョウカク" );
	clear = 0;
	stopwatch( STOPWATCH::START );
	countDown( );
	setQuestionNum( );
	for ( int i = 0; i < 9; i++ ) {
		button[ i ] = createAsset( ASSET::BUTTON );
		number_Answer[ i ] = createAsset( ASSET::NUMBER );
	}
	setRandomNum( );
	
}

void update( ) {
	time++;
	for ( i = 0; i < 9; i++ ) {
		touch = getAsset( button[ i ], CMD::TOUCH );
		if ( touch == 1 && Answer_Status[ i ] == Question1_Status && Question1_Clear == 0 ) {
			setAsset( number_Question1, CMD::VISIBLE, false );
			Question1_Clear = 1;
			time = 0;
		}
	}
	for ( i = 0; i < 9; i++ ) {
		touch = getAsset( button[ i ], CMD::TOUCH );
		if ( touch == 1 && Answer_Status[ i ] == Question2_Status && Question1_Clear == 1 && time >= 5 && Question2_Clear == 0 ) {
			setAsset( number_Question2, CMD::VISIBLE, false );
			Question2_Clear = 1;
			time = 0;
		}
	}
	for ( i = 0; i < 9; i++ ) {
		touch = getAsset( button[ i ], CMD::TOUCH );
		if ( touch == 1 && Answer_Status[ i ] == Question3_Status && time >= 5 && Question2_Clear == 1 && Question3_Clear == 0 ) {
			setAsset( number_Question3, CMD::VISIBLE, false );
			clear += 1;
			Question3_Clear = 1;
		}
	}
	if ( Question3_Clear == 1 ) {
		setQuestionNum( );
		setRandomNum( );

		Question1_Clear = 0;
		Question2_Clear = 0;
		Question3_Clear = 0;
	}
	setAsset( count, CMD::STATUS, 3 - clear );
	if ( 3 - clear == 0 ) {
		finish( );
	}
}

STRING info( ) {
	return "お題と同じ数字のボタンを押そう！";
}

int tag( ) {
	return 31;
}

GAME_END;