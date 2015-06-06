@@[Home](Home.md) -> [ProjectTasks](ProjectTasks.md)

---


# Construction by Direct Definition #

Define networks using hierarchy:

  * **components**
    * area A
      * region 1
      * region 2
      * region 3
      * region 4
    * area B
      * region 1
      * region 2
      * region 3
  * **connectivity types**
    * type 1
    * type 2
  * **circuits**
    * circuit A
      * area A region 1 -> area B region 3 with connectivity type 1
      * area A region 2 -> area A region 4 with connectivity type 1
      * area B region 3 -> area A region 1 with connectivity type 2