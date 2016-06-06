
class AssessDataProviderFactory
{
public:
	static std::unique_ptr<AssessDataProvider> getDataProviderJSON()
	{
		return std::unique_ptr<AssessDataProvider>(new AssessDataProviderJSON());
	}
};

