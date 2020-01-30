#include "quill/detail/LoggerCollection.h"
#include "quill/detail/ThreadContextCollection.h"

#include "quill/handlers/Handler.h"
#include <gtest/gtest.h>

using namespace quill;
using namespace quill::detail;

TEST(Logger, logger_can_log)
{
  ThreadContextCollection tc;
  HandlerCollection hc;

  LoggerCollection logger_collection{tc, hc};

  [[maybe_unused]] Logger* logger_1 = logger_collection.create_logger("logger_1");

  {
    LogLevel log_statement_level{LogLevel::Debug};
    EXPECT_FALSE(logger_collection.get_logger("logger_1")->can_log(log_statement_level));
  }

  {
    LogLevel log_statement_level{LogLevel::Info};
    EXPECT_TRUE(logger_collection.get_logger("logger_1")->can_log(log_statement_level));
  }

  {
    LogLevel log_statement_level{LogLevel::Error};
    EXPECT_TRUE(logger_collection.get_logger("logger_1")->can_log(log_statement_level));
  }

  // change log level
  logger_collection.get_logger("logger_1")->set_log_level(LogLevel::TraceL3);

  {
    LogLevel log_statement_level{LogLevel::TraceL3};
    EXPECT_TRUE(logger_collection.get_logger("logger_1")->can_log(log_statement_level));
  }

  {
    LogLevel log_statement_level{LogLevel::Critical};
    EXPECT_TRUE(logger_collection.get_logger("logger_1")->can_log(log_statement_level));
  }

  // change log level
  logger_collection.get_logger("logger_1")->set_log_level(LogLevel::None);

  {
    LogLevel log_statement_level{LogLevel::TraceL3};
    EXPECT_FALSE(logger_collection.get_logger("logger_1")->can_log(log_statement_level));
  }

  {
    LogLevel log_statement_level{LogLevel::Critical};
    EXPECT_FALSE(logger_collection.get_logger("logger_1")->can_log(log_statement_level));
  }
}