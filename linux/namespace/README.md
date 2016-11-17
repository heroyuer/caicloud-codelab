# Linux namespace

The directory contains experiments with linux namespace.

## PID namespace

#### Experiment 1

Build and run `pid_namespace.c`:

```
$ gcc pid_namespace.c
$ sudo ./a.out echo "running"
```

Note, root privilege is required to create pid namespace, so we need to run `a.out` with
`sudo`. Example output:

```
child pid from parent: 14015
child pid from child: 1
parent pid from parent: 0
running
```

The program forks a child program with new PID namespace. From parent point of view, it
sees that the new child has PID 14015; while from child, it sees itself with PID 1.

#### Experiment 2

List of processes in the new child namespace:

```
$ sudo ./a.out bash
# ps aux
```

Example output:

```
# ps aux
USER       PID %CPU %MEM    VSZ   RSS TTY      STAT START   TIME COMMAND
root         1  0.0  0.0  33732  4344 ?        Ss   Nov02   0:01 /sbin/init
root         2  0.0  0.0      0     0 ?        S    Nov02   0:00 [kthreadd]
root         3  0.0  0.0      0     0 ?        S    Nov02   0:00 [ksoftirqd/0]
root         5  0.0  0.0      0     0 ?        S<   Nov02   0:00 [kworker/0:0H]
...
root     13916  0.0  0.0      0     0 ?        R    07:10   0:00 [kworker/u8:0]
root     14090  0.0  0.0  65736  3976 pts/0    S    07:23   0:00 sudo ./a.out bash
root     14091  0.0  0.0   5224   788 pts/0    S    07:23   0:00 ./a.out bash
root     14092  0.0  0.0  22440  6456 pts/0    S    07:23   0:00 bash
root     14108  0.0  0.0  17168  2556 pts/0    R+   07:27   0:00 ps aux
```

If we try to kill ourself using PID from parent PID namespace, we'll get error:

```
# kill 14091
bash: kill: (14091) - No such process
```

You might be wondering that the output shows *all* processes in our system, instead of
ones in the child namespace. The is because tools like `ps` looks up processes in `/proc`
filesystem. In order to make the /proc/PID directories that correspond to a PID namespace
visible, the `proc` filesystem needs to be mounted from within that PID namespace. In the
same shell session, run the following commands:

```
mount -t proc proc /proc/
ps aux
```

This time, only processes from current PID namespace will be shown. To clean up, exit
the namespace and do `mount -t proc proc /proc/` again.

## Network namespace

#### Experiment 1

```
gcc net_namespace.c
sudo ./a.out
```

Example output:

```
$ sudo ./a.out
original `net` Namespace:
1: lo: <LOOPBACK,UP,LOWER_UP> mtu 65536 qdisc noqueue state UNKNOWN mode DEFAULT group default qlen 1
    link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00
2: eth0: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc pfifo_fast state UP mode DEFAULT group default qlen 1000
    link/ether 08:00:27:22:cb:22 brd ff:ff:ff:ff:ff:ff
3: eth1: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc pfifo_fast state UP mode DEFAULT group default qlen 1000
    link/ether 08:00:27:5c:b4:37 brd ff:ff:ff:ff:ff:ff
4: docker0: <NO-CARRIER,BROADCAST,MULTICAST,UP> mtu 1500 qdisc noqueue state DOWN mode DEFAULT group default
    link/ether 02:42:02:f4:80:57 brd ff:ff:ff:ff:ff:ff

new `net` Namespace:
1: lo: <LOOPBACK> mtu 65536 qdisc noop state DOWN mode DEFAULT group default qlen 1
    link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00
```

## Reference

https://lwn.net/Articles/531114/
