---
title: Resources加载资源，封装的一个管理类
tags: Unity,Manager,Resources
grammar_cjkRuby: true
---
```csharp?linenums
using System.Collections.Generic;
using UnityEngine;

/// <summary>
///     Resources加载资源，封装的一个管理类，可通过Sprite LoadSprite()方法的形式，照猫画虎，自己再封装预置体，或者其他类型的加载器
///     同时学到了Dictionary的ContainsKey和Add方法
/// </summary>
public class ResourcesManager {
    private static readonly Dictionary<string, object> m_ObjDic = new Dictionary<string, object>();

    /// <summary>
    ///     图片的加载
    /// </summary>
    /// <param name="spriteName">图片路径或名称</param>
    /// <returns>图片</returns>
    public static Sprite LoadSprite(string spriteName) {
        Sprite temp;
        if (!m_ObjDic.ContainsKey(spriteName)) {
            temp = Resources.Load<Sprite>(spriteName);
            m_ObjDic.Add(spriteName, temp);
        } else {
            temp = m_ObjDic[spriteName] as Sprite;
        }

        return temp;
    }
}
```