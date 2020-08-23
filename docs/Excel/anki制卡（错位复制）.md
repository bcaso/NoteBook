# 文档准备：
![文档准备.png](https://www.assdrty.com/images/2020/04/13/480457a5dca505eb8.png)

格式要求：从第1行开始，奇数行写问题，偶数行写答案
工具要求：Word，或其他编辑器，不要有空行

# 粘贴到excel
![1.png](https://www.assdrty.com/images/2020/04/13/1.png)
Q1表示问题1
A1表示答案1
以此类推

# 令B[i]=A[i+1]
![在B1处填=A2.png](https://www.assdrty.com/images/2020/04/13/2804bed1977fe6277.png)

对应的代码类似于：
```csharp
int i = 1;
List<string> Questions, Answers;
while(!end){
  B[i] = A[i+1];
  i++;
}
```
A列是Questions集合，B列是Answers集合，B列默认为空

# 执行结果
![错位复制.png](https://www.assdrty.com/images/2020/04/13/3da2336f505cc82ec.png)
第11行没有数据，所以B[10]=A[11]=0, Excel的内部处理

# 集合一对一 Question[i] 对应 Answers[i]
由执行结果看出，Questions集合中既包含包含问题又包含答案，现在Answers已经满足要求，填满了答案，是时候把Questions集合中的答案删除了
感觉像是字典，当然，把Questions和Answers两个集合中的数据整理之后，再导入到一个字典集合里也行。

## 筛选答案
在C列，使用以下函数，来标志A列是奇数行，还是偶数行，奇数行为1，偶数行为0
`=IF(MOD(ROW(A1),2)=0,"0","1")`
目的是移除A列中问题行
![C列标志位.png](https://www.assdrty.com/images/2020/04/13/5261c0b4b73c4504b.png)
选中全部数据，在数据选项卡，筛选，条件为C列=1
![筛选结果.png](https://www.assdrty.com/images/2020/04/13/65b5673b8258da592.png)

# anki问答题
经过数据筛选，再在最上面插入一行，数据列，对应Anki的note type，最后一列的tag为可选，tag也必须在最后一列
![整理后.png](https://www.assdrty.com/images/2020/04/13/74655fea17ebdec1c.png)
然后选中所有数据，复制到记事本中，编码格式UTF-8
打开anki，选择对应的desk,就可以将这个txt文件导入了
