
# Problem
## 空格问题
项目命名不要有空格！不然会导致一些意外问题，项目名称有空格，命名空间中会将空格转换为下画线，但是，如图：`Assembly.Load(string str)`参数接收的程序集名称必须与项目一致，而不是跟命名空间一致。
![项目命名不要有空格！](/images/7/69/2019-12-10_092424 Assembly.Load Method problem.jpg "项目命令不要有空格！")
## 命名空间下命名空间问题
参数只需要第一个命名空间不需要一直.
如图，`Assembly.Load("Builder_Pattern")`，而不是使用Devil所在的完整命名空间`Builder_Pattern.ConcreteBuilder.DevilBuilder`

![参数只需要第一个命名空间不需要一直.](/images/7/69/2019-12-10_092424 Assembly.Load Method problem1.jpg "参数只需要第一个命名空间不需要一直.")

# 当前项目名称
根据以上两个问题得知，`Assembly.Load(string str)`的参数使用的是当前项目文件夹的名称