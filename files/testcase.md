# Case 1 简单指令以及undo/redo 

draw -g 2 script1.txt
```
color(1)
line(1, 2, 48, 47)
text(10, 5, "OOAD")
color(0)
text(5, 45, "Bounday")
undo
undo
text(5, 45, "Bounday")
undo
redo
```

# Case 2 宏指令以及undo
draw -g 256 script2.txt

```
//带一个下划线的时间
#startTimeView{
    color(128)
    line(0,0,50,0)
    text(0,3,"08:55")    
}
//另一个带下划线的时间
#finishTimeView{
    color(80)
    line(0,0,50,0)
    text(0,3,"13:55")    
}
color(255)
text(7,40,"Time")
!startTimeView(0,30)
text(20,24,"~")
!finishTimeView(0,10)
undo
!finishTimeView(4,10)
```

# Case 3 宏指令嵌套以及undo
draw -g 256 script3.txt
```
//底部的一条分割横线
#bottomLine{
    color(255)
    line(0,0,50,0)
}
//带一个下划线的时间
#startTimeView{
    color(128)
    bottomLine(0, 0)
    text(0,3,"08:55")    
}
//另一个带下划线的时间
#finishTimeView{
    color(80)
    bottomLine(0, 0)
    text(0,3,"13:55")    
}
color(255)
text(7,40,"Time")
!startTimeView(0,30)
text(20,24,"~")
!finishTimeView(0,10)
undo
!finishTimeView(4,10)
```

# 注意：
1. 宏指令中定义的color只作用于当前宏指令内部，不影响外部color的定义.
2. 每个case运行时，除了`#`和`color`,每条指令执行后都立即向控制台输出当前的结果。即每个case会产生一个输出序列。输出每条指令的结果前，先输出执行的指令。可以重定向到一个文本文件中查看结果。请将该输出结果一并提交。
3. 屏幕大小为50 * 50