#ifndef PHOTOREDUCERMODEL_H_
#define PHOTOREDUCERMODEL_H_

#include <QObject>

class MainWindow;

class PhotoReducerModel : public QObject
{
    Q_OBJECT

public:
    explicit PhotoReducerModel(QObject *parent = nullptr);
    ~PhotoReducerModel() = default;

public slots:

signals:

private slots:


private:

};

#endif // PHOTOREDUCERMODEL_H_


