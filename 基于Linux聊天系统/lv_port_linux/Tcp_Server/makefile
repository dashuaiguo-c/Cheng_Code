#编译器
CC?=gcc
#目标文件
TARGET=main
#编译对象
SRC=$(wildcard *.c)  #所有的.c文件  #SRC source的缩写
OBJ=$(SRC:%.c=%.o)  #将所有的.c文件转化为.o文件
#引用的LIB
LIB=-lfreetype -lcjson -lpthread -L. -lserver

#编译
$(TARGET):$(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LIB)

#设置规则
clean:
	rm  -rf $(TARGET) $(OBJ)
send:
	scp ./$(TARGET) root@192.168.10.5:/cheng

# 修改探测的规则
$(OBJ):%.o:%.c     #将所有依赖文件中的.c文件生成为.o文件
	$(CC) -c $^ -o $@
