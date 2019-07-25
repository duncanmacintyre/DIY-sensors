# Saving sensor data

Now, our sensors are sensing, the serial monitor monitoring, and our Arduino flashing along happily. This is good.

The second half of making DIY sensors will take place on our computer. Our task will be to take the stream of data from the serial monitor and turn it into something more useful.

Most often, we interact with our computer through the graphical user interface, the GUI—we click and drag and type and make wonderful things happen. Much of our computer's most incredible abilities, however, can only be leveraged through the command-line interface, the CLI, the wild place where we type in text to make cool things happen. The command line is not just that freaky thing in hacker movies. Here, we will use it to give our computer instructions about how to save data from the serial monitor to a file.

These instructions are intended for Unix-like operating systems like macOS and Linux. On Windows, you will need to figure out something different.

The Unix philosophy is said to be "everything is a file". Your biology quiz study guide is a file. Your computer's list of users is a file. Your external flash drive is a file. The serial monitor is a file. To read it, we just have to know where it is.

## Monitoring the serial monitor

The video below runs through getting data from the serial monitor. It mirrors the written part that comes after; you may wish to use both together.

<!!! serial monitor video>

Let's get started! Plug in your Arduino, then open your favourite terminal app (likely Terminal) and type in 

`````
$ ls /dev
`````

and press enter. (Do not actually type the $; it is just used to signify this as a terminal command. Type just the `ls /dev` part.)

When I run `$ ls /dev` on my computer, I see

`````
duncan: ~/ $ ls /dev
afsc_type5                  ptyt1                       ttyqb
auditpipe                   ptyt2                       ttyqc
auditsessions               ptyt3                       ttyqd
autofs                      ptyt4                       ttyqe
autofs_control              ptyt5                       ttyqf
autofs_homedirmounter       ptyt6                       ttyr0
autofs_notrigger            ptyt7                       ttyr1
autofs_nowait               ptyt8                       ttyr2
bpf0                        ptyt9                       ttyr3
bpf1                        ptyta                       ttyr4
bpf2                        ptytb                       ttyr5
bpf3                        ptytc                       ttyr6
bpf4                        ptytd                       ttyr7
console                     ptyte                       ttyr8
cu.Bluetooth-Incoming-Port  ptytf                       ttyr9
cu.usbmodem14201            ptyu0                       ttyra
disk0                       ptyu1                       ttyrb
disk0s1                     ptyu2                       ttyrc
disk0s2                     ptyu3                       ttyrd
disk1                       ptyu4                       ttyre
disk1s1                     ptyu5                       ttyrf
disk1s2                     ptyu6                       ttys0
disk1s3                     ptyu7                       ttys000
disk1s4                     ptyu8                       ttys1
dtrace                      ptyu9                       ttys2
dtracehelper                ptyua                       ttys3
fbt                         ptyub                       ttys4
fd                          ptyuc                       ttys5
fsevents                    ptyud                       ttys6
io8log                      ptyue                       ttys7
io8logmt                    ptyuf                       ttys8
io8logtemp                  ptyv0                       ttys9
klog                        ptyv1                       ttysa
lockstat                    ptyv2                       ttysb
machtrace                   ptyv3                       ttysc
null                        ptyv4                       ttysd
oslog                       ptyv5                       ttyse
oslog_stream                ptyv6                       ttysf
pf                          ptyv7                       ttyt0
pfm                         ptyv8                       ttyt1
profile                     ptyv9                       ttyt2
ptmx                        ptyva                       ttyt3
ptyp0                       ptyvb                       ttyt4
ptyp1                       ptyvc                       ttyt5
ptyp2                       ptyvd                       ttyt6
ptyp3                       ptyve                       ttyt7
ptyp4                       ptyvf                       ttyt8
ptyp5                       ptyw0                       ttyt9
ptyp6                       ptyw1                       ttyta
ptyp7                       ptyw2                       ttytb
ptyp8                       ptyw3                       ttytc
ptyp9                       ptyw4                       ttytd
ptypa                       ptyw5                       ttyte
ptypb                       ptyw6                       ttytf
ptypc                       ptyw7                       ttyu0
ptypd                       ptyw8                       ttyu1
ptype                       ptyw9                       ttyu2
ptypf                       ptywa                       ttyu3
ptyq0                       ptywb                       ttyu4
ptyq1                       ptywc                       ttyu5
ptyq2                       ptywd                       ttyu6
ptyq3                       ptywe                       ttyu7
ptyq4                       ptywf                       ttyu8
ptyq5                       random                      ttyu9
ptyq6                       rdisk0                      ttyua
ptyq7                       rdisk0s1                    ttyub
ptyq8                       rdisk0s2                    ttyuc
ptyq9                       rdisk1                      ttyud
ptyqa                       rdisk1s1                    ttyue
ptyqb                       rdisk1s2                    ttyuf
ptyqc                       rdisk1s3                    ttyv0
ptyqd                       rdisk1s4                    ttyv1
ptyqe                       sdt                         ttyv2
ptyqf                       stderr                      ttyv3
ptyr0                       stdin                       ttyv4
ptyr1                       stdout                      ttyv5
ptyr2                       systrace                    ttyv6
ptyr3                       tty                         ttyv7
ptyr4                       tty.Bluetooth-Incoming-Port ttyv8
ptyr5                       tty.usbmodem14201           ttyv9
ptyr6                       ttyp0                       ttyva
ptyr7                       ttyp1                       ttyvb
ptyr8                       ttyp2                       ttyvc
ptyr9                       ttyp3                       ttyvd
ptyra                       ttyp4                       ttyve
ptyrb                       ttyp5                       ttyvf
ptyrc                       ttyp6                       ttyw0
ptyrd                       ttyp7                       ttyw1
ptyre                       ttyp8                       ttyw2
ptyrf                       ttyp9                       ttyw3
ptys0                       ttypa                       ttyw4
ptys1                       ttypb                       ttyw5
ptys2                       ttypc                       ttyw6
ptys3                       ttypd                       ttyw7
ptys4                       ttype                       ttyw8
ptys5                       ttypf                       ttyw9
ptys6                       ttyq0                       ttywa
ptys7                       ttyq1                       ttywb
ptys8                       ttyq2                       ttywc
ptys9                       ttyq3                       ttywd
ptysa                       ttyq4                       ttywe
ptysb                       ttyq5                       ttywf
ptysc                       ttyq6                       uart.BLTH
ptysd                       ttyq7                       urandom
ptyse                       ttyq8                       xcpm
ptysf                       ttyq9                       zero
ptyt0                       ttyqa
`````

These are all the files in the /dev directory on my computer.

("Directory" is just a fancy word for "folder". The notation /dev tells us that this is a directory named "dev" located in the computer's root, or bottommost, directory.)

These files mostly correspond to different "devices". That's a lot of devices!

Now we need to figure out which file is the serial monitor file. Let's see—we want something involving the USB port on our computer... let's try

`````
$ ls /dev | grep usb
`````

This will list all files in /dev, only showing those containing "usb" in the name. Now, I only get two files:

`````
duncan: ~/ $ ls /dev | grep usb
cu.usbmodem14201
tty.usbmodem14201
`````

Getting closer! Let's try reading one of these. We can use the handy cat program for reading files.

`````
$ cat /dev/cu.usbmodem14201
`````

Note: Run this with whatever file(s) you have identified. These files are in the /dev directory, so their full path begins with /dev/.

My output from this command is

`````
duncan: ~/ $ cat /dev/cu.usbmodem14201 
11812.37 21.24
11812.37 21.24
11812.37 21.24
11812.37 21.24
11812.37 21.24
11812.37 21.24
11812.37 21.24
`````

and new lines are continuously printed to the screen. We found the serial monitor! Yay!

To stop the cat program, use Ctl-c. (macOS users: this is indeed Ctl-c, not Cmd-c.)

If you don't see something that looks like the serial monitor, try a different file.

Your serial monitor file will probably change from time to time. For me, the numbers at the end of the name change depending on which port on my computer I plug my Arduino into.

We could run through the rigamarole above each time we want to collect data. Alternatively, you could try something like

`````
$ cat /dev/cu.usbmodem*
`````

and your computer will try to fill in the * when the command is run. This can run into problems if there is more than one possible file (which might happen if you plug in two Arduinos at once), but I find it reliable enough for me.

### Saving the data

Next step: save to a file. The command-line interface makes this simple. Try

`````
$ cat /dev/cu.usbmodem* > ~/Desktop/output.txt
`````

to redirect output data to a file called output.txt on the Desktop. After a few seconds of running, hit Ctl-c to stop.

Try opening the output.txt file. Does it look like serial monitor readings?

What would be even better would be if we could see sensor readings in the terminal *and* save them to a file at the same time. To do this, we'll use tee.

`````
$ cat /dev/cu.usbmodem* | tee ~/Desktop/output.txt
`````

Run for a few seconds, then stop the program. Notice how our old output.txt file was overwritten! Gone forever!

It pays to be careful when using the command line.

### Adding a time stamp

It would be really nice to add a time stamp to all of our data as it comes in. To do this, we will use the ts program, available as part of the moreutils package.

#### Installing moreutils

macOS does not include a built-in command-line package manager. I recommend using Homebrew. It is simple to install, simple to use, effective, and very well-made. It will make installing little things like moreutils *much* easier.

First, [install Homebrew](https://brew.sh). Then, simply run

`````
$ brew install moreutils
`````

to install moreutils. Now you can use ts.

On Linux, you can usually use your distro's package manager to install moreutils. For example, on Ubuntu, run

`````
$ sudo apt-get install moreutils
`````

#### Using ts

Let's time stamp some sensor readings! Try

`````
$ cat /dev/cu.usbmodem* | ts "%Y-%m-%d %H:%M:%S" | tee ~/Desktop/output.csv
`````

You should get a nice serial monitor output, with the date and time added to the beginning of each sensor reading.

The table below describes the different parts of this command.

| Part of command | Description |
|:--|:--|
| `cat` | We use the cat program to read the serial monitor file. |
| `/dev/cu.usbmodem*` | This is the path to the serial monitor file. The * signifies a wildcard; the computer will try to find a file path beginning with /dev/cu.usbmodem when the command is run. |
| `|` | This is called a pipe. With it, we can send the output from one program as input for the next. |
| `ts` | We use the ts program to add a time stamp to each line. |
| `"%Y-%m-%d %H:%M:%S"` | This parameter sets the format of the time stamp. Here, "%Y-%m-%d %H:%M:%S" tells ts to use a YYYY-MM-DD HH:MM:SS format. |
| `tee` | We use the tee program to save a copy of the data to a file. |
| `~/Desktop/output.csv` | The path to our output file. ~ signifies that the path starts in our home directory. I've changed the file extension to `.csv` to reflect that the file is in tabular format. CSV stands for "comma-separated values"; while we're using spaces, it's close enough for me. You can use `.txt` if you like. |

## Opening in Excel

Now that we have a nice output file, we can undertake all sorts of data processing endeavours. For many people, this begins with importing the file into Excel.

[<img alt="Importing output data to Excel" width="30%" src="https://video-to-markdown.netlify.com/.netlify/functions/image?url=https%3A%2F%2Fyoutu.be%2F-MQGSKWQ-dI">](https://youtu.be/-MQGSKWQ-dI "Importing output data to Excel")

1. Create a new blank workbook in Excel.
2. Go to File > Import to begin the import process. (This is where I found the import tool on macOS. It may be in a different location in other operating systems.)
3. Select "CSV file" and click "Import". (Selecting "Text file" also works. As near as I can tell, they do exactly the same thing.)
4. Find your output file and click "Get Data".
5. Select "Delimited" and click "Next".
6. Be sure the checkbox next to "Space" is checked, then click "Next".
7. If Excel asks, tell it that the first column is a date in YMD format.
8. Click "Finish" and "OK".

You should now have your sensor data in Excel. You may find that a few readings went wrong or have extra characters or noise, especially near the beginning. Simply delete these rows. Voilà!

## Caveats and improvements

The method above has worked reasonably well for me. With that said, there are a few areas for improvement.

### Timestamp precision

Perhaps the main flaw in the methods above is that ts is precise only to the nearest second. This may not be so bad as it may sound. For one thing, there is an inherent delay between a sensor event happening and recording it on the computer, likely of more than a second. Also, I suspect that most experiments do not really need millisecond precision anyways.

### Using Python to watch the serial monitor

One compelling option is to write a Python script to watch the serial monitor and log data. This [has been tried before](https://electronics.stackexchange.com/a/381800). (You could do something similar in other scripting languages.)

This method would not require moreutils. It would also give access to adding the many tools available in Python, and is more promising if you need better-than-nearest-second precision. 

### Using NumPy and Pandas for data processing

While Excel is easy to use and accessible, much of the power available for data processing can only be found in more sophisticated tools. There are several important Python libraries in this respect, but of most interest for opening our output files is [Pandas](https://pandas.pydata.org/pandas-docs/stable/getting_started/overview.html).

Pandas adds excellent table functionality to Python. It works as a wrapper for NumPy, leveraging NumPy's power while making it data easier to work.

Pandas includes [a very useful function](https://pandas.pydata.org/pandas-docs/stable/reference/api/pandas.read_csv.html) for opening delimitated text files (like our output file).

An added bonus is that, in my experience, Pandas does a much better job than Excel at automatically parsing times. If you're using Pandas, I recommend changing the time stamp format to have a hyphen instead of a space between the date and time so as to present these as one field. (Excel is not sophisticated enough to recognize that times and dates go together.)

## Further reading

If you would like to learn how to use the command line, I highly recommend William Shotts's truly excellent book [*The Linux Command Line*](http://www.linuxcommand.org/tlcl.php). (It's free.) While it's intended for new Linux users, I think that even macOS users will find it interesting and useful.

