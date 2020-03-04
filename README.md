# README

## 前言

这是OS课程的第一个Bonus，要求我们手写一个Shell，猜想是越像原生的越好。事实上一个简单的shell只需要不到一百行代码就可以完成，在老师布置作业的当天晚上我就写出了一个最简易的代码。但是不够完善，还有其他需求可以加入。因此这个bonus正在被我慢慢磨

## 平台

本mini project使用`gcc version 7.4.0 (Ubuntu 7.4.0-1ubuntu1~18.04.1) `，测试平台与开发平台均为`wsl Ubuntu 18.04.2 LTS`. 



## 修改日志

### v0.0.1 (2020-03-01 01:41:00 GMT+08:00)

* 支持echo/cd两个bash的build-in command
* 支持外部程序调用(`/bin/ls`等)
* 实现查看Log日志
  * 实现Log日志输入上下方向键查看最近匹配的command
* 实现光标的左右移动
* 支持管道 `|`
* 支持Backspace
* 支持重定向指令 `>>` `<<`



## 使用方法

首先cd进文件夹

```shell
cd Isc-Shell
```

**如果不想看下面的可以直接使用`cmake . && make && ./Isc-Shell`**

因为本项目使用CmakeFiles，所以需要先编译一遍

```shell
cmake . && make
```

编译成功后在`Shell/`目录下会有一个名为`Shell`的可执行文件，运行它。

```shell
./Isc-Shell
```

## 实现的功能

### 调用命令

#### Bash Shell自带的命令

由于Bash Shell自带部分build-in command，比如`echo`。这种命令无法通过`fork`调用，所以本项目实现了**部分**Bash Shell下的自带命令，目前实现的仅有`echo`和`cd`.

#### 其他命令

其他命令使用`fork`调用，`fork`调用后子进程调用`exec`族函数运行命令。为了避免出现孤儿进程，父进程需要使用`wait`等待子进程结束。为了避免出现僵尸进程，父进程需要在子进程结束后为子进程收尸。

由于传入参数数量未知，因此子进程调用的`exec`族函数只能使用`execv`，`execvp`或`execve`。为了避免环境变量的操作，本项目使用`execvp`调用进程。

### 管道

在Linux中，管道`|`的出现便利了开发人员的命令实现。管道的作用是将前一个进程的输出作为后一个进程的输入运行。本Shell支持管道语法，并且支持多重管道。以递归的方式实现，递归地将输入地命令以一个`|`分成两个部分，将前面部分作为子进程用`fork`调用。

例如`A | B | C`，首先本Shell将`A`作为子进程运行，将`B | C`作为父进程运行，并且将`A`进程的输出以管道的形式传输给`B | C`。接着进入递归， `B | C` 读取`A`的输出之后，又将`B`作为子进程，`C`作为父进程调用。

注意此处实现遇到的坑：管道重定向之后一度忘记恢复，导致后续读入一直都从管道读取。解决办法是先用`save = dup(STDIN_FILENO)`保存，再用`dup2(save, STDIN_FILENO)`恢复。具体代码请见`ProcessRunner.cpp`。

### Log日志

Log日志以链表的形式存储，链表插入顺序为command执行顺序。Log中含有如下属性：

```c++
LogElement *head;
LogElement *tail;
LogElement *curr;
```

其中`LogElement`代表单个command，LogElement中的属性如下

```c++
char *command;
LogElement *prev;
LogElement *next;
```

此处的实现可看`Log.h`与`Log.cpp`

### 切换command

切换command包含两部分：输入部分command补全与不输入找到上一个代码。这两个的本质是一样的，因为当不输入的时候如果进行字符串匹配操作则是以空字符串进行匹配，那么最先找到的匹配项一定就是最近使用的命令。因此此处的实现仅仅是遍历Log链表并进行字符串匹配，返回匹配成功的命令即可。

```c++
while (head != nullptr && curr->prev != nullptr) {
    curr = curr->prev;
    if (match(c, curr->command)) {
        return curr->command;
    }
}
if (head == nullptr) {
    return nullptr;
} else if (curr != nullptr) {
    if (match(c, curr->command)) {
        return curr->command;
    }
}
```

### 键入上下左右Backspace

当键入上下的时候，需要切换command。

当键入左右的时候，需要移动光标。

当键入backspace的时候，需要删减输入。

在Linux下，键入特殊控制符会在命令行上出现如^^[等的符号（具体的忘记了因为我已经实现好了就没回去看）

但是底层都是用char来输入，因此读取char即可

backspace对应的是int值为127的char输入，因此直接判断即可。

```c++
if ((int) c == 127) {
	// backspace
} 
```

上下左右对应的则是有三个char值，因此需要挨个读取

```c++
if (c == '\033') {
    if ((c = get1char()) == '[') {
        if ((c = get1char()) == 'A') {
        	// Up
        } else if (c == 'B') {
        	// Down
        } else if (c == 'C') {
        	// Right
        } else if (c == 'D') {
        	// Left
        }
    }
} 
```

其中'\033'代表控制字符，他还包括其他用处。具体请查看<https://www.cnblogs.com/demonxian3/p/8963807.html>

### 重定向输入输出

遍历一遍指令，判断是否有重定向

然后再用freopen重定向，注意记得恢复。

注意<<是不被实现的。

如果是>>，freopen用a+

如果是>， freopen用w

## 其他想要实现的一些需求

### 获取上一个Isc-Shell的Log历史

这个可能需要用到序列化和反序列化。当Log调用析构函数的时候使用序列化将数据存储至`~/.yimingShell_history`里面，当Log调用构造函数的时候使用反序列化将数据从`~/.yimingShell_history`中读取出来。

可能遇到的问题：如果内容过多怎么办？譬如我序列化之后产生一个非常大的文件，是否还要继续使用？

猜想：一般来说可能不会过大，因为存储的是小字符串。输入的command长度收到限制为512bytes。这样子一个10m大小的history都最起码需要20480条指令。因此文件过大只可能存在于使用很长久的情况下（譬如这个shell用了十几二十年）。或许可以对文件做一个大小判断？或者定期检查？

### 插件的支持

这个暂时没有想法，不知道怎么做，因此一直没有做

### 支持一些其他的build-in command

这个因为要对着文档挨个做，非常耗时耗力。因此暂时不想做

## 需求列表

 - [x] 进程调用(fork)
 - [x] Log日志的实现
    - [x] 需要实现键入上下可以切换command
    - [x] 需要实现半补全操作
 - [x] 光标的移动
 - [ ] 更多地支持一些fork无法使用的command
 - [ ] 插件支持
 - [x] 管道的支持
 - [ ] 获取上一次Isc-Shell的history
 - [x] backspace
 - [x] 重定向输入输出

## 存在bug
 - [x] g++ xxx.cpp -o xxx的时候，-o xxx参数似乎未成功使用，仍然生成的是a.out