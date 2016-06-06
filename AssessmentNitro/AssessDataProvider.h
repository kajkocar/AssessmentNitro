
class AssessDataProvider
{
public:
	AssessDataProvider() {};
	virtual ~AssessDataProvider() {};

	virtual bool Init(std::string initData) = 0;
	virtual int Size() = 0;
	virtual AssessRectangle get(int ItemNo) = 0;
};

