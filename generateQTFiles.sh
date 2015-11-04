@echo off

cd D:\docs\code\AdtLib\sources\AdtTools
::echo %CD%
moc MainWindow.h > moc.cpp
uic ui/mainwindow.ui > ui_mainwindows.h

echo Done!
pause