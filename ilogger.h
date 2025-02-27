#ifndef ILOGGER_H
#define    ILOGGER_H

#include "map.h"
#include "node.h"
#include "OpenList.h"
#include "CloseList.h"
#include <unordered_map>
#include <list>


class ILogger {
public:
    explicit ILogger(std::string loglevel) { this->loglevel = loglevel; }

    virtual bool getLog(const char *FileName, const std::string *LogParams) = 0;

    virtual void saveLog() = 0;

    virtual void writeToLogMap(const Map &map, const std::list<Node> &path) = 0;

    virtual void writeToLogOpenClose(const OpenList &open, const CloseList &close,
                                     unsigned int step, bool last) = 0;

    virtual void writeToLogPath(const std::list<Node> &path) = 0;

    virtual void writeToLogHPpath(const std::list<Node> &path) = 0;

    virtual void writeToLogNotFound() = 0;

    virtual void writeToLogSummary(unsigned int numberofsteps, unsigned int nodescreated, float length, double time,
                                   double cellSize) = 0;

    virtual ~ILogger() = default;

protected:
    std::string loglevel;
};

#endif

