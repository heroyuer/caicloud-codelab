<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](https://github.com/thlorenz/doctoc)*

- [Introduction](#introduction)
- [Kubectl command line](#kubectl-command-line)
  - [kubectl version](#kubectl-version)
  - [kubectl cluster-info](#kubectl-cluster-info)
  - [kubectl -h](#kubectl--h)
  - [kubectl command format](#kubectl-command-format)
  - [kubectl config file](#kubectl-config-file)
  - [Refereneces](#refereneces)
- [Kubernetes node](#kubernetes-node)
  - [Node information](#node-information)
  - [Node details](#node-details)
  - [Readings](#readings)
- [Kubernetes Namespace & ResourceQuota](#kubernetes-namespace--resourcequota)
  - [Namespaces](#namespaces)
  - [Resource quota](#resource-quota)
  - [Readings](#readings-1)
- [Kubernetes Pod & Deployment](#kubernetes-pod--deployment)
  - [Create Deployment](#create-deployment)
  - [Get Deployment](#get-deployment)
  - [Get Pods](#get-pods)
  - [Get Pod Logs](#get-pod-logs)
  - [Execute command in Pod](#execute-command-in-pod)
  - [Readings](#readings-2)
- [Kubernetes Service](#kubernetes-service)
  - [Create service](#create-service)
  - [Get service](#get-service)
  - [Query service](#query-service)
  - [NodePort service](#nodeport-service)
  - [Readings](#readings-3)
- [Kubernetes Label](#kubernetes-label)
  - [View selector & label](#view-selector--label)
  - [Label operations](#label-operations)
  - [Readings](#readings-4)
- [Kubernetes Deployment Operations](#kubernetes-deployment-operations)
  - [Scale up using kubectl](#scale-up-using-kubectl)
  - [View service](#view-service)
  - [Scale down using kubectl](#scale-down-using-kubectl)
  - [Update deployment](#update-deployment)
  - [Update via setting image](#update-via-setting-image)
  - [Deployment rollout](#deployment-rollout)
- [Kubernetes Yaml/Json File](#kubernetes-yamljson-file)
  - [Get resource yaml](#get-resource-yaml)
  - [Create resource using yaml](#create-resource-using-yaml)
  - [Update resource yaml](#update-resource-yaml)
  - [Readings](#readings-5)
- [Kubernetes Events](#kubernetes-events)
- [Kubernetes Pod Lifecycle](#kubernetes-pod-lifecycle)
  - [Restart policy](#restart-policy)
  - [Health Check](#health-check)
  - [Readings](#readings-6)
- [Kubernetes Job](#kubernetes-job)
  - [Readings](#readings-7)
- [Kubernetes ConfigMap & Secret](#kubernetes-configmap--secret)
  - [Readings](#readings-8)
- [Kubernetes Daemonset](#kubernetes-daemonset)
  - [Readings](#readings-9)
- [Summary](#summary)
- [Exercise](#exercise)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

# Introduction

本节我们将学习基于 Kubernetes 的应用管理，包括 kubectl, pod, deployment, service, label 等等。
针对每个内容都会给出 Reading List。注意，本节所有的操作都基于 Lab1 中创建的 Minikube 集群。

# Kubectl command line

## kubectl version

在 kubernetes 中，我们使用 kubectl 命令与 kubernetes 交互，在下面的试验中，我们将逐渐熟悉并了解更多
kubectl 相关的命令，我们可以使用 `kubectl version` 检查 kubernetes 的版本信息。

```
$ kubectl version
Client Version: version.Info{Major:"1", Minor:"7", GitVersion:"v1.7.3", GitCommit:"2c2fe6e8278a5db2d15a013987b53968c743f2a1", GitTreeState:"clean", BuildDate:"2017-08-03T15:13:53Z", GoVersion:"go1.8.3", Compiler:"gc", Platform:"darwin/amd64"}
Server Version: version.Info{Major:"1", Minor:"7", GitVersion:"v1.7.0", GitCommit:"d3ada0119e776222f11ec7945e6d860061339aad", GitTreeState:"clean", BuildDate:"2017-07-26T00:12:31Z", GoVersion:"go1.8.3", Compiler:"gc", Platform:"linux/amd64"}
```

从以上输出可以看出，kubectl 客户端的版本是 v1.7.3，kubernetes 集群的版本是 1.7.0。同时，该命令还会输出
kubernetes 编译信息。

## kubectl cluster-info

除了版本信息，我们还可以通过 kubectl 获取更多 kubernetes 集群的相关信息：

```
$ kubectl cluster-info
Kubernetes master is running at https://192.168.99.100:8443

To further debug and diagnose cluster problems, use 'kubectl cluster-info dump'.
```

上述信息给出了集群 API 服务的地址，如果使用 `kubectl cluster-info dump`，可以看到更多集群的信息。

## kubectl -h

kubectl 提供了非常好的帮助信息，我们可以通过 `kubectl -h` 来获取帮助信息。

```
$ kubectl -h
kubectl controls the Kubernetes cluster manager.

Find more information at https://github.com/kubernetes/kubernetes.

Basic Commands (Beginner):
  create         Create a resource by filename or stdin
  expose         Take a replication controller, service, deployment or pod and expose it as a new Kubernetes Service
  run            Run a particular image on the cluster
  run-container  Run a particular image on the cluster
  set            Set specific features on objects

Basic Commands (Intermediate):
  get            Display one or many resources
  explain        Documentation of resources
  edit           Edit a resource on the server
  delete         Delete resources by filenames, stdin, resources and names, or by resources and label selector

Deploy Commands:
  rollout        Manage the rollout of a resource
  rolling-update Perform a rolling update of the given ReplicationController
  rollingupdate  Perform a rolling update of the given ReplicationController
  scale          Set a new size for a Deployment, ReplicaSet, Replication Controller, or Job
  resize         Set a new size for a Deployment, ReplicaSet, Replication Controller, or Job
  autoscale      Auto-scale a Deployment, ReplicaSet, or ReplicationController

Cluster Management Commands:
  certificate    Modify certificate resources.
  cluster-info   Display cluster info
  clusterinfo    Display cluster info
  top            Display Resource (CPU/Memory/Storage) usage.
  cordon         Mark node as unschedulable
  uncordon       Mark node as schedulable
  drain          Drain node in preparation for maintenance
  taint          Update the taints on one or more nodes

Troubleshooting and Debugging Commands:
  describe       Show details of a specific resource or group of resources
  logs           Print the logs for a container in a pod
  attach         Attach to a running container
  exec           Execute a command in a container
  port-forward   Forward one or more local ports to a pod
  proxy          Run a proxy to the Kubernetes API server
  cp             Copy files and directories to and from containers.
  auth           Inspect authorization

Advanced Commands:
  apply          Apply a configuration to a resource by filename or stdin
  patch          Update field(s) of a resource using strategic merge patch
  replace        Replace a resource by filename or stdin
  update         Replace a resource by filename or stdin
  convert        Convert config files between different API versions

Settings Commands:
  label          Update the labels on a resource
  annotate       Update the annotations on a resource
  completion     Output shell completion code for the specified shell (bash or zsh)

Other Commands:
  api-versions   Print the supported API versions on the server, in the form of "group/version"
  config         Modify kubeconfig files
  help           Help about any command
  plugin         Runs a command-line plugin
  version        Print the client and server version information

Use "kubectl <command> --help" for more information about a given command.
Use "kubectl options" for a list of global command-line options (applies to all commands).
```

当我们找到需要的子命令时，可以进一步使用 -h 来查看该子命令的帮助信息：

```
$ kubectl get -h
Display one or many resources.

Valid resource types include:

  * all
  * certificatesigningrequests (aka 'csr')
  * clusterrolebindings
  * clusterroles
  * clusters (valid only for federation apiservers)
  * componentstatuses (aka 'cs')
  * configmaps (aka 'cm')
  * controllerrevisions
  * cronjobs
  * daemonsets (aka 'ds')
  * deployments (aka 'deploy')
  * endpoints (aka 'ep')
  * events (aka 'ev')
  * horizontalpodautoscalers (aka 'hpa')
  * ingresses (aka 'ing')
  * jobs
  * limitranges (aka 'limits')
  * namespaces (aka 'ns')
  * networkpolicies (aka 'netpol')
  * nodes (aka 'no')
  * persistentvolumeclaims (aka 'pvc')
  * persistentvolumes (aka 'pv')
  * poddisruptionbudgets (aka 'pdb')
  * podpreset
  * pods (aka 'po')
  * podsecuritypolicies (aka 'psp')
  * podtemplates
  * replicasets (aka 'rs')
  * replicationcontrollers (aka 'rc')
  * resourcequotas (aka 'quota')
  * rolebindings
  * roles
  * secrets
  * serviceaccounts (aka 'sa')
  * services (aka 'svc')
  * statefulsets
  * storageclasses
  * thirdpartyresources

...
```

## kubectl command format

The basic format of kubectl command is `kubectl <action> <resource>`, where `action` can be create,
delete, get, etc;`resource` is the above resources like pods, jobs, etc.

For example, to get all nodes in kubernetes cluster, use `kubectl get nodes`; to get details info of
a node, use `kubectl describe nodes ${NODENAME}`.

## kubectl config file

kubectl reads a config file to interact with kubernetes cluster, the default config locates at `~/.kube/config`

```
$ cat ~/.kube/config
apiVersion: v1
clusters:
- cluster:
    certificate-authority: /Users/deyuandeng/.minikube/ca.crt
    server: https://192.168.99.100:8443
  name: minikube
contexts:
- context:
    cluster: minikube
    user: minikube
  name: minikube
current-context: minikube
kind: Config
preferences: {}
users:
- name: minikube
  user:
    client-certificate: /Users/deyuandeng/.minikube/apiserver.crt
    client-key: /Users/deyuandeng/.minikube/apiserver.key
```

Here are three important top-level concepts: `clusters`, `users` and `contexts`.

The cluster we are using is called `minikube`, whose server address is https://192.168.99.100:8443,
and its certificate authority locates at `/Users/deyuandeng/.minikube/ca.crt`. Yours might be different.

When we send request using the config file, we are acting as user `minikube` (To be precise, the real
user name comes from certificate common name, but we'll skip it for now).

At last, `context` is a combination of various configs, for example, one context for cluster `minikube`
and user `minikube`, another context for cluster `example` and user `minikube` (which means user
`minikube` can access both `minikube` and `example` cluster).

## Refereneces

- [kubectl overview](https://kubernetes.io/docs/user-guide/kubectl-overview/)

# Kubernetes node

节点（Node）是物理机或虚拟机，他们组成了 kubernetes 的资源池。Master 节点负责资源调度、集群状态控制等，
Node 节点负责运行用户应用，承接负载。我们会在后续的章节中介绍具体的架构，现在我们只关心如何通过命令行与 kubernetes
接口交互管理节点。

## Node information

在 kubernetes 中，我们可以通过 `kubectl get nodes` 命令来获取所有节点信息：

```
$ kubectl get nodes
NAME       STATUS    AGE       VERSION
minikube   Ready     26d       v1.7.0
```

以上输出表明当前集群有 1 个节点。注意，我们无法完全从命令行区分 master 节点和 node 节点。这里 minikube
节点即是 master 也是 node，也就是说，minikube 主机即负责调度和管理，也负责用户容器的运行时。一般在生产环境中，
我们不会在 master 上运行用户容器。但是如果主机数量非常少的情况下可以考虑，前提是预留足够的资源给 master。

不承载用户容器的主机需要加上 SchedulingDisabled 的状态，例如：

```
$ kubectl get nodes
NAME                     STATUS                     AGE
i-2ze0tfg75y5plzvnd29h   Ready,SchedulingDisabled   2d
i-2ze0woc5l1230xs5zxry   Ready                      2d
i-2ze14a3m7riw0l18oemg   Ready                      2d
i-2ze14a3m7riw0l18oemh   Ready                      2d
i-2ze1nwnt9tc3wg83rsru   Ready                      2d
i-2ze8klh097pl5dksagn0   Ready                      2d
i-2zea47skez7ye2xr438v   Ready                      2d
i-2zea8dqxcrd3ew22ypwa   Ready                      2d
i-2zegwzvfbqavm6za189b   Ready                      2d
i-2zeipz60pxlvxmiloh9n   Ready                      2d
i-2zej57gmopp2yceoa6bu   Ready                      2d
```

## Node details

我们可以通过 `kubectl describe nodes` 来了解节点的详情。下面显示了 minikube 节点的详情，
我们可以暂时不关心输出内容的细节。

```
$ kubectl describe nodes minikube
Name:                   minikube
Role:
Labels:                 beta.kubernetes.io/arch=amd64
                        beta.kubernetes.io/os=linux
                        kubernetes.io/hostname=minikube
Annotations:            alpha.kubernetes.io/provided-node-ip=192.168.99.100
                        node.alpha.kubernetes.io/ttl=0
                        volumes.kubernetes.io/controller-managed-attach-detach=true
Taints:                 <none>
CreationTimestamp:      Sat, 12 Aug 2017 19:11:13 +0800
Conditions:
  Type                  Status  LastHeartbeatTime                       LastTransitionTime                      Reason                          Message
  ----                  ------  -----------------                       ------------------                      ------                          -------
  OutOfDisk             False   Fri, 08 Sep 2017 14:01:41 +0800         Wed, 06 Sep 2017 19:00:03 +0800         KubeletHasSufficientDisk        kubelet has sufficient disk space available
  MemoryPressure        False   Fri, 08 Sep 2017 14:01:41 +0800         Wed, 06 Sep 2017 19:00:03 +0800         KubeletHasSufficientMemory      kubelet has sufficient memory available
  DiskPressure          False   Fri, 08 Sep 2017 14:01:41 +0800         Wed, 06 Sep 2017 19:00:03 +0800         KubeletHasNoDiskPressure        kubelet has nodisk pressure
  Ready                 True    Fri, 08 Sep 2017 14:01:41 +0800         Fri, 08 Sep 2017 13:46:59 +0800         KubeletReady                    kubelet is posting ready status
Addresses:
  InternalIP:   192.168.99.100
  Hostname:     minikube
Capacity:
 cpu:           2
 memory:        2048444Ki
 pods:          110
Allocatable:
 cpu:           2
 memory:        1946044Ki
 pods:          110
System Info:
 Machine ID:                    b08a4d8ca72546baa1f6b8df26244529
 System UUID:                   96B8F4A3-C4A4-4B73-885C-BC3679AD55B2
 Boot ID:                       5d7ff765-02a2-4fcd-96e6-eed9e56c7d21
 Kernel Version:                4.9.13
 OS Image:                      Buildroot 2017.02
 Operating System:              linux
 Architecture:                  amd64
 Container Runtime Version:     docker://1.12.6
 Kubelet Version:               v1.7.0
 Kube-Proxy Version:            v1.7.0
ExternalID:                     minikube
Non-terminated Pods:            (3 in total)
  Namespace                     Name                                    CPU Requests    CPU Limits      Memory Requests Memory Limits
  ---------                     ----                                    ------------    ----------      --------------- -------------
  kube-system                   kube-addon-manager-minikube             5m (0%)         0 (0%)          50Mi (2%)       0 (0%)
  kube-system                   kube-dns-910330662-vd9mn                260m (13%)      0 (0%)          110Mi (5%)      170Mi (8%)
  kube-system                   kubernetes-dashboard-gflmn              0 (0%)          0 (0%)          0 (0%)          0 (0%)
Allocated resources:
  (Total limits may be over 100 percent, i.e., overcommitted.)
  CPU Requests  CPU Limits      Memory Requests Memory Limits
  ------------  ----------      --------------- -------------
  265m (13%)    0 (0%)          160Mi (8%)      170Mi (8%)
Events:
  FirstSeen     LastSeen        Count   From                    SubObjectPath   Type            Reason                  Message
  ---------     --------        -----   ----                    -------------   --------        ------                  -------
  14m           14m             1       kubelet, minikube                       Normal          Starting                Starting kubelet.
  14m           14m             1       kubelet, minikube                       Normal          NodeAllocatableEnforced Updated Node Allocatable limit across pods
  14m           14m             1       kubelet, minikube                       Normal          NodeHasSufficientDisk   Node minikube status is now: NodeHasSufficientDisk
  14m           14m             1       kubelet, minikube                       Normal          NodeHasSufficientMemory Node minikube status is now: NodeHasSufficientMemory
  14m           14m             1       kubelet, minikube                       Normal          NodeHasNoDiskPressure   Node minikube status is now: NodeHasNoDiskPressure
  14m           14m             1       kubelet, minikube                       Warning         Rebooted                Node minikube has been rebooted, boot id: 5d7ff765-02a2-4fcd-96e6-eed9e56c7d21
  14m           14m             1       kubelet, minikube                       Normal          NodeNotReady            Node minikube status is now: NodeNotReady
  14m           14m             1       kube-proxy, minikube                    Normal          Starting                Starting kube-proxy.
  14m           14m             1       kubelet, minikube                       Normal          NodeReady               Node minikube status is now: NodeReady
```

## Readings

- [kubernetes nodes](https://kubernetes.io/docs/concepts/architecture/nodes/)

# Kubernetes Namespace & ResourceQuota

Kubernetes namespace 是用来构建虚拟的资源池；使用 kubernetes namespace，管理员可以将 kubernetes
划分成多个虚拟的区域，不同的项目或者团队可以使用不同的 namespace，达到了共享 kubernetes 集群资源的目的。此外，
namespace 也被用来划分命名空间，即不同 namespace 里的资源可以取相同的名字，相同 namespace 内的资源不能重名。

## Namespaces

通过 `kubectl create -f`，我们可以轻松地创建一个 namespace：

```
$ kubectl create -f resources/ns.yaml
namespace "tutorial" created
```

然后通过 `kubectl get ns`，可以看到刚才创建的 namespace

```
$ kubectl get ns
NAME          STATUS    AGE
default       Active    26d
kube-public   Active    26d
kube-system   Active    26d
tutorial      Active    6m
```

这里 `ns` 是 `namespace` 的缩写。输出内容中的 `kube-public`, `kube-system`, `default` 都是 kubernetes
默认创建的 namespace，用来放置系统相关的资源。

```sh
$ kubectl describe ns tutorial
Name:           tutorial
Labels:         <none>
Annotations:    <none>
Status:         Active

No resource quota.

No resource limits.
```

同样，`kubectl describe` 会提供 namespace 的详细信息。这里提示我们 `No resource quota`, `No resource limits`，
接下来我们来看一看 quota 和 limit 的意思。

## Resource quota

默认情况下，namespace 只提供的名字的隔离，并没有提供资源的限制（Quota）。也就是说一个 namespace
的用户可以创建任意多的资源，直到将集群的所有资源用光。为了解决这个问题，我们可以通过创建 ResourceQuota
资源来限制某个 namespace 可以使用的资源量：这里的资源除了计算存储资源，还包括 kubernetes 的资源，例如
Pod 数量。

同样地，我们可以通过 `kubectl create -f` 创建 ResourceQuota，该 quota 限制了 tutorial namespace
只能请求 1 个 CPU 和 1Gi 内存，最多只能使用 2 个 CPU 和 2Gi 内存。这里，请求指的是 kubernetes
在调度时容器时会寻找至少有 1 个 CPU 和 1Gi 内存的节点。最多使用指的是当容器可以使用超过其请求的 1 个 CPU
数量，但是一定不可能超过 2 个 CPU。kubernetes 的这个设计目的是提供更加灵活的资源模型，支持超卖。

```
$ kubectl create -f resources/quota.yaml
resourcequota "tutorial-quota" created
```

查看 ResourceQuota 细节：

```
$ kubectl describe quota -n tutorial
Name:           tutorial-quota
Namespace:      tutorial
Resource        Used    Hard
--------        ----    ----
limits.cpu      0       2
limits.memory   0       2Gi
requests.cpu    0       1
requests.memory 0       1Gi
```

如果我们尝试在 tutorial namespace 下创建超过配额的资源，kubernetes 会直接返回错误：

```
$ kubectl create -f resources/pod_exceeds_quota.yaml
Error from server (Forbidden): error when creating "resources/pod_exceeds_quota.yaml": pods "pod" is forbidden: exceeded quota: tutorial-quota, requested: requests.cpu=2, used: requests.cpu=0, limited: requests.cpu=1
```

通过以上实验，我们初步了解了 namespace, resource quota 的概念。同时，对 kubectl 命令行也应该有了更多
的认识。接下来我们将介绍 kubernetes 中另外几个重要的概念。

## Readings

- [kubernetes namespace](https://kubernetes.io/docs/concepts/overview/working-with-objects/namespaces/)
- [namespace walkthrough](https://kubernetes.io/docs/tasks/administer-cluster/namespaces-walkthrough/)
- [kubernetes resource quotas](https://kubernetes.io/docs/concepts/policy/resource-quotas/)

# Kubernetes Pod & Deployment

当我们有一个 kubernetes 集群之后，可以开始部署应用了。在 kubernetes 的世界里，Pod 是运行应用的载体。
Pod 是由多个容器组成、是 kubernetes 的最小调度单元、Pod 共享底层资源、由 kubernetes 来管理生命周期。
然而，一般情况下，我们并不直接创建 Pod，而是通过 Deployment 来创建 Pod，由 Deployment 来负责创建、
更新、维护其所管理的所有 Pods。

一旦我们通过 Deployment 创建 Pod，会有一个 Deployment 控制器不断监控所有 Pod 的状态。例如，如果 Pod
运行的机器宕机了，那么 Deployment 控制器会在另一台机器上重新启动一个 Pod。接下来，我们将部署一个应用，
部署之后，集群将会达到下图所示的状态。

<p align="center"><img src="./images/kubernetes_cluster.png" height="350px" width="auto"></p>
<p align="center"><i>Image source: kubernetes guide</i></p><br>

这里六边形方框代表一个 kubernetes 节点，正方体代表一个 Pod。后面，我们将通过 kubectl 来管理应用。

## Create Deployment

我们可以通过 yaml 文件创建 Deployment，从而创建应用（类似之前创建 ResourceQuota 的方式）。为了简化
应用部署，kubernetes 提供了 run 子命令来快速创建应用。

```
$ kubectl run nginx --image=cargo.caicloud.io/caicloud/nginx:1.9.7 --replicas=1 --requests="cpu=100m,memory=256Mi" --limits="cpu=200m,memory=512Mi" -n tutorial
deployment "nginx" created
```

执行该命令之后，kubernetes 在集群中寻找一台满足需求的机器运行节点，然后该节点上的 agent 启动该应用。注意，
由于我们在 tutorial namespace 创建了 ResourceQuota，我们在创建应用时必须指定应用所使用的资源，否则无法成功创建应用。

## Get Deployment

创建好后，我们可以通过 `kubectl get deployment` 来查看刚刚创建的 Deployment：

```
$ kubectl get deployment -n tutorial
NAME      DESIRED   CURRENT   UP-TO-DATE   AVAILABLE   AGE
nginx     1         1         1            1           3m
```

从输出可以看出，我们请求创建一个 Pod (replica)，kubernetes 已经帮我们成功创建了一个。

## Get Pods

上面我们讲到，真正运行应用的载体是 Pod，Deployment 是用来管理 Pod 的资源（比如重启失败的 Pod），我们可以通过
`kubectl get pods` 来查看当前创建的 Pod。

```
$ kubectl get pods -n tutorial
NAME                     READY     STATUS    RESTARTS   AGE
nginx-3035859230-d2sfd   1/1       Running   0          4m
```

可以看到，现在有一个 Pod 在运行中；我们可以通过 `kubectl get pods -o wide` 来查看 Pod 运行的主机，
或者通过 `kubectl describe pods nginx-3035859230-d2sfd` 来查看 Pod 更加详细的信息（describe
中包含非常多的信息，我们将在后面介绍）。

```
$ kubectl get pods -n tutorial -o wide
NAME                     READY     STATUS    RESTARTS   AGE       IP           NODE
nginx-3035859230-d2sfd   1/1       Running   0          5m        172.17.0.2   minikube
```

## Get Pod Logs

当我们部署要应用之后，可以通过 `kubectl logs <pod name>` 和 `kubectl exec <pod name>` 与 Pod 交互。

```
$ kubectl logs nginx-3035859230-d2sfd -n tutorial
```

由于没有任何请求，nginx pod 日志暂时为空。现在我们尝试访问 nginx pod。由于 `minikube` 本身是运行在虚拟机中，
因此我们需要登录虚拟机访问 nginx pod (nginx pod ip: 172.17.0.2)。

```
$ minikube ssh

# in minikube vm
$ curl 172.17.0.2
<!DOCTYPE html>
<html>
...
</html>
```

此时再查看 nginx，可以看到 nginx 的访问日志。

```
$ kubectl logs nginx-3035859230-d2sfd -n tutorial
172.17.0.1 - - [08/Sep/2017:09:28:57 +0000] "GET / HTTP/1.1" 200 612 "-" "curl/7.53.0" "-"
```

## Execute command in Pod

有时候，我们需要在 Pod 中执行命令，可以通过 `kubectl exec`：

```
$ kubectl exec nginx-3035859230-d2sfd -n tutorial -- ls -l
total 64
drwxr-xr-x   2 root root 4096 Sep  8 09:17 bin
drwxr-xr-x   2 root root 4096 Aug 26  2015 boot
drwxr-xr-x   5 root root  380 Sep  8 09:17 dev
drwxr-xr-x   1 root root 4096 Sep  8 09:17 etc
drwxr-xr-x   2 root root 4096 Aug 26  2015 home
drwxr-xr-x   9 root root 4096 Sep  8 09:17 lib
drwxr-xr-x   2 root root 4096 Sep  8 09:17 lib64
drwxr-xr-x   2 root root 4096 Dec  4  2015 media
drwxr-xr-x   2 root root 4096 Dec  4  2015 mnt
drwxr-xr-x   2 root root 4096 Dec  4  2015 opt
dr-xr-xr-x 181 root root    0 Sep  8 09:17 proc
drwx------   2 root root 4096 Sep  8 09:17 root
drwxr-xr-x   1 root root 4096 Sep  8 09:17 run
drwxr-xr-x   2 root root 4096 Sep  8 09:17 sbin
drwxr-xr-x   2 root root 4096 Dec  4  2015 srv
dr-xr-xr-x  12 root root    0 Sep  8 09:17 sys
drwxrwxrwt   2 root root 4096 Dec  5  2015 tmp
drwxr-xr-x  10 root root 4096 Sep  8 09:17 usr
drwxr-xr-x  11 root root 4096 Sep  8 09:17 var
```

注意，我们通过双横线（“--”）区分本地终端命令和容器中执行的命令；当执行的命令只有一个单词的时候，可以省略。
如果容器中有 shell，我们也可以启动一个远程终端：

```
$ kubectl exec -it nginx-3035859230-d2sfd -n tutorial bash
root@nginx-3035859230-d2sfd:/# ls -l
total 64
drwxr-xr-x   2 root root 4096 Sep  8 09:17 bin
drwxr-xr-x   2 root root 4096 Aug 26  2015 boot
drwxr-xr-x   5 root root  380 Sep  8 09:17 dev
drwxr-xr-x   1 root root 4096 Sep  8 09:17 etc
drwxr-xr-x   2 root root 4096 Aug 26  2015 home
drwxr-xr-x   9 root root 4096 Sep  8 09:17 lib
drwxr-xr-x   2 root root 4096 Sep  8 09:17 lib64
drwxr-xr-x   2 root root 4096 Dec  4  2015 media
drwxr-xr-x   2 root root 4096 Dec  4  2015 mnt
drwxr-xr-x   2 root root 4096 Dec  4  2015 opt
dr-xr-xr-x 181 root root    0 Sep  8 09:17 proc
drwx------   2 root root 4096 Sep  8 09:17 root
drwxr-xr-x   1 root root 4096 Sep  8 09:17 run
drwxr-xr-x   2 root root 4096 Sep  8 09:17 sbin
drwxr-xr-x   2 root root 4096 Dec  4  2015 srv
dr-xr-xr-x  12 root root    0 Sep  8 09:17 sys
drwxrwxrwt   2 root root 4096 Dec  5  2015 tmp
drwxr-xr-x  10 root root 4096 Sep  8 09:17 usr
drwxr-xr-x  11 root root 4096 Sep  8 09:17 var
```

使用 `ctrl + d` 可以退出远程终端。

## Readings

- [kubernetes pod](https://kubernetes.io/docs/concepts/workloads/pods/pod/)

# Kubernetes Service

接下来我们通过一连串的命令学习 kubernetes service。kubernetes service 有以下几个作用：
- 提供固定的 IP。由于 Pod 可以随时启停，Pod IP 可能随时都会变化，例如上面 nginx pod 重启之后 IP
  可能不再是 172.17.0.2。Service 为 Pods 提供的固定 IP，其他服务可以通过 Service IP 找到提供服务的
  Pods。
- 提供负载均衡。Service 由多个 Pods 组成，kubernetes 对组成 Service 的 Pods 提供的负载均衡方案，
  例如随机访问、基于 Client IP 的 session affinity。
- 服务发现。集群中其他服务可以通过 Service 名字访问后端服务（DNS），也可以通过环境变量访问。

下图是 kubernetes Pods, Service 的典型关系。下图有两个 Deployment: A 和 B。其中 Deployment A
创建了一个 Pods（黄色），Deployment B 创建了三个 Pod（绿色）。我们可以创建两个 Service: A 和 B。
Service A 管理由 Deployment A 创建的 Pods，Service B 管理 Deployment B 创建的 Pods。可以看到，
Service A 和 Service B 都有自己独立的 IP。无论他们所管理的容器如何变化， Service 的 IP 都不会变化。

<p align="center"> <img src="./images/deployment_service.png" height="400px" width="auto"></p>
<p align="center"><i>Image source: kubernetes guide</i></p><br>

## Create service

与其他资源相同，我们可以通过 `kubectl create -f` 加文件名创建 Service。但类似 Deployment，kubernetes
提供了快捷命令让我们能快速创建 Service。

```
$ kubectl expose deployment nginx --port 80 -n tutorial
service "nginx" exposed
```

## Get service

通过 `kubectl get service` 命令可以查看 service 的详细信息：

```
$ kubectl get svc nginx -n tutorial
NAME      CLUSTER-IP   EXTERNAL-IP   PORT(S)   AGE
nginx     10.0.0.238   <none>        80/TCP    4m
```

可以看到，Service 具有一个固定的 IP 10.0.0.238。同样，通过 describe 可以看到更多详细的信息：

```
$ kubectl describe svc nginx -n tutorial
Name:                   nginx
Namespace:              tutorial
Labels:                 run=nginx
Annotations:            <none>
Selector:               run=nginx
Type:                   ClusterIP
IP:                     10.0.0.238
Port:                   <unset> 80/TCP
Endpoints:              172.17.0.2:80
Session Affinity:       None
Events:                 <none>
```

其中，Endpoint 表明 Service 所选中的 PodIP:PodPort。我们可以查看 Pod 信息来验证：

```
$ kubectl get pods -o wide -n tutorial
NAME                     READY     STATUS    RESTARTS   AGE       IP           NODE
nginx-3035859230-d2sfd   1/1       Running   0          1h        172.17.0.2   minikube
```

## Query service

创建 Service 后，我们可以在主机上直接访问该 Service。下面两条命令实际上访问的都是同一个后端。第一个
命令通过 Service IP 访问，第二个命令通过 Pod IP 访问。

通过 Service IP 访问：

```
$ minikube ssh
$ curl 10.0.0.238
<!DOCTYPE html>
<html>
...
</html>
```

通过 Pod IP 访问：

```
$ minikube ssh
$ curl 172.17.0.2
<!DOCTYPE html>
<html>
...
</html>
```

上面的命令创建了一个名为 nginx 的 Service，并使用 80 作为服务端口。这里，我们的 nginx 容器监听的是容
器的 80 端口，该端口是 Pod IP 所监听的端口；我们可以在 Service 上使用不同的端口。例如，若我们想暴露的
服务端口是 8080 端口，需要使用 port 和 targetPort 选项。

首先，删除已经创建的 Service：

```
$ kubectl delete svc nginx -n tutorial
service "nginx" deleted
```

之后，创建 Service：

```
$ kubectl expose deployment nginx --port 8080 --target-port 80 -n tutorial
service "nginx" exposed
```

尝试用 8080 端口访问服务

```
$ kubectl get svc nginx -n tutorial
NAME      CLUSTER-IP   EXTERNAL-IP   PORT(S)    AGE
nginx     10.0.0.37    <none>        8080/TCP   15m

$ minikube ssh
$ curl 10.0.0.37:8080
<!DOCTYPE html>
<html>
...
</html>
```

## NodePort service

上述创建的 Service 只能被集群内部的节点和 Pod 访问，并不能被外部访问。我们可以通过两种方式暴露服务：NodePort
和 LoadBalancer。NodePort 通过在每个节点打开一个端口对外提供服务，LoadBalancer 通过创建一个外部负载均衡器
（例如公有云负载均衡器）来对外提供服务。这里我们尝试使用 NodePort。

首先，删除已有的 Service：

```
$ kubectl delete svc nginx -n tutorial
service "nginx" deleted
```

通过 NodePort 暴露服务，注意这里使用了 `--type NodePort`：

```
$ kubectl expose deployment nginx --port 80 --type NodePort -n tutorial
service "nginx" exposed
```

查看 Service 的细节：

```
$ kubectl get svc nginx -n tutorial
NAME      CLUSTER-IP   EXTERNAL-IP   PORT(S)        AGE
nginx     10.0.0.134   <nodes>       80:30736/TCP   15m
```

```
$ kubectl describe svc nginx -n tutorial
Name:                   nginx
Namespace:              tutorial
Labels:                 run=nginx
Annotations:            <none>
Selector:               run=nginx
Type:                   NodePort
IP:                     10.0.0.134
Port:                   <unset> 80/TCP
NodePort:               <unset> 30736/TCP
Endpoints:              172.17.0.2:80
Session Affinity:       None
Events:                 <none>
```

从以上输出可以看到，nginx 服务打开了节点的 30736 端口（每个节点），我们可以通过 NodeIP:NodePort 访问服务。

```
$ curl $(minikube ip):30736
<!DOCTYPE html>
<html>
...
</html>
```

## Readings

- [kubernetes service](https://kubernetes.io/docs/concepts/services-networking/service/). Please read as much as you can, we'll come back to service again.
- [run application with service](https://kubernetes.io/docs/tasks/access-application-cluster/connecting-frontend-backend/).
- [ports in kubernetes](https://speakerdeck.com/thockin/kubernetes-a-very-brief-explanation-of-ports)

# Kubernetes Label

Service 通过 selector & label 来选取它所管理的 Pod，同样 Deployment 也是通过 selector & label
选取它所管理的 Pod。因为我们是通过 Deployment 创建的 Pod，因此 Deployment 的 selector 一定是匹配
Pod 的 label。如果我们想让 Service 选择与 Deployment 相同的 Pods，我们需要将 Service 的 selector
设为与 Deployment 相同。在上面的实验中，我们使用 `kubectl expose deployment nginx` 的时候，kubernetes
默认将 Service 的 selector 设置成与 Deployment 相同的 selector。下图对 label 做了详细的标注。

<p align="center"> <img src="./images/labels.png" height="500px" width="auto"></p>
<p align="center"><i>Image source: kubernetes guide</i></p><br>

由上图可以看出：

| Resource | selector |
|----------|----------|
| Deployment A, Service A, Pod A | app=A |
| Deployment B, Service B, Pod B | app=B |

Label 可以在创建时添加，也可以在运行时添加或修改。在运行时修改会影响集群的状态，因为现有的 selector & label
结构会被改变。

## View selector & label

从下面的输出可以看到，上述创建的 Deployment 和 Service 的 Selector 都是 `run=nginx`。Pod 具有 Label
`pod-template-hash=3035859230,run=nginx`，因此他们都选中了 `nginx-3035859230-d2sfd` 这个 Pod （只要
Pod label 的子集满足即可；这里的 `pod-template-hash=3035859230` Label 是 kubernetes 自动创建）。

```
$ kubectl describe deployment nginx -n tutorial
Name:                   nginx
Namespace:              tutorial
CreationTimestamp:      Fri, 08 Sep 2017 17:17:20 +0800
Labels:                 run=nginx
Annotations:            deployment.kubernetes.io/revision=1
Selector:               run=nginx
...
```

```
$ kubectl describe svc nginx -n tutorial
Name:                   nginx
Namespace:              tutorial
Labels:                 run=nginx
Annotations:            <none>
Selector:               run=nginx
...
```

```
$ kubectl describe pods nginx-3035859230-d2sfd -n tutorial
Name:           nginx-3035859230-d2sfd
Namespace:      tutorial
Node:           minikube/192.168.99.100
Start Time:     Fri, 08 Sep 2017 17:17:20 +0800
Labels:         pod-template-hash=3035859230
                run=nginx
```

## Label operations

kubectl 支持对资源的 label 进行管理，比如我们可以通过 -l 选项查看仅具有某个 label 的资源。

```
$ kubectl get pods -l run=nginx -n tutorial
NAME                     READY     STATUS    RESTARTS   AGE
nginx-3035859230-d2sfd   1/1       Running   0          3h
```

```
$ kubectl get svc -l run=nginx -n tutorial
NAME      CLUSTER-IP   EXTERNAL-IP   PORT(S)        AGE
nginx     10.0.0.134   <nodes>       80:30736/TCP   33m
```

当没有任何资源满足 label 时，输出为空：

```
$ kubectl get svc -l run=apache -n tutorial
```

kubectl 支持对资源的 label 进行操作，如下所示：

```
$ kubectl get pods -n tutorial
NAME                    READY     STATUS    RESTARTS   AGE
nginx-689083664-qduk1   1/1       Running   0          2h

$ kubectl label pod nginx-689083664-qduk1 app=v1 -n tutorial
pod "nginx-689083664-qduk1" labeled

$ kubectl describe pods nginx-689083664-qduk1 -n tutorial
Name:           nginx-689083664-qduk1
Namespace:      cy-20
Node:           i-2ze14a3m7riw0l18oemh/10.44.158.16
Start Time:     Tue, 22 Nov 2016 15:20:54 +0800
Labels:         app=v1
                pod-template-hash=689083664
                run=nginx
Status:         Running
IP:             192.168.65.7
Controllers:    ReplicaSet/nginx-689083664
```

注意这里我们是对 Pod 添加了一个 label，并不会影响 Deployment 与 Pod 之间的关系。因为 Pod 保持 Label
`run=nginx`，依然会被 Deployment 选中。

## Readings

- [label and selector](https://kubernetes.io/docs/concepts/overview/working-with-objects/labels/)

# Kubernetes Deployment Operations

## Scale up using kubectl

接下来我们将学习 kubernetes Deployment 的另外两个操作：水平扩展应用和更新应用。下图中，Deployment A
有一个 Pod 在运行，Service A 管理该 Pod。

<p align="center"><img src="./images/deployment_initial.png" height="350px" width="auto"></p>
<p align="center"><i>Image source: kubernetes guide</i></p><br>

通过调整 Deployment 的副本数量，我们可以将 Pod 的数量调整到 4 个。与此同时，Service 会感知到同样 label 的
Pod 被扩容到了 4 个，会将流量导到所有 Pod（而不是只有最开始的 Pod）。

<p align="center"><img src="./images/deployment_scale.png" height="350px" width="auto"></p>
<p align="center"><i>Image source: kubernetes guide</i></p><br>

首先创建 Deployment 和 Service（ 确保前面教程的 Deployment 和 Service 已经被删除）：

```
kubectl run nginx --image=index.caicloud.io/caicloud/nginx:1.9.7 --replicas=1 --requests="cpu=100m,memory=256Mi" --limits="cpu=200m,memory=512Mi" -n tutorial
kubectl expose deployment nginx --port 80 --name=nginx -n tutorial
```

接下来，我们可以通过 `kubectl scale` 子命令将 Pod 数量扩容到四个：

```
$ kubectl get deployments -n tutorial
NAME      DESIRED   CURRENT   UP-TO-DATE   AVAILABLE   AGE
nginx     1         1         1            1           3m

$ kubectl scale deployments nginx --replicas=4 -n tutorial
deployment "nginx" scaled

$ kubectl get deployments -n tutorial
NAME      DESIRED   CURRENT   UP-TO-DATE   AVAILABLE   AGE
nginx     4         4         4            4           3m

$ kubectl get pods -n tutorial -o wide
NAME                     READY     STATUS    RESTARTS   AGE       IP           NODE
nginx-3035859230-6010x   1/1       Running   0          4m        172.17.0.4   minikube
nginx-3035859230-8tzxc   1/1       Running   0          24s       172.17.0.6   minikube
nginx-3035859230-9ts45   1/1       Running   0          24s       172.17.0.5   minikube
nginx-3035859230-m5g7k   1/1       Running   0          24s       172.17.0.7   minikube
```

可以看到最后三个 Pod 的运行时间是 24s，是最新生成的容器。

## View service

之前提到，Service 会感知到 Pods 的变化，在所有的 Pods 中负载均衡，我们可以通过 kubectl 查看。

```
$ kubectl describe service nginx -n tutorial
Name:                   nginx
Namespace:              tutorial
Labels:                 run=nginx
Annotations:            <none>
Selector:               run=nginx
Type:                   NodePort
IP:                     10.0.0.159
Port:                   <unset> 80/TCP
NodePort:               <unset> 32499/TCP
Endpoints:              172.17.0.4:80,172.17.0.5:80,172.17.0.6:80 + 1 more...
Session Affinity:       None
Events:                 <none>
```

Service nginx 已经将后端 Endpoints 扩容到所有的 4 个 Pods。

## Scale down using kubectl

我们也可以通过同样的命令缩容（kubectl scale）。Deployment 不会区分是扩容命令或是缩容命令，它只关心将实例的数量调整到指定的数量。

```
$ kubectl scale deployments nginx --replicas=2 -n tutorial
deployment "nginx" scaled

$ kubectl get pods -n tutorial
NAME                     READY     STATUS    RESTARTS   AGE
nginx-3035859230-6010x   1/1       Running   0          11m
nginx-3035859230-9ts45   1/1       Running   0          7m
```

## Update deployment

接下来，我们将了解 kubernetes 如何进行应用更新。见下图，我们目前有四个运行中的应用：

<p align="center"><img src="./images/deployment_update_initial.png" height="350px" width="auto"></p>
<p align="center"><i>Image source: kubernetes guide</i></p><br>

当我们更新容器镜像时，kubernetes 会启动一个新 Pod 并关闭一个老 Pod。下图中，紫色的 Pod 为 kubernetes
新创建的 Pod，淡绿色 Pod 为老 Pod。Service 会停止向老 Pod 导流。

<p align="center"><img src="./images/deployment_update_1.png" height="350px" width="auto"></p>
<p align="center"><i>Image source: kubernetes guide</i></p><br>

第一个 Pod 更新成功后，Deployment 会更新第二个 Pod。如下图所示，紫色两个 Pod 为 Deployment 创建的新 Pod。

<p align="center"><img src="./images/deployment_update_2.png" height="350px" width="auto"></p>
<p align="center"><i>Image source: kubernetes guide</i></p><br>

最后，Deployment 将所有的 Pod 都更新完毕。

<p align="center"><img src="./images/deployment_update_done.png" height="350px" width="auto"></p>
<p align="center"><i>Image source: kubernetes guide</i></p><br>

## Update via setting image

接下来，我们通过命令行了解 kubernetes 更新应用的过程。

```
$ kubectl set image deployments nginx nginx=cargo.caicloud.io/caicloud/nginx:1.9.3 -n tutorial
deployment "nginx" image updated

$ kubectl get pods -n tutorial
NAME                     READY     STATUS              RESTARTS   AGE
nginx-3035859230-rqzgn   0/1       Running             0          26s
nginx-785607266-d6vrc    1/1       ContainerCreating   0          6s
nginx-785607266-wgf4b    0/1       ContainerCreating   0          6s
```

过一段时间后，所有 Pod 都已经更新了：

```
$ kubectl get pods -n tutorial
NAME                    READY     STATUS    RESTARTS   AGE
nginx-785607266-d6vrc   1/1       Running   0          1m
nginx-785607266-wgf4b   1/1       Running   0          1m
```

分析一下上述命令，`kubectl set image` 将 Deployment 中的 nginx 镜像版本改为 1.9.3；运行该命令之后，发现
kubernetes 删掉了一个现有的 Pod，然后重新启动了两个新的 Pod（我们可以从一串数字中看出，"785607266" 是新 Pod
的 Hash 值，"3035859230" 是老 Pod 的 Hash 值）。等待一段时间后再次查询 Pods，发现所有新的 Pods 已经上线。
整个过程中，我们都可以尝试去访问 nginx 服务，注意其版本的变化。

```
$ curl $(minikube ip):32499/version
<html>
...
<hr><center>nginx/1.9.3</center>
</html>
```

其中 32499 是 Service 暴露的 NodePort 端口。

## Deployment rollout

rollout 子命令可以用来查询部署的状态，以及回滚等操作。使用 `kubectl rollout status` 可以查询部署的状态。

```
$ kubectl rollout status deployment nginx -n tutorial
deployment nginx successfully rolled out
```

上面的状态说明之前部署的 Deployment 已经正常部署了。如果我们想要回滚到之前的版本，可以使用
`kubectl rollout undo` 命令。

首先，当前 nginx 处于 1.9.3 版本：

```
$ curl $(minikube ip):32499/version
<html>
...
<hr><center>nginx/1.9.3</center>
</body>
</html>
```

接下来使用回滚操作：

```
$ kubectl rollout undo deployment nginx -n tutorial
deployment "nginx" rolled back

$ kubectl get pods -n tutorial
NAME                     READY     STATUS    RESTARTS   AGE
nginx-3035859230-m28qm   1/1       Running   0          12s
nginx-3035859230-t3f9p   1/1       Running   0          11s
```

使用 rollout undo 之后，nginx 的版本回到了 set image 之前的版本：

```
$ curl $(minikube ip):32499/version
<html>
...
<hr><center>nginx/1.9.7</center>
</body>
</html>
```

# Kubernetes Yaml/Json File

在 Kubernetes 101 实验中，我们都是通过 kubectl 提供的快捷命令来创建、管理资源。实际上，对于 kubernetes
而言，所有的操作都是以 yaml 文件为主。我们之前所使用的命令，只是方便用户快速修改 yaml 中经常需要修改的字段。
接下来，我们学习 kubernetes yaml/json 文件格式和使用方法。首先，kubernetes yaml 文件的基本格式如下代码所示
（这里展示的是一个 Pod 的 yaml 文件，并且有部分裁剪）。kubernetes yaml 整体分为 5 个部分：apiVersion,
kind, metadata, spec, status；其中 apiVersion 表明当前 kubernetes API 的大版本；kind 表明当前操作的资源类型；
metadata 是资源的元数据，对于每种资源都是固定的，例如资源的名字，所处的 namespace, label 等；spec
是用户对资源的 “说明书”，即用户对资源的各种配置信息；status 是资源当前的状态，kubernetes 会尽最大努力使
spec 和 status 相匹配。

```yaml
apiVersion: v1
kind: Pod
metadata:
  labels:
  name:
  namespace:
spec:
  containers:
  dnsPolicy: ClusterFirst
  nodeName: i-2zea47skez7ye2xr438v
  restartPolicy: Always
  securityContext: {}
  serviceAccount: default
  serviceAccountName: default
  terminationGracePeriodSeconds: 30
  volumes:
status:
  conditions:
  hostIP: 10.44.164.150
  phase: Running
  podIP: 192.168.79.9
  startTime: 2016-11-22T14:54:57Z
```

接下来我们学习使用 yaml 文件。

## Get resource yaml

用户可以通过 kubectl get <resource> <name> -o yaml 来获取已经部署的资源的 Yaml 文件，我们可以尝试获取之前通过
`kubectl run`, `kubectl expose` 等命令部署的 Deployment 和 Service。

```yaml
$ kubectl get pods nginx-3035859230-m28qm -n tutorial -o yaml
apiVersion: v1
kind: Pod
metadata:
  annotations:
    kubernetes.io/created-by: |
      {"kind":"SerializedReference","apiVersion":"v1","reference":{"kind":"ReplicaSet","namespace":"tutorial","name":"nginx-3035859230","uid":"9ca9578f-9790-11e7-a00f-0800277a7b6e","apiVersion":"extensions","resourceVersion":"3781"}}
  creationTimestamp: 2017-09-12T08:33:55Z
  generateName: nginx-3035859230-
...
spec:
  containers:
  - image: index.caicloud.io/caicloud/nginx:1.9.7
    imagePullPolicy: IfNotPresent
    name: nginx
    resources:
      limits:
        cpu: 200m
        memory: 512Mi
      requests:
        cpu: 100m
        memory: 256Mi
...
status:
  hostIP: 192.168.99.101
  phase: Running
  podIP: 172.17.0.4
  qosClass: Burstable
  startTime: 2017-09-12T08:33:55Z
...
```

```yaml
$ kubectl get svc nginx -n tutorial -o yaml
apiVersion: v1
kind: Service
metadata:
  creationTimestamp: 2017-09-12T08:28:45Z
  labels:
    run: nginx
  name: nginx
  namespace: tutorial
  resourceVersion: "3432"
  selfLink: /api/v1/namespaces/tutorial/services/nginx
  uid: 648aee4d-9794-11e7-a00f-0800277a7b6e
spec:
  clusterIP: 10.0.0.159
  externalTrafficPolicy: Cluster
  ports:
  - nodePort: 32499
    port: 80
    protocol: TCP
    targetPort: 80
  selector:
    run: nginx
  sessionAffinity: None
  type: NodePort
status:
  loadBalancer: {}
```

## Create resource using yaml

用户可通过 kubectl create -f <file-name> 创建 kubernetes 资源。用户不需要填入更多的信息，所有信息都已经在
yaml 文件中。我们在 101 中已经通过 yaml 文件创建过 namespace 和 resource quota。这里我们创建一个 Pod。

```
$ kubectl create -f resources/pod.yaml -n tutorial
pod "nginx" created

$ kubectl get pods -n tutorial
NAME                     READY     STATUS    RESTARTS   AGE
nginx                    1/1       Running   0          17s
nginx-3035859230-m28qm   1/1       Running   0          35m
nginx-3035859230-t3f9p   1/1       Running   0          35m
```

## Update resource yaml

创建应用之后，我们可以使用 kubectl 更新 yaml 文件并将更新返回给 kubernetes。

```
# Change image from 1.9.7 to 1.9.3
$ vim resources/pod.yaml

$ kubectl apply -f resources/pod.yaml -n tutorial
Warning: kubectl apply should be used on resource created by either kubectl create --save-config or kubectl apply
pod "nginx" configured
```

更新后查询更新结果：

```
$ kubectl get pods -n tutorial
NAME                     READY     STATUS    RESTARTS   AGE
nginx                    1/1       Running   1          2m
nginx-3035859230-m28qm   1/1       Running   0          38m
nginx-3035859230-t3f9p   1/1       Running   0          38m
```

```
$ kubectl describe pods nginx -n tutorial | grep "Image:" -C 5
Status:         Running
IP:             172.17.0.6
Containers:
  nginx:
    Container ID:       docker://e950843af300074e49d4d92a46115f673dcaa8abe37537ad1d6bda830eb63e55
    Image:              cargo.caicloud.io/caicloud/nginx:1.9.3
    Image ID:           docker-pullable://cargo.caicloud.io/caicloud/nginx@sha256:ece399fcec0b3d8afa3a5abbe85e965a1f22c5f36a788396b86b541eb7e714a8
    Port:               <none>
    State:              Running
      Started:          Tue, 12 Sep 2017 17:11:57 +0800
    Last State:         Terminated
```

注意镜像已经修改为 1.9.3。kubernetes 同时支持在线编辑 yaml 文件：

```
$ kubectl get pods -n tutorial
NAME                     READY     STATUS    RESTARTS   AGE
nginx                    1/1       Running   1          5m
nginx-3035859230-m28qm   1/1       Running   0          41m
nginx-3035859230-t3f9p   1/1       Running   0          41m

# Change image from 1.9.3 to 1.9.7
$ kubectl edit pods nginx -n tutorial
pod "nginx" edited
```

同样，镜像被修改为 1.9.7。
```
$ kubectl describe pods nginx -n tutorial | grep "Image:" -C 5
Status:         Running
IP:             172.17.0.6
Containers:
  nginx:
    Container ID:       docker://e1c683b356f89149288d0374dca3606530a484861b5afb4d295c94667b83cc27
    Image:              cargo.caicloud.io/caicloud/nginx:1.9.7
    Image ID:           docker-pullable://cargo.caicloud.io/caicloud/nginx@sha256:d33ae7b1dc9326bcaa91febdf37a8ea1a7340f7d6da0e2fde365a89a11201c62
    Port:               <none>
    State:              Running
      Started:          Tue, 12 Sep 2017 17:15:41 +0800
    Last State:         Terminated
```

## Readings

- [kubernetes deployment](https://kubernetes.io/docs/concepts/workloads/controllers/deployment/)
- [run application with deployment](https://kubernetes.io/docs/tasks/run-application/run-stateless-application-deployment/)

# Kubernetes Events

Kubernetes events 显示了 kubernetes 集群中所有的事件。不同于其他资源，kubernetes events 并不是由用户创建的资源，
而是由 kubernetes 系统组件创建，用以提示用户集群发生的各种事件。我们可以通过 kubectl get 命令来查询集群的事件。
默认情况下，event 会有 TTL，超过 TTL 之后 kubernetes 会将事件删掉。

```
$ kubectl get events -n tutorial
LASTSEEN   FIRSTSEEN   COUNT     NAME                     KIND         SUBOBJECT                TYPE      REASON                  SOURCE                  MESSAGE
59m        59m         1         nginx-1007456269-gkzzv   Pod                                   Normal    Scheduled               default-scheduler       Successfully assigned nginx-1007456269-gkzzv to minikube
59m        59m         1         nginx-1007456269-gkzzv   Pod                                   Normal    SuccessfulMountVolume   kubelet, minikube       MountVolume.SetUp succeeded for volume "default-token-cbj4c"
57m        59m         4         nginx-1007456269-gkzzv   Pod          spec.containers{nginx}   Normal    Pulling                 kubelet, minikube       pulling image "index.caicloud.io/caicloud/nginx:1.11.5"
57m        59m         4         nginx-1007456269-gkzzv   Pod          spec.containers{nginx}   Warning   Failed                  kubelet, minikube       Failed to pull image "index.caicloud.io/caicloud/nginx:1.11.5": rpc error: code = 2 desc = Error: image caicloud/nginx:1.11.5 not found
56m        59m         11        nginx-1007456269-gkzzv   Pod                                   Warning   FailedSync              kubelet, minikube       Error syncing pod
56m        59m         7         nginx-1007456269-gkzzv   Pod          spec.containers{nginx}   Normal    BackOff                 kubelet, minikube       Back-off pulling image "index.caicloud.io/caicloud/nginx:1.11.5"
...
...
```

Event 与资源是相联系的，因此单独查询 Event 并不是非常有用，我们可以通过获取资源的详细信息来查看 Event 信息。例如，
`kubectl describe pod <pod name>` 会返回 Pod 的 event 信息。

```
$ kubectl describe pod nginx -n tutorial
Name:           nginx
Namespace:      tutorial
Node:           minikube/192.168.99.101
Start Time:     Tue, 12 Sep 2017 17:09:25 +0800
Labels:         <none>
...
Events:
  FirstSeen     LastSeen        Count   From                    SubObjectPath           Type            Reason                  Message
  ---------     --------        -----   ----                    -------------           --------        ------                  -------
  11m           11m             1       default-scheduler                               Normal          Scheduled               Successfully assigned nginx to minikube
  11m           11m             1       kubelet, minikube                               Normal          SuccessfulMountVolume   MountVolume.SetUp succeeded for volume "default-token-cbj4c"
  11m           4m              2       kubelet, minikube       spec.containers{nginx}  Normal          Pulled                  Container image "cargo.caicloud.io/caicloud/nginx:1.9.7" already present on machine
  4m            4m              1       kubelet, minikube       spec.containers{nginx}  Normal          Killing                 Killing container with id docker://nginx:Pod "nginx" container "nginx" hash changed (4285829788 vs 2840123128), it will be killed and re-created.
  11m           1m              4       kubelet, minikube       spec.containers{nginx}  Normal          Created                 Created container
  8m            1m              2       kubelet, minikube       spec.containers{nginx}  Normal          Killing                 Killing container with id docker://nginx:Pod "nginx" container "nginx" hash changed (2840123128 vs 4285829788), it will be killed and re-created.
  8m            1m              2       kubelet, minikube       spec.containers{nginx}  Normal          Pulled                  Container image "cargo.caicloud.io/caicloud/nginx:1.9.3" already present on machine
  11m           1m              4       kubelet, minikube       spec.containers{nginx}  Normal          Started                 Started container
```

# Kubernetes Pod Lifecycle

Pod 生命周期主要包括：
- Pod Phase
- Pod Condition
- Restart Policy
- Health Check

用户可以通过 `kubectl describe pods` 查看以上所有信息。Pod Phase 和 Pod Condition 比较简单，我们可以实时看到
kubernetes 的反馈。这里我们主要实践 Restart Policy 和 Health Check。

## Restart policy

Restart Policy 指定当 Pod 内容器出错或执行完毕后，是否重启。下面的 Pod 使用了 debian 镜像，该镜像并不会长期运行，
因此如果我们直接创建，kubernetes 会认为 Pod 出错。

```
$ kubectl create -f resources/debian.yaml -n tutorial
```

注，若提示资源不足，可以删掉现有的 Deployment 或 Pod 资源。创建之后，等待 kubernetes 拉取镜像。几分钟后，
kubernetes 提示 redis-django 进入 Crash 状态，且有多次重启：

```
$ kubectl get pods -n tutorial
NAME                     READY     STATUS             RESTARTS   AGE
debian                   0/1       CrashLoopBackOff   1          6s
nginx                    1/1       Running            4          2h
nginx-3035859230-m28qm   1/1       Running            1          2h
nginx-3035859230-t3f9p   1/1       Running            1          2h
```

现在，我们为该 Pod 添加 Restart Policy，使 kubernetes 不再不断重启 debian 容器，从而得到以下结果：

```
$ kubectl delete pods debian -n tutorial
pod "debian" deleted

$ kubectl create -f resources/debian_never_restart.yaml -n tutorial
pod "debian" created
```

debian 容器变成 `Completed` 状态（必须使用 `-a` 选项）：

```
$ kubectl get pods -n tutorial -a
NAME                     READY     STATUS      RESTARTS   AGE
debian                   0/1       Completed   0          44s
nginx                    1/1       Running     4          2h
nginx-3035859230-m28qm   1/1       Running     1          2h
nginx-3035859230-t3f9p   1/1       Running     1          2h
```

## Health Check

Health Check 分为两种：LivenessCheck 和 ReadinessCheck。Liveness 检查应用是否依然健康无错，若有错，则
kubernetes 会根据 policy 重启或仅更新状态。ReadinessCheck 检查应用是否可以对外提供服务，若应用 Readiness
检查不通过，则 kubernetes 会将 Pod 从服务池中剔除。两者的使用方法都相同，这里我们来看看 Health Check。

打开 pod_health.yaml，可以看到里面定义了 livenessProbe。当我们运行创建该 Pod 的时候，kubernetes
就开始为我们监控该 Pod 的 liveness 信息。

```
$ kubectl delete pods nginx -n tutorial
pod "nginx" deleted

$ kubectl create -f resources/pod_health.yaml -n tutorial
pod "nginx" created
```

Pod 会一直处于 Running 状态：

```
$ kubectl get pods -n tutorial
NAME                     READY     STATUS    RESTARTS   AGE
nginx                    1/1       Running   0          1m
nginx-3035859230-m28qm   1/1       Running   1          3h
nginx-3035859230-t3f9p   1/1       Running   1          3h
```

我们可以分别尝试将 livenessProbe 的 http 80 端口改为 8080，观察 Pod 的状态。

```
$ kubectl delete pods nginx -n tutorial
pod "nginx" deleted

$ kubectl create -f resources/pod_unhealth.yaml -n tutorial
pod "nginx" created
```

Pod 会首先处于 Running 状态，但是在经过一段时间之后，Pod 会变为 Crash 状态，事件里会汇报健康检查错误：

```
$ kubectl describe pod nginx -n tutorial
Name:           nginx
Namespace:      tutorial
Node:           minikube/192.168.99.100
Start Time:     Tue, 12 Sep 2017 19:58:42 +0800
Labels:         app=nginx
Annotations:    <none>
Status:         Running
IP:             172.17.0.3
Containers:
  nginx:
    Container ID:       docker://34a7702a40a2373c2dd3df284b949b3308da285103cdc83c68bf7b5ec6bd6354
    Image:              cargo.caicloud.io/caicloud/nginx:1.9.7
    Image ID:           docker-pullable://cargo.caicloud.io/caicloud/nginx@sha256:d33ae7b1dc9326bcaa91febdf37a8ea1a7340f7d6da0e2fde365a89a11201c62
    Port:               <none>
    State:              Waiting
      Reason:           CrashLoopBackOff
    Last State:         Terminated
      Reason:           Completed
      Exit Code:        0
      Started:          Tue, 12 Sep 2017 19:59:17 +0800
      Finished:         Tue, 12 Sep 2017 19:59:27 +0800
    Ready:              False
    Restart Count:      3
    Limits:
      cpu:      100m
      memory:   100Mi
    Requests:
      cpu:              100m
      memory:           100Mi
    Liveness:           http-get http://:8080/ delay=5s timeout=1s period=5s #success=1 #failure=3
    Environment:        <none>
    Mounts:
      /var/run/secrets/kubernetes.io/serviceaccount from default-token-cbj4c (ro)
Conditions:
  Type          Status
  Initialized   True
  Ready         False
  PodScheduled  True
Volumes:
  default-token-cbj4c:
    Type:       Secret (a volume populated by a Secret)
    SecretName: default-token-cbj4c
    Optional:   false
QoS Class:      Guaranteed
Node-Selectors: <none>
Tolerations:    <none>
Events:
  FirstSeen     LastSeen        Count   From                    SubObjectPath           Type            Reason                  Message
  ---------     --------        -----   ----                    -------------           --------        ------                  -------
  1m            1m              1       default-scheduler                               Normal          Scheduled               Successfully assigned nginx to minikube
  1m            1m              1       kubelet, minikube                               Normal          SuccessfulMountVolume   MountVolume.SetUp succeeded for volume "default-token-cbj4c"
  1m            26s             4       kubelet, minikube       spec.containers{nginx}  Normal          Pulled                  Container image "cargo.caicloud.io/caicloud/nginx:1.9.7" already present on machine
  1m            26s             4       kubelet, minikube       spec.containers{nginx}  Normal          Created                 Created container
  1m            26s             4       kubelet, minikube       spec.containers{nginx}  Normal          Started                 Started container
  56s           16s             9       kubelet, minikube       spec.containers{nginx}  Warning         Unhealthy               Liveness probe failed: Get http://172.17.0.3:8080/: dial tcp 172.17.0.3:8080: getsockopt: connection refused
  46s           16s             4       kubelet, minikube       spec.containers{nginx}  Normal          Killing                 Killing container with id docker://nginx:pod "nginx_tutorial(b8b7ac2f-97b1-11e7-9d12-0800277a7b6e)" container "nginx" is unhealthy, it will be killed and re-created.
  16s           3s              3       kubelet, minikube       spec.containers{nginx}  Warning         BackOff                 Back-off restarting failed container
  16s           3s              3       kubelet, minikube                               Warning         FailedSync              Error syncing pod
```

## Readings

- [kubernetes lifecycle](https://kubernetes.io/docs/concepts/workloads/pods/pod-lifecycle/)
- [define probes](https://kubernetes.io/docs/tasks/configure-pod-container/configure-liveness-readiness-probes/)

# Kubernetes Job

## Manage Jobs

Kubernetes Job 通过创建 Pod 来执行一次性任务；不同于单独跑一个 Pod，由 Job 运行起来的 Pod
在机器故障等问题下会重新调度 Pod，因此更加健壮。

下面，我们通过创建一个 Pod 来感受一下 Job 的使用：

```
$ kubectl create -f job.yaml
job "pi" created

$ kubectl get job
NAME      DESIRED   SUCCESSFUL   AGE
pi        5         0            4s

$ kubectl get pods
NAME                    READY     STATUS              RESTARTS   AGE
nginx-689083664-53ol0   1/1       Running             0          19h
pi-jmurq                0/1       ContainerCreating   0          9s
```


一段时间之后，Pod 全部运行结束，我们可以通过 `kubectl get pods -a` 查看：

```
$ kubectl get pods -a
NAME                    READY     STATUS      RESTARTS   AGE
nginx-689083664-53ol0   1/1       Running     0          20h
pi-fh4lb                0/1       Completed   0          46m
pi-jmurq                0/1       Completed   0          53m
pi-mffpb                0/1       Completed   0          50m
pi-q3x22                0/1       Completed   0          49m
pi-tlgu1                0/1       Completed   0          47m

$ kubectl get job
NAME      DESIRED   SUCCESSFUL   AGE
pi        5         5            56m
```

观察上述 Pod 的 AGE 列，可以发现 Job 内的 Pod 都是依次运行的（总共 5 个 Pod）。Job 支持并发运行等多种
控制，我们在后续任务中实现。

Job 运行完之后，删除 Job 会将所有运行结束的 Pods 也同时删掉。

```
$ kubectl delete job pi
job "pi" deleted

$ kubectl get pods
NAME                    READY     STATUS    RESTARTS   AGE
nginx-689083664-53ol0   1/1       Running   0          20h
```

## Readings

- [kubernetes job](https://kubernetes.io/docs/concepts/workloads/controllers/jobs-run-to-completion/)
- [kubernetes cronjob](https://kubernetes.io/docs/concepts/workloads/controllers/cron-jobs/)

# Kubernetes ConfigMap & Secret

ConfigMap 是 kubernetes 用来管理配置信息的资源类型。我们通过单独创建 ConfigMap，再将 ConfigMap 挂载到
Pod 内的方式分离配置和应用。我们通过一个实验来学习如何正确使用 ConfigMap。

创建 ConfigMap 可以通过 yaml 文件，也可以从文件直接创建。通过 yaml 文件的方式与创建其他资源类似。这里，
我们采用文件的方式。在 `resources` 目录下，有两个文件：game.properties 和 ui.properties。我们通过
kubectl 命令创建：

```
$ kubectl create configmap game-config --from-file=resources/game.properties --from-file=resources/ui.properties -n tutorial
configmap "game-config" created
```

创建之后，通过 kubectl get configmap 来查看创建的 ConfigMap：

```
$ kubectl get configmap game-config -o wide -n tutorial
NAME          DATA      AGE
game-config   2         2m
```

```
$ kubectl describe configmap game-config -n tutorial
Name:           game-config
Namespace:      default
Labels:         <none>
Annotations:    <none>

Data
====
game.properties:
----
enemies=aliens
lives=3
enemies.cheat=true
enemies.cheat.level=noGoodRotten
secret.code.passphrase=UUDDLRLRBABAS
secret.code.allowed=true
secret.code.lives=30
ui.properties:
----
color.good=purple
color.bad=yellow
allow.textmode=true
how.nice.to.look=fairlyNice
Events: <none>
```

查看详情：

```
$ kubectl get configmap game-config -o yaml -n tutorial
apiVersion: v1
data:
  game.properties: |-
    enemies=aliens
    lives=3
    enemies.cheat=true
    enemies.cheat.level=noGoodRotten
    secret.code.passphrase=UUDDLRLRBABAS
    secret.code.allowed=true
    secret.code.lives=30
  ui.properties: |-
    color.good=purple
    color.bad=yellow
    allow.textmode=true
    how.nice.to.look=fairlyNice
kind: ConfigMap
metadata:
  creationTimestamp: 2017-09-12T12:18:19Z
  name: game-config
  namespace: default
  resourceVersion: "14798"
  selfLink: /api/v1/namespaces/default/configmaps/game-config
  uid: 7636e590-97b4-11e7-9d12-0800277a7b6e
```

创建 ConfigMap 之后，我们可以创建 Pod 来使用该 ConfigMap：

```
$ kubectl create -f resources/pod_configmap.yaml -n tutorial
pod "pod-configmap" created
```

由于该 Pod 只打印信息，很快便结束运行，我们需要用 `-a` 查看：

```
$ kubectl get pods -n tutorial -a
NAME                     READY     STATUS             RESTARTS   AGE
pod-configmap            0/1       Completed          0          2m

$ kubectl logs pod-configmap -n tutorial
enemies=aliens
lives=3
enemies.cheat=true
enemies.cheat.level=noGoodRotten
secret.code.passphrase=UUDDLRLRBABAS
secret.code.allowed=true
secret.code.lives=30color.good=purple
color.bad=yellow
allow.textmode=true
how.nice.to.look=fairlyNice
```

这里我们看到了通过挂载文件的方式使用 configmap，kubernetes 同时也支持通过环境变量的方式使用 configmap。
此外，Secret 的使用方式与 Configmap 类似，但内容会被加密。

## Readings

- [kubernetes configmap](https://kubernetes.io/docs/tasks/configure-pod-container/configmap/)
- [distribute secret](https://kubernetes.io/docs/tasks/inject-data-application/distribute-credentials-secure/)

# Kubernetes Daemonset

## Manage Daemonset

DaemonSet 默认在每台主机上运行 Pod，典型的场景包括日志收集、存储进程等。这里，我们通过 kubectl create
来创建一个 DaemonSet：

```
$ kubectl create -f resources/daemonset.yaml
daemonset "ds-nginx" created

$ kubectl get ds
NAME       DESIRED   CURRENT   READY     UP-TO-DATE   AVAILABLE   NODE-SELECTOR   AGE
ds-nginx   1         1         1         1            1           <none>          4s

$ kubectl get pods
NAME             READY     STATUS    RESTARTS   AGE
ds-nginx-hnndc   1/1       Running   0          8s
```

可以看到，minikube 节点都运行了一个 DaemonSet。由于目前只有一个节点，很难观测到效果，但当我们向集群中增加新的节点，
DaemonSet 会自动在新的节点中启动 Pod。

我们可以通过 kubectl delete 删除 DaemonSet：

```
$ kubectl delete daemonset daemonset
```

DaemonSet 相对于其他控制器（Deployment, Job 等）有几个特点：
- DaemonSet 不经过调度器。因为 DaemonSet 的本质就是在每个节点运行，因此调度实际上是不再需要的。这意味着
  - 即使调度器没有启动，也可以用来运行 Pod
  - 如果一个节点被标记为不可调度，由 DaemonSet 启动的容器也会运行在某个节点上
- DaemonSet 启动的 Pod 优先级较高，与后续介绍的 Taints 等概念有不同的交互

## Readings

- [kubernetes daemonset](https://kubernetes.io/docs/concepts/workloads/controllers/daemonset/)

# Summary

本节介绍了 Kubernetes deployment 的更多操作, Yaml 文件规范，事件，Pod 生命周期等，接下来会介绍其他应用
相关模块，存储。为确保已经掌握上面知识，请思考下面的问题。

目前为止简单介绍了 Kubernetes command line, Pod, Deployment, Service 和 Label。这些都是 kubernetes
中最为核心的概念，接下来我们将深入了解 Deployment 的功能，然后开始涉及其他模块。本节暂无实验内容。

# Exercise

以下问题是在 kubernetes 使用或运维中较常使用的命令或方式方法。

1. 学习 kubectl proxy 命令及其含义。回答如何通过 proxy 访问 kubernetes 集群？
2. 学习 kubectl port-forward 命令极其含义。回答如何通过 port-forward 访问应用？
3. 修改 Pod label 使其与 Deployment 不相符，集群有什么变化？
4. 进一步学习 kubectl run。回答如何向 Pod 注入环境变量？如何查看是否注入成功？
5. 进一步学习 kubectl rollout。回答如何通过 kubectl rollout 将应用回滚到指定版本？
6. Pod LivenessProbe 实验中，检查方式采用的是 http 模式。回答如何使用 exec 进行健康检查？请写出 yaml 文件。
7. 进一步学习 Pod Lifecycle。回答如何使用 Prestart Hook？请写出 yaml 文件。
8. 登录宿主机，使用 docker ps 查看 Pod，如何理解 docker ps 输出？
9. 学习使用 Secret，然后创建一个 Secret 并在 Pod 内访问。请写出 secret 和 pod 的 yaml 文件。
10. ConfigMap 实验中，我们采用文件加载的方式使用 ConfigMap。请写出利用环境变量加载 configmap 的例子。
11. 学习 Job 的更多配置，修改 Job 的 yaml 文件使其能同时运行多个 Pod。
