#include "DBfetch.h"
#include "gui.h"

int main(int argc, char** argv){

    QCoreApplication a(argc, argv);

    loadStuff();
    resizeStuff();
    createButtons();
    insertButtons();
    loadSounds();

    category.play();

    imgtext = "Our GUI";
    cv::namedWindow(imgtext);
    cv::setMouseCallback(imgtext, callBackFunc);    

    cv::imshow(imgtext, imggui_resized);

    cv::waitKey(0);

    return 0;
}
