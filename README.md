# Troubleshoot `irdma`

> This repository is owned by [Animesh Trivedi](https://github.com/animeshtrivedi/rdma-example.git). I have already forked it before so it isn't possible to 're-fork' it; that is why I've just copied all of the code and uploaded it as my code.

> IMPORTANT NOTE: This repo contains code which might not be useful for everyone; intended for troubleshooting, rather understanding `irdma` dynamic debug logs.

* Make sure to enable dynamic debug feature of irdma before starting out

```shell
# Step 1 (Unload the irdma driver if already loaded)
sudo rmmod irdma

# Step 2 (Re-load with dynamic debug feature ON)
sudo modprobe irdma dyndbg='+p'
```

