#include <QApplication>
#include "GUI.h"
#include "Repository/FileRepo.h"
#include "Repository/CSVWatchList.h"
#include "Service/Service.h"
#include <QInputDialog>
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    try {
        auto* service = new Service();
        auto* repo = new FileRepo("tutorial.txt");
        service->setTypeOfRepo(repo);

        auto* watchList = new CSVWatchList("watchlist.csv");
        service->setTypeOfWatchList(watchList);

        service->generateTutorials();

        auto* gui = new GUI(service);
        gui->show();

        return a.exec();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }




}