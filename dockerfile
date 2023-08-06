FROM centos  // 基于什么镜像
MAINTAINER zhou <zhou@123.com> // 说明镜像负责人
RUN echo "test" > /usr/local/test.txt  // 执行一些命令
ADD full /usr/local/full  // 将文件添加到镜像
RUM chmod 755 /usr/local/full