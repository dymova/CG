#pragma once
class Panel
{
private:
	int sizeX;
	int sizeY;

public:
	Panel(int sizeX, int sizeY);
	~Panel();


	int getSizeX() const;

	int getSizeY() const;
};

