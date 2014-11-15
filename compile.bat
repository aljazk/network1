@echo OFF
echo Compiling...
g++ main.cpp src/Ball.cpp src/Enemies.cpp src/Map.cpp -o ball -o release/ball -static-libgcc -static-libstdc++ -DSFML_STATIC -lsfml-graphics-s -lsfml-window-s -lsfml-system-s
echo DONE 
pause
REM če hočš konzolo removej -mwindows