#include <gtest/gtest.h>
#include <tbox/event/loop.h>
#include <tbox/base/scope_exit.hpp>
#include <tbox/base/log.h>
#include <tbox/base/log_output.h>

#include "composite_action.h"
#include "sleep_action.h"
#include "loop_action.h"
#include "function_action.h"
#include "sequence_action.h"

namespace tbox {
namespace flow {

class TimeCountAction : public CompositeAction {
  public:
    TimeCountAction(event::Loop &loop) : CompositeAction(loop, "TimeCount") {
        auto seq_action = new SequenceAction(loop);
        seq_action->append(new SleepAction(loop, std::chrono::milliseconds(100)));
        seq_action->append(new FunctionAction(loop, [this] { ++count_; return true; }));
        auto loop_action = new LoopAction(loop, seq_action);
        setChild(loop_action);
    }

    virtual void onReset() {
        count_ = 0;
        CompositeAction::onReset();
    }

    int count() const { return count_; }

  private:
    int count_ = 0;
};


TEST(CompositeAction, Basic) {
    auto loop = event::Loop::New();
    SetScopeExitAction([loop] { delete loop; });

    TimeCountAction action(*loop);
    action.start();

    loop->exitLoop(std::chrono::milliseconds(1010));
    loop->runLoop();

    action.stop();
    EXPECT_GE(action.count(), 10);
}
}
}
