/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include "SpriteCodex.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	board(gfx),
	player({20, 15}),
	food(), frameTimer()
{
	MILLISECONDS_PER_MOVEMENT = 0.1f;
	delta_location = { 1, 0 };
	moveCounter = 0.0f;
	gameOver = false;
	gameStarted = false;
}

void Game::Go()
 {
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	if (wnd.kbd.KeyIsPressed(VK_RETURN) && !gameStarted)
	{
		gameStarted = true;
	}

	// STOP ANY LOGIC CALCULATION IF THE TITLE HASN'T BEEN REMOVED OR GAME IS OVER
	if (!gameStarted || gameOver)
	{
		return;
	}

	if (wnd.kbd.KeyIsPressed(VK_UP) && delta_location.y != 1)
	{
		delta_location = { 0, -1 };
	}
	if (wnd.kbd.KeyIsPressed(VK_DOWN) && delta_location.y != -1)
	{
		delta_location = { 0, 1 };
	}
	if (wnd.kbd.KeyIsPressed(VK_LEFT) && delta_location.x != 1)
	{
		delta_location = { -1, 0 };
	}
	if (wnd.kbd.KeyIsPressed(VK_RIGHT) && delta_location.x != -1)
	{
		delta_location = { 1, 0 };
	}

	if (moveCounter >= MILLISECONDS_PER_MOVEMENT)
	{
		if (food.isEaten(player))
		{
			player.grow();
			// WHEN SNAKE EATS FOOD, RESPAWN FOOD AT NEW LOCATION
			do
			{
				food.respawn();
			} while (player.checkForCollision(food.cordinate));

			if (MILLISECONDS_PER_MOVEMENT > 0.05f)
			{
				MILLISECONDS_PER_MOVEMENT -= 0.005f;
			}
		}
		// IF THE SNAKE'S HEAD COLLIDES WITH ITS BODY PART, GAME OVER
		if (player.checkForCollision(player.getHeadCordinate()))
		{
			gameOver = true;
		}
		
		moveCounter = 0.0f;
		player.moveBy(delta_location); // MOVE SNAKE EVERY NUMBER OF FRAMES SPECIFIED BY 'MILLISECONDS_PER_MOVEMENT'
	}
	moveCounter += frameTimer.timeInterval();

	// IF SNAKE COLLIDES WITH WALL, GAME OVER
	if (player.isAtBoundary())
	{
		gameOver = true;
	}
}

void Game::ComposeFrame()
{
	if (gameOver)
	{
		SpriteCodex::DrawGameOver(358, 268, gfx);
		return;
	}

	if (!gameStarted)
	{
		SpriteCodex::DrawTitle(326, 213, gfx);
		return;
	}

	player.draw(board);
	food.draw(board);
	board.drawBoundary();
}
