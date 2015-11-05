@echo off

cd D:/docs/code/AdtTools/sources/gui
::echo %CD%
moc MainWindow.h > moc.cpp
uic ui/mainwindow.ui > ui/ui_mainwindows.h

echo Done!
pause