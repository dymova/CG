#pragma once
class Circle
{
private:
	int radius;
	int positionX;
	int positionY;
public:
	Circle(int r, int x, int y);
	~Circle();
	int getR() const;
	int getPositionX() const;
	int getPositionY() const;

	void setR(int r);
	void setPositionX(int x);
	void setPositionY(int y);



};

