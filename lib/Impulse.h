#pragma once
#include <string>
#include <map>

// 画面サイズ
static const int SCREEN_WIDTH = 1920;
static const int SCREEN_HEIGHT = 1080;

// ステータス
const int BUTTON_NORMAL = 0x1000;
const int BUTTON_TURNON = 0x1001;
const int BUTTON_DISABLED = 0x1002;

const int MARBLE_NORMAL = 0x2000;
const int MARBLE_BREAK = 0x2001;

const int MARK_DRINK = 0x3001;
const int MARK_SHOES = 0x3002;
const int MARK_WATCH = 0x3003;
const int MARK_MISANGA = 0x3004;

const int MARK_CLUB = 0x3005;
const int MARK_DIA = 0x3006;
const int MARK_HEART = 0x3007;
const int MARK_SPADE = 0x3008;

const int MARK_UP = 0x3009;
const int MARK_DOWN = 0x3010;
const int MARK_LEFT = 0x3011;
const int MARK_RIGHT = 0x3012;

const int MARK_MARU = 0x3013;
const int MARK_BATU = 0x3014;
const int MARK_CIRCLE = 0x3015;

const int PLATE_THEME = 0x4001;
const int PLATE_REMAINING = 0x4002;

const int BACKGROUND_TYPE_01 = 0x5000;
const int BACKGROUND_TYPE_02 = 0x5001;
const int BACKGROUND_TYPE_03 = 0x5002;

// アセット
enum class ASSET {
	BUTTON,
	HAZARD,
	MARK,
	MARBLE,
	SCREEN,
	NUMBER,
	FRAME,
	PLATE,
	BACKGROUND,
};

// コマンド
enum class CMD {
	POS_X,
	POS_Y,
	STATUS,
	TOUCH,
	VISIBLE,
	WIDTH,
	HEIGHT,
	PRIORITY,
};

// ストップウォッチ
enum class STOPWATCH {
	START,
	STOP
};

// SE
enum class SE {
	HIT,
	MISS,
	SET,
};

// メソッド
int  createAsset( ASSET asset ); // アセットの生成
void destroyAsset( int id );	 // アセットの破棄
void setAsset( int id, CMD cmd, int value );	// コマンドセット
int getAsset( int id, CMD cmd ); // コマンドゲット
int getRand( ); // ランダム値の取得
void playSe( SE se );
void finish( ); // ゲームの終了
void stopwatch( STOPWATCH sw ); // ストップウォッチコントロール
void creator( std::string major, std::string name ); // 製作者情報登録

//
// ライブラリ読み込み
//
#ifndef __ANDROID__
#if _DEBUG
#pragma comment( lib, "Impulse_d.lib" )
#else
#pragma comment( lib, "Impulse_r.lib" )
#endif // _DEBUG
#endif // __ANDROID__

//
// マクロ定義
//
// Property
#define PROPERTY( _TAG_, _ARG_ ) \
static class cs##Peoperty##_TAG_##ce : public Property { \
public: virtual ~cs##Peoperty##_TAG_##ce ( ) {} \
cs##Peoperty##_TAG_##ce ( ) { set( #_TAG_, #_ARG_ ); } \
} __##cs##Peoperty##_TAG_##ce##__;
// Game
#define GAME_BEGIN( _TITLE_ ) \
static class cs##_TITLE_##ce : public Game { \
public: \
	cs##_TITLE_##ce() : Game( #_TITLE_ ) { } \
	virtual ~cs##_TITLE_##ce() { }

#define GAME_END \
} __game__;

//
// クラス
//
// Property.cpp
class Property {
public:
	Property( ) { }
	virtual ~Property( ) { }
protected:
	static void set( const char* tag, const char* arg );
};
// game.cpp
#define STRING std::string
class Game {
public:
	Game( const char* tag );
	virtual ~Game( );
	virtual void setup( ) { }
	virtual void update( ) { }
	virtual STRING info( ) { return ""; }
	virtual int tag( ) { return 0; };
};

//
// プロパティ設定
//
// パフォーマンスモードを有効にするか設定します
PROPERTY( PERFORMANCE, FALSE );
// フルスクリーンモードを有効にするか設定します
PROPERTY( FULLSCREEN, FALSE );
// 仮想フルスクリーンモードを有効にするか設定します。
// 注意：フルスクリーンと同時に有効になっていた場合はフルスクリーンを優先します
PROPERTY( VIRTUALFULLSCREEN, FALSE );
// デバック用コンソールを表示するか設定します
PROPERTY( CONSOLE, FALSE );
// メニューを有効にするか設定します
PROPERTY( MENU, FALSE );
// マウスカーソルを表示するか設定します
PROPERTY( MOUSE,TRUE );
// パッケージされた開発環境かどうかを設定します
// 注意：変更しないでください。リソースの読み込みができなくなります
PROPERTY( PACKAGE, TRUE );
// ウインドウモード時のウィンドウサイズを設定します
PROPERTY( SCALE, 0.8 );