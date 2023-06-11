#include "Impulse.h"
#include "time.h"
#define BUTTON_MAX_SIZE 16
GAME_BEGIN( A_Kai_2 );



int button[BUTTON_MAX_SIZE] = {};
int button_num[BUTTON_MAX_SIZE] = {};
int button_num_show[16] = { MARK_DRINK,MARK_DRINK,MARK_SHOES,MARK_SHOES,MARK_WATCH ,MARK_WATCH ,MARK_MISANGA ,MARK_MISANGA 
,MARK_DRINK,MARK_DRINK,MARK_SHOES,MARK_SHOES,MARK_WATCH ,MARK_WATCH ,MARK_MISANGA ,MARK_MISANGA };
int countdown = {};
clock_t begin = 0;
double countdown_time = 5;
double time_spent = {};
int get_id = -1;

void setup( ) {
	time_spent = {};
	

	int n = sizeof( button_num_show ) / sizeof( button_num_show[ 0 ] );
	getRandize( button_num_show, n );
	
	for ( int i = 0; i < 4; i++ ) {
		for ( int j = 0; j < 4; j++ ) {
			button[i+j*4] = createAsset( ASSET::BUTTON );
			setAsset( button[ i + j * 4 ], CMD::POS_X, (( SCREEN_WIDTH / 5 ) * j)+SCREEN_WIDTH/5 );
			setAsset( button[ i + j * 4 ], CMD::POS_Y, (145*i)+400 );
			button_num[ i + j * 4 ] = createAsset( ASSET::MARK );
			setAsset( button_num[ i + j * 4 ], CMD::POS_X, ( ( SCREEN_WIDTH / 5 ) * j ) + SCREEN_WIDTH / 5 );
			setAsset( button_num[ i + j * 4 ], CMD::POS_Y, ( 145 * i ) + 400 );
			setAsset( button_num[ i + j * 4 ], CMD::STATUS, button_num_show[ i + j * 4 ] );
		}
	}


	/*begin = clock( );*/
	stopwatch( STOPWATCH::START );
	stopwatch( STOPWATCH::STOP );
	creator( "ゲームプログラマー専攻 ２年", "カイウッティアナン クンニティ" );

}

void update( ) {
	int disable_count = 0;
	stopwatch(STOPWATCH::START);

	
	for ( int i = 0; i < BUTTON_MAX_SIZE; i++ ) {
		
		int t = getAsset( button[ i ], CMD::TOUCH );
		if ( t ) {
			setAsset( button_num[ i ], CMD::VISIBLE, 1 );
			setAsset(button[i], CMD::STATUS, BUTTON_DISABLED);

			if ( get_id == -1 ) {
				get_id = i;
				
			} else {
				if ( getAsset( button_num[ i ], CMD::STATUS ) == getAsset( button_num[ get_id ], CMD::STATUS )  ) {
					setAsset( button_num[ i ], CMD::VISIBLE, 0 );
					setAsset( button_num[ get_id ], CMD::VISIBLE, 0 );
					setAsset( button[ i ], CMD::STATUS, BUTTON_DISABLED );
					setAsset( button[ get_id ], CMD::STATUS, BUTTON_DISABLED );
					get_id = -1;

				} else if ( getAsset( button_num[ i ], CMD::STATUS ) != getAsset( button_num[ get_id ], CMD::STATUS ) ) {
		
					setAsset(button[get_id], CMD::STATUS, BUTTON_NORMAL);
					setAsset(button[i], CMD::STATUS, BUTTON_NORMAL);

					get_id = -1;

				}
			}
			
		}
		if (getAsset(button[i],CMD::STATUS) == BUTTON_DISABLED)
		{
			disable_count++;
		}

	}
	if (disable_count >= BUTTON_MAX_SIZE)
	{
		destory_all_asset(BUTTON_MAX_SIZE);
		returnToNull(BUTTON_MAX_SIZE);
		stopwatch(STOPWATCH::STOP);

		finish();
	}
}

STRING info( ) {
	return "同じマークがついたボタンを2回連続で\nタッチして全て消そう！";
}

void mark_x(int get_id,int i) {
	int posx_1 = getAsset(button[get_id], CMD::POS_X);
	int posy_1 = getAsset(button[get_id], CMD::POS_Y);
	int posx_2 = getAsset(button[i], CMD::POS_X);
	int posy_2 = getAsset(button[i], CMD::POS_Y);
	int mark_x1 = createAsset(ASSET::MARK);
	int mark_x2 = createAsset(ASSET::MARK);
	setAsset(mark_x1, CMD::POS_X, posx_1);
	setAsset(mark_x1, CMD::POS_Y, posy_1);
	setAsset(mark_x2, CMD::POS_X, posx_2);
	setAsset(mark_x2, CMD::POS_Y, posy_2);


	setAsset(mark_x1, CMD::STATUS, MARK_DRINK);
	setAsset(mark_x2, CMD::STATUS, MARK_DRINK);

	setAsset(mark_x1, CMD::VISIBLE, 0);
	setAsset(mark_x2, CMD::VISIBLE, 0);
}


void swap( int* a, int* b ) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void getRandize( int arr[ ], int n ) {
	srand(getRand() );
	int i;
	for ( i = n - 1; i > 0; i-- ) {
		int j = rand( ) % ( i + 1 );
		swap( &arr[ i ], &arr[ j ] );
	}
}
void destory_all_asset(int num) {
	for (int i = 0; i < num; i++)
	{
		destroyAsset(button_num[i]);
		destroyAsset(button[i]);
	}
}
void returnToNull(int num) {
	for (int i = 0; i < num; i++)
	{
		button[i] = NULL;
	}
}

int tag( ) {
	return 17;
}

GAME_END;