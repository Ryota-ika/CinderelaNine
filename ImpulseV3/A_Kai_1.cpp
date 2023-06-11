#include "Impulse.h"

GAME_BEGIN( A_Kai_1 );

typedef struct pos {
	int x = 0;
	int y = 0;
	bool used = false;
}pos;

pos position[ 20 ];
int score = 0;
int	button[ 7 ] = {};
int mark[ 7 ] = {};
int dummy_mark = -1;
int dummy_mark_2 = -1;
int dummy_mark_3 = -1;

int ans_mark = -1;
int count = 0;
void setup( ) {
	score = 0;
	count = 0;

	for ( int i = 0; i < 4; i++ ) {
		for ( int j = 0; j < 5; j++ ) {
			position[ i + j * 4 ].x = ( ( SCREEN_WIDTH / 6 ) * j ) + SCREEN_WIDTH / 6;
			position[ i + j * 4 ].y = ( 140 * i ) + 400;
		}
	}
	stopwatch( STOPWATCH::START );
	creator( "ゲームプログラマー専攻 ２年","カイウッティアナン クンニティ" );
}

void update( ) {
	if ( count <= 2 ) {
		if ( button[ 0 ] == 0 ) {
			create_button( 3 );
		} else {
			loop_stage_check( 3 );
		}
	} else if ( count >= 3 && count <= 3 ) {
		if ( button[ 3 ] == 0 ) {
			//destory_all_asset(3);
			create_button( 5 );
		} else {
			loop_stage_check( 5 );
		}
	} else if ( count >= 4 && count <= 4 ) {
		if ( button[ 3 ] == 0 ) {
			//destory_all_asset(3);
			create_button( 7 );
		} else {
			loop_stage_check( 7 );
		}
	}
	if ( score >= 5 ) {
		stopwatch( STOPWATCH::STOP );
		finish( );
	}
}
STRING info( ) { 
	return "ペアがないマークを探して押そう！";
}
void reset_all_pos( ) {
	for ( int i = 0; i < 20; i++ ) {
		position[ i ].used = false;
	}
}
void change_posi( int num ) {
	reset_all_pos( );
	ans_mark = getRand_ans( );
	dummy_mark = getRand_not_ans( ans_mark );

	for ( int i = 0; i < num; i++ ) {
		int getRand_pos = getRand_position_not_use( position );


		setAsset( button[ i ], CMD::POS_X, position[ getRand_pos ].x );
		setAsset( button[ i ], CMD::POS_Y, position[ getRand_pos ].y );


		setAsset( mark[ i ], CMD::POS_X, position[ getRand_pos ].x );
		setAsset( mark[ i ], CMD::POS_Y, position[ getRand_pos ].y );
		if ( i == 1 ) {
			setAsset( mark[ i ], CMD::STATUS, ans_mark );

		} else {
			setAsset( mark[ i ], CMD::STATUS, dummy_mark );

		}
		position[ getRand_pos ].used = true;

	}
}
void loop_stage_check( int num ) {
	for ( int i = 0; i < num; i++ ) {
		if ( button[i] != NULL ) {
			int t = getAsset( button[ i ], CMD::TOUCH );
			if ( getAsset( mark[ i ], CMD::STATUS ) == ans_mark && t ) {
				count++;
				if ( count <= num ) {
					change_posi( num );
				}
				destory_all_asset( num );
				returnToNull( num );
				score++;
			}
		}
		
	}
}
int getRand_position_not_use( pos target[ ] ) {
	int num = -1;
	do {
		num = getRand( ) % 20;
		/*if (target[num].used == false)
		{
			break;
		}*/
	} while ( target[ num ].used == true );
	return num;
}
void create_button( int button_size ) {
	ans_mark = getRand_ans( );
	dummy_mark = getRand_not_ans( ans_mark );
	dummy_mark_2 = getRand_not_ans( ans_mark, dummy_mark );
	dummy_mark_3 = getRand_not_ans( ans_mark, dummy_mark, dummy_mark_2 );
	for ( int i = 0; i < button_size; i++ ) {
		int getRand_pos = getRand_position_not_use( position );

		button[ i ] = createAsset( ASSET::BUTTON );
		setAsset( button[ i ], CMD::POS_X, position[ getRand_pos ].x );
		setAsset( button[ i ], CMD::POS_Y, position[ getRand_pos ].y );

		mark[ i ] = createAsset( ASSET::MARK );
		setAsset( mark[ i ], CMD::POS_X, position[ getRand_pos ].x );
		setAsset( mark[ i ], CMD::POS_Y, position[ getRand_pos ].y );
		if ( i == 1 ) {
			setAsset( mark[ i ], CMD::STATUS, ans_mark );

		} else if ( i <= 2 ) {
			setAsset( mark[ i ], CMD::STATUS, dummy_mark );

		} else if ( i <= 4 ) {
			setAsset( mark[ i ], CMD::STATUS, dummy_mark_2 );

		} else {
			setAsset( mark[ i ], CMD::STATUS, dummy_mark_3 );

		}

		position[ getRand_pos ].used = true;
	}
}
int getRand_ans( ) {
	int ans = MARK_DRINK + ( getRand( ) % 4 );
	return ans;
}
int getRand_not_ans( int ans, int not_dummy = -1, int not_dummy_2 = -1 ) {
	int dummy = -1;
	do {
		dummy = MARK_DRINK + ( getRand( ) % 4 );

	} while ( dummy == ans || dummy == not_dummy || dummy == not_dummy_2 );
	return dummy;
}

void destory_all_asset( int num ) {
	for ( int i = 0; i < num; i++ ) {
		destroyAsset( mark[ i ] );
		destroyAsset( button[ i ] );
	}
}

void returnToNull( int num ) {
	for ( int i = 0; i < num; i++ ) {
		button[ i ] = NULL;
	}
}

int tag( ) {
	return 16;
}

GAME_END;