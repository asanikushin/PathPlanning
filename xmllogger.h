#ifndef XMLLOGGER_H
#define    XMLLOGGER_H

#include "tinyxml2.h"
#include "ilogger.h"

using tinyxml2::XMLElement;
//That's the class that flushes the data to the output XML


class XmlLogger : public ILogger {

public:
    XmlLogger(std::string loglevel) : ILogger(loglevel) {}


    bool getLog(const char *FileName, const std::string *LogParams) override;

    void saveLog() override;

    void writeToLogMap(const Map &Map, const std::list<Node> &path) override;

    void writeToLogOpenClose(const OpenList &open, const CloseList &close,
                             unsigned int step, bool last) override;

    void writeToLogPath(const std::list<Node> &path) override;

    void writeToLogHPpath(const std::list<Node> &hppath) override;

    void writeToLogNotFound() override;

    void writeToLogSummary(unsigned int numberofsteps, unsigned int nodescreated, float length, double time,
                           double cellSize) override;

    XMLElement *createXMLLogFullNode(const Node &node);

private:
    std::string LogFileName;
    tinyxml2::XMLDocument doc;
};

#endif

