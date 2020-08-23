`TestUnityJson.cs`
```csharp
using System;
using System.Collections.Generic;
using UnityEngine;
namespace Test.testJSON 
{
  public class TestUnityJson : MonoBehaviour 
  {
    private void Start() 
    {
      //      SimpleTest();
      AdvancedTest();
    }
    private void SimpleTest() 
    {
      //序列化
      Hero hero = new Hero() 
      {
        Name         = "李四",
                Age          = 21,
                CurrentLevel = new Level() 
        {
          CurLevel = 111}
                };
          string heroInfo = JsonUtility.ToJson(hero);
          Debug.Log(string.Format("hero {0}", heroInfo));
          //反序列化
          Hero heroNew = JsonUtility.FromJson<Hero>(heroInfo);
          Debug.Log(string.Format("newHero: heroNew.Name:{0},heroNew.Age:{1},heroNew.CurLevel:{2}",
                                        heroNew.Name, heroNew.Age, heroNew.CurrentLevel.CurLevel));
          //重写对象,把heroNew的Name修改为“张三”，然后序列化到文件，再反序列化重写hero对象
          heroNew.Name = "张三";
          heroInfo     = JsonUtility.ToJson(heroNew);
          JsonUtility.FromJsonOverwrite(heroInfo, hero);
          Debug.Log(string.Format("被修改后的hero {0}", heroInfo));
        }
        private void AdvancedTest() 
        {
          //读取配置
          TextAsset configFile = Resources.Load<TextAsset>("People");
          if (!configFile) Debug.LogError("文件读取失败");
          Debug.Log("配置文件内容：" + configFile.text);
          Debug.Log("配置文件：" + configFile);
          //序列化到string 对象, json 到 json, strPeoples为"{}"
          string strPeoples = JsonUtility.ToJson(configFile.text);
          Debug.Log("json -> json  strPeoples ==" + strPeoples);
          //json -> json  strPeoples =={}
          //反序列化到一个Peoples对象，json 到对象
          Peoples p = JsonUtility.FromJson<Peoples>(configFile.text);
          Debug.Log("p -> " + p);
          Debug.Log("p.ListPerson.Count -> " + p.People.Count);
          //遍历并打印结果
          foreach (People person in p.People) 
          {
            Debug.Log(string.Format("Name:{0}, Age{1}",
                                            person.Name, person.Age));
          }
        }
      }
      #region SimpleTest
        [Serializable]
        public class Hero 
      {
        public string Name;
        public int    Age;
        public Level  CurrentLevel;
      }
      [Serializable]
        public class Level 
      {
        public int CurLevel;
      }
      #endregion SimpleTest
        #region AdvancedTest
        [Serializable]
        public class Peoples 
      {
        //    public List<People> ListPerson;//在反序列化时会失败，但不会报错。数组名不一致，导致反序列化后的对象的list数组的count为0
        public List<People> People;
        //json数组对应的就是类中的list数组，两个的名称要对应一致
      }
      [Serializable]
        public class People 
      {
        public string Name;
        public string Age;
      }
      #endregion AdvancedTest
    }
```

`People.json`
```json?linenums
{
  "People": [
    {
      "Name": "张三",
      "Age": 20
    },
    {
      "Name": "李四",
      "Age": 21
    },
    {
      "Name": "王五",
      "Age": "22"
    }
  ]
}
```
# 总结
1. json文件名，类名，无所谓
2. json文件要放在`Resources`目录下
3. json中的字段对应类中的字段
4. json中的数组对应类中的`List<T>`数组
5. 不要对json文件做`ToJson`操作

## Debug的输出 与 FromJson 的读取参数
假如定义如下：
```
TextAsset configFile = Resources.Load<TextAsset>("People");
```

下面两行代码输出输出的内容相同，都是文件中的文本
```
Debug.Log(configFile.text);
Debug.Log(configFile);
```
`FromJson<T>(string json)`
但是因为`configFile` 的类型是`TextAsset`，与`string`不匹配，编译器会报错。
需要使用`configFile.text`形式，如下：
`Peoples p = JsonUtility.FromJson<Peoples>(configFile.text);`
