#include <raylib.h>
#include <iostream>
#include <string>

//Globals
int Xres = 560, Yres = 500;
Rectangle Blocks[366];
Vector2 scorePositionText = { 50, 450 };
Vector2 scorePositonNum = { 150 ,450 };
bool moving = false;
int game_score = 0;

Font font = LoadFontEx("C:/Users/Omar/Desktop/Pac/pac-man/emulogic-font/font.ttf", 32, 0, 0);

int Grid[22][28] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
	{1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1},
	{3, 3, 3, 3, 3, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 3, 3, 3, 3, 3},
	{1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1},
	{3, 3, 3, 3, 3, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 3, 3, 3, 3, 3},
	{1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
	{1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1},
	{1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

struct Fruit_Item {
	Rectangle fruit;
	bool eaten = false;
};
Fruit_Item Fruit_Blocks[300];


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


	void moveX(int pos)
	{
		position.x = pos;
		if (framerec.width < 0)
			framerec.width = -framerec.width;
		isVertical = false;
	}
	void moveY(int pos)
	{
		position.y = pos;
		if (framerec.width < 0)
			framerec.width = -framerec.width;
		isVertical = true;
	}


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

		if (IsKeyDown(KEY_RIGHT) && IsKeyDown(KEY_LEFT))
			return;

		if (IsKeyDown(KEY_UP) && IsKeyDown(KEY_DOWN))
			return;

		pac_direction.x = (float)IsKeyDown(KEY_RIGHT) - (float)IsKeyDown(KEY_LEFT);
		pac_direction.y = (float)IsKeyDown(KEY_DOWN) - (float)IsKeyDown(KEY_UP);


		if (IsKeyDown(KEY_RIGHT))
		{
			if (last == 2)
				moveRight();
			else if (last == 3 || last == 4)
			{
				if (!checkNextCollisionRight())
					moveRight();
				else 
					queueRight = true;
			}
		}
		else if (IsKeyDown(KEY_LEFT))
		{
			if (last == 1)
				moveLeft();
			else if (last == 3 || last == 4)
			{
				if (!checkNextCollisionLeft())
					moveLeft();
				else
				{
					queueLeft = true;
				}
			}
			
		}
		else if (IsKeyDown(KEY_UP))

		{
			if (last == 4)
				moveUp();
			else if (last == 1 || last == 2)
			{
				if (!checkNextCollisionUp())
					moveUp();
				else
					queueUp = true;
			}
		}
		else if (IsKeyDown(KEY_DOWN))
		{
			if (last == 3)
				moveDown();
			else if (last == 1 || last == 2)
			{
				if (!checkNextCollisionDown())
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
					if (!checkNextCollisionDown())
					{
						last = 4;
						queueDown = false;
						return;
					}
				}

				if (queueUp)
				{
					if (!checkNextCollisionUp())
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
					std::cout << "Im called\n";
					if (!checkNextCollisionDown())
					{
						last = 4;
						queueDown = false;
						return;
					}
				}

				if (queueUp)
				{
					if (!checkNextCollisionUp())
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
					if (!checkNextCollisionRight())
					{
						last = 1;
						queueRight = false;
						return;
					}
				}

				if (queueLeft)
				{
					if (!checkNextCollisionLeft())
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
					if (!checkNextCollisionRight())
					{
						last = 1;
						queueRight = false;
						return;
					}
				}

				if (queueLeft)
				{
					if (!checkNextCollisionLeft())
					{
						last = 2;
						queueLeft = false;
						return;
					}
				}
				
			}

		}






		++frameIndex;
		framerec.x = (float)frameWidth * frameIndex;
	}



	bool checkNextCollisionDown()
	{

		Rectangle Hitbox = getHitbox();
		Hitbox.y += 10;
		for (int i = 0; i < 366; i++)
		{
			if (CheckCollisionRecs(Hitbox, Blocks[i]))
			{
				return true;
			}
		}
		return false;
	}
	bool checkNextCollisionUp()
	{

		Rectangle Hitbox = getHitbox();
		Hitbox.y -= 10;
		for (int i = 0; i < 366; i++)
		{
			if (CheckCollisionRecs(Hitbox, Blocks[i]))
			{
				return true;
			}
		}
		return false;
	}

	bool checkNextCollisionRight()
	{

		Rectangle Hitbox = getHitbox();
		Hitbox.x += 10;
		for (int i = 0; i < 366; i++)
		{
			if (CheckCollisionRecs(Hitbox, Blocks[i]))
			{
				return true;
			}
		}
		return false;
	}

	bool checkNextCollisionLeft()
	{

		Rectangle Hitbox = getHitbox();
		Hitbox.x -= 10;
		for (int i = 0; i < 366; i++)
		{
			if (CheckCollisionRecs(Hitbox, Blocks[i]))
			{
				return true;
			}
		}
		return false;
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


	void checkCollisions(Rectangle rec[])
	{
		Rectangle hitbox = getHitbox();
		for (int i = 0; i < 366; ++i)
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
				collision = true;
				return;
			}

			collision = false;
		}
	}

	bool returnCheckCollisions(Rectangle rec[])
	{
		Rectangle hitbox = getHitbox();
		for (int i = 0; i < 366; ++i)
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

	void trackPosition(int array[][28], int length, int width)
	{
		for (int i = 0; i < length; ++i)
		{
			for (int j = 0; j < width; j++)
			{
				if (pac_direction.x == 1 && array[i][j + 1] == 0)
				{
					array[i][j + 1] = 2;
					array[i][j];
				}
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
					if (blockCount < 366) {
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


	InitWindow(Xres, Yres, "Pac-Man indevelopment by Omar Adly");

	Map pacMap;
	PacMan pac;
	Fruits pacFruit;

	pac.pacGrid(Grid, 22, 28);
	while (!WindowShouldClose())
	{
		DrawTextEx(font, "Score:", scorePositionText, 25, 2, WHITE);

		BeginDrawing();

		if (!moving)
		{
			pac.startMoving();
		}
		else
		{
			//pac.lastStatus();
			pac.checkLogic();
			pac.checkCollisions(Blocks);
			pacFruit.createFruits(Grid, 21, 28);
			pac.eatFruit();
		}

		ClearBackground(BLACK);
		pacMap.createGrid(Grid, 22, 28);
		pac.Draw();

		std::string score = std::to_string(game_score);
		DrawTextEx(font, score.c_str(), scorePositonNum, 25, 2, WHITE);
		EndDrawing();
	}

	CloseWindow();

	return 0;
}
