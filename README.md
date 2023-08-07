"# container" 

### 1、 docker 容器入门
### 2、 docker 容器原理
### 3、 docker 容器化服务常见问题
### 4、 docker 容器编排和部署
### 5、 总结
############################################################
正文
##### 1.1 虚拟化 Virtualization

虚拟化是一种资源管理技术，将计算机的各种资源(CPU,MEM,DISK,NET device)予以抽象，转换后呈现出来并提供可分割
、组合为一个或多个计算机的配置环境，虚拟化技术打破了计算机内部实体结构不可分割的障碍，使用户能够以比原本更好的配置方式来
应用这些计算机硬件资源。

关键字: 抽象、分割 资源   将一台计算机分割为多台机器使用

##### 1.2 什么是容器？ 为什么要用容器

先引入一下传统的虚拟化和操作系统虚拟化的区别   操作系统虚拟化也就是我们所说的容器

发展进程：
    
    1.2.1 全虚拟化 (见文字图1)
            1) 不需要定制的Guest OS
            2) 虚拟机的硬件由软件进行抽象提供
            3) 性能较差
            4) 安全性较好
            对于全虚拟化的Guest OS 来说，它的硬件都是虚构的，它执行的指令都要有 Hypervisor 翻译，运行效率比较低

    
    1.2.2 半虚拟化 (见文字图2)
            1) 需要定制的Guest OS
            2) 虚拟机可以直接用CPU等硬件
            3) 性能接近于物理机
            4) 安全性好
            半虚拟化和全虚拟化最大的差别就是半虚拟化能直接使用硬件设备，但是问题是 Guest OS 需要定制，甚至运行的程序也是特殊版本
            同事也没有解决你虚拟机里需要额外运行一个 Guest OS 所造成的 CPU MEM 浪费问题

    1.2.3 操作系统虚拟化 (见文字图3)
            也就是我们所说的容器
            1) 不需要 Guest OS, 和宿主机共享内核
            2) 直接使用 CPU 等硬件
            3) 性能几乎和物理机没有差别
            4) 安全性较差
            容器的实现和传统虚拟化是相当不同的一个方式, 它不需要 Hypervisor，容器的进程实际上就是运行在宿主机的OS上的，容器通过
            操作系统提供的一些列隔离机制限制某几个或者某个进程所获得的资源信息，形成一个看不见的墙，把这组进程罩在一个罩子里面

##### 1.3 容器发展的历史

> 1979年 chroot 命令的提出是隔离的雏形, 通过切换root目录达到一定隔离进程的目的
> 
> 2004年 早期容器
> 
> 2007年 Google 向 Linux 提交了 CGroup, 形成了 Linux 容器技术上的一个基石
> 
> 2008年 Linux 上有了 lxc 容器
> 
> 2013年 docker 有了镜像的容器, 有了镜像之后容器技术就能像传统虚拟化一样进行迁移分发然后再运行
> 
> 2018年 又出现了一些安全容器 比如 kata gVisor 之类的

##### 1.4 容器的用途

早期用途：

1. 轻量化沙箱 - 利用隔离能力可以进行一些测试以及服务检测等相关应用
2. 快速部署 - 利用docker镜像, 有了镜像之后就可以像传统虚拟化一样进行迁移分发然后再运行
3. 轻量级的虚拟化 - 利用通过容器的快速部署能力，把容器当虚拟机使用


    和传统的虚拟机比，容器的优点:

    1. 秒级的自动启动
    2. 更轻量的镜像，降低传输耗时
    3. 直接在宿主机上运行，性能损耗小
    
    缺点:
    1. 隔离相比于传统的VM较差

##### 2.1 操作docker

流程简述: 
`docker pull centos -> docker run -ti centos bash -> cker rm -f container_id`

文字描述: 拉取镜像 -> 启动容器 -> 销毁容器

==================================================================

docker pull centos

docker images // 输出所有拉下来的镜像

docker images 里关注 TAG 和 IMAGE ID   一个是版本号  一个是可以通过镜像ID启动一个容器

docker run -ti centos bash   // 这里用 centos 镜像名或者IMAGE ID 都可以

简单介绍一下这个命令

docker run 是启动

-t 是让docker加载一个伪终端

-i 是让伪终端交互打开

输入命令后会进入容器的伪终端  按住 ctrl + p + q 就可以退出

=======================================================================

docker 命令的一些补充

1. docker ps 可以看一下所有运行的容器
2. docker kill container_id 结束这个容器的运行
3. docker kill 结束了容器的运行 但是没有销毁，docker ps -a 可以看到所有的容器
4. docker rm -f container_id 就可以销毁容器

##### 2.2 dockerfile

这里是docker最关键的镜像，我们写docker的内容时 要知道怎样去写一个镜像
打镜像我们也有两种方式
1. dockerfile, 命名一个 dockerfile 文件，将内容写在里面 然后用docker build -t myimg:1.0.1 $DIR  这里-t是指定它镜像名和tag
2. 我们可以启动一个容器，在里面安装各种东西，之后用 docker commit 导出也可以打一个镜像

业内推荐的方式是写dockerfile

===========================================

写个docker file的 例子把

dockerfile  见文件

full.cpp 见文件

g++ 编译 full full.cpp

在Linux服务器中让他们属于同一目录下

docker build -t myimg:0.1.0 .

记得一定要加 . 表示当前目录    这里要指定编译目录

docker images  看看我们编译好的镜像

docker run -ti image_id bash

我们进入启动的容器后  可以去  /usr/local 下看我们搞的 full 二进制和 test.txt 文件

一切都如我们所愿

===========================================

##### 2.3 观察docker

docker run -ti -cpus=1 myimg
这里限制只用一个核

你在使用 `docker run` 命令时，使用了错误的参数格式导致了错误。正确的格式应该是 `-c, --cpu-shares=<value>`，其中 `<value>` 为一个整数，表示容器使用 CPU 资源的权重。

你可以使用以下命令来限制容器使用 1 个 CPU 核心：

```shell
docker run -ti --cpu-shares=1024 myimg
```

其中 `1024` 表示容器使用 CPU 资源的权重，这里将其设置为 1024，相当于限制容器使用一个 CPU 核心。

你可以根据实际情况修改权重值。

在容器中 启动 /usr/local/full & 后台运行   并用 top 命令可以看到full进程占用cpu 很高

然后我们在宿主机上用 top 命令也能看到full进程  但是我们可以发现 PID 不同

这里后面的隔离机制会讲到  PID 映射

##### 2.4 容器的基本实现

我们要实现docker  首先要实现的就是资源的限制和隔离

docker实现的方法主要是用了Linux的两个子系统

1. CGroup -> control groups 是Linux内核的一个功能，用来限制、控制与分离一个进程
   
    
    https://luoxn28.github.io/2020/01/04/cgroup-yuan-li-jie-xi/
    https://blog.csdn.net/zhonglinzhang/article/details/64905759
    https://zhuanlan.zhihu.com/p/433327341
    https://www.feiyiblog.com/2020/03/26/Docker%E6%A0%B8%E5%BF%83%E5%8E%9F%E7%90%86-Cgroup/


cgroups为每种资源定义了一个子系统，典型的子系统如下：

- cpu 子系统，主要限制进程的 cpu 使用率。
- cpuacct 子系统，可以统计 cgroups 中的进程的 cpu 使用报告。
- cpuset 子系统，可以为 cgroups 中的进程分配单独的 cpu 节点或者内存节点。
- memory 子系统，可以限制进程的 memory 使用量。
- blkio 子系统，可以限制进程的块设备 io。
- devices 子系统，可以控制进程能够访问某些设备。
- net_cls 子系统，可以标记 cgroups 中进程的网络数据包，然后可以使用 tc 模块（traffic control）对数据包进行控制。
- freezer 子系统，可以挂起或者恢复 cgroups 中的进程。
- ns 子系统，可以使不同 cgroups 下面的进程使用不同的 namespace。
    
    
2. namespace -> cgroup 只是进行了一些资源隔离，但是还有很多问题，比如pid、username、env 这些内容无法处理所以就用了namespace这么一个子系统

https://zhuanlan.zhihu.com/p/433327341

主要分离的内容有

- user namespace 拥有自己的一组用户 ID 和组 ID，用于分配给进程。这意味着进程可以在其 user namespace 中拥有 root 权限，而不需要在其他 user namespace 中获得。
- process ID (PID) namespace 将一组 PID 分配给独立于其他 namespace 中的一组 PID 的进程。在新的 namespace 中创建的第一个进程分得 PID 1，子进程被分配给后续的 PID。如果子进程使用自己的 PID namespace 创建，则它在该 namespace 中使用 PID 1，在父进程的 namespace 中使用自己的 PID。请参见下面的示例。
- network namespace 拥有独立的网络栈：自己的专用路由表、IP 地址集、套接字列表、连接跟踪表、防火墙及其他网络相关资源。
- mount namespace 拥有一个独立的挂载点列表，并对该 namespace 中的进程可见。这意味着您可以在 mount namespace 中挂载和卸载文件系统，而不会影响主机文件系统。
- interprocess communication (IPC) namespace 拥有自己的 IPC 资源，例如 POSIX 消息队列。
- UNIX Time‑Sharing (UTS) namespace 允许单个系统对不同的进程显示不同的主机名和域名。

##### 2.5 docker的镜像

docker的镜像不会造成存储空间的浪费，如果我们要用同一个镜像的会会进行文件复用

复用文件发生了修改会启用 **"写时复制"**

常见的容器的联合文件系统

unionfs 可以实现多个container共享一个镜像

写时复制 copy on write

用时分配 allocate on demand

https://www.jianshu.com/p/3ba255463047

##### 3 docker化服务常见问题

1. **服务性能有差异**

使用对应的工具确认服务本身是否有问题

一些性能检查工具，看看一般问题在哪，如果大量的时间都消耗在内核态上，很有可能是受到隔离能力不健全导致的应i选哪个

确认不是自己的问题后一半就是去看公用内核的调用问题

共用内核可能会造成的问题: 容器之间相互影响的问题存在，根本原因还是共用内核
    
- 所有进程实际上都是在宿主机上运行的
- 内核实现的机制问题: 内核本身就是一个大进程，内核内部也有资源竞态(内核态的资源竞态)
    
        补充竞态说明
        https://zhuanlan.zhihu.com/p/492350879
        1. 并发与竞态概念

        何为并发：并发是指多个执行单元同时、并行被执行。
        
        何为竞态：并发的执行单元对共享资源（硬件资源和软件上的全局变量，静态变量等）的访问容易发生竞态。

        2. 竞态发生的情况

        - 对称多处理器（SMP）的多个CPU：SMP是一种紧耦合、共享存储的系统模型，它的特点是多个CPU使用共同的系统总线，因此可以访问共同的外设和存储器。
        
        - 单CPU内进程与抢占它的进程：2.6的内核支持抢占调度，一个进程在内核执行的时候可能被另一高优先级进程打断。
        
        - 中断（硬中断、软中断、tasklet、低半部）与进程之间：中断可以打断正在执行的进程，处理中断的程序和被打断的进程间也可能发生竞态。

- IO调用栈共用且没有 buffer 和 cache 的隔离
- 某些资源信息隔离不完全(比如时间)

2. **共用内核造成的问题**
   
- CPU相关

        1. 自己或者其他业务存在大量系统调用，争抢内核态资源
        2. 对CPU核心切换十分敏感，必须同numa
        https://zhuanlan.zhihu.com/p/534989692
        https://zhuanlan.zhihu.com/p/554043638
        
        NUMA:
            非均匀内存访问(NUMA)是一种用于多出力的计算机内存设计，其中内存访问之间取决于相对于处理器的内存位置。
            在 NUMA 下，处理器可以比非本地内存(另一个处理器的本地内存或处理器之间共享的内存)更快地访问自己的本地内存
            NUMA的又是仅限于特定的工作负载，特别是在数据通常与某些任务或者用户密切相关的服务器上
        3. 使用外部框架，自动生成了线程数庞大的线程池
        举个例子，你限制了容器资源8核，但是你的host是64核的，因为共用，所以如果直接调用框架就会导致过多的生成线程导致过多切换损耗性能了

- IO相关
        
        1. 网络IO未进行隔离或限制
        2. 磁盘directIO有隔离和限制但是bufferIO没有

- 常见情况
    
      1. 某个节点流量没变，CPU负载飙升
      - 容器CPU 负载大幅度提升
      - 接口耗时增加
      - 服务没有变更，性能却受到了影响
      可以使用一些性能分析工具来检查服务性能
      比如 c++ -> perf

      2. 服务可靠性问题
      - 首先检查程序是否panic或者coredump
      - 使用dmesg命令查看是否有oom情况
      
===================================

dmesg 补充

在 Linux 系统中，dmesg 命令用于显示内核环境变量。如果系统出现了 OOM（Out Of Memory）情况，可以通过 dmesg 命令来查看系统日志，以确定是否是由于内存不足导致的。

具体来说，我们可以使用以下命令来查看 dmesg 日志中是否出现 OOM 相关的信息：

```shell
dmesg | grep -i oom
```

该命令会输出 dmesg 日志中包含 OOM 相关信息的行，其中 `-i` 参数表示不区分大小写。

如果输出结果中包含类似于以下信息：

```
[  123.456789] Out of memory: Kill process 1234 (some_process) score 5678 or sacrifice child
```

那么就说明系统曾经出现过 OOM 情况，同时也显示了导致 OOM 的进程 ID（1234）、进程名称（some_process）以及进程的分数（5678）。这些信息可以帮助我们定位和解决系统内存不足的问题。

需要注意的是，dmesg 日志中只会记录最近发生的事件，因此如果 OOM 事件发生的时间比较久远，可能无法通过 dmesg 命令来查看到相关信息。此时，可以查看系统的其他日志文件，如 /var/log/messages 或 /var/log/syslog，以获取更完整的系统日志。

===================================

```shell
docker run [OPTIONS] IMAGE [COMMAND] [ARG...]
```
OPTIONS说明：

-a stdin: 指定标准输入输出内容类型，可选 STDIN/STDOUT/STDERR 三项；

-d: 后台运行容器，并返回容器ID；

-i: 以交互模式运行容器，通常与 -t 同时使用；

-P: 随机端口映射，容器内部端口随机映射到主机的端口

-p: 指定端口映射，格式为：主机(宿主)端口:容器端口

-t: 为容器重新分配一个伪输入终端，通常与 -i 同时使用；

--name="nginx-lb": 为容器指定一个名称；

--dns 8.8.8.8: 指定容器使用的DNS服务器，默认和宿主一致；

--dns-search example.com: 指定容器DNS搜索域名，默认和宿主一致；

-h "mars": 指定容器的hostname；

-e username="ritchie": 设置环境变量；

--env-file=[]: 从指定文件读入环境变量；

--cpuset="0-2" or --cpuset="0,1,2": 绑定容器到指定CPU运行；

-m :设置容器使用内存最大值；

--net="bridge": 指定容器的网络连接类型，支持 bridge/host/none/container: 四种类型；

--link=[]: 添加链接到另一个容器；

--expose=[]: 开放一个端口或一组端口；

--volume , -v: 绑定一个卷

实例

使用docker镜像nginx:latest以后台模式启动一个容器,并将容器命名为mynginx。
docker run --name mynginx -d nginx:latest

使用镜像nginx:latest以后台模式启动一个容器,并将容器的80端口映射到主机随机端口。
docker run -P -d nginx:latest

使用镜像 nginx:latest，以后台模式启动一个容器,将容器的 80 端口映射到主机的 80 端口,主机的目录 /data 映射到容器的 /data。
docker run -p 80:80 -v /data:/data -d nginx:latest

绑定容器的 8080 端口，并将其映射到本地主机 127.0.0.1 的 80 端口上。
$ docker run -p 127.0.0.1:80:8080/tcp ubuntu bash

使用镜像nginx:latest以交互模式启动一个容器,在容器内执行/bin/bash命令。
runoob@runoob:~$ docker run -it nginx:latest /bin/bash

**docker 文档**

https://www.runoob.com/docker/docker-run-command.html

**docker 源码入门**

https://www.jianshu.com/p/4a1f712185c4

https://github.com/docker/docker-ce/tree/master/components/cli/man

===================================

##### 4.1 容器的编排部署 k8s
https://kubernetes.io/zh-cn/docs/home/

目的是为了怎样更合理的去使用容器

容器编排系统

| 特性 | 说明 |
| :------: |  :------: |
| Provisioning   | 提供/管理/调度容器   | 
| Configuration Scripting  | 通过配置定义容器服务   | 
| Monitoring  | 跟踪/监控容器的健康   | 
| Rolling upgrades and rollback  | 滚动升级和回滚   | 
| Service Discovery  | 服务发现   | 
| Container policy management   | 容器部署规则   | 
| Interoperability   | 和其他系统的协同能力   | 

##### 4.2 编排工具对比
  kubernetes mesos docker-swarm openshift 自研平台 -> kubernetes 一统江湖
  
**k8s的优点**
- 编排强可扩展性  方便企业根据自身情况定制扩展 k8s 编排的能力
- 部署环境强扩展性，可部署Node于虚拟机、物理机等
- 丰富工具集，k8s相关github项目超过1.2w个
- 由谷歌开源并持续维护，保证了项目的可持续性与bug修复

一个例子

运营中的常见故障
- 服务器故障 容器无法使用      -> 节点数保持  对应传统的服务器宕机  服务器迁移
- 服务流量持续上涨，不扩容就血崩 -> 水平扩容  扩容降载
- 服务版本升级                -> 服务发布  灰度控制  自动化滚动升级

##### 4.3 k8s中的基本管理单位 pod
k8s中使用pod来管理容器，每个pod可以包含一个或者多个紧密关联的容器

pod内容器共享PID IPC Network 和 UTS namespace

如何被定义一个pod

首先要写一个yaml文件 (yaml 文件详解: https://developer.aliyun,com/article/928015)

```yaml
# nginx_test.yaml
apiVersion: v1
kind: Pod
metadata:
  name: nginx
spec:
  containers:
    - name: nginx
      image: nginx:latest
      resource:
        limits:
          cpu: 100m
          memory: 300Mi
      ports:
        - containerPort: 80
```
创建Pod kubectl create -f nginx_test.yaml

查询Pod kubectl get pod

检查pod kubectl describe pod nginx

    节点数保持
    yaml 文件中由一个配置项 ReplicaSet [RS] 确保容器应用的副本数始终保持在用户定义的副本数

    RS 升级版 - Deployment
    定义 Deployment 来创建Pod 和 ReplicaSet
    滚动升级和回滚应用
    扩容和缩容
    暂停和继续部署

##### 4.4 插入k8s概念 选择pod label

label 是识别kubernetes对象的标签，以key/value的形式附加在对象上

Annotations 用来记录一些附加信息 用来辅助应用部署、安全策略以及调度策略等

##### 4.3 关于 Deployment
```yaml
# Deployment.yaml
apiVersion: extensions/v1
kind: Deployment
metadata:
  name: nginx
  labels: 
    app: nginx
spec:
  replicas: 3
  selector: 
    matchLabels:
      app: nginx
  template:
    metadata:
      labels:
        app: nginx
  spec:
    containers:
      - name: nginx
        image: nginx:latest
        resource:
          limits:
            cpu: "1"
            memory: 300Mi
      ports:
        - containerPort: 80
```
创建服务: kubectl apply -f nginx.yaml

删除服务: kubectl delete -f nginx.yaml

扩容: kubectl scale deployment nginx--replicas 10

升级: kubectl set image deployment/nginx nginx=nginx:1.9.4

回滚: kubectl rollout undo deployment/nginx

其中可以用 kubctl get deployment 可以看到所有deployment集群

kubectl get pods 可以看到所有的pod 然后看到 deployment 集群的pods会自动带上一些字符串后缀进行区分

##### 4.5 自动扩容HPA 自动扩缩容Pod
```yaml
# nginx_hpa.yaml
apiVersion: autoscaling/v1
kind: HorizontalPodAutoscaler
metadata:
  name: nginx-hpa
spec:
  scaleTargetRef:
    apiVsersion: apps/v1
    kind: Deployment
    name: nginx
  minReplicas: 1
  maxReplicas: 10
  metrics:
    - type: Resource
      resource:
        name: CPU
        target:
          type: Utilization
          averageUtilization: 5
```
创建HPA: kubectl create -f nginx_hpa.yaml

删除HPA:kubectl delete -f nginx_hpa.yaml

查看HPA: kubectl get hpa

```shell
# kubectl 命令补充
kubectl get pod
kubectl cp target_file pod_name:/DIR/DIR # kubectl cp full nginx:/usr/local
kubectl exec -ti pod_name bash # 登录pod执行命令
```
##### 4.6 k8s的服务发现

Kubernetes服务发现是通过`kube-proxy`和`Service`对象来实现的。

`kube-proxy`是Kubernetes集群中的一个组件，主要负责实现服务发现和负载均衡。它会监视Kubernetes API服务器中的`Service`和`Endpoints`资源对象，然后生成对应的iptables规则，将流量转发到正确的Pod中，从而实现服务发现和负载均衡。

`Service`对象是Kubernetes中定义服务的一种资源对象，它可以让多个Pod共享同一个虚拟IP和端口，从而组成一个逻辑上的服务。当Pod启动或停止时，`Service`对象会自动更新其后端的`Endpoints`对象，从而维护服务的可用性和准确性。

当客户端访问一个服务时，请求会先到达`kube-proxy`所在的节点，`kube-proxy`会根据服务的类型（ClusterIP、NodePort、LoadBalancer或ExternalName）和端口号等信息，将请求转发到正确的Pod中。如果服务有多个后端Pod，`kube-proxy`会根据负载均衡算法（如轮询、随机等）来选择其中一个Pod来处理请求。

总之，Kubernetes服务发现是通过`kube-proxy`和`Service`对象来实现的，它可以让集群中的各个组件和应用程序可以方便地相互发现和通信，从而构建高可用、可伸缩的分布式应用系统。

这些是k8s自带的服务发现的机制，但是在很多地方我们的服务发现都是自研的一些工具
这些服务发现都是需要我们在宿主机上安装一个agent  这个时候就要用到 k8s 的DemonSet机制
K8s 确保一个node运行一个pod的副本 主要用于部署agent 多见于服务发现和日志采集等agent

三个基本问题解决 -- 运营中的常见故障
- 服务器故障，容器无法使用          --> 节点数保持 对应传统的 宕机 服务器迁移 -> ReplicaSet Deployment 服务发现
- 服务流量持续上涨，不扩容就血崩     --> 水平扩容  扩容降载                 -> k8s HPA
- 服务版本升级                    --> 服务发布  灰度控制，自动化滚动升级    -> Deployment

##### 5.1 k8s的核心原理

k8s的系统架构

https://www.kubernetes.org.cn/kubernetes%E8%AE%BE%E8%AE%A1%E6%9E%B6%E6%9E%84

k8s的架构设计

k8s的系统构建 - API server
> 提供集群管理的 REST API 接口，包括授权认证、数据校验以及集群状态变更等
> 
> 提供其他模块之间的数据交互和通信枢纽

k8s系统构件 - kubelet
- 节点管理
- Pod管理
- 容器健康检查
- cAdvisor 资源监控
- kubelet Eviction 驱逐
- 容器运行时

k8s系统构件 - controller manager

kubernetes的大脑

通过 apiserver 监控整个集群的状态，并确保集群处于预期的工作状态

k8s的资源控制器
> Job/CronJob 一般用于批处理脚本的场景
> 
> StatefulSet 有状态的服务应用程序可用，用于有状态的服务，比如说数据库，不能随便迁移 也不能祟拜你重启
> 
> - 稳定的持球话存储 基于 PVC 实现
> - 提供稳定的网络标志
> - 有序部署、扩展和伸缩 即从 n-1 到 0
> 
> HorizontalPodAutoscaling 自动扩展，用于控制其他控制器自动扩展

k8s的资源控制器 -- HPA

HPA 是在k8s里的 HPA controller 实现的

Pod 水平自动扩容 Horizontal Pod Autoscaler
> 基于cpu利用率伸缩 replication controller 、 Deployment 和 replicaSet 中Pod的数量
> 
> 也可以基于其他应用程序提供的度量指标 custom metrics

举个例子

我们前面的HPA测试的yaml文件里设置的是CPU超过5%就扩容，容器的cpu上升了以后呢，宿主机里的 kubelet 里面的 cAdvisor 就会采集到这个信息，然后
上报到普罗米修斯里面， HPA controller 就会去监听这个普罗米修斯里面我们设置监听的容器的负载的变化，cpu大于5之后就会增加deployment中我们的指定
的replicas的数量，HPA修改了这个数量之后会提交到API server 里面，replicaSet controller 就会监听到API server 里面这个 replica 数量发生了变化
controller就会做出响应 扩充新的容器

k8s中的调度器 -- scheduler
> 负责分配调度 Pod 到集群内的 Node 上，它监听API server，查询还未分配Node的Pod 然后根据调度策略为这些Pod分配Node

调度顺序: [看图就好](https://www.modb.pro/db/174089)

##### 6 小结

- 什么是容器编排
- 为什么是k8s
        
      
    1. HPA
    2. Node Pod container
    3. Deployment & ReplicaSet
    4. controller
    5. Damon Set

- k8s 架构
  
      1. API Server
      2. Kubelet
      3. Scheduler
      4. controller manager