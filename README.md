# Sylar

## 一、日志系统

```
//  sylar/log.h
LogEvent   
|
LogLevel
|
LogFormatter
|
LogAppender 
        |
        StdoutLogAppender
        |
        FileLogAppender
Logger


```

## 二、配置系统
### yaml
下载安装yaml

修改/创建bin/conf/log.yml，后面要解析这个文件
```
logs:
    - name: root
      level: info
      formatter: %d%T%m%n
      appender:
          - type: FileLogAppender
            file: log.txt
          - type: StdoutLogAppender
    - name: system
      level: debug
      formatter: %d%T%m%n
      appender:
          - type: FileLogAppender
            file: log.txt
          - type: StdoutLogAppender
```
修改cmake做yaml测试
```
#添加yaml的一些实现， 逻辑不清
include_directories(/apps/sylar/include)

target_link_libraries(test_config sylar yaml-cpp)
```

修改yaml_cpp测试程序

```
#/root/sylar/tests/test_config.cc

#include <yaml-cpp/yaml.h>

······

void print_yaml(const YAML::Node& node, int level) {
    if(node.IsScalar()) {
        SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << std::string(level * 4, ' ')
            << node.Scalar() << " - " << node.Type() << " - " << level;
    } else if(node.IsNull()) {
        SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << std::string(level * 4, ' ')
            << "NULL - " << node.Type() << " - " << level;
    } else if(node.IsMap()) {//map结构
        for(auto it = node.begin();
                it != node.end(); ++it) {
            SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << std::string(level * 4, ' ')
            << it->first << " - " << it->second.Type() << " - " << level;
            print_yaml(it->second, level + 1);
        }
    } else if(node.IsSequence()) {
        for(size_t i = 0; i < node.size(); ++i) {
            SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << std::string(level * 4, ' ')
            << i << " - " << node[i].Type() << " - " << level;
            print_yaml(node[i], level + 1);
        }
    }
}

void test_yaml() {
    YAML::Node root = YAML::LoadFile("/root/sylar/bin/conf/log.yaml");
    print_yaml(root, 0);
    //SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << root;
}

int main(int argc, char** argvs) {
    // SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << g_int_value_config->getValue();
    // SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << g_float_value_config->toString();
    test_yaml();
    return 0;
}
```

## 配置系统 复杂类型的支持
配置系统的原则：约定优于配置

```cpp
//抽象出来转化方法
template<T, FromStr, ToStr>
class Config;

//通用的转化模式，并给出默认实现
template<F, T>
LexicalCast;

//容器偏特化，目前支持vector
```

加油！ 

***

## 配置系统 更多stl容器支持
13_ConfigSystem_5_更多stl容器的支持
```
//使得容器偏特化支持更多类型：list, set, unordered_set, map, unorded_map
//map, unorded_map支持 key = std::string 偏特化
//遗留问题：Config::Lookup(key), key相同, 类型不同的, 不会有报错
```

# log&config类图
<img src="img/53T_VUK}LD~B3}ZVI8DJEGD.png" title="log&config类图">

**********

## 线程库

Thread, Mutex