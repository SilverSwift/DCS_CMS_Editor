#ifndef SERVICEOBJECT_H
#define SERVICEOBJECT_H

#include <QObject>

class ServiceObject : public QObject
{
    Q_OBJECT
public:
    explicit ServiceObject(QObject *parent = nullptr);
#ifdef QT_DEBUG
    void generateDefaults(QString outputDir = {});
#endif

signals:

};

#endif // SERVICEOBJECT_H
