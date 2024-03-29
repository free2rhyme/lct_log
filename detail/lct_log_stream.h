/**********************************************************************
 * @copyright   Copyright (C), 2017
 * @file        lct_log_stream.h
 * @version     1.0
 * @date        Jun 8, 2017 6:56:26 PM
 * @author      wlc2rhyme@gmail.com
 * @brief       TODO
 *********************************************************************/
#ifndef SRC_LOG_LCT_LOG_STREAM_H_
#define SRC_LOG_LCT_LOG_STREAM_H_

#include "lct_common_define.h"
#include <memory>
#include <sstream>
#include <ctime>
#include <chrono>

enum class ELogLevel: int8_t
{
   TRACE   = 1,
   DEBUG   = 2,
   INFOR   = 3,
   WARNG   = 4,
   ERROR   = 5,
   CRITC   = 6
};

typedef std::string                            CLctLogMessage;
typedef std::shared_ptr<CLctLogMessage>        CLctLogMessageShp;


typedef std::chrono::system_clock              CLctLogClock;
typedef std::chrono::time_point<CLctLogClock>  CLctLogTimepoint;
typedef CLctLogClock::duration                 CLctLogTimeDuation;

typedef struct tm   CLctLogTime;

class CLctLogStream final
{
public:
   explicit CLctLogStream(const ELogLevel level,
         char const* const file,
         const char* const function,
         const int32_t line);

   explicit CLctLogStream(const std::string& loggerName,
         const ELogLevel level,
         char const* const file,
         const char* const function,
         const int32_t line);

   ~CLctLogStream();

   template <typename CArgs>
   CLctLogStream& operator << (const CArgs& args) {
      m_sstream << args;
      return *this;
   }

   const CLctLogMessageShp& messagePtr();
   const std::string& message();

   LCT_ERR_CODE logEnd();

   DISALLOW_COPY_MOVE_OR_ASSIGN(CLctLogStream);

public:
   const std::string& loggerName() const
   {
      return m_loggerName;
   }

   ELogLevel logLevel() const
   {
      return m_logLevel;
   }

   int32_t lineNumber() const
   {
      return m_line;
   }

   const char* fileName() const
   {
      return m_fileNm;
   }

   const char* functionName() const
   {
      return m_functionNm;
   }

   const CLctLogTimepoint& timepoint() const
   {
      return m_timepoint;
   }

   const CLctLogTimeDuation& timeDurationSinceEpoch() const
   {
      return m_timestampDuration;
   }

   const CLctLogTime& timestamp() const
   {
      return m_timestamp;
   }

private:
   const ELogLevel           m_logLevel;
   const int32_t             m_line;
   const char* const         m_fileNm;
   const char* const         m_functionNm;

   const std::string         m_loggerName;
   std::ostringstream        m_sstream;
   std::string               m_content;
   CLctLogMessageShp         m_messageShp;

   CLctLogTimepoint          m_timepoint;
   CLctLogTimeDuation        m_timestampDuration;
   CLctLogTime               m_timestamp;
};

typedef std::shared_ptr<CLctLogStream>   CLctLogStreamShp;

#endif /* SRC_LOG_LCT_LOG_STREAM_H_ */
