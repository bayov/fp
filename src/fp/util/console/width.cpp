#include <sys/ioctl.h>
#include <unistd.h>

#include "width.h"

namespace fp::util::console {

size_t width() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_col;
}

} // namespace fp::util::console
