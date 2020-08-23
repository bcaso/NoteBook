---
title: linq整理文件
tags: Linq
grammar_mindmap: true
renderNumberedHeading: true
grammar_code: true
grammar_mathjax: true
---
```csharp?linenums
using System;
using System.IO;
using System.Linq;


class Program {
	static void Main(string[] args) {
		var MainDirectory = new DirectoryInfo(@"C:\Users\Administrator\Desktop\新建文件夹");
		var GroupQuery = from item in MainDirectory.EnumerateFiles()
		                 group item by item.Name[0];
		foreach (var item in GroupQuery) {
			var CurrentDirectory = Directory.CreateDirectory($"{MainDirectory.FullName}\\{item.Key.ToString()}");
			foreach (var FileItem in item) {
				FileItem.MoveTo($"{CurrentDirectory.FullName}\\{FileItem.Name}");
			}
		}

		Console.WriteLine("done.");
		Console.ReadKey();
	}
}
```
>http://blog.leanote.com/post/tangjun/%E6%8C%89%E9%A6%96%E5%AD%97%E6%AF%8D%E6%96%87%E4%BB%B6%E5%88%86%E7%BB%84%E6%95%B4%E7%90%86
