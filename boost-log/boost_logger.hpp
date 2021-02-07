#include <string>

class BoostLogger {
public:
	BoostLogger(const std::string& log_path);

	virtual void info(const std::string& msg);
	virtual void warn(const std::string& msg);
	virtual void error(const std::string& msg);
};