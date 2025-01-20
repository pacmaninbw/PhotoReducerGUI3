#ifndef PHOTOCOUNTER_H
#define PHOTOCOUNTER_H

#include <QObject>

class PhotoCounter : public QObject
{
    Q_OBJECT

public:
    PhotoCounter(QObject *parent = nullptr) :
        QObject(parent), m_value{0}
    {

    }

    std::size_t value() const { return m_value; }
    void increment()
    {
        ++m_value;
        emit valueChanged(m_value);
    }

public slots:
    void setValue(int value)
    {
        if (value != m_value) {
            m_value = value;
            emit valueChanged(value);
        }
    };

signals:
    void valueChanged(std::size_t newValue);

private:
    std::size_t m_value;
};

#endif