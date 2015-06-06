@@[Home](Home.md) -> [DevelopmentEnvironment](DevelopmentEnvironment.md) -> [Sources](Sources.md)

---


## Repository Contents ##

googlecode repository consists of:

  * codebase of high level architecture (HLA) version branches ($HOME/trunk\_HLAv2, $HOME/trunk\_HLAv3)
  * external code used with related materials - their headers and built libs are commited to trunk\_HLAv3/library and used from there; if something should be changed in externals - you need to update externals, make build there, and commit resulting library to current HLA branch ($HOME/externals)
  * research area - place to commit various articles and documents, arranging them in a systematic manner ($HOME/research)
  * storage of diagrams and pictures copied from varied sources to make it constantly available, as well as own aHuman content created manually or generated using graphviz ($HOME/images)

## Build ##

  * primary development area is aHuman solution ($HOME/trunk\_HLAv3/human.sln) which includes all active projects
  * not all dependencies are included into project settings, so sequence to build is:
```
1. build platform project (general functions and services)
2. build mind project (mind engine)
3. build ahuman project (for aHuman target)
4. build tools project (which is set of tiny programs)
Includes console client which is able to connect 
to running target process and execute specific command
```