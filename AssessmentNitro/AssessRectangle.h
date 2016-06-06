
class AssessRectangle
{
public:
	AssessRectangle() : x(0), y(0), width(0), height(0) {};
	AssessRectangle(int _x, int _y, int _width, int _height) : x(_x), y(_y), width(_width), height(_height) {};

	bool operator ==(const AssessRectangle& v) const;

	void set(int _x, int _y, int _width, int _height);

	void setX(int _x) { x = _x; }
	int getX() { return x; }
	void setY(int _y) { y = _y; }
	int getY() { return y; }

	void setWidth(int _width) { width = _width; }
	int getWidth() { return width; }
	void setHeight(int _height) { height = _height; }
	int getHeight() { return height; }


	bool isValid();
	bool intersect(AssessRectangle& comp, AssessRectangle& intersectRect);
	std::string dump();

private:
	int x, y, width, height;
};
