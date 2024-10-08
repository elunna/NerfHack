// Copyright (c) Warwick Allison, 1999.
// Qt4 conversion copyright (c) Ray Chason, 2012-2014.
// NetHack may be freely redistributed.  See license for details.

// qt_streq.h -- string requestor

#ifndef QT4STREQ_H
#define QT4STREQ_H

#include "qt_line.h"

namespace nethack_qt_ {

class NetHackQtStringRequestor : QDialog {
private:
    QLabel prompt;
    NetHackQtLineEdit input;
    QPushButton* okay;
    QPushButton* cancel;

public:
        NetHackQtStringRequestor(QWidget *parent, const char *p,
                                 const char *cancelstr = "Cancel",
                                 const char *okaystr = "Okay");
        void SetDefault(const char *);
        // maxchar is size of buffer[], minchar is size of line edit widget
        bool Get(char *buffer, int maxchar = 80, int minchar = 20);
        virtual void resizeEvent(QResizeEvent *);
};

} // namespace nethack_qt_

#endif
