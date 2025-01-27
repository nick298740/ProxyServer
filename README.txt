README
For context, this was written a long time ago, during my days in University. 
I added it as a public repo for portfolio purposes.
However, code will not currently run as intended because it is using
servers owned by the University of North Texas (UNT), which no one would have 
access to, and could have changed since my time at UNT
_______________________________________________________

compile code using
$	gcc codeToCompile.c -o executableName

run code using
$	./executableName [portNumber]

for example, to compile and run server,
$	gcc server.c -o server
$	./server 22000

You MUST run proxy server on the defined IP_ADDRESS specified in client.c, or this program will not run correctly

Run client on cse02.cse.unt.edu

Follow instructions on screen that prompt user. When making URL request from client, only use format:
$ >>	www.exampleSite.com

The requested URL is saved locally on server, then file contents retrieved and sent to client.

I did not include a list.txt because I believe my method for finding a cached file is better. 
