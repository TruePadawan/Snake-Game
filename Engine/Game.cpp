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
	random_num_generator( std::random_device()() ),
	player({20, 15}),
	xDist(0, 38),
	yDist(0, 28),
	food({ xDist(random_num_generator), yDist(random_num_generator) })
{
	delta_location = { 1, 0 };
	moveCounter = 0;
	FRAME_PER_MOVEMENT = 10;
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

	if (wnd.kbd.KeyIsPressed(VK_UP))
	{
		delta_location = { 0, -1 };
	}
	if (wnd.kbd.KeyIsPressed(VK_DOWN))
	{
		delta_location = { 0, 1 };
	}
	if (wnd.kbd.KeyIsPressed(VK_LEFT))
	{
		delta_location = { -1, 0 };
	}
	if (wnd.kbd.KeyIsPressed(VK_RIGHT))
	{
		delta_location = { 1, 0 };
	}

	if (moveCounter == FRAME_PER_MOVEMENT)
	{
		if (food.isEaten(player))
		{
			player.grow();
			// WHEN SNAKE EATS FOOD, RESPAWN FOOD AT NEW LOCATION
			Location newFoodCordinate;
			do
			{
				newFoodCordinate = { xDist(random_num_generator), yDist(random_num_generator) };
			} while (player.checkForCollision(newFoodCordinate));
			food.setCordinate(newFoodCordinate);

			if (FRAME_PER_MOVEMENT > 5)
			{
				--FRAME_PER_MOVEMENT;
			}
		}
		// IF THE SNAKE'S HEAD COLLIDES WITH ITS BODY PART, GAME OVER
		if (player.checkForCollision(player.getHeadCordinate()))
		{
			gameOver = true;
		}

		moveCounter = 0;
		player.moveBy(delta_location); // MOVE SNAKE EVERY NUMBER OF FRAMES SPECIFIED BY 'FRAME_PER_MOVEMENT'
	}
	++moveCounter;

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


	/*for (int y = 0; y < Board::CELL_PER_HEIGHT; y++)
	{
		for (int x = 0; x < Board::CELL_PER_WIDTH; x++)
		{
			Location cordinate{ x, y };
			board.drawCell(cordinate, Colors::LightGray);
		}
	}*/
	player.draw(board);
	food.draw(board);
	board.drawBoundary();
}
