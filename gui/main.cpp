#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QStandardItemModel>
#include <QtQml>

static QStandardItemModel *createDirModel()
{
    auto *model = new QStandardItemModel();
    QStandardItem *root = model->invisibleRootItem();

    auto *WORK = new QStandardItem("Work/");
    auto *HIDDEN = new QStandardItem("Hidden/");
    auto *BSUIR = new QStandardItem("BSUIR/");
    auto *Yandex = new QStandardItem("Yandex/");

    auto *Backend = new QStandardItem("Backend/");
    auto *Frontend = new QStandardItem("Frontend/");
    Yandex->appendRow(Frontend);
    Yandex->appendRow(Backend);

    WORK->appendRow(BSUIR);
    WORK->appendRow(Yandex);

    root->appendRow(WORK);
    root->appendRow(HIDDEN);

    return model;
}

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    static QStandardItemModel *dirModel = createDirModel();

    qmlRegisterSingletonInstance(
        "Nightlock.Models", 1, 0,
        "DirModel",
        dirModel
        );

    QQmlApplicationEngine engine;
    engine.loadFromModule("nightlock", "Main");

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
