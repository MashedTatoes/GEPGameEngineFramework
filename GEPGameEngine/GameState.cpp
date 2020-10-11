#include "GameState.h"
#include "Game.h"
#include "PauseMenuPopupState.h"
void GameState::Enter()
{
	
	

	m_pFont = TTF_OpenFont("Font/LTYPE.TTF", 30);

	SDL_Rect bgSrcRect;
	bgSrcRect.x = bgSrcRect.y = 0;
	SDL_QueryTexture(bgSpriteTex, NULL, NULL, &bgSrcRect.w, &bgSrcRect.h);

	SDL_Rect bgDestRect;
	bgDestRect.x = bgDestRect.y = 0;
	SDL_GetWindowSize(Game::Instance()->GetWindow(), &bgDestRect.w, &bgDestRect.h);

	bg = new SpriteEx(bgSpriteTex, bgSrcRect, bgDestRect);

	  
	player = new Player(mainSpriteTex, bgDestRect.w*0.5, bgDestRect.h - 100);
	//scorpion = new Scorpion(bgDestRect.w * 0.5, bgDestRect.h - 100);
 
}


void GameState::Update()
{
	if (Game::Instance()->KeyDown(SDL_SCANCODE_ESCAPE) == 1)
	{
		Game::Instance()->GetFSM()->PushState(new PauseMenuPopupState());
		return; //to make sure we don't run the game in background while pause menu shows
	}

	if (player) player->Update();
	
 

	if (player) this->CheckCollision();

	if (Game::Instance()->KeyDown(SDL_SCANCODE_SPACE) && player)
	{
	 
	 
	}
 
 

}


void GameState::Render()
{
	SDL_SetRenderDrawColor(Game::Instance()->GetRenderer(), 0, 0, 0, 255); //set background window color
	SDL_RenderClear(Game::Instance()->GetRenderer()); //clear the screen

	bg->Render();

	if (player) player->Render();
	
  
	ScreenState::Render();


}


void GameState::Exit()
{
	//to-do:: de-allocate memory, texture, surface etc, sound 

}

void GameState::CheckCollision()
{
	 

}
