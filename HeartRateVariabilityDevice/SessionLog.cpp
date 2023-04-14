#include "SessionLog.h"

SessionLog::SessionLog(QLineSeries* series, int level, QObject* parent) :
    QObject(parent),
    series(series),
    level(level)
{ }

SessionLog::~SessionLog() {
    delete series;
}
