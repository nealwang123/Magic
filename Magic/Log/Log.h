#include "logger.h"
#include "logWrap.h"
#include "logLevel.h"
#include "logEvent.h"
#include "logAppender.h"
#include "logFormatter.h"
#include "loggerManager.h"
#include "../Util/Util.h"

#define  MAGIC_LOG_LEVEL(logger,level) \
                if(level >= logger->getLevel()) \
                    Magic::LogWrap(logger,level,std::unique_ptr<Magic::LogEvent>(new Magic::LogEvent(__LINE__,static_cast<uint64_t>(time(nullptr)),1,Magic::getFiberId(),Magic::getThreadId(),__FILE__,logger->getLogName(),"threadName"))).get()
                
#define MAGIC_LOG_DEBUG(logger)       MAGIC_LOG_LEVEL(logger,Magic::LogLevel::DEBUG)

#define MAGIC_LOG_INFO(logger)          MAGIC_LOG_LEVEL(logger,Magic::LogLevel::INFO)

#define MAGIC_LOG_WARN(logger)        MAGIC_LOG_LEVEL(logger,Magic::LogLevel::WARN)

#define MAGIC_LOG_ERROR(logger)       MAGIC_LOG_LEVEL(logger,Magic::LogLevel::ERROR)

#define MAGIC_LOG_FATAL(logger)        MAGIC_LOG_LEVEL(logger,Magic::LogLevel::FATAL)
