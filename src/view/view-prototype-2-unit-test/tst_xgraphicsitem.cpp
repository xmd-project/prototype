#include <QString>
#include <QtTest>

class XGraphicsItemUnitTest : public QObject
{
    Q_OBJECT

public:
    XGraphicsItemUnitTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testCase1();
    void testCase1_data();
};

XGraphicsItemUnitTest::XGraphicsItemUnitTest()
{
}

void XGraphicsItemUnitTest::initTestCase()
{
}

void XGraphicsItemUnitTest::cleanupTestCase()
{
}

void XGraphicsItemUnitTest::testCase1()
{
    QFETCH(QString, data);
    QVERIFY2(true, "Failure");
}

void XGraphicsItemUnitTest::testCase1_data()
{
    QTest::addColumn<QString>("data");
    QTest::newRow("0") << QString();
}

QTEST_APPLESS_MAIN(XGraphicsItemUnitTest)

#include "tst_xgraphicsitem.moc"
