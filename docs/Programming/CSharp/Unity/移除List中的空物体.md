---
title: 移除List中的空物体
tags: 新建,模板,小书匠
grammar_cjkRuby: true
---
问题：当敌人退出触发器时，list<GameObject>中对物体的引用还在，只是丢失了。list的Count没变
```csharp?linenums
    private List<GameObject> _enemyGameObjects = new List<GameObject>();
    private void OnTriggerEnter(Collider other) {
        if (other.CompareTag(Tags.Enemy)) {
            EnemyGameObjects.Add(other.gameObject);
        }
    }

    private void OnTriggerExit(Collider other) {
        if (other.CompareTag(Tags.Enemy)) {
            EnemyGameObjects.Remove(other.gameObject);
        }
    }
}
```
解决：
```csharp?linenums
    /// <summary>
    /// 删除List<GameObject>集合中的missing 物体，这个方法应该在判断list[0]为空时调用。
    /// </summary>
    public void RemveMissingObject() {
        List<int> objectIndexList = new List<int>();
        for (int index = 0; index < objectIndexList.Count; index++) {
            if (objectIndexList[index] == null) {
                objectIndexList.Add(index);
            }
        }
        //再遍历原集合，把空物体索引所对应集合中的元素删除
        for (int index = 0; index < objectIndexList.Count; index++) {
            EnemyGameObjects.RemoveAt(objectIndexList[index]);//再通过原集合的静态方法RemoveAt来移除索引所对应的物体。
        }
    }
```