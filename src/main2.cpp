//
// Created by Douglas on 2019-01-20.
//
#include <iostream>
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include "boost/log/utility/setup.hpp"
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include "boost/log/utility/setup.hpp"
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
namespace logging = boost::log;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;
namespace keywords = boost::log::keywords;
void init() {
  static const std::string COMMON_FMT("[%TimeStamp%][%Severity%]:  %Message%");

  boost::log::register_simple_formatter_factory<boost::log::trivial::severity_level, char>("Severity");
  boost::log::add_console_log(
      std::cout,
      boost::log::keywords::format = COMMON_FMT,
      boost::log::keywords::auto_flush = true
  );
  logging::add_file_log
      (
          keywords::file_name = "sample_%N.log",
          keywords::rotation_size = 10 * 1024 * 1024,
          keywords::time_based_rotation = sinks::file::rotation_at_time_point(0, 0, 0),
          keywords::format = COMMON_FMT,
          keywords::auto_flush = true
      );

  logging::core::get()->set_filter
      (
          logging::trivial::severity >= logging::trivial::info
      );
  logging::add_common_attributes();

}

int main(int, char *[]) {
  init();

  using namespace logging::trivial;
  src::severity_logger<severity_level> lg;
  BOOST_LOG_SEV(lg, trace) << "A trace severity message";
  BOOST_LOG_SEV(lg, debug) << "A debug severity message";
  BOOST_LOG_SEV(lg, info) << "An informational severity message";
  BOOST_LOG_SEV(lg, warning) << "A warning severity message";
  BOOST_LOG_SEV(lg, error) << "An error severity message";
  BOOST_LOG_SEV(lg, fatal) << "A fatal severity message";

  return 0;
}