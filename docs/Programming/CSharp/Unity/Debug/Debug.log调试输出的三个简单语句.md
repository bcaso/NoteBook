---
title: Debug.log调试的三个输出语句
grammar_cjkRuby: true
---
# Debug调试的三个简单语句
Debug还有更多的输出语句。自行查找。

# Debug.Log(string message);

public static void Log(object message);
public static void Log(object message, Object context);
最简单的输出。

# Debug.LogWarnning(string message);
public static void LogWarning(object message);
public static void LogWarning(object message, Object context);
稍需要注意的输出

# Debug.LogError(string message);
public static void LogError(object message);
public static void LogError(object message, Object context);
自定义输出错误信息。