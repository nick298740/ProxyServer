compile code using
$	gcc codeToCompile.c -o executableName

run code using
$	./executableName [portNumber]

for example, to compile and run server,
$	gcc server.c -o server
$	./server 22000

You MUST run proxy server on cse01.cse.unt.edu, or this program will not run correctly

Run client on cse02.cse.unt.edu

Follow instructions on screen that prompt user. When making URL request from client, only use format:
$ >>	www.exampleSite.com

The requested URL is saved locally on server, then file contents retrieved and sent to client.

I did not include a list.txt because I believe my method for finding a cached file is better. 