
class AssessRectsContainer
{
public:
	AssessRectsContainer();
	virtual ~AssessRectsContainer();

	int add(AssessRectangle& rec);
	unsigned int Size();
	AssessRectangle get(int ItemNo);

	int findIntersectFrom(int start, AssessRectangle& comp, AssessRectangle& res);

private:
	std::vector< AssessRectangle > Rects;
};

