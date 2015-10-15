# Set up
* Install httplib2 library. [Home page](https://github.com/jcgregorio/httplib2)

```
pip install httplib2
```
If you meet permission issues when installing new python lib, try to use `chmod` command to grant permission to current user belonged group after adding current user to group such as <em><strong>wheel</strong></em> by command `useradd` for [linux](http://www.yolinux.com/TUTORIALS/LinuxTutorialManagingGroups.html), for Mac, the command is `sudo dscl . append /groups/groupname GroupMembership username` per [link](https://discussions.apple.com/thread/1917638?tstart=0)
