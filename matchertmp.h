#ifndef MATCHERTMP_H
#define MATCHERTMP_H

#include <QtCore>
#include <QtGui>
#include "matcher.h"

class MatcherTmp : QObject {

    Q_OBJECT

public:

    Matcher* m_match;

    MatcherTmp();

public slots:

    void callMe();

};

#endif // MATCHERTMP_H
