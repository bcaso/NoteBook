---
title: 将字符串转换为Enum类型
tags: Csharp
grammar_mindmap: true
renderNumberedHeading: true
grammar_code: true
grammar_mathjax: true
---
```csharp
class Item{
    //...
    public enum ItemType {
	    Consumable,
    	Equipment,
    	Weapon
    }
    //...    
}
```


```csharp
private Item _item = new Item();
void TestEnum(){
    string str = "strEnum";
    _item.ItemType type = (_item.ItemType)System.Enum.Parse(typeof(_item.ItemType), str);
    switch(type){
        case _item.ItemType.Consumable:
            break;
        case _item.ItemType.Equipment:
            break;
        case _item.ItemType.Weapon:
            break;
    }
}    
```

