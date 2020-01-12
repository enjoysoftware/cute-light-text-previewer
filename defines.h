#ifndef DEFINES_H
#define DEFINES_H
#include <QIcon>
#define ICON_RESOURCE QString(":/icons/ContrastHigh/%1.png")
#define ICON_OPEN QIcon::fromTheme("document-open",QIcon(ICON_RESOURCE.arg("document-open")))
#define ICON_PRINT QIcon::fromTheme("document-print",QIcon(ICON_RESOURCE.arg("document-print")))
#define ICON_EXIT QIcon::fromTheme("application-exit",QIcon(ICON_RESOURCE.arg("application-exit")))
#endif // DEFINES_H
