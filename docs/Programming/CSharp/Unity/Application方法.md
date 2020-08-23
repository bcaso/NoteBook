---
title: Application方法
tags: Unity,Application
grammar_cjkRuby: true
---
该方法多是应用的设置项
例：

```csharp
    print(Application.identifier);
    print(Application.companyName);
    print(Application.productName);
    print(Application.installName);
    print(Application.installMode);
    print(Application.isEditor);
    print(Application.isFocused);
    print(Application.isMobilePlatform);
    print(Application.isPlaying);
    print(Application.isWebPlayer);
    print(Application.platform);
    print(Application.unityVersion);
    print(Application.version);
    print(Application.runInBackground);
    
    Application.Quit();//游戏退出，在编辑模式下不会退出
    Application.OpenURL("www.sikiedu.com");
    Application.CatureScreenshot("游戏截图");
    Application.IsPlaying = false;//退出编辑器模式
```