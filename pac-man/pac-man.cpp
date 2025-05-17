#include <raylib.h>

int Xres = 560, Yres = 440;
Rectangle Blocks[650];

class PacMan {
public:

	void checkLogic() {

		pac_direction.x = (float)IsKeyDown(KEY_RIGHT) - (float)IsKeyDown(KEY_LEFT);
		pac_direction.y = (float)IsKeyDown(KEY_DOWN) - (float)IsKeyDown(KEY_UP);

		if (IsKeyDown(KEY_RIGHT))
		{
			position.x += 2.5;
			if (framerec.width < 0)
				framerec.width = -framerec.width;
			isVertical = false;
		}
		else if (IsKeyDown(KEY_LEFT))
		{
			position.x -= 2.5;
			if (framerec.width > 0)
				framerec.width = -framerec.width;
			isVertical = false;
		}
		else if (IsKeyDown(KEY_UP))
		{
			isVertical = true;
			position.y -= 2.5;
			if (framerec.height < 0)
				framerec.height = -framerec.height;


		}
		else if (IsKeyDown(KEY_DOWN))
		{
			isVertical = true;
			position.y += 2.5;
			if (framerec.height > 0)
				framerec.height = -framerec.height;
		}

		++frameIndex;
		framerec.x = (float)frameWidth * frameIndex;
	}

	void checkCollisions(Rectangle rec[])
	{
		Rectangle hitbox = getHitbox();
		for (int i = 0; i < 620; ++i)
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


private:
	bool isVertical = false;
	Texture2D pac_right = LoadTexture("C:/Users/Omar/Desktop/Pac/pac-man/pac-man-h.png");
	Texture2D pac_up = LoadTexture("C:/Users/Omar/Desktop/Pac/pac-man/pac-man-v.png");
	int frameWidth = pac_right.width / 9;
	int frameIndex = 0;
	Rectangle framerec = { 0.0f, 0.0f, (float)pac_right.width / 9 , (float)pac_right.height };
	Vector2 position = { 20, 20 };
	Vector2 pac_direction = {1, 1};
};



class Map {
public:

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
					if (blockCount < 620){
						Blocks[blockCount] = block;
						blockCount++;
					}
					DrawRectangleRec(block, mapcolor);
				}
			}
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
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
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


int main()

{
	SetTargetFPS(60);


	InitWindow(Xres, Yres, "Pac-Man indevelopment by Omar Adly");

	Map pacMap;
	PacMan pac;


	while (!WindowShouldClose())
	{


		BeginDrawing();


		pac.checkCollisions(Blocks);
		pac.checkLogic();

		ClearBackground(BLACK);

		pacMap.createGrid(Grid, 22, 28);
		pac.Draw();

		EndDrawing();
	}

	CloseWindow();
	
	return 0;
}