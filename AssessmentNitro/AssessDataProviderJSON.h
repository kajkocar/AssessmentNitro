
class AssessDataProviderJSON : public AssessDataProvider
{
public:
	AssessDataProviderJSON() : AssessDataProvider() {};
	virtual ~AssessDataProviderJSON();

	// in case of JSON data provider, init data is file name 
	// (with full path if not in executable folder)
	bool Init(std::string initData) override;
	int Size() override;
	AssessRectangle get(int ItemNo) override;

private:
	cJSON * root;
	cJSON * rects;
};
