播放视频，按下F12，点击鼠标选取页面元素，定位到“子弹文字”。
①找到文字的样式，将`font-size:10px` 改为 `font-size:0px`
②找到子弹头所在的div标签，把div改为p标签或其他标签，貌似这是用标签定位的。

关键还是改样式,下面的代码是那段定时文字的css样式。
```css
text-align: center;
font-size: 10px;
line-height: 1;
font-weight: 400;
font-style: normal;
font-family: Arial,Helvetica,sans-serif;
color: rgb(255, 255, 253);
--darkreader-inline-outline: initial;
box-sizing: inherit;
position: absolute !important;
display: block !important;
transform: none !important;
right: unset !important;
bottom: unset !important;
opacity: 1 !important;
left: 1110px !important;
top: 77.267px !important;
```
可以把display设置为`none`即可隐藏，也就是①改div，②改样式