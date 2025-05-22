#include <raylib.h>
#include <iostream>
#include <string>

int Xres = 560, Yres = 500;
Rectangle Blocks[366];
Vector2 scorePositionText = { 50, 450 };
Vector2 scorePositonNum = { 150 ,450 };
int game_score = 0;

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


	void moveRight() {
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

	void checkLogic() {

		if (IsKeyDown(KEY_RIGHT) && IsKeyDown(KEY_LEFT))
			return;

		if (IsKeyDown(KEY_UP) && IsKeyDown(KEY_DOWN))
			return;

		pac_direction.x = (float)IsKeyDown(KEY_RIGHT) - (float)IsKeyDown(KEY_LEFT);
		pac_direction.y = (float)IsKeyDown(KEY_DOWN) - (float)IsKeyDown(KEY_UP);


		if (IsKeyDown(KEY_RIGHT))
			moveRight();
		else if (IsKeyDown(KEY_LEFT))
			moveLeft();
		else if (IsKeyDown(KEY_UP))
			moveUp();
		else if (IsKeyDown(KEY_DOWN))
			moveDown();
		else {
			switch (last)
			{
			case 1:
				moveRight();
				pac_direction.x = 1;
				break;
			case 2:
				moveLeft();
				pac_direction.x = -1;
				break;
			case 3:
				moveUp();
				pac_direction.y = -1;
				break;
			case 4:
				moveDown();
				pac_direction.y = 1;
			}
		}




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
			}
		}
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
				std::cout << "sound\n";
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


private:
	bool isVertical = false;
	Texture2D pac_right = LoadTexture("C:/Users/Omar/Desktop/Pac/pac-man/pac-man-h.png");
	Texture2D pac_up = LoadTexture("C:/Users/Omar/Desktop/Pac/pac-man/pac-man-v.png");
	int frameWidth = pac_right.width / 9;
	int frameIndex = 0;
	Rectangle framerec = { 0.0f, 0.0f, (float)pac_right.width / 9 , (float)pac_right.height };
	Vector2 position = { 20, 20 };
	Vector2 pac_direction = { 1, 1 };
	int last = 0;

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
			std::cout << "----------------------------------------------\n\n\n";
		}
	}


private:
	int blockCount = 0;
	int blockSize = 20;
	Color mapcolor = { 0,0,139,200 };
	Rectangle pacMap = { 50, 50, 550, 650 };



};



int Grid[22][28] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
	{1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1},
	{0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0},
	{1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1},
	{0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0},
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

Font font = LoadFontEx("C:/Users/Omar/Desktop/Pac/pac-man/emulogic-font/font.ttf", 32, 0, 0);

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

		pac.checkCollisions(Blocks);
		pac.checkLogic();
		pacFruit.createFruits(Grid, 21, 28);
		pac.eatFruit();

		ClearBackground(BLACK);

		pacMap.createGrid(Grid, 22, 28);
		//pac.trackPosition(Grid, 22, 28);
		//pacMap.displayScore();
		pac.Draw();

		std::string score = std::to_string(game_score);
		DrawTextEx(font, score.c_str(), scorePositonNum, 25, 2, WHITE);

		EndDrawing();
	}
	CloseWindow();

	return 0;
}