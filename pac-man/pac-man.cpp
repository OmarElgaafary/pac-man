#include <raylib.h>

int Xres = 560, Yres = 440;

class PacMan {
public:

	void checkLogic() {


		if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
		{
			position.x += 5;
			if (framerec.width < 0)
				framerec.width = -framerec.width;
			isVer = false;
		}
		else if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
		{
			position.x -= 5;
			if (framerec.width > 0)
				framerec.width = -framerec.width;
			isVer = false;
		}
		else if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W))
		{
			isVer = true;
			position.y -= 5;
			if (framerec.height < 0)
				framerec.height = -framerec.height;


		}
		else if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S))
		{
			isVer = true;
			position.y += 5;
			if (framerec.height > 0)
				framerec.height = -framerec.height;
		}

		++frameIndex;
		framerec.x = (float)frameWidth * frameIndex;

	}

	void checkCollision()
	{

	}

	void Draw()
	{
		if (isVer)
			DrawTextureRec(pac_up, framerec, position, WHITE);
		else if (!isVer)
			DrawTextureRec(pac_right, framerec, position, WHITE);

	}

	Rectangle getHitbox()
	{
		Rectangle hitbox = { position.x, position.y, (float)frameWidth, (float)pac_right.height };
		return hitbox;
	}

	Vector2 getPacPosition()
	{
		return position;
	}



private:
	bool isVer = false;
	Texture2D pac_right = LoadTexture("C:/Users/Omar/Desktop/Pac/pac-man-h.png");
	Texture2D pac_up = LoadTexture("C:/Users/Omar/Desktop/Pac/pac-man-v.png");
	int frameWidth = pac_right.width / 9;
	int frameIndex = 0;
	Rectangle framerec = { 0.0f, 0.0f, (float)pac_right.width / 9 , (float)pac_right.height };
	Vector2 position = { 100, 100 };
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

					Rectangle block = { x_position, y_position, blockSize, blockSize };
					DrawRectangleRec(block, mapcolor);
				}
			}
		}
	}

	Rectangle getMapFrame()
	{
		return pacMap;
	}

private:
	int blockSize = 20;
	Color mapcolor = { 0,0,139,200 };
	Rectangle pacMap = { 50, 50, 550, 650 };
	Rectangle Blocks[50] = {};

};


int main()

{
	SetTargetFPS(60);


	InitWindow(Xres, Yres, "Pac-Man indevelopment by Omar Adly");

	Map pacMap;
	PacMan pac;


	int Grid[31][28] = {
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



	while (!WindowShouldClose())
	{



		BeginDrawing();


		pacMap.createGrid(Grid, 31, 28);
		pac.checkLogic();


		ClearBackground(BLACK);

		pac.Draw();



		EndDrawing();
	}

	CloseWindow();

	return 0;
}