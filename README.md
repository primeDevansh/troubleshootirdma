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
		printf("\033[0;93;43m%s -- Press Enter to continue\033[0m", s);
		getc(stdin);
	}
	else
		return;
}
```

> This function takes a string as input; outputs it on stdout and does not proceed further before asking from user. All this only done if custom debugging is turned ON by providing a non-zero integer at the start of the program.

> In C, we can use ANSI escape codes to print text in different colors in the terminal. These escape codes are sequences of characters that the terminal interprets to change the text color, background color, and other text formatting options like bold or underlined text.

> The ANSI escape code format for text color is: `\033[<style>;<foreground_color>;<background_color>m`

* \033 is the escape character.
* [ is the beginning of the escape code.
* `<style>` is the style of the text (e.g., 1 for bold, 0 for normal).
* `<foreground_color>` is the color code for the text.
* `<background_color>` is the color code for the background (optional).

Here are some commonly used ANSI color codes:

| Color          | Foreground Code | Background Code |
| -------------- | --------------- | --------------- |
| Black          | 30              | 40              |
| Red            | 31              | 41              |
| Green          | 32              | 42              |
| Yellow         | 33              | 43              |
| Blue           | 34              | 44              |
| Magenta        | 35              | 45              |
| Cyan           | 36              | 46              |
| White          | 37              | 47              |
| Bright Black   | 90              | 100             |
| Bright Red     | 91              | 101             |
| Bright Green   | 92              | 102             |
| Bright Yellow  | 93              | 103             |
| Bright Blue    | 94              | 104             |
| Bright Magenta | 95              | 105             |
| Bright Cyan    | 96              | 106             |
| Bright White   | 97              | 107             |

2. Tracing `dmesg` logs

```shell
# On Node 1
sudo dmesg -TW | grep irdma
```

> `-T` used for getting timestamp; `-W` used to show only new messages