# ECHO Server

### Description

Echo server implementing exchange of data packets using UDP protocol.
There are two modules: the server and the client.

### Configure

#### Config file

If you want you can specify settings in a config file using the special syntax:
* If you want to define a server port, write: `server_port = <your_port>
`
* If you want to define a client port, write: `client_port = <your_port>`
* If you want to define a server address, write: `server_address = 192.168.3.1`

Note, that you have to write certain option either on new line or use `;` symbol.

#### Command line options

Besides, if you want, you can specify settings in the command line while running the program.
There are all options below:

* `-s, --server_port <server_port>` - the port of the server
* `-c, --client_port <client_port>` - the port of the client
* `-a, --address <ip_address>` - the ip address of the server
* `-f, --config_file <path>` - the path of the file containing program settings

### How to use

To use this program you have to launch it with administrator permission, because of only that way allows you
open a socket.

So, at first, you have to launch the server using:
```shell script
sudo ./EchoServer -f ./cfg.txt
```
or 
```shell script
sudo ./EchoServer -s <server_port>
```

As you may have noticed, you may don't specify an address of the server, because it's "127.0.0.1" by default.

Then, you have to launch the client using:
```shell script
sudo ./EchoClient -f ./cfg.txt
```
or
```shell script
sudo ./EchoClient -s <server_port> -c <client_port> -a <address>
```

**NOTE**: If you specified `-f` option, settings which were specified in this file will override settings which you 
specified in the command line. But, also it will complement these settings, if somewhere the settings are, but somewhere they aren't.

### Examples

#### Launch

You launch the server with the port `8000` and the ip address `127.0.0.1`:
```shell script
sudo ./EchoServer -s 8000 -a 127.0.0.1
```
You launch the server with the port `8000` and the ip address is retrieving from the file:
```shell script
sudo ./EchoServer -s 8000 -f cfg.txt
```
You launch the client with the server port `8000` and the client port and ip address are retrieving from the file:
```shell script
sudo ./EchoClient -s 8000 -f cfg.txt
```

#### Config file
The config file may be such as:
```text
server_port = 8000 
client_port = 8001
server_address = 127.0.0.1
```