文本编辑框
四个必要组件：controller, focusNode, style, cursorCorlor
```c#
	public override Widget build(BuildContext context) {
		return WQF.ListView
			.Child(new EditableText(
			                        controller: new TextEditingController("123"),
			                        focusNode: new FocusNode(),
			                        style: new TextStyle(),
			                        cursorColor: Color.black
			                       )
			      )
			.Child(
			       new GestureDetector(
			                           child: new BtnAddView(
			                                                 onAdd: data => { this.setState(() => { mTodoData.Add(data); }); }
			                                                )
			                          )
			      )
			.Children(TodoViews())
			.Padding(EdgeInsets.only(top: 50))
			.EndListView();
	}
```
# 使用注意事项
①必须包在Container中
②要设置Width，否则就是占一整行