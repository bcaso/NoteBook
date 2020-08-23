# Process进程练习

## 杀死进程
```csharp?linenums
using System.Diagnostics;

	class Program {
		static void Main(string[] args) {
		    //得到所有进程，存放到pro数组中
			Process[] pro = Process.GetProcesses();
			//遍历并杀死每一个进程
			foreach (var item in pro) {
				item.Kill();
			}
			Console.WriteLine("Hello World!");
		}
	}
```
上面的代码不要轻易执行。

## 模拟Win + R，任务对话框，运行
`Process.Start(string name);`
```csharp?linenums
using System;
using System.Diagnostics;

class Program {
	static void Main(string[] args) {
		Process.Start("Notepad");
	}
}
```

## 打开文件
```csharp?linenums
using System;
using System.Diagnostics;

class Program {
	/// <summary>
	/// 要打开的文件名
	/// </summary>
	public static string fileName { get; set; }

	static void Main(string[] args) {
		fileName = @"C:\Users\god\Desktop\许昌职业技术学院_教务处_章.gif";
		ProcessStartInfo processStartInfo = new ProcessStartInfo() {
			FileName = fileName
		};

		Process process = new Process();
		process.StartInfo = processStartInfo;

		//开始进程，静态方法
		//Process.Start(processStartInfo);
		//拿对象自己的Start()方法来开启进程
		process.Start();
	}
}
```