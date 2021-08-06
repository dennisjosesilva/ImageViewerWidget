#include <QApplication>
#include <QString>

#include "mainwindow.hpp"

int main(int argc, char *argv[])
{
  QApplication app{argc, argv};
  MainWindow mainwindow;

  mainwindow.show();

  return app.exec();
}