#include "Udp.hpp"
#include "PaSound.hpp"
#include "Opus.hpp"
#include "Gui.hpp"
#include "BabelClient.hpp"

int main(int ac, char **av)
{
    Gui		gui(ac, av);
    PaSound	sound;
    Opus	op;
    Udp		udp(ac, av);

    BabelClient	babel(gui, sound, op, udp);

    return babel.run();
}
