## Set up Java Dev Env
1. Install JDK
   Download  from [Oracle site] (http://www.oracle.com/technetwork/java/javase/downloads/).
2. On MacOs, just install DMG file, after installation, the installed version is choosen as current jdk. You can check out that 
by `printenv | grep -i java`. More information about installation on MacOs could be found from [here](https://docs.oracle.com/javase/8/docs/technotes/guides/install/mac_jdk.html)
3. On MacOs, the java home would be like "/Library/Java/JavaVirtualMachines/jdxxx/Contents/Home". Just type `cd $JAVA_HOME`
4. Source code for Java library is located at `$JAVA_HOME/src.zip`. To unzip it, type `jar xvf ./src.zip`
5. JDK document could be downloaded from [Oracle document download page](http://www.oracle.com/technetwork/java/javase/documentation/jdk8-doc-downloads-2133158.html)


