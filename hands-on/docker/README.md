## Installation

-  [Installaton on Mac OS X](https://docs.docker.com/installation/mac/)

Use the Docker Toolbox to install Docker Machine as well as the other Docker tools.
It is also a tutorial for getting start with docker, telling us how to run _hello-world_ of docker.


## Run on Mac
Steps to run docker images.
- First run command: `docker-machine start default` to start docker daemon host VM
- Then run command to export some envirionment variables to current shell by:
```
eval "$(docker-machine env default)"
```
- List all availabe images by `docker images`
- If you want to run some docker image, type command like:
```
# Run ubuntu image interactively by launching bash
docker run -it ubuntu bash

# Run nginx image as daemon
docker run -d -P --name web nginx
```

### How to ssh to docker machine?
First, deploy a new docker machine providing desired opotions, like the following:
```

```
Then you can ssh to that VM after starting it.
Check out detail guide [here][1]

##Tips
- <b>How to remove all stopped docker containers?
`docker rm $(docker ps -a -q)`

- <b> How to remove all untagged docker images?
`docker rmi $(docker images -a | grep '^<none>' | awk '{print $3}')`


[1]: https://blog.docker.com/2015/06/docker-machine-0-3-0-deep-dive/