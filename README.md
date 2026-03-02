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

However, the game will not compile out of the box because you will get a bunch of linker errors saying that it can not find the stuff in Media.h. This is because the github repository is missing a bunch of .o files that the game needs to compile. Said .o files are the image, music, and sound effect files that the game uses and get baked into the .exe. They contain copyrighted material that I do not own, so they can not be included in the repository. If you need the .o files and want to compile them, you will need to contact me privately either on here or on Discord so I can send them to you.

Feel free to fork this, use this, sell a game using it, basically do whatever you want with it, just be mindful of the zlib license this project uses and DO NOT claim this engine as your own, please credit me, DPBOX.

I'd also really appreciate seeing the things people make with my engine and what kinds of edits people make. This Github repository will not be updated very often, and you can visit my Discord server to show off what you've done with my engine as well as chat with members of my server, see sneek peeks and get updates on my projects, and more. https://discord.gg/aBFJ2H7
