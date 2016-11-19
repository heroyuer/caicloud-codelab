# Linux cgroups

The directory contains experiments with linux cgroups.

## Prerequisites

cgroups tools are needed in order to experiment with cgroups, for ubuntu:

```
sudo apt-get install cgroup-bin
```

for centos:
```
sudo yum install libcgroup-tools
```

## Experiment 1

create cgroups: parent is limited to 12MB, and two children without setting limits:

```
sudo mkdir /sys/fs/cgroup/memory/test_parent
sudo mkdir /sys/fs/cgroup/memory/test_parent/child1
sudo mkdir /sys/fs/cgroup/memory/test_parent/child2

sudo bash -c "echo 12582912 > /sys/fs/cgroup/memory/test_parent/memory.limit_in_bytes"
sudo bash -c "echo 12582912 > /sys/fs/cgroup/memory/test_parent/memory.memsw.limit_in_bytes"
```

build and run `cg_mem.c` in two terminals:
```
gcc cg_mem.c
sudo cgexec -g memory:/test_parent/child1 ./a.out
sudo cgexec -g memory:/test_parent/child2 ./a.out
```

child1 (or child2) will be killed when their **total** allocated memory is 12MB;
then the other one will proceed since memory is freed. This demonstrated cgroup
hierarchy tree property.
