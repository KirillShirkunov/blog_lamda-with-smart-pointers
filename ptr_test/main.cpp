#include <QCoreApplication>

#include <memory>

#include <QDebug>
#include <QTimer>

int main(int argc, char * argv[]) {
    QCoreApplication a(argc, argv);

    QObject obj;
    {
        auto timer_ptr = std::make_shared<QTimer>();
        obj.connect(timer_ptr.get(), &QTimer::timeout, [timer_ptr]() mutable {
            qDebug() << "timeout!";
            timer_ptr.reset();
        });
        obj.connect(timer_ptr.get(), &QTimer::destroyed,
                    []() { qDebug() << "destroyed!"; });
        timer_ptr->start(1000);
    }

    return a.exec();
}
