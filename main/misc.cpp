#include <iostream>

#include <tbox/base/log.h>

#include "context.h"
#include "apps.h"

namespace tbox::main {

void GetVersion(int &major, int &minor, int &rev, int &build)
{
    major = 1;
    minor = 0;
    rev   = 0;
    build = 0;
}

__attribute__((weak))
//! 定义为弱定义，默认运行时报错误提示，避免编译错误
void RegisterApps(Apps &apps)
{
    const char *src_text = R"(
#include <tbox/main/main.h>
#include "your_app.h"

namespace tbox::main {
void RegisterApps(Apps &apps)
{
    apps.add(new YourApp);
}
}
)";
    std::cerr << "WARN: You should implement tbox::main::RegisterApps().\nExp:" << std::endl
         << src_text << std::endl;
}

__attribute__((weak))
std::string GetAppBuildTime()
{
    return "Unknown";
}

__attribute__((weak))
std::string GetAppDescribe()
{
    return "Author didn't specify";
}

__attribute__((weak))
void GetAppVersion(int &major, int &minor, int &rev, int &build)
{
    major = minor = rev = build = 0;
}

}