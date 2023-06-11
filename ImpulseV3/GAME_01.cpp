#include "Impulse.h"
#include <array>
#include <vector>

GAME_BEGIN( GAME_01 );

struct Vec {
	const unsigned int VECTOR_MARGIN = 1 << 15;

	int x;
	int y;

	Vec( )
		: x( 0 )
		, y( 0 ) {
	}

	Vec( const int inX, const int inY )
		: x( ( int )inX )
		, y( ( int )inY ) {
	}

	virtual ~Vec( ) {

	}

	inline bool operator==( const Vec& inVec ) const {
		int sx = ( int )( this->x * VECTOR_MARGIN );
		int sy = ( int )( this->y * VECTOR_MARGIN );
		int dx = ( int )( inVec.x * VECTOR_MARGIN );
		int dy = ( int )( inVec.y * VECTOR_MARGIN );
		return
			sx == dx &&
			sy == dy;
	}
};

struct OBJECT {
	int button = 0;
	int mark = 0;
};

const std::array< int, 4 > getRandom_ARRAY = {
	MARK_DRINK,
	MARK_SHOES,
	MARK_WATCH,
	MARK_MISANGA,
};

std::array< int, 2 > _theme = { };
std::array< int, 2 > _frame = { };
std::array< int, 2 > _plate = { };
std::array< std::array< OBJECT, 8 >, 2 > _object = { { } };

const int GENERATE_ERROR_CODE = -9999;

int tag( ) {
	return 1;
}

void setup( ) {
	for ( int i = 0; i < 2; i++ ) {
		for ( int j = 0; j < 8; j++ ) {
			_object[ i ][ j ].button = NULL;
			_object[ i ][ j ].mark = NULL;
		}
	}

	this->createTheme( );
	this->createObject( );

	stopwatch( STOPWATCH::START );

	creator( "ゲームプログラマー専攻 ３年", "岡田 征海" );
}

void update( ) {
	for ( int i = 0; i < 8; i++ ) {
		if ( _object[ 0 ][ i ].button == NULL ) {
			continue;
		}

		if ( getAsset( _object[ 0 ][ i ].button, CMD::TOUCH ) == 1 ) {
			setAsset( _object[ 0 ][ i ].button, CMD::VISIBLE, 0 );
			setAsset( _object[ 0 ][ i ].mark, CMD::VISIBLE, 0 );
			_object[ 0 ][ i ].button = NULL;
			_object[ 0 ][ i ].mark = NULL;
		}
	}

	bool result = true;
	for ( int i = 0; i < 8; i++ ) {
		if ( _object[ 0 ][ i ].button != NULL ) {
			result = false;
			break;
		}
	}

	if ( result ) {
		finish( );
	}
}

STRING info( ) {
	return "お題のマークと同じマークの付いた\nボタンをタップして全て消そう！";
}

void createTheme( ) {
	_theme[ 0 ] = createAsset( ASSET::MARK );
	_theme[ 1 ] = createAsset( ASSET::MARK );
	_frame[ 0 ] = createAsset( ASSET::FRAME );
	_frame[ 1 ] = createAsset( ASSET::FRAME );
	_plate[ 0 ] = createAsset( ASSET::PLATE );
	_plate[ 1 ] = createAsset( ASSET::PLATE );
	setAsset( _theme[ 0 ], CMD::STATUS, getRandom_ARRAY[ getRand( ) % 4 ] );

	while ( true ) {
		int temp = getRandom_ARRAY[ getRand( ) % 4 ];

		if ( temp != getAsset( _theme[ 0 ], CMD::STATUS ) ) {
			setAsset( _theme[ 1 ], CMD::STATUS, temp );
			break;
		}
	}

	int py = getAsset( _theme[ 0 ], CMD::HEIGHT ) / 2 + 40;
	setAsset( _theme[ 0 ], CMD::POS_X, SCREEN_WIDTH / 2 - 250 );
	setAsset( _theme[ 0 ], CMD::POS_Y, py );
	setAsset( _frame[ 0 ], CMD::POS_X, SCREEN_WIDTH / 2 - 250 );
	setAsset( _frame[ 0 ], CMD::POS_Y, py );

	setAsset( _theme[ 1 ], CMD::POS_X, SCREEN_WIDTH / 2 + 250 );
	setAsset( _theme[ 1 ], CMD::POS_Y, py );
	setAsset( _frame[ 1 ], CMD::POS_X, SCREEN_WIDTH / 2 + 250 );
	setAsset( _frame[ 1 ], CMD::POS_Y, py );

	setAsset( _plate[ 0 ], CMD::POS_X, SCREEN_WIDTH / 2 - 250 );
	setAsset( _plate[ 0 ], CMD::POS_Y, py - 80 );
	setAsset( _plate[ 1 ], CMD::POS_X, SCREEN_WIDTH / 2 + 250 );
	setAsset( _plate[ 1 ], CMD::POS_Y, py - 80 );
}

void createObject( ) {
__GENERATE_EXCEPTION:
	for ( int i = 0; i < 2; i++ ) {
		for ( int j = 0; j < 8; j++ ) {
			if ( _object[ i ][ j ].button != NULL ) {
				setAsset( _object[ i ][ j ].button, CMD::VISIBLE, 0 );
			}
			if ( _object[ i ][ j ].mark != NULL ) {
				setAsset( _object[ i ][ j ].mark, CMD::VISIBLE, 0 );
			}
		}
	}

	_object[ 0 ].fill( OBJECT( ) );
	_object[ 1 ].fill( OBJECT( ) );

	// マークを調整 + ボタンを生成
	for ( int i = 0; i < 2; i++ ) {
		for ( int j = 0; j < 8; j++ ) {
			_object[ i ][ j ].button = createAsset( ASSET::BUTTON );
			_object[ i ][ j ].mark = createAsset( ASSET::MARK );

			if ( i == 0 ) { // テーマオブジェクトの生成
				if ( j < 2 ) { // テーマの生成の保証
					setAsset( _object[ i ][ j ].mark, CMD::STATUS, getAsset( _theme[ j ], CMD::STATUS ) );
					csGAME_01ce::Vec vec = getObjectCreatePos( _object[ i ][ j ].mark );
					if ( vec.x == GENERATE_ERROR_CODE ) {
						goto __GENERATE_EXCEPTION;
					}
					setAsset( _object[ i ][ j ].mark, CMD::POS_X, vec.x );
					setAsset( _object[ i ][ j ].mark, CMD::POS_Y, vec.y );
				} else {
					setAsset( _object[ i ][ j ].mark, CMD::STATUS, getAsset( _theme[ getRand( ) % 2 ], CMD::STATUS ) );
					csGAME_01ce::Vec vec = getObjectCreatePos( _object[ i ][ j ].mark );
					if ( vec.x == GENERATE_ERROR_CODE ) {
						goto __GENERATE_EXCEPTION;
					}
					setAsset( _object[ i ][ j ].mark, CMD::POS_X, vec.x );
					setAsset( _object[ i ][ j ].mark, CMD::POS_Y, vec.y );
				}
			} else { // オブジェクトの生成
				std::vector< int >type;
				for ( int i = 0; i < 4; i++ ) {
					if ( getAsset( _theme[ 0 ], CMD::STATUS ) == getRandom_ARRAY[ i ] or
						 getAsset( _theme[ 1 ], CMD::STATUS ) == getRandom_ARRAY[ i ] ) {
						continue;
					}
					type.push_back( getRandom_ARRAY[ i ] );
				}
				setAsset( _object[ i ][ j ].mark, CMD::STATUS, type[ j % 2 ] );
				csGAME_01ce::Vec vec = getObjectCreatePos( _object[ i ][ j ].mark );
				if ( vec.x == GENERATE_ERROR_CODE ) {
					goto __GENERATE_EXCEPTION;
				}
				setAsset( _object[ i ][ j ].mark, CMD::POS_X, vec.x );
				setAsset( _object[ i ][ j ].mark, CMD::POS_Y, vec.y );
			}
		}
	}
	// マークの座標にボタンを移動
	for ( int i = 0; i < 2; i++ ) {
		for ( int j = 0; j < 8; j++ ) {
			setAsset( _object[ i ][ j ].button, CMD::POS_X, getAsset( _object[ i ][ j ].mark, CMD::POS_X ) );
			setAsset( _object[ i ][ j ].button, CMD::POS_Y, getAsset( _object[ i ][ j ].mark, CMD::POS_Y ) );
		}
	}
}

csGAME_01ce::Vec getObjectCreatePos( const int idx ) {
	const int AREA_BEGIN = 70;
	const int AREA_X_BEGIN = 150;

	const int AREA_X = SCREEN_WIDTH - AREA_BEGIN * 2;
	const int AREA_Y = SCREEN_HEIGHT - AREA_X_BEGIN - AREA_BEGIN * 2;

	int bx = 0;
	int by = 0;

	int generate_count = 0;

	while ( true ) {
		generate_count++;
		bx = AREA_BEGIN + getRand( ) % AREA_X;
		by = AREA_BEGIN + AREA_X_BEGIN + getRand( ) % AREA_Y;

		if ( !isHitting( csGAME_01ce::Vec( bx, by ) ) ) {
			break;
		}

		if ( generate_count >= 5000 ) {
			return csGAME_01ce::Vec( GENERATE_ERROR_CODE, 0 );
		}
	}

	return csGAME_01ce::Vec( bx, by );
};

int calAbs( int n ) {
	if ( n < 0 ) {
		n *= -1;
	}
	return n;
}

bool isHitting( csGAME_01ce::Vec vec ) {
	for ( int i = 0; i < 2; i++ ) {
		for ( int j = 0; j < 8; j++ ) {
			if ( _object[ i ][ j ].mark == NULL ) {
				continue;
			}

			int diff_width = calAbs( vec.x - getAsset( _object[ i ][ j ].mark, CMD::POS_X ) );
			int diff_height = calAbs( vec.y - getAsset( _object[ i ][ j ].mark, CMD::POS_Y ) );

			if ( diff_width < 140 &&
				 diff_height < 140 ) {
				return true;
			}
		}
	}

	return false;
}

GAME_END;