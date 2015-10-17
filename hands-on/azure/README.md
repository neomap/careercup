## Tips
- <b>How to generate pem/cer file to access linux from mac?

The simple answer is to use the following openssl command to generate x509 format
certificate from existing isa keys:
```
# openssl req -x509 -key ~/.ssh/id_rsa -nodes -days 365 -newkey rsa:2048 -out myCert.pem
```
Azure provided [detail guide][1]

- <b>How to connect to created Linux VM?

First check out that VM's _ssh detail_ from __dashboard__ tab, and then connect via ssh command
with provided user name. Here is [detail][2]

- <b>How to leverage ssh to host a local socket server as proxy to _external world_?

Run command like this locally: `ssh -D 10086 andyub`
Then install proxy add-on for firefox or chrome, and add a sockets v4/v5 SOCKETS Host: `localhost, 10086` 

[1]: https://azure.microsoft.com/en-us/documentation/articles/virtual-machines-linux-use-ssh-key/
[2]: https://azure.microsoft.com/en-us/documentation/articles/virtual-machines-linux-how-to-log-on/