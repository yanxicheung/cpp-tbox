#ifndef TBOX_NETWORK_FD_H_20171030
#define TBOX_NETWORK_FD_H_20171030

#include <unistd.h>
#include <sys/uio.h>

#include "tbox/base/defines.h"

namespace tbox {
namespace network {

//! 文件描述符类，封装了对fd的基础操作
class Fd {
  public:
    Fd();
    Fd(int fd);
    virtual ~Fd();

    NONCOPYABLE(Fd);

    Fd(Fd&& other);
    Fd& operator = (Fd&& other);

    void swap(Fd &other);
    void reset();
    bool isNull() const { return fd_ == -1; }

  public:
    //! 获取文件描述符的值。注意谨慎使用
    int get() const { return fd_; }
    operator int () const { return fd_; }

    //! 读
    ssize_t read(void *ptr, size_t size) const;
    ssize_t readv(const struct iovec *iov, int iovcnt) const;

    //! 写
    ssize_t write(const void *ptr, size_t size) const;
    ssize_t writev(const struct iovec *iov, int iovcnt) const;

    //! 其它
    void setNonBlock(bool enable) const;    //! 开启或关闭非阻塞选项
    bool isNonBlock() const;        //! 检查是否非阻塞
    void setCloseOnExec() const;    //! 设置Exec时关闭选项

  private:
    int fd_ = -1;
};

}
}

#endif //TBOX_NETWORK_FD_H_20171030