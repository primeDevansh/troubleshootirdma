# Troubleshoot `irdma`

A repository to store code that would help in demystifying `irdma` dynamic-debug messages.

I will be using [Animesh Trivedi](https://github.com/animeshtrivedi)'s [rdma-example](https://github.com/animeshtrivedi/rdma-example.git) repository to write some troubleshooting code for my RoCEv2 setup. I am using Intel E810 RNIC which runs RDMA through `irdma` driver.

> It would've been easy to just fork Animesh's [repo](https://github.com/animeshtrivedi/rdma-example.git) but since I already have a fork of that repository ([benchmark_rdma-example](https://github.com/primeDevansh/benchmark_rdma-example.git)), I was only left with this way of adding personal touches to it.

> IMPORTANT NOTE: This repo contains code which might not be useful for everyone; intended for troubleshooting, rather understanding `irdma` dynamic debug logs. Running this code will print a lot of statements on `stdout`.

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
	if(dbg_true) {
		printf("%s -- Press Enter to continue", s);
		getc(stdin);
	}
	else
		return;
}
```

> This function takes a string as input; outputs it on stdout and does not proceed further before asking from user. All this only done if custom debugging is turned ON by providing a non-zero integer at the start of the program.

2. Tracing `dmesg` logs

```shell
# On Node 1
sudo dmesg -TW | grep irdma
```

> -T used for getting timestamp
> -W used to show only new messages