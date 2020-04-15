#include <string>

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

class BoostLogger
{
public:
	BoostLogger(const std::string& log_path)
	{
		auto log_msg_format = (
			boost::log::expressions::stream
			<< "["
			<< boost::log::expressions::format_date_time< boost::posix_time::ptime >("TimeStamp", "%Y-%m-%d %H:%M:%S %f")
			<< "] [" << boost::log::trivial::severity
			<< "] " << boost::log::expressions::smessage);

		boost::log::add_console_log
		(
			std::cout,
			boost::log::keywords::format = log_msg_format
		);

		boost::log::add_file_log
		(
			boost::log::keywords::file_name = log_path,
			boost::log::keywords::rotation_size = 10 * 1024 * 1024,
			boost::log::keywords::time_based_rotation = boost::log::sinks::file::rotation_at_time_point(0, 0, 0),
			boost::log::keywords::format = log_msg_format
		);

		boost::log::core::get()->set_filter
		(
			boost::log::trivial::severity >= boost::log::trivial::debug
		);
		
		boost::log::add_common_attributes();
	}

	virtual void info(const std::string& msg)
	{
		BOOST_LOG_TRIVIAL(info) << msg;
	}

	virtual void warn(const std::string& msg)
	{
		BOOST_LOG_TRIVIAL(warning) << msg;
	}

	virtual void error(const std::string& msg)
	{
		BOOST_LOG_TRIVIAL(error) << msg;
	}
};

int main()
{
	BoostLogger logger("log.log");
	logger.info("Info 1");
	logger.info("Info 2");
	logger.warn("Warn 1");
	logger.error("Error 1");
}