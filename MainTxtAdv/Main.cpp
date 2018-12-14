#include "AdvGame.h"
#include "ConsoleIO.h"

int main()
{
    ConsoleIO io;
    AdvGame game(&io);
    game.Run();
}