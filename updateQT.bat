cd D:\work\AdtLib\AdtLib\src
echo %CD%
moc window.h > moc.cpp
uic ../resource/untitled.ui > ui_untitled.h
pause