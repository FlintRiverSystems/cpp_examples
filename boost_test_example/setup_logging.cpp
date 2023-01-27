
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/support/date_time.hpp>

#include <boost/log/utility/setup/console.hpp>

using namespace std;
using namespace boost::log;
namespace expr = boost::log::expressions;

void setup_logging()
{
	add_common_attributes();
	register_simple_formatter_factory< trivial::severity_level, char>("Severity");

	/* setup write to console */
	auto cl = add_console_log
	(
		std::cout,
		keywords::auto_flush = true
	);

	auto formatter = expr::stream 
			<< expr::format_date_time<boost::posix_time::ptime>("TimeStamp", "%Y-%m-%d %H:%M:%S.%f")
			<< " : " 
			<< "<" << std::setw(7) << left << trivial::severity << "> "
			<< expr::message;

	cl->set_formatter(formatter);
}
