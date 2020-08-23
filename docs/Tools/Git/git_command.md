# 设置用户
设置用户名 `git config --global user.name 'username'`
<br/>
设置用户名邮箱 `git config --global user.email 'xxx@xxx.com'`
<br/>
查看设置项 `git config --list`

说明: 设置的用户名和邮箱与git仓库登录时的用户名和账号没有任何关系, 这里的用户名和邮箱只是为了与仓库中的其他用户区分

# 解决 git log 命令中文乱码
试试 `git --no-pager log`
如果可以显示的话，把 pager 设置为 more
`git config --global core.pager more`

!!! note
    commit 时, 最好还是用英文

# 基本操作

* 初始化
```
mk mysite
cd mysite
git init
```

* 创建文件, 并修改文件
```
touch test.py
# vim test.py
touch test_1.py
mkdir testFolder
```

* 查看工作区状态
 `git status`

* 添加文件到git暂存区
```
git add test.py
git add test_1.py
git add testFolder.py

add 可选命令参数 : Î
  --all 全部文件
  --no-all 忽略部分文件, 需要配置 .ignore 文件

git add *.txt   # 添加所有.txt文件
git add *       # 表示添加当前目录中的所有文件, 但名称以.开头的文件除外, 这只是Shell的功能, Git只会接受到文件列表
git add .       # 表示递归添加当前目录下的所有文件, 包含以.开头的文件
```

* 提交到本地库 `git commit -m 'comments'`


* 修改文件
```
vim test.py  
git status         # 再次查看仓库状态 git status  
git add test.py    # 再次添加已修改的文件到暂存区

git commit -m '对test.py做了一点修正' # 再次提交到本地库
```

* 删除文件
```
rm -rf test.py  # 或者在文件夹中手动删除
  
git rm test.py  # 从git暂存区中删除文件

git commit -m '删除文件test.py' # 再次提交到本地库
```

* 添加远程账户
```
vim .git/config 

将 
    [remote "origin"]
        url = https://github.com/用户名/仓库名.git
修改为:
    [remote "origin"]
        url = https://用户名:密码@github.com/用户名/仓库名.git

```

# 以github文件为主
当本地文件与 gihub 仓库文件大不同时, 先clone github到本地, 把本地的配置好, 再把修改的内容添加到那个目录, 然后再提交到github

提交到远程仓库 `git push` (需要进入到包含.git文件夹的同级目录下)

# 下载(克隆)仓库到本地
```
cd targetFolder               # 先进入目标文件夹, 仓库保存目录
git clone "https://***.git"   # git clone "https://***.git"  #号后面是仓库地址
```
