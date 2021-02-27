## 1.UE4反射机制

### 1.1资料

[知乎-UE4反射] https://zhuanlan.zhihu.com/p/60622181

### 1.2

反射可以实现序列化、editor的details panel、垃圾回收、网络复制、蓝图/C++通信和相互调用等功能。

只有主动标记的类型、属性、方法会被反射系统追踪

UnrealHeaderTool会收集这些信息，生成用于支持反射机制的C++代码，然后再编译工程。