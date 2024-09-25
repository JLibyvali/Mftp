#pragma  once

#include <QObject>
#include <QMap>
#include <QString>

QT_BEGIN_NAMESPACE

namespace Web{

    class Person : QObject {
        Q_OBJECT
        Q_PROPERTY(int age READ getAge WRITE setAge MEMBER m_age NOTIFY ageChanged)
        Q_PROPERTY(QString name MEMBER m_name)
        Q_PROPERTY(double score MEMBER m_score)

        private:
            int m_age = -1;
            double m_score = -1;
            QString m_name ;
            QMap<QString, QPair<int, double>> m_person;
        
        public:
            explicit Person(QStringView _name, QObject *parent = nullptr );
            explicit Person(QMap<QString, QPair<int, double>>& _person, QObject *parent=nullptr);
            ~Person() = default;

    //  Property functions
            int getAge(){return 0;}
            bool setAge(int _age){return false;}
    //   Custom
        int getAge(QStringView _name);
        bool setAge(QStringView _name, int _age);

        signals:
            void ageChanged();

    };
}   // namespace  EX1


QT_END_NAMESPACE