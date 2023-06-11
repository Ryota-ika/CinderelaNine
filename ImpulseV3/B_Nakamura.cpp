#include "Impulse.h"

GAME_BEGIN( B_Nakamura );

int _marble[ 10 ] = { };
int _mark[ 10 ] = { };
int _mark_status[ 3 ] = { MARK_MISANGA, MARK_DRINK, MARK_SHOES };
const int _MARK_AND_MARK_NUM = 10;
int _marble_pos_x_data = 0;
int _marble_pos_y_data = 0;
int _delete_count = 0;
bool _delete[ 10 ] = { false };
const int _MARBLE_SPACE_X = 190;
int _marble_pos_x = 100;
int _marble_pos_y = 400;

STRING info( ) {
	return "マークが付いたマーブルを\n同じマークの円の中に入れよう！";
}

void setup( ) {
	creator( "ゲームプログラマー専攻 １年", "中村 翔" );
	stopwatch( STOPWATCH::START );
	makeStage( );
	makeMarbleMakeMarkStatus( );
}

void makeStage( ) {
	makeFrame( );
	makeSymbol( );
}

void makeFrame( ) {
	int frame[ 3 ] = { };
	const int ROW = 3;
	for ( int i = 0; i < ROW; i++ ) {
		const int FRAME_X = 300;
		const int FRAME_SPACE_X = 650;
		int pos_x = FRAME_X + FRAME_SPACE_X * i;
		const int POS_Y = 940;
		frame[ i ] = createAsset( ASSET::MARK );
		setAsset( frame[ i ], CMD::POS_X, pos_x );
		setAsset( frame[ i ], CMD::POS_Y, POS_Y );
		setAsset( frame[ i ], CMD::STATUS, MARK_CIRCLE );
	}
}

void makeSymbol( ) {
	int symbol[ 3 ] = { };
	int frame[ 3 ] = { };
	const int ROW = 3;
	for ( int i = 0; i < ROW; i++ ) {
		const int SYMBOL_X = 300;
		const int SYMBOL_SPACE_X = 650;
		int pos_x = SYMBOL_X + SYMBOL_SPACE_X * i;
		const int POS_Y = 800;
		symbol[ i ] = createAsset( ASSET::MARK );
		setAsset( symbol[ i ], CMD::POS_X, pos_x );
		setAsset( symbol[ i ], CMD::POS_Y, POS_Y );
		setAsset( symbol[ i ], CMD::STATUS, _mark_status[ i ] );
		frame[ i ] = createAsset( ASSET::FRAME );
		setAsset( frame[ i ], CMD::POS_X, pos_x );
		setAsset( frame[ i ], CMD::POS_Y, POS_Y );
	}
}

void makeMarbleMakeMarkStatus( ) {
	_delete_count = 0;
	int rand_mark_status[ 10 ] = { };
	int club_mark_count = 0;
	int spade_mark_count = 0;
	int dia_mark_count = 0;
	for ( int i = 0; i < _MARK_AND_MARK_NUM; i++ ) {
		_delete[ i ] = { false };
		_marble[ i ] = createAsset( ASSET::MARBLE );
		setAsset( _marble[ i ], CMD::POS_X, _marble_pos_x + _MARBLE_SPACE_X * i );
		setAsset( _marble[ i ], CMD::POS_Y, _marble_pos_y );
		_mark[ i ] = createAsset( ASSET::MARK );
		if ( club_mark_count == 0 ) {
			rand_mark_status[ i ] = _mark_status[ 0 ];
			club_mark_count++;
		} else if ( spade_mark_count == 0 ) {
			rand_mark_status[ i ] = _mark_status[ 1 ];
			spade_mark_count++;
		} else if ( dia_mark_count == 0 ) {
			rand_mark_status[ i ] = _mark_status[ 2 ];
			dia_mark_count++;
		} else {
			rand_mark_status[ i ] = _mark_status[ rand( ) % 3 ];
		}
	}
	for ( int i = 0; i < _MARK_AND_MARK_NUM; i++ ) {
		setAsset( _mark[ i ], CMD::STATUS, rand_mark_status[ i ] );
	}
}

void update( ) {
	moveLimitMarble( );
	setMarkOnMarble( );
	finishCondition( );
}

void moveLimitMarble( ) {
	for ( int i = 0; i < _MARK_AND_MARK_NUM; i++ ) {
		_marble_pos_x_data = getAsset( _marble[ i ], CMD::POS_X );
		_marble_pos_y_data = getAsset( _marble[ i ], CMD::POS_Y );
		if ( _marble_pos_x_data < 0 ) {
			setAsset( _marble[ i ], CMD::POS_X, 0 );
		} else if ( SCREEN_WIDTH < _marble_pos_x_data ) {
			setAsset( _marble[ i ], CMD::POS_X, SCREEN_WIDTH );
		} else if ( _marble_pos_y_data < 0 ) {
			setAsset( _marble[ i ], CMD::POS_Y, 0 );
		} else if ( SCREEN_HEIGHT < _marble_pos_y_data ) {
			setAsset( _marble[ i ], CMD::POS_Y, SCREEN_HEIGHT );
		}
	}
}

void setMarkOnMarble( ) {
	for ( int i = 0; i < _MARK_AND_MARK_NUM; i++ ) {
		_marble_pos_x_data = getAsset( _marble[ i ], CMD::POS_X );
		_marble_pos_y_data = getAsset( _marble[ i ], CMD::POS_Y );
		setAsset( _mark[ i ], CMD::POS_X, _marble_pos_x_data );
		setAsset( _mark[ i ], CMD::POS_Y, _marble_pos_y_data );
	}
}

int judgeArea( int pos_x, int pos_y ) {
	const int LEFT = 0;
	const int CENTER = 1;
	const int RIGHT = 2;
	const int LEFT_RANGE_BORDER = 550;
	const int RIGHT_RANGE_BORDER = 1350;
	int this_pos_x_place = -1;
	if ( pos_x < LEFT_RANGE_BORDER - 50 &&
		 60 < pos_x ) {
		this_pos_x_place = LEFT;
	} else if ( LEFT_RANGE_BORDER + 180 < pos_x &&
				pos_x < RIGHT_RANGE_BORDER - 180 ) {
		this_pos_x_place = CENTER;
	} else if ( RIGHT_RANGE_BORDER + 50 < pos_x &&
				pos_x < SCREEN_WIDTH - 60 ) {
		this_pos_x_place = RIGHT;
	}
	const int HEIGHT = 3;
	const int HEIGHT_RANGE_BORDER = 710;
	int this_pos_y_place = -1;
	if ( HEIGHT_RANGE_BORDER < pos_y ) {
		this_pos_y_place = HEIGHT;
	}
	int status = -1;
	if ( this_pos_x_place == LEFT &&
		 this_pos_y_place == HEIGHT ) {
		status = MARK_MISANGA;
	}
	if ( this_pos_x_place == CENTER &&
		 this_pos_y_place == HEIGHT ) {
		status = MARK_DRINK;
	}
	if ( this_pos_x_place == RIGHT &&
		 this_pos_y_place == HEIGHT ) {
		status = MARK_SHOES;
	}
	return status;
}

void finishCondition( ) {
	for ( int i = 0; i < _MARK_AND_MARK_NUM; i++ ) {
		int touch = getAsset( _marble[ i ], CMD::TOUCH );
		int mark_on_marble_status_data = getAsset( _mark[ i ], CMD::STATUS );
		_marble_pos_x_data = getAsset( _marble[ i ], CMD::POS_X );
		_marble_pos_y_data = getAsset( _marble[ i ], CMD::POS_Y );
		int this_area_mark = judgeArea( _marble_pos_x_data, _marble_pos_y_data );
		if ( mark_on_marble_status_data == this_area_mark && !touch && !_delete[ i ] ) {
			setAsset( _marble[ i ], CMD::VISIBLE, false );
			setAsset( _mark[ i ], CMD::VISIBLE, false );
			_delete_count++;
			_delete[ i ] = true;
		}
		if ( mark_on_marble_status_data != this_area_mark && !touch ) {
			setAsset( _marble[ i ], CMD::POS_X, _marble_pos_x + _MARBLE_SPACE_X * i );
			setAsset( _marble[ i ], CMD::POS_Y, _marble_pos_y );
		}
	}
	if ( _delete_count == 10 ) {
		finish( );
	}
}

int tag( ) {
	return 22;
}

GAME_END;


