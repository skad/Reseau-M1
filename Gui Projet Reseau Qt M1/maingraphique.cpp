/* 
 * File:   main.cpp
 * Author: LUPO Kévin - LAMOUROUX Vincent - KEMPF Anthony 
 */

 #include <QApplication>
 #include "MainWindow.h"

 int main(int argc, char *argv[])
 {
     QApplication app(argc, argv);
     MainWindow window;
     window.show();
     return app.exec();
 }