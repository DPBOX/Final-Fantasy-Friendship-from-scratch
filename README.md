This fan game https://gamejolt.com/games/my-little-pony-rpg-the-elements-of-harmony/104325 was released in 2012 and was made in RPG Maker. I have decided to remaster this game by making an RPG engine completely from scratch using just C++ and Raylib, and I have full support from the game's creator and he gave me permission to remaster his game. I then plan on using this RPG engine to make my own RPG games.

How to compile

debug version on linux
g++ *.cpp -Wnon-virtual-dtor -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wzero-as-null-pointer-constant -Wmain -pedantic -Wextra -Wall -g -std=gnu++20 -fPIC -DOS_LINUX -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o RPG_debug_linux o/*.o

release version on linux
g++ *.cpp -s -o3 -std=gnu++20 -fPIC -DOS_LINUX -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o RPG_linux o/*.o

debug version on windows
g++ *.cpp -Wnon-virtual-dtor -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wzero-as-null-pointer-constant -Wmain -pedantic -Wextra -Wall -g -std=gnu++20 -fPIC -DOS_LINUX -lraylib -lgdi32 -lwinmm -lm -lpthread -o RPG_debug_windows o/*.o

release version on windows
g++ *.cpp -s -o3 -std=gnu++20 -fPIC -DOS_LINUX -lraylib -lgdi32 -lwinmm -lm -lpthread -o RPG_windows o/*.o

However, the game won't compile out of the box
