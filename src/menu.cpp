#include "menu.hpp"

void Menu::selectUp()
{
	gSoloud.play( gMenuMove );

	if( cursor != 0 )
		cursor--;
	else
		cursor = MENU_ITEMS-1;
}


void Menu::selectDown()
{
	gSoloud.play( gMenuMove );

	if( cursor != MENU_ITEMS-1 )
		cursor++;
	else
		cursor = 0;
}


void Menu::menuNav()
{
	if( gInput.wasPressed( Input::up ) || gInput.wasPressed( Input::lAnalogUp ) )
	{
		selectUp();
	}
	if( gInput.wasPressed( Input::down ) || gInput.wasPressed( Input::lAnalogDown ) )
	{
		selectDown();
	}
}

bool Menu::selectItem()
{
	return gInput.wasPressed( Input::cross );
}


bool Menu::touchSelect( MenuItem item )
{
	memcpy( touch_old, touch, sizeof( touch_old ) );
	sceTouchPeek( 0, &touch[0], 1 );

	int x = touch[0].report[0].x / 2;
	int y = touch[0].report[0].y / 2;

	if( ( x > item.x ) && ( x < item.x + BUTTON_WIDTH ) &&
		( y > item.y ) && ( y < item.y + BUTTON_HEIGHT )
		)
	{
		return true;
	}	
		
	return false;
}


void Menu::renderCursor( MenuItem item )
{
	//vita2d_draw_texture( gCursorTexture.texture, item.x, item.y );
	vita2d_draw_rectangle( item.x, item.y, BUTTON_WIDTH, BUTTON_HEIGHT, RGBA8( 30, 30, 30, 140 ) );

	int border_thickness = 4;

	vita2d_draw_rectangle( item.x, item.y, BUTTON_WIDTH, border_thickness, MAIN_FONT_COLOR );
	vita2d_draw_rectangle( item.x + BUTTON_WIDTH - border_thickness, item.y, border_thickness, BUTTON_HEIGHT, MAIN_FONT_COLOR );
	vita2d_draw_rectangle( item.x, item.y + BUTTON_HEIGHT - border_thickness, BUTTON_WIDTH, border_thickness, MAIN_FONT_COLOR );
	vita2d_draw_rectangle( item.x, item.y, border_thickness, BUTTON_HEIGHT, MAIN_FONT_COLOR );
}

void Menu::renderCursor( int x, int y, int w, int h )
{
	vita2d_draw_rectangle( x, y, w, h, RGBA8( 30, 30, 30, 100 ) );
}


void Menu::renderButton( MenuItem item )
{
	int text_w = vita2d_font_text_width( gFont[ 25 ], 25, item.name );
	int text_h = vita2d_font_text_height( gFont[ 25 ], 25, item.name );
	int text_x = item.x + ( ( BUTTON_WIDTH - text_w ) / 2 );
	int text_y = item.y + ( ( BUTTON_HEIGHT - text_h ) / 2 ) + text_h;

	vita2d_font_draw_text( gFont[ 25 ], text_x, text_y , MAIN_FONT_COLOR, 25, item.name );
}


// Main menu initialization
MainMenu::MainMenu()
{
	sceTouchSetSamplingState(SCE_TOUCH_PORT_FRONT, SCE_TOUCH_SAMPLING_STATE_START);
	sceTouchEnableTouchForce(SCE_TOUCH_PORT_FRONT);

	// Nr of selectable menu items
	MENU_ITEMS = 4;

	// Initialize menu items
	item[0].name = "Start Game";
	item[0].x = 310.0f;
	item[0].y = 170.0f;

	item[1].name = "How to play";
	item[1].x = 310.0f;
	item[1].y = 260.0f;

	item[2].name = "Options";
	item[2].x = 310.0f;
	item[2].y = 350.0f;

	item[3].name = "Exit";
	item[3].x = 310.0f;
	item[3].y = 440.0f;

	// Initialize cursor
	cursor = startGame;
}

void MainMenu::renderBackground()
{
	drawBackground();
}


PauseMenu::PauseMenu()
{
	// Nr of selectable menu items
	MENU_ITEMS = 2;

	// Initialize menu items
	item[0].name = "Resume game";
	item[0].x = 310.0f;
	item[0].y = 310.0f;

	item[1].name = "Main menu";
	item[1].x = 310.0f;
	item[1].y = 411.0f;

	// Initialize cursor
	cursor = resumeGame;
}

void PauseMenu::renderBackground()
{
	drawBackground();
}


GameOverMenu::GameOverMenu()
{
	// Nr of selectable menu items
	MENU_ITEMS = 2;

	// Initialize menu items
	item[0].name = "Play Again";
	item[0].x = 310.0f;
	item[0].y = 310.0f;

	item[1].name = "Main menu";
	item[1].x = 310.0f;
	item[1].y = 411.0f;

	// Initialize cursor
	cursor = playAgain;
}

void GameOverMenu::renderBackground()
{
	drawBackground();
}


DifficultyMenu::DifficultyMenu()
{
	// Nr of selectable menu items
	MENU_ITEMS = 2;

	// Initialize menu items
	item[0].name = "Classic";
	item[0].x = 310.0f;
	item[0].y = 207.0f;

	item[1].name = "Hardcore";
	item[1].x = 310.0f;
	item[1].y = 310.0f;

	// Initialize cursor
	cursor = classic;
}

void DifficultyMenu::renderBackground()
{
	drawBackground();
}

void DifficultyMenu::renderSnake()
{
	switch( GAME_DIFFICULTY )
	{
		case 0:
			drawPlayer( body, SCREEN_WIDTH - ( SCREEN_HEIGHT*0.04 ), SCREEN_HEIGHT - ( SCREEN_HEIGHT*0.04 ), 2.3, 2.3, ( -45 * M_PI ) / 180 );
			drawPlayer( head, SCREEN_WIDTH - ( SCREEN_HEIGHT*0.14 ), SCREEN_HEIGHT - ( SCREEN_HEIGHT*0.14 ), 2.5, 2.5, ( -45 * M_PI ) / 180 );
			break;
		case 1:
			drawPlayer( body, SCREEN_WIDTH - (SCREEN_HEIGHT*0.04), SCREEN_HEIGHT - (SCREEN_HEIGHT*0.04), 2.3, 2.3, (-45 * M_PI) / 180 );
			drawPlayer( headAngry, SCREEN_WIDTH - (SCREEN_HEIGHT*0.14), SCREEN_HEIGHT - (SCREEN_HEIGHT*0.14), 2.5, 2.5, (-45 * M_PI) / 180 );
			break;
	}
}

void DifficultyMenu::renderDescription()
{
	int text_width1, text_width2;
	int font_size = 18;

	switch( GAME_DIFFICULTY )
	{
	case 0:
		text_width1 = vita2d_font_text_width( gFont[ font_size ], font_size, "Collect as many apples as you can,");
		text_width2 = vita2d_font_text_width( gFont[ font_size ], font_size, "just don't bite your tail!");

		vita2d_font_draw_text( gFont[ font_size ], (SCREEN_WIDTH - text_width1)/2, 430, MAIN_FONT_COLOR, font_size, "Collect as many apples as you can,");
		vita2d_font_draw_text( gFont[ font_size ], (SCREEN_WIDTH - text_width2)/2, 470, MAIN_FONT_COLOR, font_size, "just don't bite your tail!");
		break;
	case 1:
		text_width1 = vita2d_font_text_width( gFont[ font_size ], font_size, "Recommended for experienced players,");
		text_width2 = vita2d_font_text_width( gFont[ font_size ], font_size, "touching the game border kills the snake.");

		vita2d_font_draw_text( gFont[ font_size ], (SCREEN_WIDTH - text_width1)/2, 430, MAIN_FONT_COLOR, font_size, "Recommended for experienced players,");
		vita2d_font_draw_text( gFont[ font_size ], (SCREEN_WIDTH - text_width2)/2, 470, MAIN_FONT_COLOR, font_size, "touching the game border kills the snake.");
		break;
	}
}
