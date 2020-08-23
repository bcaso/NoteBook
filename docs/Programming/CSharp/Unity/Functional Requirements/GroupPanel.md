![](https://i.loli.net/2019/10/06/64aKir12cU8wvxq.png)
Unity中要实现类似Winform的GroupPanel的效果，很简单。
不需要复杂的代码。仅通过渲染层级的关系就能实现。

将不同的分页面，放置在上层，先渲染，切换分页面的按钮放在最下面。
如SetPanel下的OptionPage, StatisticsPage, ProducerPage这个三分页面。
切换这三个页面的三个按钮都放在他们下面，所以点击按钮切换分页后，其他的两个按钮还能显示在新的页面上。