---
title: Dictionary.TryGetValue测试使用
tags: Unity,Csharp
grammar_cjkRuby: true
---
```csharp
/*
 * 测试脚本
 */

using System.Collections.Generic;
using UnityEngine;

namespace DefaultNamespace {
	public class Test :MonoBehaviour{
		Dictionary<string, string> _dicTest = new Dictionary<string, string>();

		private void Start() {
			string strResult = string.Empty;//输出内容
			
			_dicTest.Add("zhangsan","张三");
			_dicTest.Add("lisi","李四");
			
			//查询
			_dicTest.TryGetValue("zhangsan", out strResult);
			print(strResult);
		}
	}
}
```
![输出结果](https://i.loli.net/2019/04/04/5ca5f184557e7.jpg)