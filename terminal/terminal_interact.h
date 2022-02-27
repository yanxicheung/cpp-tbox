#ifndef TBOX_TERMINAL_INTERACT_H_20220214
#define TBOX_TERMINAL_INTERACT_H_20220214

#include "types.h"

namespace tbox::terminal {

class Connection;

class TerminalInteract {
  public:
    virtual SessionToken newSession(Connection *wp_conn) = 0;
    virtual bool deleteSession(const SessionToken &st) = 0;

    virtual bool onBegin(const SessionToken &st) = 0;
    virtual bool onExit(const SessionToken &st) = 0;
    virtual bool onRecvString(const SessionToken &st, const std::string &str) = 0;
    virtual bool onRecvWindowSize(const SessionToken &st, uint16_t w, uint16_t h) = 0;

  protected:
    virtual ~TerminalInteract() { }
};

}

#endif //TBOX_TERMINAL_INTERACT_H_20220214