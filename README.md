# Troubleshoot `irdma`

> This repository is owned by [Animesh Trivedi](https://github.com/animeshtrivedi/rdma-example.git). It would've been easy to just fork Animesh's repo but since I have an existing fork of that repository 

> IMPORTANT NOTE: This repo contains code which might not be useful for everyone; intended for troubleshooting, rather understanding `irdma` dynamic debug logs.

* Make sure to enable dynamic debug feature of irdma before starting out

```shell
# Step 1 (Unload the irdma driver if already loaded)
sudo rmmod irdma

# Step 2 (Re-load with dynamic debug feature ON)
sudo modprobe irdma dyndbg='+p'
```

### What I Did:

1. First, I added custom debug statements (`dbg()`) statements to only the main() function of both client and server codes. dbg() function definition is as follows:

  ```C
  void dbg(char *s) {
    printf("%s -- Press Enter to continue", s);
    getc(stdin);
    return;
  }
  ```

  > This function takes a string as input; outputs it on stdout and does not proceed further before asking from user.

