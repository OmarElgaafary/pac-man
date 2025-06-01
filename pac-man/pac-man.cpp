#include <raylib.h>
#include <iostream>
#include <string>
#include <cstdlib>
//Globals
int Xres = 560, Yres = 800;
const int blockAmount = 556;

Rectangle Blocks[blockAmount];
Rectangle Ghosts[4];
Vector2 scorePositionText = { 50, 700 };
Vector2 scorePositonNum = { 150 ,700 };
bool moving = false;
int game_score = 0;
bool gameRunning = false;



Font font = LoadFontEx("C:/Users/Omar/Desktop/Pac/pac-man/emulogic-font/font.ttf", 32, 0, 0);

int Grid[31][28] = {
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,2,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,1,1,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,0,1},
	{1,0,1,1,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,0,1},
	{1,0,1,1,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,0,1},
	{1,0,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,0,1},
	{1,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1},
	{1,1,1,1,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1},
	{1,1,1,1,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,1,1,1,1},
	{1,1,1,1,1,1,0,1,1,0,1,1,3,3,3,3,1,1,0,1,1,0,1,1,1,1,1,1},
	{1,1,1,1,1,1,0,1,1,0,1,3,3,3,3,3,3,1,0,1,1,0,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,1,3,3,3,3,3,3,1,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,0,1,1,0,1,3,3,3,3,3,3,1,0,1,1,0,1,1,1,1,1,1},
	{1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1},
	{1,1,1,1,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,1,1,1,1},
	{1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,1,1,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,0,1},
	{1,0,1,1,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,0,1},
	{1,0,0,0,1,1,0,0,0,0,0,0,0,3,3,0,0,0,0,0,0,0,1,1,0,0,0,1},
	{1,1,1,0,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,1,1,0,1,1,0,1,1,1},
	{1,1,1,0,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,1,1,0,1,1,0,1,1,1},
	{1,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,1},
	{1,0,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,1,1,0,1},
	{1,0,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,1,1,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

struct Fruit_Item {
	Rectangle fruit;
	bool eaten = false;
};
Fruit_Item Fruit_Blocks[300];

class check_collisions {
public:
	bool checkNextCollisionDown(Rectangle rec)
	{
		rec.y += 10;
		for (int i = 0; i < blockAmount; i++)
		{
			if (CheckCollisionRecs(rec, Blocks[i]))
			{
				return true;
			}
		}
		return false;
	}
	bool checkNextCollisionUp(Rectangle rec)
	{
		rec.y -= 10;
		for (int i = 0; i < blockAmount; i++)
		{
			if (CheckCollisionRecs(rec, Blocks[i]))
			{
				return true;
			}
		}
		return false;
	}
	bool checkNextCollisionRight(Rectangle rec)
	{
		rec.x += 10;
		for (int i = 0; i < blockAmount; i++)
		{
			if (CheckCollisionRecs(rec, Blocks[i]))
			{
				return true;
			}
		}
		return false;
	}

	bool checkNextCollisionLeft(Rectangle rec)
	{
		rec.x -= 10;
		for (int i = 0; i < blockAmount; i++)
		{
			if (CheckCollisionRecs(rec, Blocks[i]))
			{
				return true;
			}
		}
		return false;
	}
};


class Fruits {
public:

	void createFruits(int Grid[][28], int length, int width)
	{
		int fruitCounter = 0;
		for (int i = 0; i < length + 1; ++i)
		{
			for (int j = 0; j < width; ++j)
			{
				if (Grid[i][j] == 0)
				{
					int x_postion = j * 20;
					int y_position = i * 20;

					if (Fruit_Blocks[fruitCounter].eaten)
					{
						fruitCounter++;
						continue;

					}

					Fruit_Item Fruit = { (float)x_postion, (float)y_position, 2.5, 2.5 };
					DrawRectangle(x_postion + 10, y_position + 10, Fruit.fruit.width, Fruit.fruit.height, WHITE);
					Fruit_Blocks[fruitCounter] = Fruit;
					fruitCounter++;

				}

				if (Grid[i][j] == 3)
				{
					continue;
				}
			}
		}
	}


private:
};

class PacMan {
public:


	void moveRight()
	{
		position.x += 2.5;
		if (framerec.width < 0)
			framerec.width = -framerec.width;
		isVertical = false;
		last = 1;
	}

	void moveLeft()
	{
		position.x -= 2.5;
		if (framerec.width > 0)
			framerec.width = -framerec.width;
		isVertical = false;
		last = 2;

	}

	void moveUp()
	{
		isVertical = true;
		position.y -= 2.5;
		if (framerec.height < 0)
			framerec.height = -framerec.height;
		last = 3;

	}

	void moveDown()
	{
		isVertical = true;
		position.y += 2.5;
		if (framerec.height > 0)
			framerec.height = -framerec.height;
		last = 4;
	}

	void startMoving()
	{
		if (IsKeyDown(KEY_RIGHT))
		{
			last = 1;
			moving = true;
		}
		else if (IsKeyDown(KEY_LEFT))
		{
			last = 2;
			moving = true;
		}
		else if (IsKeyDown(KEY_UP))
		{
			last = 3;
			moving = true;
		}
		else if (IsKeyDown(KEY_DOWN))
		{
			last = 4;
			moving = true;
		}
	}

	void checkLogic() {

		pac_direction.x = (float)IsKeyDown(KEY_RIGHT) - (float)IsKeyDown(KEY_LEFT);
		pac_direction.y = (float)IsKeyDown(KEY_DOWN) - (float)IsKeyDown(KEY_UP);

		check_collisions check;

		if (IsKeyPressed(KEY_RIGHT))
		{
			
			if (last == 4 && check.checkNextCollisionDown(getHitbox()) && check.checkNextCollisionRight(getHitbox()))
			{
				last = 2;
				return;
			}

			if (last == 3 && check.checkNextCollisionUp(getHitbox()) && check.checkNextCollisionRight(getHitbox()))
			{
				last = 2;
				return;
			}


			if (last == 2)
				moveRight();
			else if (last == 3 || last == 4)
			{
				if (!check.checkNextCollisionRight(getHitbox()))
					moveRight();
				else
					queueRight = true;
			}
		}
		else if (IsKeyPressed(KEY_LEFT))
		{
			if (last == 4 && check.checkNextCollisionDown(getHitbox()) && check.checkNextCollisionLeft(getHitbox()))
			{
				last = 1;
				return;
			}

			if (last == 3 && check.checkNextCollisionUp(getHitbox()) && check.checkNextCollisionLeft(getHitbox()))
			{
				last = 1;
				return;
			}



			if (last == 1)
				moveLeft();
			else if (last == 3 || last == 4)
			{
				if (!check.checkNextCollisionLeft(getHitbox()))
					moveLeft();
				else
				{
					queueLeft = true;
				}
			}

		}
		else if (IsKeyPressed(KEY_UP))

		{
			if (last == 4)
				moveUp();
			else if (last == 1 || last == 2)
			{
				if (!check.checkNextCollisionUp(getHitbox()))
					moveUp();
				else
					queueUp = true;
			}
		}
		else if (IsKeyPressed(KEY_DOWN))
		{
			if (last == 3)
				moveDown();
			else if (last == 1 || last == 2)
			{
				if (!check.checkNextCollisionDown(getHitbox()))
					moveDown();
				else
					queueDown = true;
			}
		}
		else {

			switch (last)
			{
			case 1:
				moveRight();
				pac_direction.x = 1;

				if (queueDown)
				{
					std::cout << "Im called\n";
					if (!check.checkNextCollisionDown(getHitbox()))
					{
						last = 4;
						queueDown = false;
						return;
					}
				}

				if (queueUp)
				{
					if (!check.checkNextCollisionUp(getHitbox()))
					{
						last = 3;
						queueUp = false;
						return;
					}
				}


				break;
			case 2:

				moveLeft();
				pac_direction.x = -1;
				if (queueDown)
				{
					if (!check.checkNextCollisionDown(getHitbox()))
					{
						last = 4;
						queueDown = false;
						return;
					}
				}

				if (queueUp)
				{
					if (!check.checkNextCollisionUp(getHitbox()))
					{
						last = 3;
						queueUp = false;
						return;
					}
				}

				break;
			case 3:
				moveUp();
				pac_direction.y = -1;
				if (queueRight)
				{
					if (!check.checkNextCollisionRight(getHitbox()))
					{
						last = 1;
						queueRight = false;
						return;
					}
				}

				if (queueLeft)
				{
					if (!check.checkNextCollisionLeft(getHitbox()))
					{
						last = 2;
						queueLeft = false;
						return;
					}
				}


				break;
			case 4:
				moveDown();
				pac_direction.y = 1;
				if (queueRight)
				{
					if (!check.checkNextCollisionRight(getHitbox()))
					{
						last = 1;
						queueRight = false;
						return;
					}
				}

				if (queueLeft)
				{
					if (!check.checkNextCollisionLeft(getHitbox()))
					{
						last = 2;
						queueLeft = false;
					}
				}

			}

		}




		checkCollisions(getHitbox());

		++frameIndex;
		framerec.x = (float)frameWidth * frameIndex;
	}



	

	void pacGrid(int array[][28], int length, int width)

	{
		// updates pac-man on the 2d grid 

		for (int i = 0; i < length; ++i)
		{
			for (int j = 0; j < width; ++j)
			{
				if (array[i][j] == 2)
				{
					position.x = j * 20;
					position.y = i * 20;

				}
			}
		}
	}


	void checkCollisions(Rectangle rec)
	{
		for (int i = 0; i < blockAmount; ++i)
		{
			if (CheckCollisionRecs(Blocks[i], rec))
			{
				if (pac_direction.x > 0)
					position.x = Blocks[i].x - rec.width;
				else if (pac_direction.x < 0)
					position.x = Blocks[i].x + rec.width;
				else if (pac_direction.y > 0)
					position.y = Blocks[i].y - rec.height;
				else if (pac_direction.y < 0)
					position.y = Blocks[i].y + rec.height;
				collision = true;
				return;
			}

			collision = false;
		}
	}

	bool returnCheckCollisions(Rectangle rec[])
	{
		Rectangle hitbox = getHitbox();
		for (int i = 0; i < blockAmount; ++i)
		{
			if (CheckCollisionRecs(rec[i], hitbox))
			{
				if (pac_direction.x > 0)
					position.x = rec[i].x - hitbox.width;
				else if (pac_direction.x < 0)
					position.x = rec[i].x + hitbox.width;
				else if (pac_direction.y > 0)
					position.y = rec[i].y - hitbox.height;
				else if (pac_direction.y < 0)
					position.y = rec[i].y + hitbox.height;

				return true;
			}
		}

		return false;
	}

	void Draw()
	{
		if (isVertical)
			DrawTextureRec(pac_up, framerec, position, WHITE);
		else if (!isVertical)
			DrawTextureRec(pac_right, framerec, position, WHITE);

	}

	Rectangle getHitbox()
	{
		Rectangle hitbox = { position.x, position.y, (float)frameWidth, (float)pac_right.height };

		return hitbox;
	}

	void eatFruit()
	{
		for (int i = 0; i < 300; ++i)
		{
			if (CheckCollisionRecs(getHitbox(), Fruit_Blocks[i].fruit) && !Fruit_Blocks[i].eaten)
			{
				Fruit_Blocks[i].eaten = true;
				game_score += 10;
			}
		}
	}

	void pos()
	{
		std::cout << "PAC (X): " << position.x << "\n";
		std::cout << "PAC (Y): " << position.y << "\n";
	}

	void direction()
	{
		std::cout << "PAC DIRECTION (X): " << pac_direction.x << "\n";
		std::cout << "PAC DIRECTION (Y): " << pac_direction.y << "\n";
	}

	void lastStatus()
	{
		std::cout << "Last: " << last << std::endl;
	}


private:

	Texture2D pac_right = LoadTexture("C:/Users/Omar/Desktop/Pac/pac-man/pac-man-h.png");
	Texture2D pac_up = LoadTexture("C:/Users/Omar/Desktop/Pac/pac-man/pac-man-v.png");

	Rectangle framerec = { 0.0f, 0.0f, (float)pac_right.width / 9 , (float)pac_right.height };

	Vector2 position = { 20, 20 };
	Vector2 pac_direction = { 1, 1 };

	int frameWidth = pac_right.width / 9;
	int frameIndex = 0;
	int last = 0;

	bool isVertical = false;
	bool collision = false;
	bool queueUp = false;
	bool queueDown = false;
	bool queueRight = false;
	bool queueLeft = false;

};

struct availablePosition 
{
	int position;
	bool availability;
};

class Ghost
{
public:

	check_collisions check;

	void red_ghost_move_left()

	{
		red_position.x += 5;

	}

	void updateRand()
	{
		int clock = time(0);
		srand(clock);
		
	}

	void redGhost()
	{
		drawRedGhost();
		createGhost(red_rec, red_position, red_direction, redGhostLast);
		ghostCollision(red_rec);
	}

	void blueGhost()
	{
		drawBlueGhost();
		createGhost(blue_rec, blue_position, blue_direction, blueGhostLast);
		ghostCollision(blue_rec);
	}

	void createGhost(Rectangle& rec, Vector2& Position, Vector2& direction, int& GhostLast)
	{
		red_rec.x = red_position.x;
		red_rec.y = red_position.y;

		if (!check.checkNextCollisionRight(rec))
		{
			available[0] = 1;
		}
		if (!check.checkNextCollisionLeft(rec))
		{
			available[1] = 2;
		}
		if (!check.checkNextCollisionUp(rec))
		{
			available[2] = 3;
		}
		if (!check.checkNextCollisionDown(rec))
		{
			available[3] = 4;
		}

		if (direction.x > 0)
		{
			direction.x = 1;
			direction.y = 0;
		}
		else if (direction.x < 0)
		{
			direction.x = -1;
			direction.y = 0;
		}
		else if (direction.y < 0)
		{
			direction.x = 0;
			direction.y = -1;
		}
		else if (direction.y > 0)
		{
			direction.x = 0;
			direction.y = 1;
		}

		if (GhostLast == 0)
		{
			ranNum = (rand() % 4) + 1;
			GhostLast = ranNum;
		}

		int availableCount = 0;

		for (int i = 0; i < 4; i++)
		{
			if (available[i] != 0)
			{
				availableCount++;
			}
		}



		// check available positons for movement


		if (direction.y == 0)
		{
			if (checkNumAvailable(3) && checkNumAvailable(4))
			{
				// rand num

				ranNum = ((rand() % 2) + 1) + 2;

				GhostLast = ranNum;


			}
			else if (checkNumAvailable(3) && !check.checkNextCollisionUp(rec))
			{
				// move up

				GhostLast = 3;
			}
			else if (checkNumAvailable(4) && !check.checkNextCollisionDown(rec))
			{
				// move down

				GhostLast = 4;
			}
		}

		else if (direction.x == 0)
		{
			if (checkNumAvailable(1) && checkNumAvailable(2))
			{
				// rand num

				ranNum = (rand() % 2) + 1;

				GhostLast = ranNum;
			}
			else if (checkNumAvailable(1) && !check.checkNextCollisionRight(rec))
			{
				// move right
				GhostLast = 1;
			}
			else if (checkNumAvailable(2) && !check.checkNextCollisionLeft(rec))
			{
				// move left
				GhostLast = 2;
			}
		}



		// movement

		switch (GhostLast)
		{
		case 1:
			Position.x += 5;
			direction.x = 1;
			direction.y = 0;

			break;
		case 2:
			Position.x -= 5;
			direction.x = -1;
			direction.y = 0;

			break;
		case 3:
			std::cout << "im called\n";
			Position.y -= 5;
			direction.y = -1;
			direction.x = 0;
			break;
		case 4:
			Position.y += 5;
			direction.y = 1;
			direction.x = 0;
			break;
		}




	}
	
	bool checkNumAvailable(int num)
	{
		for (int i = 0; i < 4; i++)
		{
			if (available[i] == num)
				return true;
		}
		return false;
	}


	

	int collisionChange(int input)
	{
		int randNum = (rand() % 4) + 1;

		if (randNum != input)
			return randNum;
		else 
			return collisionChange(input);
	}

	Rectangle getGhostHitbox()
	{
		Rectangle hitbox = { red_position.x, red_position.y, red_ghost_texture.width, red_ghost_texture.height };
			return hitbox;
	}

	void ghostCollision(Rectangle& rec)
	{
		for (int i = 0; i < blockAmount; ++i)
		{
			if (CheckCollisionRecs(getGhostHitbox(), Blocks[i]))
			{
				if (red_direction.x > 0)
					red_position.x = Blocks[i].x - rec.width;
				else if (red_direction.x < 0)
					red_position.x = Blocks[i].x + rec.width;
				else if (red_direction.y > 0)
					red_position.y = Blocks[i].y - rec.height;
				else if (red_direction.y < 0)
					red_position.y = Blocks[i].y + rec.height;
				redGhostCollided = true;
				return;
			}
		}
	}


	bool checkGhostCollision()
	{
		for (int i = 0; i < blockAmount; ++i)
		{
			if (CheckCollisionRecs(red_rec, Blocks[i]))
			{
				return true;
				redGhostCollided = true;

			}
		}
		redGhostCollided = false;

		return false;
	}

	

	void drawRedGhost()
	{
		DrawTextureRec(red_ghost_texture, red_rec, red_position, WHITE);
	}

	void drawBlueGhost()
	{
		DrawTextureRec(blue_ghost_texture, blue_rec, blue_position, WHITE);
	}

	void checkGhostCollision(Rectangle rec)
	{
		
			if (CheckCollisionRecs(rec, red_rec))
			{
				std::cout << "Game Over\n";
				gameRunning = false;
			}
	}
	
	


private:

	Texture2D red_ghost_texture = LoadTexture("C:/Users/Omar/Desktop/Pac/pac-man/red_ghost.png");
	Rectangle red_rec = { (float)red_position.x, (float)red_position.y , (float)red_ghost_texture.width, (float)red_ghost_texture.height};
	Vector2 red_position = { 260, 240};
	Vector2 red_direction = { 1, 1 };
	int redGhostLast = 0;

	Texture2D blue_ghost_texture = LoadTexture("C:/Users/Omar/Desktop/Pac/pac-man/blue_ghost.png");
	Rectangle blue_rec = { (float)blue_position.x, (float)blue_position.y, 20, 20 };
	Vector2 blue_position = {280, 240};
	Vector2 blue_direction = { 1, 1 };
	int blueGhostLast = 0;





	int ghostCount = 0;
	int available[4] = { 0,0,0,0 };
	int ranNum;
	bool redGhostCollided = false;

};

class Map {
public:

	Vector2 getScorePosition()
	{
		return scorePositionText;
	}

	void createGrid(int array[][28], int length, int width)
	{
		for (int i = 0; i < length; ++i)
		{
			for (int j = 0; j < width; ++j)
			{
				if (array[i][j] == 1)
				{
					int x_position = j * blockSize;
					int y_position = i * blockSize;



					Rectangle block = { (float)x_position, (float)y_position, (float)blockSize, (float)blockSize };
					if (blockCount < blockAmount) {
						Blocks[blockCount] = block;
						blockCount++;
					}
					DrawRectangleRec(block, mapcolor);
				}
			}
		}
	}



	void printMap(int array[][28], int length, int width)
	{
		for (int i = 0; i < length; ++i)
		{
			for (int j = 0; j < width; j++)
			{
				std::cout << array[i][j];
			}
			std::cout << "\n";
		}
	}


private:

	int blockCount = 0;
	int blockSize = 20;

	Color mapcolor = { 0,0,139,200 };
	Rectangle pacMap = { 50, 50, 550, 650 };

};


int main()

{
	SetTargetFPS(60);
	SetTraceLogLevel(LOG_NONE);

	InitWindow(Xres, Yres, "Pac-Man indevelopment by Omar Adly");

	Map pacMap;
	PacMan pac;
	Ghost ghosts;
	Fruits pacFruit;

	pac.pacGrid(Grid, 31, 28);

	while (!WindowShouldClose())
	{
		DrawTextEx(font, "Score:", scorePositionText, 25, 2, WHITE);

		BeginDrawing();
		pac.Draw();

		if (!moving)
		{
			pac.startMoving();
			gameRunning = true;
		}
		
		if (gameRunning)
		{
			ghosts.checkGhostCollision(pac.getHitbox());
			pac.checkLogic();
			ghosts.redGhost();
			//ghosts.blueGhost();
			pac.eatFruit();
			ghosts.updateRand();
		}

		ClearBackground(BLACK);

		pacFruit.createFruits(Grid, 30, 28);

		pacMap.createGrid(Grid, 31, 28);

		std::string score = std::to_string(game_score);
		DrawTextEx(font, score.c_str(), scorePositonNum, 25, 2, WHITE);
		EndDrawing();
	}

	CloseWindow();

	return 0;
}
