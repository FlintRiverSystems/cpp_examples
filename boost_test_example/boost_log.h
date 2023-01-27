#pragma once

#include <boost/log/trivial.hpp>
#include <boost/log/sources/severity_logger.hpp>

using logger_t = boost::log::sources::severity_logger_mt<boost::log::trivial::severity_level>;
using lvl = boost::log::trivial::severity_level;

